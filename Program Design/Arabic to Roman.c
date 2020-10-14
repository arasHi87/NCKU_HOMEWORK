#include <stdio.h>

int a, idx=0, val[5];
char ch[5][15][5] = {
	{},
	{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X"},
	{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC", "C"},
	{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM", "M"},
	{"", "M", "MM", "MMM"}
};

int main() {
	scanf("%d", &a);
	
	while (a) val[++idx]=a%10, a/=10;

	for (int i=idx;i>=1;i--)
		printf("%s", ch[i][val[i]]);
}
