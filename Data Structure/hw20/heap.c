#include <stdio.h>
#include <stdlib.h>
#define maxN 100000

typedef struct _heap {
    int size, capt, *data;
} Heap;

Heap* init()
{
    Heap* tmp = (Heap*)malloc(sizeof(Heap));
    tmp->data = (int*)malloc(sizeof(int) * (maxN + 1));
    tmp->size = 0;
    tmp->capt = maxN;
    tmp->data[0] = -1;
    return tmp;
}

void insert(Heap* h, int x)
{
    int idx = ++h->size;
    while (x < h->data[idx >> 1])
        h->data[idx] = h->data[idx >> 1], idx >>= 1;
    h->data[idx] = x;
}

int destroy(Heap* h)
{
    int idx = 1, child;
    int top = h->data[1], tmp = h->data[h->size--];
    while (idx << 1 <= h->size) {
        child = idx << 1;
        if (child != h->size && h->data[child] > h->data[child | 1])
            child++;
        if (tmp < h->data[child])
            break;
        else
            h->data[idx] = h->data[child], idx = child;
    }
    h->data[idx] = tmp;
    return top;
}

int n, t;

int main()
{
    // x = 0 -> destroy
    // x = 1 -> insert
    Heap* h = init();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &t), insert(h, t);
    scanf("%d", &t);
    for (int i = 1, x; i <= t; i++) {
        scanf("%d", &x);
        if (x)
            scanf("%d", &x), insert(h, x);
        else
            destroy(h);
    }
}