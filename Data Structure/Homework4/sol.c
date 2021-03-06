#include <stdio.h>
#include <stdlib.h>
#define maxN 110

typedef struct BSTNode {
	int val;
	struct BSTNode* left;
	struct BSTNode* right;
	struct BSTNode* parent;
} bstNode;

typedef struct QNode {
	bstNode* val;
	struct QNode* next;
} qNode;

typedef struct {
	qNode* front;
	qNode* rear;
} Queue;

char ch;
int n, num=0, flag=1;

void BSTInsertNode(bstNode* root, int val) {
	bstNode* cur=root;
	bstNode* tmp=NULL;
	bstNode* node=(bstNode*)malloc(sizeof(bstNode));

	node->val=val;

	while (cur!=NULL) {
		tmp=cur;
		cur=(node->val<cur->val ? cur->left : cur->right);
	}

	node->parent=tmp;

	node->val<tmp->val ? (tmp->left=node) : (tmp->right=node);
}

bstNode* BSTMinNode(bstNode* root) {
	if (root->left) return root->left;
	return root;
}

bstNode* BSTDeleteNode(bstNode* root, int val) {
	if (!root) return root;
	else if (val>root->val) root->right=BSTDeleteNode(root->right, val);
	else if (val<root->val) root->left=BSTDeleteNode(root->left, val);
	else {
		int tar;
		bstNode* tmp;

		if (root->left) {
			for (tmp=root->left;tmp->right;tmp=tmp->right);
			
			tar=tmp->val, tmp->val=root->val, root->val=tar;
			root->left=BSTDeleteNode(root->left, tmp->val);
		} else if (root->right) {
			for (tmp=root->right;tmp->left;tmp=tmp->left);
			
			tar=tmp->val, tmp->val=root->val, root->val=tar;
			root->right=BSTDeleteNode(root->right, tmp->val);
		} else {
			free(root);

			return NULL;
		}
	}

	return root;
}

void InQueue(Queue* q, bstNode* val) {
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

bstNode* DeQueue(Queue* q) {
	qNode* node=(qNode*)malloc(sizeof(qNode));
	bstNode* val=(bstNode*)malloc(sizeof(bstNode));

	node=q->front;
	q->front=q->front->next;
	val=node->val;

	free(node);

	return val;
}

int EmptyQueue(Queue* q) { return (q->front==NULL ? 1 : 0); }

void PrintBST(bstNode* root) {
	Queue* q=(Queue*)malloc(sizeof(Queue));
	bstNode* node=(bstNode*)malloc(sizeof(bstNode));

	q->front=NULL;
	q->rear=NULL;
	
	printf("%d", root->val);
	
	if (root->left) InQueue(q, root->left);
	if (root->right) InQueue(q, root->right);
	
	while (!EmptyQueue(q)) {
		node=DeQueue(q);

		printf("\n%d", node->val);

		if (node->left) InQueue(q, node->left);
		if (node->right) InQueue(q, node->right);
	}
}

int main() {
	bstNode* root=(bstNode*)malloc(sizeof(bstNode));

	root->val=-1;
	root->left=NULL;
	root->right=NULL;
	
	while (~scanf("%c", &ch)) {
		if ((ch==' ' || ch=='\n') && flag) {
			if (ch=='\n') flag=0;
			
			~root->val ? BSTInsertNode(root, num) : (root->val=num);
			
			num=0;
		}
		else if ((ch==' ' || ch=='\n') && !flag) BSTDeleteNode(root, num), num=0;
		else num*=10, num+=(ch-'0');
	}

	PrintBST(root);
}
