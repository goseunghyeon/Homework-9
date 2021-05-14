/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do {
		printf("[----- [고승현] [2016039086] -----]\n");
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);
	

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}


/*중위순회를 구현*/
void inorderTraversal(Node* ptr)
{
	if (ptr != NULL) {
		inorderTraversal(ptr->left);
		printf("%d ", ptr->key);
		inorderTraversal(ptr->right);
	}
}
/*전위순회 구현*/
void preorderTraversal(Node* ptr)
{
	if (ptr != NULL) {
		printf("%d ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}
/*후위순화 구현*/
void postorderTraversal(Node* ptr)
{
	if (ptr != NULL) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("%d ", ptr->key);
	}
}

/*새로운 노드를 삽입하는 함수로 루트 노드부터 해당 키값을
비교하면서 해당 노드의 키값이 들어갈 위치를 찾고
부모노드와 연결해준다*/
int insert(Node* head, int key)
{
	Node* temp;
	Node* select = head;
	if (head == NULL)
		return 0;
	if (select->left == NULL) {
		temp = (Node*)malloc(sizeof(Node));
		temp->right = NULL;
		temp->left = NULL;
		temp->key = key;
		select->left = temp;
		return 0;
	}
	select = select->left;
	temp = (Node*)malloc(sizeof(Node));
	temp->right = NULL;
	temp->left = NULL;
	temp->key = key;
	while (select != NULL) {
		if (key < select->key) {
			if (select->left == NULL) {
				select->left = temp;
				break;
			}
			select = select->left;
		}
		else {
			if (select->right == NULL) {
				select->right = temp;
				break;
			}
			select = select->right;
		}
	}
	return 0;
}
/*리프노드를 삭제하는 함수로 매개변수로 받은 키값과
반복을 이용해서 비교하면서 일치하는 키값을 찾고 해당노드가
리프노드일 경우 삭제한다*/
int deleteLeafNode(Node* head, int key)
{
	Node* preview;
	Node* select = head->left;
	preview = head;
	if (select == NULL) {
		return 0;
	}
	while (select != NULL) {
		if (select->key == key) {
			if (select->left == NULL && select->right == NULL) {
				printf("key:%d add: %u\n", key, select);
				if (preview->left == select)
					preview->left = NULL;
				else
					preview->right = NULL;
				free(select);
				return 0;
			}
			else {
				printf("not leaf node\n");
				return 0;
			}

		}
		else {
			if (key < select->key) {
				preview = select;
				select = select->left;
			}
			else {
				preview = select;
				select = select->right;
			}
		}
		if (select == NULL)
			printf("cannot find key:%d\n", key);
	}
	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	Node* select=NULL;
	if (ptr) {
		if (ptr->key == key) {
			return ptr;
		}
		select = searchRecursive(ptr->left,key);
		if(select==NULL)
		select = searchRecursive(ptr->right, key);
			
	}

	return select;
}

Node* searchIterative(Node* head, int key)
{
    Node* select = head->left;
	while (select!=NULL) {
		if (key > select->key) {
			select = select->right;
		}
		else if (key < select->key) {
			select = select->left;
		}
		else {
			return select;
		}
	}
	return NULL;
}

/*헤드의 주소를 받아서 순회를 이용해서 노드들을 해제해주고
마지막에는 헤드노드를 판별해서 헤드노드까지 해제해준다*/
int freeBST(Node* head)
{
	if (head == NULL)
		return 0;
	if (head == head->right&&head->left==NULL) {
		free(head);
		return 0;
	}
	if (head) {
		freeBST(head->left);
		if (head->right == head) {
			free(head);
			return 0;
		}
		freeBST(head->right);
		free(head);
	}


	return 0;
}
