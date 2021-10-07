#include <stdio.h>
#include <string.h>
#define LL long long
const int maxN = 75;

LL t, n, ans[maxN];
char ch[10];

LL recursive(LL x)
{
    if (x == 0 || x == 1)
        return x;
    else {
        return recursive(x - 1) + recursive(x - 2);
    }
}

void iterative()
{
    ans[0] = 0, ans[1] = 1;
    for (int i = 2; i <= 70; i++) {
        ans[i] = ans[i - 1] + ans[i - 2];
    }
}

int main()
{
    scanf("%lld", &t), iterative();
    while (t--) {
        scanf("%s%lld", ch, &n);
        if (!strcmp(ch, "recursive"))
            printf("%lld\n", recursive(n));
        else {
            printf("%lld\n", ans[n]);
        }
    }
}