#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxN 20

typedef struct Node {
	int val;
	struct Node* next;
} qNode;

typedef struct {
	qNode* front;
	qNode* rear;
} Queue;

int idx=13;
char ch[5];
char list[14][3]={"", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

Queue* CreateQueue() {
	Queue* q=(Queue*)malloc(sizeof(Queue));
	q->front=NULL;
	q->rear=NULL;

	return q;
}

void InQueue(Queue* q, int val) {
	qNode* node=(qNode*)malloc(sizeof(qNode));
	
	node->val=val;
	node->next=NULL;	

	if (q->front==NULL) {
		q->front=node;
		q->rear=node;
	} else {
		q->rear->next=node;
		q->rear=node;
	}
}

char OutQueue(Queue* q) {
	int val;
	qNode* temp=q->front;
	
	if (q->front == q->rear) q->front=q->rear=NULL;
	else q->front=q->front->next;

	val=temp->val;
	free(temp);

	return val;
}

void PrintQueue(Queue* q) {
	qNode* node=q->front;

	printf("%s", list[node->val]); node=node->next;

	while (node) {
		printf(" %s", list[node->val]);
		node=node->next;
	}
	puts("");
}

int c2i(char val[]) {
	int ret;
	
	if (!strcmp(val, "A")) ret=1;
	else if (!strcmp(val, "2")) ret=2;
	else if (!strcmp(val, "3")) ret=3;
	else if (!strcmp(val, "4")) ret=4;
	else if (!strcmp(val, "5")) ret=5;
	else if (!strcmp(val, "6")) ret=6;
	else if (!strcmp(val, "7")) ret=7;
	else if (!strcmp(val, "8")) ret=8;
	else if (!strcmp(val, "9")) ret=9;
	else if (!strcmp(val, "10")) ret=10;
	else if (!strcmp(val, "J")) ret=11;
	else if (!strcmp(val, "Q")) ret=12;
   	else ret=13;
	
	return ret;
}

int main() {
	Queue* q=CreateQueue();
	
	while (~scanf("%s", ch)) InQueue(q, c2i(ch));
	
	while (idx) {
		PrintQueue(q);
		
		int temp=OutQueue(q);

		if (idx!=temp) InQueue(q, temp);
		else idx--;
	}
}
