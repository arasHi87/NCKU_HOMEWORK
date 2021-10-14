#include <stdio.h>
#include <string.h>
const int maxN = 100;

char pre[maxN], post[maxN], stk[maxN][maxN];

int is_op(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

void pre2post()
{
    char op1[maxN], op2[maxN];
    int top = 0, len = strlen(pre);

    for (int i = len - 1; i >= 0; i--) {
        // printf("%c\n", pre[i]);
        if (is_op(pre[i])) {
            strcpy(op1, stk[--top]);
            strcpy(op2, stk[--top]);
            sprintf(stk[top++], "%s%s%c", op1, op2, pre[i]);
        } else {
            stk[top][0] = pre[i], stk[top++][1] = '\0';
        }
        // for (int i = top - 1; i >= 0; i--)
        //         printf("%s", stk[i]);
        //     puts("");
        // printf("%d\n", top);
    }
    for (int i = top - 1; i >= 0; i--)
        printf("%s", stk[i]);
}

void post2pre()
{
    char op1[maxN], op2[maxN];
    int top = 0, len = strlen(post);

    for (int i = 0; i < len; i++) {
        if (is_op(post[i])) {
            strcpy(op1, stk[--top]);
            strcpy(op2, stk[--top]);
            sprintf(stk[top++], "%c%s%s", post[i], op2, op1);
        } else {
            stk[top][0] = post[i], stk[top++][1] = '\0';
        }
    }
    for (int i = top - 1; i >= 0; i--)
        printf("%s", stk[i]);
}

int main()
{
    scanf("%s%s", pre, post);
    pre2post();
    puts("");
    post2pre();
}