#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxN 25000
#define type int

typedef struct Node {
	type val;
	struct Node* next;
} qNode;

typedef struct {
	qNode* front;
	qNode* rear;
} Queue;

typedef struct {
	qNode* top;
} Stack;

char ch[50];
int n;
Queue* qList[maxN];

Queue* CreateQueue() {
	Queue* q=(Queue*)malloc(sizeof(Queue));
	q->front=NULL;
	q->rear=NULL;
	
	return q;
}

void InQueue(Queue* q, type val) {
	qNode* node=(qNode*)malloc(sizeof(qNode));

	node->val=val;
	node->next=NULL;

	if (!q->front) {
		q->front=node;
		q->rear=node;
	} else {
		q->rear->next=node;
		q->rear=node;
	}
}

type OutQueue(Queue* q) {
	type val;
	qNode* temp=q->front;

	if (q->front == q->rear) {
		q->front=NULL;
		q->rear=NULL;
	} else q->front=q->front->next;
	
	val=temp->val;
	free(temp);

	return val;
}

void InStack(Stack* s, type val) {
	qNode* node=(qNode*)malloc(sizeof(qNode));

	node->val=val;
	node->next=s->top;
	s->top=node;
}

type OutStack(Stack* s) {
	type val;
	qNode* node=s->top;
	
	val=s->top->val;
	s->top=s->top->next;
	
	free(node);

	return val;
}

void PrintQueue(Queue* q) {
	qNode* node=q->front;

	while (node) {
		printf("%d ", node->val);
		node=node->next;
	}
	puts("");
}

int main() {
	char _idx;
	int val, cus, idx;
	Queue* q=(Queue*)malloc(sizeof(Queue));
	Stack* stack=(Stack*)malloc(sizeof(Stack)); 
	
	while (~scanf("%s", ch)) {
		if (!strcmp(ch, "PUSH")) {
			scanf("%d%*c", &val);

			InStack(stack, val);
		}
		if (!strcmp(ch, "POP")) {
			cus=OutStack(stack);
		}
		if (!strcmp(ch, "ENQUEUE")) {
			scanf(" %c%*c", &_idx);

			idx=_idx-'A'+1;
			
			if (!&qList[idx]->front)
				qList[idx]=CreateQueue();

			InQueue(qList[idx], cus);
		}
		if (!strcmp(ch, "DEQUEUE")) {
			scanf(" %c%*c", &_idx);

			idx=_idx-'A'+1;

			printf("%d\n", OutQueue(qList[idx]));
		}
	}
}
