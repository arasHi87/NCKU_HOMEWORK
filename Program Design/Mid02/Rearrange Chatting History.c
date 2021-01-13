int cmp(const void* a, const void* b) {
    int a_h = ((struct message_info*)a)->time.hour;
    int a_m = ((struct message_info*)a)->time.minute;
    int b_h = ((struct message_info*)b)->time.hour;
    int b_m = ((struct message_info*)b)->time.minute;  
    

    if (a_h!=b_h) return a_h-b_h;
    return a_m-b_m;
}

void sort_message(struct message_info *m, int *total) {
// m is array of each message information wrapped in a struct
// total is the number of total message
    qsort(m, *total, sizeof(struct message_info), cmp);
}
