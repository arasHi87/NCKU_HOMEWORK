#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int use[30];
char arr[30], str[30];

void dfs(int idx) {
    if (idx==strlen(arr)) {
        printf("%s\n", str);
        return;
    }

    for (int i=0;i<(int)strlen(arr);i++) {
        if (!use[i]) {
            use[i]=1;
            str[idx]=arr[i];
            dfs(idx+1);
            use[i]=0;
        }
    }

    return;
}

int main() {
    scanf("%s", arr);

    for (int i=0;i<strlen(arr);i++)
        for (int j=i+1;j<strlen(arr);j++)
            if (arr[i]>arr[j])
                arr[i] ^= arr[j] ^= arr[i] ^= arr[j];
    dfs(0);
}
