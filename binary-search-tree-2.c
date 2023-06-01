/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {   //typedef형 구조체 node
	int key;           //int형 변수 key 선언
	struct node *left; //struct node *left, 왼쪽 자식 노드를 가리킴
	struct node *right; //struct node *right, 오른쪽 자식 노드
} Node; //구조체 이름은 Node

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE]; 
int top = -1; //정수형 변수 top -1로 초기화

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1; //정수형 변수 front 선언, -1로 초기화
int rear = -1; //정수형 변수 rear 선언, -1로 초기화



int initializeBST(Node** h); //int형을 반환하는 함수 initializeBST(Node** h) 정의
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */
Node* pop();              //Node *pop() 함수 정의
void push(Node* aNode); //void형 함수 push(Node* aNode) 정의
Node* deQueue();       //Node *deQueue() 함수 정의
void enQueue(Node* aNode);//void형 enQueue(Node *aNode) 정의

/* you may add your own defined functions if necessary */


void printStack();//void형 함수 printStack() 정의



int main()
{
	char command; //char형 변수 command 선언
	int key; //int형 변수 key 선언
	Node* head = NULL; //Node *head 선언, NULL로 초기화

    printf("[----- [Kim ah hyeon] [2022041010] -----\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n"); //---------------------------------------------------------------- 출력
		printf("                   Binary Search Tree #2                        \n"); //                   Binary Search Tree #2                         출력
		printf("----------------------------------------------------------------\n"); //---------------------------------------------------------------- 출력
		printf(" Initialize BST       = z                                       \n"); // Initialize BST       = z                                        출력
		printf(" Insert Node          = i      Delete Node                  = d \n"); // Insert Node          = i      Delete Node                  = d  출력
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n"); // Recursive Inorder    = r      Iterative Inorder (Stack)    = t  출력
		printf(" Level Order (Queue)  = l      Quit                         = q \n"); // Level Order (Queue)  = l      Quit                         = q  출력
		printf("----------------------------------------------------------------\n"); //---------------------------------------------------------------- 출력

		printf("Command = "); //Command =  출력
		scanf(" %c", &command); //command를 입력받음

		switch(command) { //제어식이 command
		case 'z': case 'Z': //command가 'z'이거나 'Z'일 경우
			initializeBST(&head); //함수 initializeBST(&head) 호출
			break;          //break문
		case 'q': case 'Q': //command가 'q'이거나 'Q'일 경우
			freeBST(head); //함수 freeBST(head) 호출
			break;          //break문
		case 'i': case 'I': //command가 'i'이거나 'I'일 경우
			printf("Your Key = "); //Your Key =  출력
			scanf("%d", &key); //key 값을 입력받음
			insert(head, key); //함수 insert(head, key) 호출
			break;          //break문
		case 'd': case 'D': //command가 'd'이거나 'D'일 경우
			printf("Your Key = "); //Your Key =  출력
			scanf("%d", &key); //key 값을 입력받음
			deleteNode(head, key); //함수 deleteNode(head, key) 호출
			break;          //break문

		case 'r': case 'R': //command가 'r'이거나 'R'일 경우
			recursiveInorder(head->left);
			break;          //break문
		case 't': case 'T': //command가 't'이거나 'T'일 경우
			iterativeInorder(head->left);
			break;          //break문

		case 'l': case 'L': //command가 'l'이거나 'L'일 경우
			levelOrder(head->left); //함수 levelOrder(head->left) 호출
			break;          //break문

		case 'p': case 'P': //command가 'p'이거나 'P'일 경우
			printStack(); //함수 printStack() 호출
			break;          //break문

		default:           //위의 경우가 모두 아닐 경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //       >>>>>   Concentration!!   <<<<<      출력
			break;          //break문
		}

	}while(command != 'q' && command != 'Q'); //command가 'q'가 아니고 'Q'가 아니면 계속 실행

	return 1; //1 값을 반환
}

int initializeBST(Node** h) { //int형 initializeBST(Node ** h)

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //*h가 NULL이 아니면
		freeBST(*h);//함수 freeBST(*h) 호출

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //*h의 메모리 주소에 동적할당
	(*h)->left = NULL;	/* root */ //*h->left를 NULL로 초기화
	(*h)->right = *h;             //*h->right에 *h 대입
	(*h)->key = -9999; //*h->key에 -9999 대입

	top = -1; //top에 -1 대입

	front = rear = -1;//front에 -1 대입, rear에 -1 대입

	return 1; //1 값 반환
}



