#include <stdio.h>
#include <stdlib.h>

#define swap(x, y, t) (*t = *x, *x = *y, *y = *t)

struct binomialTree {
    //struct binomialTree *parent;
    struct binomialTree* rightSibling;
    struct binomialTree* child;
    int data;
    int degree;
};
typedef struct binomialTree* bnode;

bnode newTree(int);
void insertTree(int);
void deleteMin();
void merge(int, int);

bnode stack[5000];

int stackIndex = -1;

bnode newTree(int data)
{
    bnode temp = malloc(sizeof(struct binomialTree));
    temp->child = NULL;
    // temp->parent = NULL;
    temp->rightSibling = NULL;
    temp->data = data;
    temp->degree = 1;
    return temp;
}

void insertTree(int data)
{
    bnode node = newTree(data);
    stack[++stackIndex] = node;
    int index1 = 0, index2 = 1;
    while (index2 <= stackIndex) {
        if (stack[index1]->degree == stack[index2]->degree) {
            merge(index1, index2);
            index1 = 0;
            index2 = 1;
            continue;
        }
        index1++;
        index2++;
    }
}

void deleteMin()
{
    bnode min = newTree(9999);
    int todelete = 0;
    for (int i = 0; i <= stackIndex; i++) {
        if (min->data > stack[i]->data) {
            min = stack[i];
            todelete = i;
        }
    }
    int count = 0, level = min->degree;
    while (level != 1) {
        count++;
        level /= 2;
    }
    bnode temp = min->child;
    min = NULL;

    for (int i = todelete + 1; i <= stackIndex; i++)
        stack[i - 1] = stack[i];

    stack[stackIndex--] = NULL;

    if (count == 0) {
        return;
    } else {
        for (int i = 1; i <= count; i++) {

            stack[++stackIndex] = temp;
            if (temp->rightSibling != NULL)
                temp = temp->rightSibling;
        }

        int index1 = 0, index2 = 0;
        while (index1 <= stackIndex) {
            while (index2 <= stackIndex) {
                if (index1 != index2 && stack[index1]->degree == stack[index2]->degree) {
                    merge(index1, index2);
                    index1 = 0;
                    index2 = 0;
                    continue;
                }
                index2++;
            }
            index1++;
            index2 = 0;
        }
    }
}

void merge(int index1, int index2)
{
    if (stack[index1]->data > stack[index2]->data) {
        bnode temp = malloc(sizeof(struct binomialTree));
        swap(stack[index1], stack[index2], temp);
        free(temp);
    }
    if (stack[index1]->degree > 1 && stack[index2]->degree > 1)
        stack[index2]->rightSibling = stack[index1]->child;

    stack[index1]->child = stack[index2];
    stack[index1]->degree += stack[index2]->degree;
    for (int i = index2 + 1; i <= stackIndex; i++)
        stack[i - 1] = stack[i];
    stack[stackIndex--] = NULL;
}

int n, t;

int main()
{
    // x = 0 -> destroy
    // x = 1 -> insert
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &t), insertTree(t);
    scanf("%d", &t);
    for (int i = 1, x; i <= t; i++) {
        scanf("%d", &x);
        if (x)
            scanf("%d", &x), insertTree(t);
        else
            deleteMin();
    }
}