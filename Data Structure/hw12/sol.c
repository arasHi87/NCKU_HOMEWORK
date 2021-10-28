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

void change(Heap* h, int x, int y)
{
    int idx = 0, child = 0;
    for (int i = 1; i <= h->size; i++)
        if (x == h->data[i]) {
            idx = i, h->data[i] = y;
            break;
        }
    if (x > y) {
        while (y < h->data[idx >> 1])
            h->data[idx] = h->data[idx >> 1], idx >>= 1;
    } else if (x < y) {
        while (idx << 1 <= h->size) {
            child = idx << 1;
            if (child != h->size && h->data[child] > h->data[child | 1])
                child++;
            if (y < h->data[child])
                break;
            else
                h->data[idx] = h->data[child], idx = child;
        }
    }
    h->data[idx] = y;
}

int verfy(Heap* h)
{
    for (int i = 1; i << 1 <= h->size; i++) {
        if (h->data[i << 1] <= h->data[i])
            return 0;
        if ((i << 1 | 1) <= h->size && h->data[i << 1 | 1] < h->data[i])
            return 0;
    }
    return 1;
}

int main()
{
    Heap* h = init();
    int n = 10;
    int arr[15] = { 0, 12, 43, 65, 32, 4, 46, 87, 21, 54, 66 };

    for (int i = 1; i <= n; i++)
        insert(h, *(arr + i));
    change(h, 4, 100000);
    printf("%d\n", verfy(h));
    change(h, 87, 1);
    printf("%d\n", verfy(h));
    for (int i = 1; i <= n; i++)
        printf("%d ", destroy(h));
}