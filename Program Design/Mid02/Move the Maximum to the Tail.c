void MoveToTail() {
    int max=0;
    struct node* temp=(struct node*)malloc(sizeof(struct node));

    temp->next=head, temp->val=-1, head=temp;

    for(struct node* cur = head; cur != NULL; cur = cur->next)
        if (cur->next && cur->next->val>max) max=cur->next->val, temp=cur;

    tail->next=temp->next;
    temp->next=temp->next->next;
    tail->next->next=NULL;
    tail=tail->next;
    head=head->next;
}

