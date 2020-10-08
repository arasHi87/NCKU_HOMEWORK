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

char ch[50];
int n, top=0, stack[maxN];
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
	
	while (~scanf("%s", ch)) {
		if (!strcmp(ch, "PUSH")) {
			scanf("%d%*c", &val);

			stack[++top]=val;
		}
		if (!strcmp(ch, "POP")) {
			cus=stack[top--];
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
