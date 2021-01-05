void add(char a[], char b[], char res[]){
    int s_a=strlen(a)-1, s_b=strlen(b)-1, s_r=0;

    for (int i=0;i<105;i++) res[i]='0';

    while (s_a>=0 || s_b>=0) {
        int sum=res[s_r]-'0';

        if (s_a>=0) sum+=(a[s_a]-'0');
        if (s_b>=0) sum+=(b[s_b]-'0');
        if (sum>9) sum-=10, res[s_r+1]='1';

        res[s_r]=(sum+'0');
        
        s_r++, s_a--, s_b--;
    } res[s_r]='\0';

    char *x=&res[0], *y=x+strlen(res)-1;

    while (x<y) 
        *x ^= *y ^= *x ^= *y, x++, y--; 
}
