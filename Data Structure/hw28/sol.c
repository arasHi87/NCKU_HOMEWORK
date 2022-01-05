#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 1007

typedef struct node {
    int key, val;
} Node;

Node* arr[maxN];

int hash(int key) { return key % maxN; }

Node* init(int key, int val)
{
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->key = key, tmp->val = val;
    return tmp;
}

void insert(int key, int val)
{
    int idx = hash(key);
    Node* tmp = init(key, val);
    while (arr[idx] && arr[idx]->key != key && ~arr[idx]->key)
        idx++, idx %= maxN;
    if (!arr[idx] || !~arr[idx]->key)
        arr[idx] = tmp;
}

void destroy(int key)
{
    int idx = hash(key);
    while (arr[idx]) {
        if (arr[idx]->key == key) {
            arr[idx]->key = -1;
            return;
        }
        idx++, idx %= maxN;
    }
}

int search(int key)
{
    int idx = hash(key), cnt = 0;
    while (arr[idx] && cnt <= maxN) {
        if (arr[idx]->key == key)
            return arr[idx]->val;
        idx++, idx %= maxN;
    }
    return -1;
}

int main()
{
    // 0->insert, 1->delete, 2->search
    int x, y, z;
    while (~scanf("%d", &x)) {
        if (x == 0)
            scanf("%d%d", &y, &z), insert(y, z);
        if (x == 1)
            scanf("%d", &y), destroy(y);
        if (x == 2)
            scanf("%d", &y), printf("%d\n", search(y));
    }
}