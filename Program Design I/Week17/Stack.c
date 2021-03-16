void push(struct head *stack_p, int data) {     // create an element and push it to the top of the stack
    struct element* tmp=(struct element*)malloc(sizeof(struct element));
    
    tmp->data=data;
    tmp->next=NULL;
    stack_p->size+=1;

    if (stack_p->next) {
        stack_p->top->next=tmp;
        stack_p->top=tmp;
    } else {
        stack_p->top=tmp;
        stack_p->next=tmp;
    }
}

struct element* pop(struct head *stack_p) {     // return the element which is popped from the stack
    struct element* tmp=stack_p->top;
    struct element* meow=(struct element*)malloc(sizeof(struct element));
    
    tmp=stack_p->top;
    stack_p->size-=1;

    if (!stack_p->size) {
        stack_p->top=NULL;
        stack_p->next=NULL;
    } else {
        meow=stack_p->next;

       while (meow->next!=stack_p->top)
           meow=meow->next;
        
       meow->next=NULL;
       stack_p->top=meow;
    }

    return tmp;
}
