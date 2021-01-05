#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct pair {
	int ft, sd;
} pair;

typedef struct Node {
	char idx;
	int c_s, p_s, s_s;
} node;

char str[5][5];
pair arr[5];
node ans[5];

pair convert(char s[]) {
	pair* tmp=(pair*)malloc(sizeof(pair*));

	if (s[0]>='0' && s[0]<='9') tmp->ft=s[0]-'0';
	else {
		if (s[0]=='t') tmp->ft=10;
		else if (s[0]=='j') tmp->ft=11;
		else if (s[0]=='q') tmp->ft=12;
		else if (s[0]=='k') tmp->ft=13;
		else if (s[0]=='a') tmp->ft=14;
	}

	tmp->sd=s[1]-'a';

	return *tmp;
}

int pair_cmp(const void* a, const void* b) {
	if (((pair*)a)->ft!=((pair*)b)->ft) return ((pair*)b)->ft - ((pair*)a)->ft;
	return ((pair*)b)->sd - ((pair*)a)->sd;
}

int node_cmp(const void* a, const void* b) {
	if (((node*)a)->c_s!=((node*)b)->c_s) return ((node*)b)->c_s - ((node*)a)->c_s;
	
	switch (((node*)a)->c_s) {
		case 9:
		case 6:
		case 5:
		case 3:
		case 2:
		case 1:
			if (((node*)a)->p_s!=((node*)b)->p_s) return ((node*)b)->p_s - ((node*)a)->p_s;
			return ((node*)b)->s_s - ((node*)a)->s_s;
			break;
		case 8:
		case 7:
		case 4:
			return ((node*)b)->p_s - ((node*)a)->p_s;
			break;
	}
}

int flush(int idx) {
	for (int i=0;i<4;i++)
		if (arr[i].sd!=arr[i+1].sd)
			return 0;
	
	ans[idx].c_s=6;
	ans[idx].p_s=arr[0].ft;
	ans[idx].s_s=arr[0].sd;

	return 1;
}

int straight(int idx) {
	for (int i=0;i<4;i++)
		if (arr[i].ft-1 != arr[i+1].ft)
			return 0;
	
	ans[idx].c_s=5;
	ans[idx].p_s=arr[0].ft;
	ans[idx].s_s=arr[0].sd;

	return 1;
}

int straight_flush(int idx) {
	if (!flush(idx) || !straight(idx))
		return 0;

	ans[idx].c_s=9;

	return 1;
}

int four_of_a_kind(int idx) {
	if (arr[1].ft!=arr[2].ft || arr[2].ft!=arr[3].ft) return 0;
	if (arr[0].ft!=arr[1].ft && arr[3].ft!=arr[4].ft) return 0;

	ans[idx].c_s=8;
	ans[idx].p_s=arr[2].ft;
	ans[idx].s_s=0;

	return 1;
}

int full_house(int idx) {
	if (arr[0].ft!=arr[1].ft || arr[3].ft!=arr[4].ft) return 0;
	if (arr[2].ft!=arr[1].ft && arr[2].ft!=arr[3].ft) return 0;

	ans[idx].c_s=7;
	ans[idx].p_s=arr[2].ft;
	ans[idx].s_s=0;

	return 1;
}

int three_of_a_kind(int idx) {
	int cnt=0;

	for (int i=0;i<=4;i++)
		if (arr[i].ft==arr[2].ft)
			cnt++;

	if (cnt!=3) return 0;

	ans[idx].c_s=4;
	ans[idx].p_s=arr[2].ft;
	ans[idx].s_s=0;

	return 1;
}

int two_pairs(int idx) {
	if ((arr[0].ft==arr[1].ft && (arr[2].ft==arr[3].ft || arr[3].ft==arr[4].ft))) {
		ans[idx].c_s=3;
		ans[idx].p_s=arr[0].ft;
		ans[idx].s_s=arr[0].sd;

		return 1;
	} else if (arr[1].ft==arr[2].ft && arr[3].ft==arr[4].ft) {
		ans[idx].c_s=3;
		ans[idx].p_s=arr[1].ft;
		ans[idx].s_s=arr[1].sd;

		return 1;
	}

	return 0;
}

int _pair(int idx) {
	for (int i=0;i<4;i++)
		if (arr[i].ft==arr[i+1].ft) {
			ans[idx].c_s=2;
			ans[idx].p_s=arr[i].ft;
			ans[idx].s_s=arr[i].sd;

			return 1;
		}

	return 0;
}

int main() {
	for (int i=0;i<4;i++) { 
		for (int j=0;j<=4;j++) {
			scanf("%s", str[j]);
			
			arr[j]=convert(str[j]);
		} getchar();
		
		qsort(arr, 5, sizeof(pair), pair_cmp);
		
		ans[i].idx='A'+i;

		if (straight_flush(i));
		else if (four_of_a_kind(i));
		else if (full_house(i));
		else if (flush(i));
		else if (straight(i));
		else if (three_of_a_kind(i));
		else if (two_pairs(i));
		else if (_pair(i));
		else {
			ans[i].c_s=1;
			ans[i].p_s=arr[0].ft;
			ans[i].s_s=arr[0].sd;
		}
	}
	
	qsort(ans, 4, sizeof(node), node_cmp);

	for (int i=0;i<4;i++)
		printf("%c ", ans[i].idx);
}
