#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// RBT structure
struct rbt {
    struct rbt* left;
    struct rbt* right;
    struct rbt* parent;
    int color, data;
};
typedef struct rbt* RBT;
RBT root = NULL;
RBT neel;
RBT newTree(int);
void rotateRight(RBT);
void rotateLeft(RBT);
void toInsert(int);
void insertFix(RBT);
RBT search(int);
RBT successor(RBT);
RBT leftmost(RBT);
void deleteRBT(int);
void deleteFix(RBT);

RBT newTree(int data)
{
    RBT node = (RBT)malloc(sizeof(struct rbt));
    node->data = data;
    node->color = 0; // means red
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

void rotateRight(RBT node)
{
    RBT left = node->left;
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

void rotateLeft(RBT node)
{
    RBT right = node->right;
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

void toInsert(int data)
{
    RBT x = root;
    RBT y = neel;
    RBT node = newTree(data);
    while (x != neel) {
        y = x;
        if (node->data < x->data)
            x = x->left;
        else if (node->data > x->data)
            x = x->right;
        else
            return;
    }
    node->parent = y;
    if (y == neel)
        root = node;
    else if (node->data < y->data)
        y->left = node;
    else
        y->right = node;
    node->left = neel;
    node->right = neel;
    insertFix(node);
    neel->parent = root;
}

void insertFix(RBT currentNode)
{

    while (currentNode->parent->color == 0) {
        // parent is grand->left
        if (currentNode->parent == currentNode->parent->parent->left) {
            RBT uncle = currentNode->parent->parent->right;
            // case1 : uncle is red
            if (uncle->color == 0) {
                currentNode->parent->color = 1;
                uncle->color = 1;
                currentNode->parent->parent->color = 0;
                currentNode = currentNode->parent->parent;
            }
            // case2 & 3 : uncle is black
            else {
                if (currentNode == currentNode->parent->right) {
                    currentNode = currentNode->parent;
                    rotateLeft(currentNode);
                }
                currentNode->parent->color = 1;
                currentNode->parent->parent->color = 0;
                rotateRight(currentNode->parent->parent);
            }
        }
        // parent is grand->right
        else {
            RBT uncle = currentNode->parent->parent->left;
            // case 1 : uncle is red
            if (uncle->color == 0) {
                currentNode->parent->color = 1;
                uncle->color = 1;
                currentNode->parent->parent->color = 0;
                currentNode = currentNode->parent->parent;
            }
            // case 2 & 3 : same as above
            else {
                if (currentNode == currentNode->parent->left) {
                    currentNode = currentNode->parent;
                    rotateRight(currentNode);
                }
                currentNode->parent->color = 1;
                currentNode->parent->parent->color = 0;
                rotateLeft(currentNode->parent->parent);
            }
        }
    }
    root->color = 1; // make sure root is black
}

RBT search(int key)
{
    RBT current = root;
    while (current != neel && current->data != key) {
        if (current->data > key)
            current = current->left;
        else
            current = current->right;
    }
    if (current == neel)
        return NULL;
    else
        return current;
}

RBT leftmost(RBT current)
{
    while (current->left != neel)
        current = current->left;
    return current;
}

RBT successor(RBT current)
{
    if (current->right != neel)
        return leftmost(current->right);
    RBT current_pt = current->parent;
    while (current_pt != neel && current == current_pt->right) {
        current = current_pt;
        current_pt = current_pt->parent;
    }
    return current_pt;
}

void deleteRBT(int key)
{
    RBT toDelete = search(key);
    if (toDelete == NULL)
        return;
    RBT x, y;
    if (toDelete->left == neel || toDelete->right == neel)
        y = toDelete;
    else
        y = successor(toDelete);
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
        toDelete->data = y->data;

    if (y->color == 1)
        deleteFix(x);
    neel->parent = root;
}

void deleteFix(RBT current)
{
    while (current != root && current->color == 1) {
        if (current == current->parent->left) {
            RBT sibling = current->parent->right;
            if (sibling->color == 0) {
                sibling->color = 1;
                current->parent->color = 0;
                rotateLeft(current->parent);
                sibling = current->parent->right;
            }
            if (sibling->left->color == 1 && sibling->right->color == 1) {
                sibling->color = 0;
                current = current->parent;
            } else {
                if (sibling->right->color == 1) {
                    sibling->left->color = 1;
                    sibling->color = 0;
                    rotateRight(sibling);
                    sibling = current->parent->right;
                }
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->right->color = 1;
                rotateLeft(current->parent);
                current = root;
            }
        } else {
            RBT sibling = current->parent->left;
            if (sibling->color == 0) {
                sibling->color = 1;
                current->parent->color = 0;
                rotateRight(current->parent);
                sibling = current->parent->left;
            }
            if (sibling->left->color == 1 && sibling->right->color == 1) {
                sibling->color = 0;
                current = current->parent;
            } else {
                if (sibling->left->color == 1) {
                    sibling->right->color = 1;
                    sibling->color = 0;
                    rotateLeft(sibling);
                    sibling = current->parent->left;
                }
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->left->color = 1;
                rotateRight(current->parent);
                current = root;
            }
        }
    }
    current->color = 1;
}

// int main()
// {
//     neel = (RBT)malloc(sizeof(struct rbt));
//     neel->color = 1;
//     neel->left = NULL;
//     neel->right = NULL;
//     neel->parent = NULL;
//     root = neel;
//     root->parent = neel;
//     // 0->insert 1->delete 2->search
//     int n, t;
//     scanf("%d", &n);
//     for (int i = 1, x; i <= n; i++)
//         scanf("%d", &x), toInsert(x);
//     scanf("%d", &t);
//     for (int i = 1, x; i <= t; i++) {
//         scanf("%d", &x);
//         if (x == 0)
//             scanf("%d", &x), toInsert(x);
//         if (x == 1)
//             scanf("%d", &x), deleteRBT(x);
//         if (x == 2)
//             scanf("%d", &x), search(x);
//     }
// }