#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 107

typedef struct node {
    int val;
    struct node* next;
} Node;

typedef struct {
    Node *head, *rear;
} Queue;

Queue* initQ()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->head = q->rear = NULL;
    return q;
}

Node* initN(int x)
{
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->val = x;
    tmp->next = NULL;
    return tmp;
}

void inq(Queue* q, int x)
{
    Node* tmp = initN(x);
    if (!q->head)
        q->head = tmp;
    if (!q->rear)
        q->rear = tmp;
    else
        q->rear = q->rear->next = tmp;
}

int outq(Queue* q)
{
    Node* tmp = q->head;
    if (q->head == q->rear)
        q->head = q->rear = NULL;
    else
        q->head = q->head->next;
    return tmp->val;
}

int t, n, m;
int arr[maxN][maxN], vis[maxN];

void bfs(int x)
{
    Queue* q = initQ();
    inq(q, x), vis[x] = 1;
    while (q->head) {
        printf("%d ", (x = outq(q)));
        for (int i = 0; i < n; i++) {
            if (arr[x][i] && !vis[i])
                inq(q, i), vis[i] = 1;
        }
    }
}

int main()
{
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        memset(vis, 0, sizeof vis);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &arr[i][j]);
        bfs(m), puts("");
    }
}