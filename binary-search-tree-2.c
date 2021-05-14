/*
 * Binary Search Tree #2
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

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
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
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			//printStack();
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

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	for (;;) {
		for (; node; node = node->left)
			push(node);
		node = pop();
		if (node == NULL)
			break;
		printf(" [%d] ", node->key);
		node = node->right;

	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if (ptr == NULL)
		return;
	enQueue(ptr);
	for (;;) {
		ptr = deQueue();
		if (ptr) {
			printf(" [%d] ", ptr->key);
			if (ptr->left) {
				enQueue(ptr->left);
			}
			if (ptr->right) {
				enQueue(ptr->right);
			}
		}
		else
			break;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* select = head->left;
	Node* prev = head;
	Node* now = NULL;
	Node* before = NULL;
	if (select == NULL)
		return 0;
	while (select != NULL) {
		if (select->key > key) {
			prev = select;
			select = select->left;
		}
		else if (select->key < key) {
			prev = select;
			select = select->right;
		}
		else break;
	}
	if (select == NULL) {
		printf("No such data\n");
		return 0;
	}

		if (select->left == NULL && select->right == NULL) {
			if (prev->left == select) {
				free(select);
				prev->left = NULL;
			}
			else {
				free(select);
				prev->right = NULL;
			}
		}

		else if (select->left != NULL && select->right != NULL) {
			now = select->right;
			before = now;
			while (now->left != NULL) {
				before = now;
				now = now->left;
			}
			if (now->right == NULL) {
				before->left = NULL;
				now->left = select->left;
				now->right = select->right;
				if (prev->right == select) {
					prev->right = now;
				}
				else
					prev->left = now;
				free(select);
			}
		
			else {
				before->left =now->right ;
				now->left = select->left;
				now->right = select->right;
				if (prev->right == select) {
					prev->right = now;
				}
				else
					prev->left = now;
				free(select);
			}
			if (now->right == now)
				now->right = NULL;
			if (now->left == now)
				now->left == NULL;
		}

		else {
			if (select->right != NULL) {
				if (prev->right == select) {
					prev->right = select->right;
					free(select);
				}
				else {
					prev->left = select->right;
					free(select);
				}
			}

			else {
				if (prev->right == select) {
					prev->right = select->left;
					free(select);
				}
				else {
					prev->left = select->left;
					free(select);
				}
			}
			
		}
		
}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{	
	Node* select;
	if (top >= 0) {
		select = stack[top];
		stack[top] = NULL;
		top--;
		return select;
	}
	else {
		printf("empty\n");
		return NULL;
	}
}

void push(Node* aNode)
{
	if (top < MAX_STACK_SIZE-1)
		stack[++top] = aNode;
	else {
		printf("full\n");
		return;
	}
}



Node* deQueue()
{
	Node* temp;
	int i = front;
	i = (i + 1) % MAX_QUEUE_SIZE;
	if (queue[i] == NULL) {
		printf("empty\n");
		return NULL;
	}
	front = i;
	temp = queue[front];
	queue[front] == NULL;
	return temp;
}

void enQueue(Node* aNode)
{
	int i = rear;
	i = (i+1) % MAX_QUEUE_SIZE;
	if (i == front) {
		printf("max\n");
		return;
	}
	rear = i;
	queue[rear] = aNode;
}





