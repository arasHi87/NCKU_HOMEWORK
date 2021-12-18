#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDER 3
#define POINTERS (ORDER << 1)
#define DATA (POINTERS - 1)

typedef struct Node {
    int data[DATA], index, leaf;
    struct Node* child[POINTERS];
} Node;

typedef struct BTree {
    Node* root;
} BTree;

int size = 0, top = -1, t, x;
int stk[10000];
char opt[20];

Node* initNode()
{
    int index = 0;
    Node* new = (Node*)malloc(sizeof(Node));

    for (index = 0; index < DATA; index++)
        new->data[index] = (int)INFINITY;
    for (index = 0; index < POINTERS; index++)
        new->child[index] = NULL;
    new->index = 0;
    new->leaf = 1;
    return new;
}

BTree* initTree()
{
    BTree* root = (BTree*)malloc(sizeof(BTree));
    Node* head = initNode();
    root->root = head;
    return root;
}

int getLeftMax(Node* node)
{
    if (!node->leaf)
        return getLeftMax(node->child[node->index]);
    else
        return node->data[node->index - 1];
}

int getRightMin(Node* node)
{
    if (!node->leaf)
        return getRightMin(node->child[0]);
    else
        return node->data[0];
}

int cmp(const void* a, const void* b)
{
    int* aa = (int*)a;
    int* bb = (int*)b;
    return (*aa) - (*bb);
}

void push(int data)
{
    stk[++top] = data;
    qsort(stk, size, sizeof(int), cmp);
}

int getKth(int kth)
{
    return stk[kth - 1];
}

void spliting(int index, Node* parent, Node* child)
{

    Node* new = initNode();
    new->leaf = child->leaf;
    new->index = ORDER - 1;
    for (int i = 0; i < ORDER - 1; i++)
        new->data[i] = child->data[ORDER + i];
    if (!child->leaf) {
        for (int i = 0; i < ORDER; i++)
            new->child[i] = child->child[ORDER + i];
    }
    child->index = ORDER - 1;
    for (int i = parent->index; i >= index; i--)
        parent->child[i + 1] = parent->child[i];
    parent->child[index] = new;
    for (int i = parent->index; i >= index; i--)
        parent->data[i] = parent->data[i - 1];
    parent->data[index - 1] = child->data[ORDER - 1];
    parent->index++;
}

void insertNonFull(Node* n, int data)
{
    int index = n->index;
    if (n->leaf) {
        while (index >= 1 && data < n->data[index - 1]) {
            n->data[index] = n->data[index - 1];
            index--;
        }
        n->data[index] = data;
        n->index++;
    } else {
        while (index >= 1 && data < n->data[index - 1])
            index--;
        if (n->child[index]->index == DATA) {
            spliting(index + 1, n, n->child[index]);
            if (data > n->data[index])
                index++;
        }
        insertNonFull(n->child[index], data);
    }
}

Node* insert(int data, BTree* b)
{
    size++;
    Node* root = b->root;
    if (root->index == DATA) {
        Node* new = initNode();
        b->root = new;
        new->leaf = 0;
        new->index = 0;
        new->child[0] = root;
        spliting(1, new, root);
        insertNonFull(new, data);
    } else
        insertNonFull(b->root, data);
    return b->root;
}

int search(int data, Node* node)
{
    int index = 0;
    while (index < node->index && data > node->data[index])
        index++;
    if (index == POINTERS)
        index--;
    if (index <= node->index && data == node->data[index])
        return 1;
    if (node->leaf)
        return 0;
    else
        return search(data, node->child[index]);
}

void merge(Node* root, int index, Node* child1, Node* child2)
{
    child1->index = DATA;
    int checking;
    for (checking = ORDER; checking < DATA; checking++)
        child1->data[checking] = child2->data[checking - ORDER];
    child1->data[ORDER - 1] = root->data[index];
    if (!child2->leaf)
        for (checking = ORDER; checking < POINTERS; checking++)
            child1->child[checking] = child2->child[checking - ORDER];
    for (checking = index + 1; checking < root->index; checking++) {
        root->data[checking - 1] = root->data[checking];
        root->child[checking] = root->child[checking + 1];
    }
    root->index--;
    free(child2);
}

void borrowLeft(Node* root, int index, Node* left, Node* current)
{
    current->index++;
    int checking;
    for (checking = current->index - 1; checking > 0; checking--)
        current->data[checking] = current->data[checking - 1];
    current->data[0] = root->data[index];
    root->data[index] = left->data[left->index - 1];
    if (!left->leaf) {
        for (checking = current->index; checking > 0; checking--)
            current->child[checking] = current->child[checking - 1];
    }
    current->child[0] = left->child[left->index];
    left->index--;
}

