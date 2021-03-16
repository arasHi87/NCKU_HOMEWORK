void mul(struct Node* node_array , long long int * ans){
    for (int i=0;i<SIZE;node_array++, i++)
        *ans*=node_array->a;
}
