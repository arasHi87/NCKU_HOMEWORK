#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// AVL structure
struct avl {
    struct avl* left;
    struct avl* right;
    int data, height;
};
typedef struct avl* AVL;

int max(int, int);
int height(AVL);
AVL newNode(int);
AVL rightRotate(AVL);
AVL leftRotate(AVL);
int balance(AVL);
AVL insert(AVL, int);
void findKey(AVL, int);
AVL updateAVL(AVL);
void updateHeight(AVL);
AVL deleteAVL(AVL, int);
void getF(AVL, int);

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(AVL node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

AVL newNode(int data)
{
    AVL node = (AVL)malloc(sizeof(struct avl));
    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

AVL rightRotate(AVL node)
{
    AVL S = node->left;
    AVL T = S->right;
    // start rotate
    S->right = node;
    node->left = T;
    // new height
    node->height = max(height(node->left), height(node->right)) + 1;
    S->height = max(height(S->left), height(S->right)) + 1;
    // S is new root
    return S;
}

AVL leftRotate(AVL node)
{
    AVL S = node->right;
    AVL T = S->left;
    // start rotate
    S->left = node;
    node->right = T;
    // new height
    node->height = max(height(node->left), height(node->right)) + 1;
    S->height = max(height(S->left), height(S->right)) + 1;

    return S;
}

int balance(AVL node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

AVL insert(AVL node, int data)
{
    if (node == NULL)
        return newNode(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // no same data
        return node;
    node->height = max(height(node->left), height(node->right)) + 1;
    int BT = balance(node);
    // LL
    if (BT > 1 && data < node->left->data)
        return rightRotate(node);
    // RR
    if (BT < -1 && data > node->right->data)
        return leftRotate(node);
    // LR
    if (BT > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL
    if (BT < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void findKey(AVL node, int key)
{
    AVL temp = node;
    while (temp != NULL && temp->data != key) {
        if (temp->data > key)
            temp = temp->left;
        else if (temp->data < key)
            temp = temp->right;
    }
    if (temp == NULL)
        printf("Not exist\n");
    else {
        printf("exist\n");
        return;
    }
}

AVL updateAVL(AVL node)
{
    int BT = balance(node);
    if (BT > 1) {
        // LL
        if (node->left && node->left->left)
            return rightRotate(node);
        // LR
        else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    } else if (BT < -1) {
        // RR
        if (node->right && node->right->right)
            return leftRotate(node);
        // RL
        else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    // safe
    return node;
}

void updateHeight(AVL node)
{
    if (node == NULL)
        return;
    node->height = max(height(node->left), height(node->right)) + 1;
}

AVL deleteAVL(AVL node, int key)
{
    // nothing
    if (node == NULL)
        return node;
    if (key < node->data)
        node->left = deleteAVL(node->left, key);
    else if (key > node->data)
        node->right = deleteAVL(node->right, key);
    else if (key == node->data) {
        // one child or no child case
        if (node->left == NULL) {
            AVL temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            AVL temp = node->left;
            free(node);
            return temp;
        } else {
            // two children case
            AVL temp = node;
            while (temp && temp->left)
                temp = temp->left;
            node->data = temp->data;
            node->right = deleteAVL(node->right, temp->data);
        }
    } else
        return node;
    updateHeight(node);
    node = updateAVL(node);
    return node;
}

void getF(AVL node, int key)
{
    AVL temp = node;
    while (temp != NULL) {
        if (temp->data == key)
            break;
        else if (temp->data > key)
            temp = temp->left;
        else if (temp->data < key)
            temp = temp->right;
    }
    if (temp == NULL)
        printf("Not found\n");
    else
        printf("%d\n", balance(temp));
}

// int main()
// {
//     AVL root = NULL;
//     // 0->insert 1->delete 2->search
//     int n, t;
//     scanf("%d", &n);
//     for (int i = 1, x; i <= n; i++)
//         scanf("%d", &x), insert(root, x);
//     scanf("%d", &t);
//     for (int i = 1, x; i <= t; i++) {
//         scanf("%d", &x);
//         if (x == 0)
//             scanf("%d", &x), insert(root, x);
//         if (x == 1)
//             scanf("%d", &x), deleteAVL(root, x);
//         if (x == 2)
//             scanf("%d", &x), findKey(root, x);
//     }
// }