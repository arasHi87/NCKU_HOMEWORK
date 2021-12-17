#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 10009
#define swap(x, y) \
    do {           \
        int t = x; \
        x = y;     \
        y = t;     \
    } while (0)

int heap[maxN], size = 0;

void sort(int idx)
{
    int parent = (idx & 1 ? ((idx - 1) >> 1) : ((idx - 2) >> 1)), grandpa;
    int L = (parent << 1) | 1, R = (parent + 1) << 1;
    if (parent & 1) {
        grandpa = (parent - 1) >> 1;
        if (parent != 0 && grandpa >= 0 && heap[idx] < heap[(grandpa << 1) | 1])
            swap(heap[idx], heap[(grandpa << 1) | 1]);
        if (parent != 0 && grandpa >= 0 && heap[idx] > heap[(grandpa + 1) << 1])
            swap(heap[idx], heap[(grandpa + 1) << 1]);
    } else {
        grandpa = (parent - 2) >> 1;
        if (grandpa >= 0 && heap[idx] < heap[(grandpa << 1) | 1])
            swap(heap[idx], heap[(grandpa << 1) | 1]);
        if (grandpa >= 0 && heap[idx] > heap[(grandpa + 1) << 1])
            swap(heap[idx], heap[(grandpa + 1) << 1]);
    }
    if (parent >= 0 && L <= size && R <= size && heap[L] > heap[R])
        swap(heap[L], heap[R]);
}

void popmax()
{
    int P = 2, L = 4, R = 6, max;
    heap[P] = heap[(--size) + 1];
    while (L <= size && R <= size) {
        max = heap[P];
        if (heap[L] > max)
            max = heap[L];
        if (heap[R] > max)
            max = heap[R];
        if (max != heap[P]) {
            if (heap[L] == max)
                heap[L] = heap[P], heap[P] = max, P = L, L = P << 1, R = (P + 1) << 1;
            if (heap[R] == max)
                heap[R] = heap[P], heap[P] = max, P = R, L = P << 1, R = (P + 1) << 1;
        } else
            P = L, L = P << 1, R = (P + 1) << 1;
    }
    if (L <= size)
        if (heap[P] < heap[R])
            swap(heap[P], heap[R]);
    if (heap[P] < heap[P - 1])
        swap(heap[P], heap[P - 1]);
}

void popmin()
{
    int P = 1, L = 3, R = 5, min;
    heap[P] = heap[(--size) + 1];
    while (L <= size && R <= size) {
        min = heap[P];
        if (heap[L] < min)
            min = heap[L];
        if (heap[R] < min)
            min = heap[R];
        if (heap[P] != min) {
            if (heap[L] == min)
                heap[L] = heap[P], heap[P] = min, P = L, L = (P << 1) | 1, R = ((P + 1) << 1) | 1;
            if (heap[R] == min)
                heap[R] = heap[P], heap[P] = min, P = R, L = (P << 1) | 1, R = ((P + 1) << 1) | 1;
        } else
            P = L, L = (P << 1) | 1, R = ((P + 1) << 1) | 1;
    }
    if (L <= size)
        if (heap[P] > heap[L])
            swap(heap[L], heap[P]);
    if (P + 1 <= size && heap[P] > heap[P + 1])
        swap(heap[P], heap[P + 1]);
}

int main()
{
    int x;
    char opt[15];
    while (~scanf("%s", opt)) {
        if (!strcmp(opt, "insert")) {
            scanf("%d", &x), heap[++size] = x;
            for (int i = size; i >= 0; i--)
                sort(i);
        } else if (!strcmp(opt, "show")) {
            puts("NULL");
            int s = 1, l = 0;
            for (int i = 1; i <= size; i++) {
                printf("%d ", heap[i]), l++;
                if (l == pow(2, s))
                    puts(""), s++, l = 0;
            }
            if (l)
                puts("");
        } else if (!strcmp(opt, "delete")) {
            scanf("%s", opt);
            (!strcmp(opt, "min") ? popmin() : popmax());
        } else
            return 0;
    }
}