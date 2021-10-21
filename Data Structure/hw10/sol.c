#include <stdio.h>
#include <stdlib.h>
const int maxN = 1e3 + 10;

typedef struct node {
    int val;
    struct node *left, *right;
} Node;

Node* root;
int n, arr[maxN];

Node* new_node(int x)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = x;
    node->left = node->right = NULL;
    return node;
}

void build()
{
    int top = 0;
    Node *stk[maxN], *cur = (Node*)malloc(sizeof(Node));

    root = new_node(arr[1]), stk[++top] = root;
    for (int i = 2; i <= n; i++) {
        Node* new = new_node(arr[i]);
        cur = stk[top];
        while (cur->left && cur->right)
            cur = stk[top--];
        if (!cur->left) {
            // printf("%d left is %d\n", cur->val, arr[i]);
            cur->left = new_node(arr[i]);
            cur = cur->left;
        } else {
            // printf("%d right is %d\n", cur->val, arr[i]);
            cur->right = new_node(arr[i]);
            cur = cur->right;
        }
        if (arr[i] != -1)
            stk[++top] = cur;
    }
}

void pre()
{
    int top = 0;
    Node *stk[maxN], *cur = (Node*)malloc(sizeof(Node));

    stk[++top] = root;
    while (top) {
        cur = stk[top--];
        printf("%d ", cur->val);

        if (cur->right->val != -1)
            stk[++top] = cur->right;
        if (cur->left->val != -1)
            stk[++top] = cur->left;
    }
    puts("");
}

void in()
{
    int top = 0;
    Node *stk[maxN], *cur = root;

    while (cur->val != -1 || top) {
        while (cur->val != -1)
            stk[++top] = cur, cur = cur->left;
        cur = stk[top--];
        printf("%d ", cur->val);
        cur = cur->right;
    }
}

void swap()
{
    int top = 0;
    Node *stk[maxN], *cur = (Node*)malloc(sizeof(Node)), *tmp = (Node*)malloc(sizeof(Node));

    stk[++top] = root;
    while (top) {
        cur = stk[top--];
        *tmp = *cur->left;
        *cur->left = *cur->right;
        *cur->right = *tmp;

        if (cur->right->val != -1)
            stk[++top] = cur->right;
        if (cur->left->val != -1)
            stk[++top] = cur->left;
    }
}

int main()
{
    scanf("%d", &n), n = 1;
    while (~scanf("%d", arr + n))
        n++;
    n -= 1;
    build(), swap(), pre(), in();
}