#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val, npl;
    struct node *left, *right;
} Node;

Node* merge(Node*, Node*);
Node* _merge(Node*, Node*);

Node* init(int x)
{
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->val = x;
    tmp->npl = 0;
    tmp->left = tmp->right = NULL;
    return tmp;
}

int dis(Node* x) { return x ? x->npl : -1; }

void swap(Node* x, Node* y)
{
    Node tmp = *x;
    *x = *y;
    *y = tmp;
}

Node* _merge(Node* x, Node* y)
{
    if (x->left == NULL)
        x->left = y;
    else {
        x->right = merge(x->right, y);
        if (x->left->npl < x->right->npl)
            swap(x->left, x->right);
        x->npl = x->right->npl + 1;
    }
    return x;
}

Node* merge(Node* x, Node* y)
{
    if (x == NULL)
        return y;
    if (y == NULL)
        return x;
    return (x->val < y->val ? _merge(x, y) : _merge(y, x));
}

Node* insert(Node* h, int x)
{
    Node* tmp = init(x);
    h = merge(h, tmp);
    return h;
}

Node* destroy(Node* h)
{
    // printf("%d ", h->val);
    return merge(h->left, h->right);
}

int n, t;
Node* leftist;

int main()
{
    // x = 0 -> destroy
    // x = 1 -> insert
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &t), leftist = insert(leftist, t);
    scanf("%d", &t);
    for (int i = 1, x; i <= t; i++) {
        scanf("%d", &x);
        if (x)
            scanf("%d", &x), leftist = insert(leftist, x);
        else
            leftist = destroy(leftist);
    }
}