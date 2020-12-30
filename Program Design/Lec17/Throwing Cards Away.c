#include <stdio.h>
#include <stdlib.h>
#define type int

typedef struct Node {
    type val;
    struct Node* next;
} qNode;

typedef struct {
	qNode* front;
	qNode* rear;
} Queue;

int n, m;

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

int main() {
    Queue* q=CreateQueue();

    scanf("%d%d", &n, &m);
    
    for (int i=1;i<=n;i++)
        InQueue(q, i);
    
    for (int i=1;i<=m;i++) {
        printf("%d ", OutQueue(q));
        
        if (q->front)
            InQueue(q, OutQueue(q));
    }
}
