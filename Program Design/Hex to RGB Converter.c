#include <stdio.h>

char ch[5];
int idx=0, ans[5];

int h2d(char tmp) {
	if (tmp>='0' && tmp<='9') return tmp-'0';
	return tmp-'A'+10;
}

int main() {
	getchar();

	while (~scanf("%2s", ch))
		ans[++idx]=(h2d(ch[0])<<4)+h2d(ch[1]);

	printf("rgb(%d,%d,%d)", ans[1], ans[2], ans[3]);
}

