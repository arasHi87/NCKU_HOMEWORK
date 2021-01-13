typedef struct Node {
    int idx, cnt;
    char name[20];
} node;

int max(int a, int b) { return a>b ? a : b; }

void find_fruit(char input[],char fruit[][15]){
// input is the fruit sequence eg: watermelon+_+watermelon+_+coconut+_+grape+_+coconut
// fruit is 20 kinds of fruit name eg: fruit[0] is "guava", fruit[1] is litchi and so on. 
// you need to check the Loader code to understand above meaning 
    node arr[20];
    int MAX=-1;
    char *str=strtok(input, "+_+");

    for (int i=0;i<20;i++) {
        arr[i].idx=i;
        arr[i].cnt=0;
        strcpy(arr[i].name, fruit[i]);
    }

    while (str!=NULL) {
        for (int i=0;i<20;i++) {
            if (!strcmp(arr[i].name, str)) {
                arr[i].cnt++;
                
                break;
            }
        } str=strtok(NULL, "+_+");
    }
    
    for (int i=0;i<20;i++) MAX=max(MAX, arr[i].cnt);
    for (int i=0;i<20;i++)
        if (arr[i].cnt==MAX)
            printf("%s\n", arr[i].name);
}
