int addition(char str[]) {
    int sum=0, tmp=0;

    for (int i=0;i<strlen(str);i++)
        if (str[i]>='0' && str[i]<='9') tmp*=10, tmp+=(str[i]-'0');
        else sum+=tmp, tmp=0;

    return sum+tmp;
}