void recursiveInorder(Node* ptr) //void형 recursiveInorder(Node* ptr)
{
	if(ptr) { //ptr이 NULL이 아니라면
		recursiveInorder(ptr->left);//recursiveInorder(ptr->left) 함수 호출
		printf(" [%d] ", ptr->key);//ptr->key 값 출력
		recursiveInorder(ptr->right);//recursiveInorder(ptr->right) 함수 호출
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) //void형 iterativeInorder(Node* node), 중위순회
{
	for(;;) //무한 반복문 실행
	{
		for(; node; node = node->left) //
			push(node); //push(node) 함수 호출
		node = pop(); //node에 pop() 값 대입

		if(!node) break;  //node가 NULL이면 break문
		printf(" [%d] ", node->key); //node->key 값 출력

		node = node->right; //node에 node->right 값 대입
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) //void형 levelOrder(Node* ptr)
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */ //ptr이 NULL이면 0 값 반환

	enQueue(ptr); //enQueue(ptr) 함수 호출

	for(;;)     //무한 반복문 실행
	{
		ptr = deQueue(); //ptr에 deQueue() 대입
		if(ptr) { //ptr이 NULL이 아니면
			printf(" [%d] ", ptr->key); //ptr->key 값 출력

			if(ptr->left) //ptr->key가 NULL이 아니면
				enQueue(ptr->left); //enQueue(ptr->left) 함수 호출
			if(ptr->right) //ptr->key가 NULL이 아니면
				enQueue(ptr->right); //enQueue(ptr->right) 함수 호출
		}
		else //ptr이 NULL이면
			break; //break문

	}

}


int insert(Node* head, int key) //int형 insert(Noden* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //Node *newNode 메모리 주소 동적 할당
	newNode->key = key; //newNode->key에 key 대입
	newNode->left = NULL; //newNode->left를 NULL로 초기화
	newNode->right = NULL;//newNode->right = NULL

	if (head->left == NULL) { //head->left가 NULL이면
		head->left = newNode;//head->left에 newNode 대입
		return 1; //1 값 반환
	}

	/* head->left is the root */
	Node* ptr = head->left; //Node *ptr에 head->left 값 대입

	Node* parentNode = NULL; //Node *parentNode를 NULL로 초기화
	while(ptr != NULL) { //ptr이 NULL이 아니면

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //ptr->key이 key라면 1 값 반환

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //parentNode에 ptr 값 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr->key이 key보다 작으면
			ptr = ptr->right; //ptr에 ptr->right 값 대입
		else //ptr->key이 key보다 같거나 크면
			ptr = ptr->left; //ptr에 ptr->left 값 대입
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) //parentNode->key가 key보다 크면
		parentNode->left = newNode; //parentNode->left에 newNode 값 대입
	else                            // //parentNode->key가 key보다 같거나 작으면
		parentNode->right = newNode;//parentNode->right에 newNode 값 대입
	return 1; //1 값 반환
}


