int top=0, stk[2500000];

int get_type(const char* good_type) {
    for (int i=0;i<3;i++)
        if (!strcmp(good_type, good_types[i]))
            return i;
    return 87;
}

void *produce(void *top_of_stack, const char *good_type, const size_t count){
    int type=get_type(good_type), cnt=count;
	
	while (cnt--) stk[top++]=type;
}

void *consume(void *top_of_stack, const size_t count){
    top-=count;
}

void list_remain(void *top_of_stack){
    int cnt=0, tmp=stk[top-1];
    
    if (top) {
        for (int i=top-1;i>=0;i--) {
            if (!i || tmp!=stk[i-1]) {
                printf("%s x %d\n", good_types[tmp], cnt+1);

                cnt=0, tmp=stk[i-1];
            } else cnt++;
        }
    } else puts("Empty");
}
