#include <stdio.h>
#include <stdlib.h>
#define maxN 100007

typedef struct node {
    int val, rtag, ltag;
    struct node *left, *right;
} Node;

int n, r;
char str[20];
Node *tree, *pre;

Node* init(int x)
{
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->val = x;
    tmp->ltag = tmp->rtag = 0;
    tmp->left = tmp->right = NULL;
    return tmp;
}

int insert(Node* root, int x, int y, int flag) // 0 ->left 1->right
{
    if (root->val == x) {
        if (flag)
            root->right = init(y);
        else
            root->left = init(y);
        return 1;
    } else {
        if (root->left && insert(root->left, x, y, flag))
            return 1;
        if (root->right && insert(root->right, x, y, flag))
            return 1;
    }
    return 0;
}

void thread(Node* root)
{
    if (root) {
        thread(root->left);
        if (!root->left) {
            root->ltag = 1;
            root->left = pre;
        }
        if (pre && !pre->right) {
            pre->rtag = 1;
            pre->right = root;
        }
        pre = root, thread(root->right);
    }
}

void inorder(Node* root)
{
    Node* cur = root;
    while (cur) {
        while (!cur->ltag)
            cur = cur->left;
        printf("%d ", cur->val);
        while (cur && cur->rtag)
            cur = cur->right, printf("%d ", cur->val);
        cur = cur->right;
    }
    puts("");
}

int main()
{
    scanf("%d%d", &n, &r), tree = init(r);
    for (int i = 1, x, y; i <= n; i++)
        scanf("%d%s%d", &x, str, &y), insert(tree, x, y, str[0] == 'r');
    thread(tree), inorder(tree);
}