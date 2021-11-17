#include <stdio.h>
#include <stdlib.h>
#define maxN 1007

int t, n, pre[maxN], in[maxN], post[maxN];
char str[maxN];

void topost(int* _in, int* _pre, int len)
{
    if (len) {
        for (int i = 0; i < len; i++) {
            if (*(_in + i) == *_pre) {
                topost(_in, _pre + 1, i);
                topost(_in + i + 1, _pre + i + 1, len - i - 1);
                printf("%d ", *_pre);
                return;
            }
        }
    }
}

void topre(int* _in, int* _post, int len)
{
    if (len) {
        for (int i = len; i >= 0; i--) {
            if (*(_in + i) == *(_post + len - 1)) {
                printf("%d ", *(_post + len - 1));
                topre(_in, _post, i);
                topre(_in + i + 1, _post + i, len - i - 1);
                return;
            }
        }
    }
}

int main()
{
    scanf("%d", &t);
    while (t--) {
        scanf("%s%d", str, &n);
        for (int i = 0; i < n; i++)
            scanf("%d", str[1] == 'r' ? pre + i : post + i);
        for (int i = 0; i < n; i++)
            scanf("%d", in + i);
        str[1] == 'r' ? topost(in, pre, n) : topre(in, post, n);
        puts("");
    }
}