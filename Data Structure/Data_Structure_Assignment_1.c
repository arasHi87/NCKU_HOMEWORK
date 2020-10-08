#include <stdio.h>
#include <string.h>
#include <getopt.h>
#define maxN 20000

int ch;
char h3x[maxN], ascii[maxN], res[maxN];
char char_set[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
FILE *inp, *oup;

int main(int argc, char **argv) {
	// parse arguments
	while (~(ch = getopt(argc, argv, "i:o:"))) {
		switch (ch) {
			case 'i':
				inp = fopen(optarg, "r");
				break;

			case 'o':
				oup = fopen(optarg, "w");
				break;
		}
	}

	// input case
	while (fgets(h3x, maxN, inp)) {
		int h_len=strlen(h3x), a_len=-1, r_len=-1, left=0;

		h3x[h_len-1]='\0'; //replace newline with end singal

		// convert hex to ascii
		for (int i=0, tmp;i<h_len;i+=2) {
			tmp=0;

			for (int j=i;j<=i+1;j++) {
				if (h3x[j]>='0' && h3x[j]<='9') tmp+=(int)(h3x[j]-'0');
				if (h3x[j]>='A' && h3x[j]<='F') tmp+=(int)(h3x[j]-'A'+10);
				if (j==i) tmp<<=4;
			}

			ascii[++a_len]=(char)tmp;
		}
		
		ascii[a_len+1]='\0', left=0;

		//convert ascii to base64
		for (int i=0;i<a_len;i+=3) {
			int val=0, bit=0, cnt=0, tmp=0, idx=0;

			for (int j=i;j<a_len && j<=i+2;j++) 
				val=((val<<8)|ascii[j]), cnt++;
			
			bit=cnt<<3;
			left=bit%3;

			while (bit) {
				if (bit>=6) tmp=(bit-=6), idx=(val>>tmp)&63;
				else tmp=6-bit, bit=0, idx=(val<<tmp)&63;

				res[++r_len] = char_set[idx];
			}
		}

		for (int i=1;i<=left;i++) 
			res[++r_len]='=';

		res[++r_len]='\0';

		fprintf(oup, "%s\n", res);
	}	
}
