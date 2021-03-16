#include <stdio.h>
#define maxN 50

int n, k, idx=1, arr[maxN];
char ch;

int main() {
	scanf("%d", &n); getchar();
	
	for (int i=1;i<=n;i++)
		scanf("%c", &ch), arr[i]=ch-'a';
	
	getchar();

	while (~scanf("%c", &ch) && ch!='\n') {
		if (idx>n) idx=1;
		
		k=arr[idx], k%=26;
		
		if (ch>='a' && ch<='z') printf("%c", 'a'+(ch-'a'+k)%26), idx++;
		else if (ch>='A' && ch<='Z') printf("%c", 'A'+(ch-'A'+k)%26), idx++;
		else printf("%c", ch);
	}
}