void borrowRight(Node* root, int index, Node* right, Node* current)
{
    current->index++;
    current->data[current->index - 1] = root->data[index];
    root->data[index] = right->data[0];
    for (int i = 0; i < right->index - 1; i++)
        right->data[i] = right->data[i + 1];
    if (!right->leaf) {
        current->child[current->index] = right->child[0];
        for (int i = 0; i < right->index; i++)
            right->child[i] = right->child[i + 1];
    }
    right->index--;
}

void deleteNotNone(int key, Node* root)
{
    int i;
    if (root->leaf) {
        i = 0;
        while (i < root->index && key > root->data[i])
            i++;
        if (key == root->data[i]) {
            for (; i < root->index - 1; i++)
                root->data[i] = root->data[i + 1];
            root->index--;
        } else {
            size++;
            printf("remove(%d) = not found\n", key);
            return;
        }
    } else {
        i = 0;
        Node *previous = NULL, *next = NULL;
        while (i < root->index && key > root->data[i])
            i++;
        if (i < root->index && key == root->data[i]) {
            previous = root->child[i];
            next = root->child[i + 1];
            if (previous->index > ORDER - 1) {
                int a = getLeftMax(previous);
                root->data[i] = a;
                deleteNotNone(a, previous);
            } else if (next->index > ORDER - 1) {
                int a = getRightMin(next);
                root->data[i] = a;
                deleteNotNone(a, next);
            } else {
                merge(root, i, previous, next);
                deleteNotNone(key, previous);
            }
        } else {
            previous = root->child[i];
            Node* sibling = NULL;
            if (i < root->index)
                next = root->child[i + 1];
            if (i > 0)
                sibling = root->child[i - 1];
            if (previous->index == ORDER - 1) {
                if (sibling && sibling->index > ORDER - 1)
                    borrowLeft(root, i - 1, sibling, previous);
                else if (next && next->index > ORDER - 1)
                    borrowRight(root, i, next, previous);
                else if (sibling) {
                    merge(root, i - 1, sibling, previous);
                    previous = sibling;
                } else
                    merge(root, i, previous, next);
            }

            deleteNotNone(key, previous);
        }
    }
}

Node* destroy(int data, BTree* b)
{
    if (size == 1) {
        size--;
        Node* new = initNode();
        return new;
    }
    if (b->root->index == 1) {
        Node* child1 = b->root->child[0];
        Node* child2 = b->root->child[1];
        if (child1 != NULL && child2 != NULL) {
            if (child1->index == ORDER - 1 && child2->index == ORDER - 1) {
                merge(b->root, 0, child1, child2);
                deleteNotNone(data, child1);
                size--;
                return child1;
            }
        }
    }
    size--;
    deleteNotNone(data, b->root);
    return b->root;
}

int main()
{
    BTree* root = initTree();
    scanf("%d", &t);
    while (t--) {
        scanf("%s%d", opt, &x);
        if (!strcmp(opt, "add"))
            insert(x, root), push(x), printf("add(%d) = ok\n", x);
        if (!strcmp(opt, "get"))
            search(x, root->root) ? printf("get(%d) = %d\n", x, x) : printf("get(%d) = not found\n", x);
        if (!strcmp(opt, "getk"))
            (x > size || x == 0) ? printf("getk(%d) = not found\n", x) : printf("getk(%d) = %d\n", x, getKth(x));
        if (!strcmp(opt, "remove")) {
            if (search(x, root->root)) {
                printf("remove(%d) = %d\n", x, x);
                int j = 0;
                for (; j <= top; j++) {
                    if (stk[j] == x)
                        break;
                }
                for (; j < top; j++)
                    stk[j] = stk[j + 1];
                stk[top] = 0;
                top--;
            }
            root->root = destroy(x, root);
        }
        if (!strcmp(opt, "removek")) {
            if (x > size || x == 0) {
                printf("removek(%d) = not found\n", x);
            } else {
                int data = getKth(x);
                printf("removek(%d) = %d\n", x, data);
                int i;
                for (i = 0; i <= top; i++) {
                    if (stk[i] == data)
                        break;
                }
                for (; i < top; i++)
                    stk[i] = stk[i + 1];
                stk[top] = 0;
                top--;
                root->root = destroy(data, root);
            }
        }
    }
}