#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

typedef struct node {
    int val[MAX];
    struct node** child[MAX];
    int top;
} node;

int cmp(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}
int main()
{
    node* n = (node*)malloc(sizeof(struct node));
    n->top = 0;
    char str[15];
    int t, x, a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", str);
        if (*str == 'a') {
            scanf("%d", &x);
            n->val[n->top++] = x;
            qsort(n->val, n->top, sizeof(int), cmp);
        } else if (*(str + 1) == 'a') {
            scanf("%d%d", &a, &b);
            printf("range [%d,%d) = [", a, b);
            for (int i = 0; i < n->top; ++i) {
                if (n->val[i] >= a && n->val[i] < b) {
                    printf("%d", n->val[i]);
                    if (i + 1 < n->top && n->val[i + 1] < b)
                        printf(",");
                }
            }
            printf("]\n");
        } else if (*(str + 1) == 'e') {
            scanf("%d", &x);
            for (int i = 0; i < n->top; ++i) {
                if (n->val[i] == x) {
                    for (int j = i; j + 1 < n->top; ++j) {
                        n->val[j] = n->val[j + 1];
                    }
                    n->top--;
                    break;
                } else if (n->val[i] > x)
                    break;
            }
        }
    }
}