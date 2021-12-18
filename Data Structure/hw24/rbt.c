#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct RBTNode {
    int color, key;
    struct RBTNode *left, *right, *parent;
} RBTNode;

RBTNode *root = NULL, *neel;

RBTNode* RBTInitNode(int key)
{
    RBTNode* node = (RBTNode*)malloc(sizeof(RBTNode));
    node->key = key;
    node->color = 0;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

void RBTInitTree()
{
    neel = (RBTNode*)malloc(sizeof(RBTNode));
    neel->color = 1;
    neel->left = neel->right = neel->parent = NULL;
    root = neel, root->parent = neel;
}

void RBTRightRotate(RBTNode* node)
{
    RBTNode* left = node->left;
    node->left = left->right;
    if (left->right != neel)
        left->right->parent = node;
    left->parent = node->parent;
    if (node->parent == neel)
        root = left;
    else if (node == node->parent->left)
        node->parent->left = left;
    else
        node->parent->right = left;
    left->right = node;
    node->parent = left;
}

void RBTLeftRotate(RBTNode* node)
{
    RBTNode* right = node->right;
    node->right = right->left;
    if (right->left != neel)
        right->left->parent = node;
    right->parent = node->parent;
    if (node->parent == neel)
        root = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left = node;
    node->parent = right;
}

void RBTInsertFixup(RBTNode* currentNode)
{

    while (currentNode->parent->color == 0) {
        if (currentNode->parent == currentNode->parent->parent->left) {
            RBTNode* uncle = currentNode->parent->parent->right;
            if (uncle->color == 0) {
                currentNode->parent->color = 1;
                uncle->color = 1;
                currentNode->parent->parent->color = 0;
                currentNode = currentNode->parent->parent;
            } else {
                if (currentNode == currentNode->parent->right) {
                    currentNode = currentNode->parent;
                    RBTLeftRotate(currentNode);
                }
                currentNode->parent->color = 1;
                currentNode->parent->parent->color = 0;
                RBTRightRotate(currentNode->parent->parent);
            }
        } else {
            RBTNode* uncle = currentNode->parent->parent->left;
            if (uncle->color == 0) {
                currentNode->parent->color = 1;
                uncle->color = 1;
                currentNode->parent->parent->color = 0;
                currentNode = currentNode->parent->parent;
            } else {
                if (currentNode == currentNode->parent->left) {
                    currentNode = currentNode->parent;
                    RBTRightRotate(currentNode);
                }
                currentNode->parent->color = 1;
                currentNode->parent->parent->color = 0;
                RBTLeftRotate(currentNode->parent->parent);
            }
        }
    }
    root->color = 1;
}

void RBTInsert(int key)
{
    RBTNode* x = root;
    RBTNode* y = neel;
    RBTNode* node = RBTInitNode(key);
    while (x != neel) {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else if (node->key > x->key)
            x = x->right;
        else
            return;
    }
    node->parent = y;
    if (y == neel)
        root = node;
    else if (node->key < y->key)
        y->left = node;
    else
        y->right = node;
    node->left = neel;
    node->right = neel;
    RBTInsertFixup(node);
    neel->parent = root;
}

RBTNode* RBTSearch(int key)
{
    RBTNode* current = root;
    while (current != neel && current->key != key) {
        if (current->key > key)
            current = current->left;
        else
            current = current->right;
    }
    if (current == neel)
        return NULL;
    else
        return current;
}

RBTNode* RBTLeftmost(RBTNode* current)
{
    while (current->left != neel)
        current = current->left;
    return current;
}

RBTNode* RBTSuccessor(RBTNode* current)
{
    if (current->right != neel)
        return RBTLeftmost(current->right);
    RBTNode* current_pt = current->parent;
    while (current_pt != neel && current == current_pt->right) {
        current = current_pt;
        current_pt = current_pt->parent;
    }
    return current_pt;
}

void RBTDeleteFixup(RBTNode* current)
{
    while (current != root && current->color == 1) {
        if (current == current->parent->left) {
            RBTNode* sibling = current->parent->right;
            if (sibling->color == 0) {
                sibling->color = 1;
                current->parent->color = 0;
                RBTLeftRotate(current->parent);
                sibling = current->parent->right;
            }
            if (sibling->left->color == 1 && sibling->right->color == 1) {
                sibling->color = 0;
                current = current->parent;
            } else {
                if (sibling->right->color == 1) {
                    sibling->left->color = 1;
                    sibling->color = 0;
                    RBTRightRotate(sibling);
                    sibling = current->parent->right;
                }
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->right->color = 1;
                RBTLeftRotate(current->parent);
                current = root;
            }
        } else {
            RBTNode* sibling = current->parent->left;
            if (sibling->color == 0) {
                sibling->color = 1;
                current->parent->color = 0;
                RBTRightRotate(current->parent);
                sibling = current->parent->left;
            }
            if (sibling->left->color == 1 && sibling->right->color == 1) {
                sibling->color = 0;
                current = current->parent;
            } else {
                if (sibling->left->color == 1) {
                    sibling->right->color = 1;
                    sibling->color = 0;
                    RBTLeftRotate(sibling);
                    sibling = current->parent->left;
                }
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->left->color = 1;
                RBTRightRotate(current->parent);
                current = root;
            }
        }
    }
    current->color = 1;
}

void RBTDelete(int key)
{
    RBTNode* toDelete = RBTSearch(key);
    if (toDelete == NULL)
        return;
    RBTNode *x, *y;
    if (toDelete->left == neel || toDelete->right == neel)
        y = toDelete;
    else
        y = RBTSuccessor(toDelete);
    if (y->left != neel)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;

    if (y->parent == neel)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != toDelete)
        toDelete->key = y->key;

    if (y->color == 1)
        RBTDeleteFixup(x);
    neel->parent = root;
}

// int main()
// {
//     neel = (RBTNode*)malloc(sizeof(struct rbt));
//     neel->color = 1;
//     neel->left = NULL;
//     neel->right = NULL;
//     neel->parent = NULL;
//     root = neel;
//     root->parent = neel;
//     // 0->insert 1->delete 2->RBTSearch
//     int n, t;
//     scanf("%d", &n);
//     for (int i = 1, x; i <= n; i++)
//         scanf("%d", &x), RBTInsert(x);
//     scanf("%d", &t);
//     for (int i = 1, x; i <= t; i++) {
//         scanf("%d", &x);
//         if (x == 0)
//             scanf("%d", &x), RBTInsert(x);
//         if (x == 1)
//             scanf("%d", &x), RBTDeleteNode*(x);
//         if (x == 2)
//             scanf("%d", &x), RBTSearch(x);
//     }
// }