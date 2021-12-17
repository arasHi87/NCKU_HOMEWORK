#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE_ORDER 3
#define NODE_POINTERS (NODE_ORDER * 2)
#define NODE_DATA NODE_POINTERS - 1

struct treeNode {
    int data_array[NODE_DATA];
    struct treeNode* child_array[NODE_POINTERS];
    int data_index;
    bool Leaf;
};
typedef struct treeNode* node;

struct BTree {
    node root;
};
typedef struct BTree* btree;
btree newTree();

static node newNode();
node insert(int, btree);
void insertNonFull(node, int);
void spliting(int index, node parent, node child_array);

bool search(int, node);

node destroy(int, btree);
void deleteNoNon(int, node);
void merge(node, int, node, node);
void borrowLeft(node, int, node, node);
void borrowRight(node, int, node, node);
int GetLeftMax(node);
int GetRightMin(node);

int Size = 0;
int top = -1;
int stack[10000];

int cmp(const void*, const void*);
void push(int);
int getKth(int);

int t, x;
char opt[20];

int main()
{
    btree root = newTree();
    scanf("%d", &t);
    while (t--) {
        scanf("%s%d", opt, &x);
        if (!strcmp(opt, "add"))
            insert(x, root), push(x), printf("add(%d) = ok\n", x);
        if (!strcmp(opt, "get"))
            search(x, root->root) ? printf("get(%d) = %d\n", x, x) : printf("get(%d) = not found\n", x);
        if (!strcmp(opt, "getk"))
            (x > Size || x == 0) ? printf("getk(%d) = not found\n", x) : printf("getk(%d) = %d\n", x, getKth(x));
        if (!strcmp(opt, "remove")) {
            if (search(x, root->root)) {
                printf("remove(%d) = %d\n", x, x);
                int j = 0;
                for (; j <= top; j++) {
                    if (stack[j] == x)
                        break;
                }
                for (; j < top; j++)
                    stack[j] = stack[j + 1];
                stack[top] = 0;
                top--;
            }
            root->root = destroy(x, root);
        }
        if (!strcmp(opt, "removek")) {
            if (x > Size || x == 0) {
                printf("removek(%d) = not found\n", x);
            } else {
                int data = getKth(x);
                printf("removek(%d) = %d\n", x, data);
                int i;
                for (i = 0; i <= top; i++) {
                    if (stack[i] == data)
                        break;
                }
                // shifting
                for (; i < top; i++)
                    stack[i] = stack[i + 1];
                stack[top] = 0;
                top--;
                root->root = destroy(data, root);
            }
        }
    }
}

btree newTree()
{
    btree root = (btree)malloc(sizeof(struct BTree));
    node head = newNode();
    root->root = head;
    return root;
}

static node newNode()
{
    int index = 0;
    node new = (node)malloc(sizeof(struct treeNode));

    for (index = 0; index < NODE_DATA; index++)
        new->data_array[index] = (int)INFINITY;
    for (index = 0; index < NODE_POINTERS; index++)
        new->child_array[index] = NULL;
    new->data_index = 0;
    new->Leaf = true;
    return new;
}

node insert(int data, btree b)
{
    Size++;
    node root = b->root;
    // if full, split
    if (root->data_index == NODE_DATA) {
        node new = newNode();
        b->root = new;
        new->Leaf = false;
        new->data_index = 0;
        new->child_array[0] = root;
        spliting(1, new, root);
        insertNonFull(new, data);
    } else // not full
        insertNonFull(b->root, data);
    return b->root;
}

void insertNonFull(node n, int data)
{
    int index = n->data_index;
    // if is leaf
    if (n->Leaf) {
        // shifting
        while (index >= 1 && data < n->data_array[index - 1]) {
            n->data_array[index] = n->data_array[index - 1];
            index--;
        }
        n->data_array[index] = data;
        n->data_index++;
    }
    // has child
    else {
        while (index >= 1 && data < n->data_array[index - 1])
            index--;
        // if insert's childindex is full
        if (n->child_array[index]->data_index == NODE_DATA) {
            spliting(index + 1, n, n->child_array[index]);
            if (data > n->data_array[index])
                index++;
        }
        // keep checking
        insertNonFull(n->child_array[index], data);
    }
}

void spliting(int index, node parent, node child_array)
{

    node new = newNode();
    new->Leaf = child_array->Leaf;
    new->data_index = NODE_ORDER - 1;
    // moving
    for (int i = 0; i < NODE_ORDER - 1; i++)
        new->data_array[i] = child_array->data_array[NODE_ORDER + i];
    // moving child pointers
    if (!child_array->Leaf) {
        for (int i = 0; i < NODE_ORDER; i++)
            new->child_array[i] = child_array->child_array[NODE_ORDER + i];
    }
    child_array->data_index = NODE_ORDER - 1;

    // right shift parent's child pointer
    for (int i = parent->data_index; i >= index; i--)
        parent->child_array[i + 1] = parent->child_array[i];
    // point to the split new
    parent->child_array[index] = new;

    // right shifting keys
    for (int i = parent->data_index; i >= index; i--)
        parent->data_array[i] = parent->data_array[i - 1];

    // set parent's median data to child's median
    parent->data_array[index - 1] = child_array->data_array[NODE_ORDER - 1];

    // shift parent data index
    parent->data_index++;
}

bool search(int data, node node)
{
    int index = 0;
    while (index < node->data_index && data > node->data_array[index])
        index++;
    // prevent overflow
    if (index == NODE_POINTERS)
        index--;
    // if found
    if (index <= node->data_index && data == node->data_array[index]) {
        return true;
    }
    // not found then check whether is leaf
    if (node->Leaf) {
        return false;
    } else {
        // result res = getResult();
        return search(data, node->child_array[index]);
    }
}