int deleteNode(Node* head, int key) //int형 deleteNode(Node* head, int key)
{
	if (head == NULL) {                    //head가 NULL이면
		printf("\n Nothing to delete!!\n"); // Nothing to delete!! 출력
		return -1;
	}

	if (head->left == NULL) { //head->left가 NULL이면
		printf("\n Nothing to delete!!\n");// Nothing to delete!! 출력
		return -1; //-1 값 반환
	}

	/* head->left is the root */
	Node* root = head->left; //Node* root에 head->left 값 대입



	Node* parent = NULL; //Node* parent를 NULL로 초기화
	Node* ptr = root; //Node* ptr에 root 값 대입

	while((ptr != NULL)&&(ptr->key != key)) { //ptr이 NULL이 아니고 ptr->key가 key 값이 아니면
		if(ptr->key != key) { //ptr->key가 key가 아니면

			parent = ptr;	/* save the parent */ //parent에 ptr 대입

			if(ptr->key > key) //ptr->key가 key보다 크면
				ptr = ptr->left;//ptr에 ptr->left 값 대입
			else //ptr->key가 key보다 작거나 같으면
				ptr = ptr->right; //ptr에 ptr->right 값 대입
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) //ptr이 NULL이면
	{
		printf("No node for key [%d]\n ", key);//No node for key  출력
		return -1; //-1 값 반환
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL) //ptr->left가 NULL이고 ptr->right가 NULL이면
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */ //parent가 NULL이 아니면
			if(parent->left == ptr) //parent->left가 ptr이면
				parent->left = NULL; //parent->left를 NULL로 초기화
			else //parent->left가 ptr이 아니면
				parent->right = NULL;//parent->right를 NULL로 초기화
		} else { //parent가 NULL이면
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL; //head->left를 NULL로 초기화

		}

		free(ptr); //ptr의 메모리 주소 해제
		return 1; //1 값 반환
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) //ptr->left가 NULL이거나 ptr->right가 NULL이면
	{
		Node* child; //Node *child 정의
		if (ptr->left != NULL) //ptr->left가 NULL이 아니면
			child = ptr->left; //child에 ptr->left 값 대입
		else                   //ptr->left가 NULL이면
			child = ptr->right;//child에 ptr->right 값 대입

		if(parent != NULL) //parent가 NULL이 아니면
		{
			if(parent->left == ptr) //parent->left가 ptr이면
				parent->left = child;//parent->left에 child 값 대입
			else                     //parent->left가 ptr이 아니면
				parent->right = child;//parent->right에 child 값 대입
		} else { //parent가 NULL이면
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;//root에 child 값 대입
		}

		free(ptr); //ptr의 메모리 주소 해제
		return 1; //1 값 반환
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate; //Node *candidate 선언
	parent = ptr;   //parent에 ptr 값 대입


	candidate = ptr->right; //candidate에 ptr->right 값 대입

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL) //candidate->left가 NULL이 아니면
	{
		parent = candidate;        //parent에 candidate 값 대입
		candidate = candidate->left;//candidate에 candidate->left 값 대입
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) //parent->right가 candidate이면
		parent->right = candidate->right; //parent->right에 candidate->right 값 대입
	else                                //parent->right가 candidate이 아니면
		parent->left = candidate->right;//parent->right에 candidate->right 값 대입

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; //ptr->key에 candidate->key 값 대입

	free(candidate); //candidate의 메모리 주소 해제
	return 1;//1 값 반환
}


void freeNode(Node* ptr) //void형 freeNode(Node* ptr)
{
	if(ptr) { //ptr이 NULL이 아니면
		freeNode(ptr->left);//함수 freeNode(ptr->left) 호출
		freeNode(ptr->right);//함수 freeNode(ptr->right) 호출
		free(ptr);//ptr의 메모리 주소 해제
	}
}

int freeBST(Node* head) //int형 freeBST(Node* head)
{

	if(head->left == head) //head->left가 head이면
	{
		free(head); //head의 메모리 주소 해제
		return 1; //1 값 반환
	}

	Node* p = head->left; //Node *p에 head->left 값 대입

	freeNode(p); //함수 freeNode(p) 호출

	free(head); //head의 메모리 주소 해제
	return 1; //1 값 반환
}



Node* pop() //
{
	if (top < 0) return NULL; //top이 0보다 작으면 NULL 값 반환
	return stack[top--]; //stack[top--] 값 반환
}

void push(Node* aNode) //void형 push(Node* aNode)
{
	stack[++top] = aNode; //stack[++top]에 aNode 대입
}


void printStack() //void형 printStack()
{
	int i = 0; //정수형 변수 i 선언, 0으로 초기화
	printf("--- stack ---\n"); //--- stack --- 출력
	while(i <= top) //i가 top보다 같거나 작으면
	{
		printf("stack[%d] = %d\n", i, stack[i]->key); //stack[%d] =  출력
	}
}


Node* deQueue() //Node *deQueue
{
	if (front == rear) { //front가 rear라면
		// printf("\n....Now Queue is empty!!\n" ); //....Now Queue is empty!! 출력
		return NULL; //NULL 값 반환
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //front에 (front+1)을 MAX_QUEUE_SIZE로 나눈 나머지 값 대입
	return queue[front]; //queue[front] 값 대입

}

void enQueue(Node* aNode) //void형 enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;//rear에 (rear+1)을 MAX_QUEUE_SIZE로 나눈 나머지 값 대입
	if (front == rear) {//front가 rear라면
		// printf("\n....Now Queue is full!!\n");
		return; //0 값 반환
	}

	queue[rear] = aNode; //queue[rear]에 aNode 값 대입
}