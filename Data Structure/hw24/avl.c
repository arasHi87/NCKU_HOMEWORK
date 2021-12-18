#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data, bf;
    struct Node *left, *right;
} Node;

bool balanced;

void AVLLeftRotate(Node** root, bool isInsert)
{
    Node *node = *root, *child = node->left;
    if (isInsert)
        balanced = true;

    if (child->bf == 1 || child->bf == 0) {
        node->left = child->right;
        child->right = node;
        if (child->bf == 0) {
            child->bf = -1;
            node->bf = 1;
            balanced = true;
        } else
            child->bf = node->bf = 0;
        (*root) = child;
    } else {
        Node* grand = child->right;
        child->right = grand->left;
        grand->left = child;
        node->left = grand->right;
        grand->right = node;
        switch (grand->bf) {
        case 1:
            node->bf = -1;
            child->bf = 0;
            break;
        case 0:
            node->bf = child->bf = 0;
            break;
        case -1:
            node->bf = 0;
            child->bf = 1;
            break;
        }
        *root = grand;
        (*root)->bf = 0;
    }
}

void AVLRightRotate(Node** root, bool isInsert)
{
    Node *node = *root, *child = node->right;
    if (isInsert)
        balanced = true;

    if (child->bf == -1 || child->bf == 0) {
        node->right = child->left;
        child->left = node;
        if (child->bf == 0) {
            child->bf = 1;
            node->bf = -1;
            balanced = true;
        } else
            child->bf = node->bf = 0;
        (*root) = child;
    } else {
        Node* grand = child->left;
        child->left = grand->right;
        grand->right = child;
        node->right = grand->left;
        grand->left = node;
        switch (grand->bf) {
        case 1:
            node->bf = 0;
            child->bf = -1;
            break;
        case 0:
            node->bf = child->bf = 0;
            break;
        case -1:
            node->bf = 1;
            child->bf = 0;
            break;
        }
        *root = grand;
        (*root)->bf = 0;
    }
}

void AVLInsert(Node** root, int data)
{
    if (!*root) {
        *root = (Node*)malloc(sizeof(Node));
        (*root)->left = (*root)->right = NULL;
        (*root)->bf = 0;
        (*root)->data = data;
        balanced = false;
    } else if (data < (*root)->data) {
        Node* node = *root;
        AVLInsert(&(node->left), data);
        if (!balanced)
            switch (node->bf) {
            case -1:
                node->bf = 0;
                balanced = true;
                break;
            case 0:
                node->bf = 1;
                break;
            case 1:
                AVLLeftRotate(root, true);
                break;
            }
    } else if (data > (*root)->data) {
        Node* node = *root;
        AVLInsert(&(node->right), data);
        if (!balanced)
            switch (node->bf) {
            case 1:
                node->bf = 0;
                balanced = true;
                break;
            case 0:
                node->bf = -1;
                break;
            case -1:
                AVLRightRotate(root, true);
                break;
            }
    }
}

void AVLExist(Node* root, int targ)
{
    for (Node* now = root; now; now = (targ > now->data) ? now->right : now->left)
        if (targ == now->data) {
            printf("exist\n");
            return;
        }
    printf("Not exist\n");
}

int AVLFindReplace(Node* n)
{
    Node* ans = n->left;
    while (ans->right)
        ans = ans->right;
    return ans->data;
}

void AVLDelete(Node** root, int targ)
{
    Node* node = *root;
    if (!node)
        return;
    if (node->data == targ) {
        if (!node->left || !node->right) {
            (*root) = (node->left) ? (node->left) : (node->right);
            balanced = false;
        } else {
            int new_targ = AVLFindReplace(node);
            AVLDelete(root, new_targ);
            node->data = new_targ;
        }
    } else if (targ < node->data) {
        AVLDelete(&(node->left), targ);
        if (!balanced)
            switch (node->bf) {
            case -1:
                AVLRightRotate(root, false);
                break;
            case 0:
                node->bf = -1;
                balanced = true;
                break;
            case 1:
                node->bf = 0;
                break;
            }
    } else if (targ > node->data) {
        AVLDelete(&(node->right), targ);
        if (!balanced)
            switch (node->bf) {
            case 1:
                AVLLeftRotate(root, false);
                break;
            case 0:
                node->bf = 1;
                balanced = true;
                break;
            case -1:
                node->bf = 0;
                break;
            }
    }
}

void AVLSearch(Node* root, int targ)
{
    for (Node* now = root; now; now = (targ > now->data) ? now->right : now->left)
        if (targ == now->data) {
            printf("%d\n", now->bf);
            return;
        }
    printf("Not found\n");
}