node destroy(int data, btree b)
{
    if (Size == 1) {
        Size--;
        node new = newNode();
        return new;
    }
    if (b->root->data_index == 1) {
        node child1 = b->root->child_array[0];
        node child2 = b->root->child_array[1];
        if (child1 != NULL && child2 != NULL) {
            if (child1->data_index == NODE_ORDER - 1 && child2->data_index == NODE_ORDER - 1) {
                merge(b->root, 0, child1, child2);
                // free(b);
                deleteNoNon(data, child1);
                Size--;
                return child1;
            }
        }
    }
    Size--;
    deleteNoNon(data, b->root);
    return b->root;
}

void merge(node root, int index, node child1, node child2)
{
    child1->data_index = NODE_DATA;
    int checking;
    // moving child2's keys to child1's right
    for (checking = NODE_ORDER; checking < NODE_DATA; checking++)
        child1->data_array[checking] = child2->data_array[checking - NODE_ORDER];
    // shift index down
    child1->data_array[NODE_ORDER - 1] = root->data_array[index];
    // if child2 is not leaf
    if (!child2->Leaf) {
        for (checking = NODE_ORDER; checking < NODE_POINTERS; checking++)
            child1->child_array[checking] = child2->child_array[checking - NODE_ORDER];
    }
    // update root, shifing left
    for (checking = index + 1; checking < root->data_index; checking++) {
        root->data_array[checking - 1] = root->data_array[checking];
        root->child_array[checking] = root->child_array[checking + 1];
    }
    root->data_index--;
    free(child2);
}

void borrowLeft(node root, int index, node left, node current)
{
    current->data_index++;
    int checking;
    for (checking = current->data_index - 1; checking > 0; checking--)
        current->data_array[checking] = current->data_array[checking - 1];
    current->data_array[0] = root->data_array[index];
    root->data_array[index] = left->data_array[left->data_index - 1];
    // if left is not leaf
    if (!left->Leaf) {
        for (checking = current->data_index; checking > 0; checking--)
            current->child_array[checking] = current->child_array[checking - 1];
    }
    current->child_array[0] = left->child_array[left->data_index];
    left->data_index--;
}

void borrowRight(node root, int index, node right, node current)
{
    current->data_index++;
    current->data_array[current->data_index - 1] = root->data_array[index];
    root->data_array[index] = right->data_array[0];
    for (int i = 0; i < right->data_index - 1; i++)
        right->data_array[i] = right->data_array[i + 1];
    // not leaf
    if (!right->Leaf) {
        current->child_array[current->data_index] = right->child_array[0];
        for (int i = 0; i < right->data_index; i++)
            right->child_array[i] = right->child_array[i + 1];
    }
    right->data_index--;
}

void deleteNoNon(int key, node root)
{
    int i;
    // case 1 : leaf--just delete
    if (root->Leaf) {
        i = 0;
        while (i < root->data_index && key > root->data_array[i])
            i++;
        if (key == root->data_array[i]) {
            for (; i < root->data_index - 1; i++)
                root->data_array[i] = root->data_array[i + 1];
            root->data_index--;
        } else {
            Size++;
            printf("remove(%d) = not found\n", key);
            return;
        }
    }
    // case 2 && 3 : internal
    else {
        i = 0;
        node previous = NULL, next = NULL;
        // find
        while (i < root->data_index && key > root->data_array[i])
            i++;
        if (i < root->data_index && key == root->data_array[i]) {
            previous = root->child_array[i];
            next = root->child_array[i + 1];
            // case a : previous has keys > half
            if (previous->data_index > NODE_ORDER - 1) {
                int a = GetLeftMax(previous);
                root->data_array[i] = a;
                deleteNoNon(a, previous);
            }
            // case b : next has keys > half
            else if (next->data_index > NODE_ORDER - 1) {
                int a = GetRightMin(next);
                root->data_array[i] = a;
                deleteNoNon(a, next);
            }
            // case c : both have keys < half
            else {
                merge(root, i, previous, next);
                deleteNoNon(key, previous);
            }
        }
        // still not found yet
        else {
            previous = root->child_array[i];
            node sibling = NULL;
            if (i < root->data_index)
                next = root->child_array[i + 1];
            if (i > 0)
                sibling = root->child_array[i - 1];
            // start borrowing
            if (previous->data_index == NODE_ORDER - 1) {
                if (sibling && sibling->data_index > NODE_ORDER - 1)
                    borrowLeft(root, i - 1, sibling, previous);
                else if (next && next->data_index > NODE_ORDER - 1)
                    borrowRight(root, i, next, previous);
                else if (sibling) {
                    merge(root, i - 1, sibling, previous);
                    previous = sibling;
                } else
                    merge(root, i, previous, next);
            }

            deleteNoNon(key, previous);
        }
    }
}

int GetLeftMax(node node)
{
    if (!node->Leaf)
        return GetLeftMax(node->child_array[node->data_index]);
    else
        return node->data_array[node->data_index - 1];
}

int GetRightMin(node node)
{
    if (!node->Leaf)
        return GetRightMin(node->child_array[0]);
    else
        return node->data_array[0];
}

void push(int data)
{
    stack[++top] = data;
    qsort(stack, Size, sizeof(int), cmp);
}

int getKth(int kth)
{
    return stack[kth - 1];
}
int cmp(const void* a, const void* b)
{
    int* aa = (int*)a;
    int* bb = (int*)b;
    return (*aa) - (*bb);
}