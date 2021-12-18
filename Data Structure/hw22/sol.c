#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key, val, degree;
    char mark, c;
    struct Node *parent, *child, *left, *right;
} Node;

Node* mini = NULL;
int no_of_nodes = 0;

void insert(int val, int key)
{
    Node* new = (Node*)malloc(sizeof(Node));
    new->key = key;
    new->val = val;
    new->degree = 0;
    new->mark = 'W';
    new->c = 'N';
    new->parent = NULL;
    new->child = NULL;
    new->left = new;
    new->right = new;
    if (mini != NULL) {
        (mini->left)->right = new;
        new->right = mini;
        new->left = mini->left;
        mini->left = new;
        if (new->key < mini->key)
            mini = new;
    } else {
        mini = new;
    }
    no_of_nodes++;
}

void link(Node* ptr2, Node* ptr1)
{
    (ptr2->left)->right = ptr2->right;
    (ptr2->right)->left = ptr2->left;
    if (ptr1->right == ptr1)
        mini = ptr1;
    ptr2->left = ptr2;
    ptr2->right = ptr2;
    ptr2->parent = ptr1;
    if (ptr1->child == NULL)
        ptr1->child = ptr2;
    ptr2->right = ptr1->child;
    ptr2->left = (ptr1->child)->left;
    ((ptr1->child)->left)->right = ptr2;
    (ptr1->child)->left = ptr2;
    if (ptr2->key < (ptr1->child)->key)
        ptr1->child = ptr2;
    ptr1->degree++;
}

void consolidate()
{
    int tmp1;
    float tmp2 = (log(no_of_nodes)) / (log(2));
    int tmp3 = tmp2;
    Node* arr[tmp3 + 1];
    for (int i = 0; i <= tmp3; i++)
        arr[i] = NULL;
    Node* ptr1 = mini;
    Node* ptr2;
    Node* ptr3;
    Node* ptr4 = ptr1;
    do {
        ptr4 = ptr4->right;
        tmp1 = ptr1->degree;
        while (arr[tmp1] != NULL) {
            ptr2 = arr[tmp1];
            if (ptr1->key > ptr2->key) {
                ptr3 = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr3;
            }
            if (ptr2 == mini)
                mini = ptr1;
            link(ptr2, ptr1);
            if (ptr1->right == ptr1)
                mini = ptr1;
            arr[tmp1] = NULL;
            tmp1++;
        }
        arr[tmp1] = ptr1;
        ptr1 = ptr1->right;
    } while (ptr1 != mini);
    mini = NULL;
    for (int j = 0; j <= tmp3; j++) {
        if (arr[j] != NULL) {
            arr[j]->left = arr[j];
            arr[j]->right = arr[j];
            if (mini != NULL) {
                (mini->left)->right = arr[j];
                arr[j]->right = mini;
                arr[j]->left = mini->left;
                mini->left = arr[j];
                if (arr[j]->key < mini->key)
                    mini = arr[j];
            } else {
                mini = arr[j];
            }
            if (mini == NULL)
                mini = arr[j];
            else if (arr[j]->key < mini->key)
                mini = arr[j];
        }
    }
}

void extract(int* val, int* key)
{
    if (mini == NULL)
        ;
    else {
        *val = mini->val;
        *key = mini->key;
        Node* tmp = mini;
        Node* pntr;
        pntr = tmp;
        Node* x = NULL;
        if (tmp->child != NULL) {

            x = tmp->child;
            do {
                pntr = x->right;
                (mini->left)->right = x;
                x->right = mini;
                x->left = mini->left;
                mini->left = x;
                if (x->key < mini->key)
                    mini = x;
                x->parent = NULL;
                x = pntr;
            } while (pntr != tmp->child);
        }
        (tmp->left)->right = tmp->right;
        (tmp->right)->left = tmp->left;
        mini = tmp->right;
        if (tmp == tmp->right && tmp->child == NULL)
            mini = NULL;
        else {
            mini = tmp->right;
            consolidate();
        }
        no_of_nodes--;
    }
}

void cut(Node* found, Node* tmp)
{
    if (found == found->right)
        tmp->child = NULL;

    (found->left)->right = found->right;
    (found->right)->left = found->left;
    if (found == tmp->child)
        tmp->child = found->right;

    tmp->degree = tmp->degree - 1;
    found->right = found;
    found->left = found;
    (mini->left)->right = found;
    found->right = mini;
    found->left = mini->left;
    mini->left = found;
    found->parent = NULL;
    found->mark = 'B';
}

void cascaseCut(Node* tmp)
{
    Node* ptr5 = tmp->parent;
    if (ptr5 != NULL) {
        if (tmp->mark == 'W') {
            tmp->mark = 'B';
        } else {
            cut(tmp, ptr5);
            cascaseCut(ptr5);
        }
    }
}

void decrease(Node* found, int val)
{
    found->key = val;
    Node* tmp = found->parent;
    if (tmp != NULL && found->key < tmp->key) {
        cut(found, tmp);
        cascaseCut(tmp);
    }
    if (found->key < mini->key)
        mini = found;
}

void find(Node* mini, int old_key, int key, int val)
{
    Node* found = NULL;
    Node* tmp5 = mini;
    tmp5->c = 'Y';
    Node* found_ptr = NULL;
    if (tmp5->key == old_key && tmp5->val == val) {
        found_ptr = tmp5;
        tmp5->c = 'N';
        found = found_ptr;
        decrease(found, key);
    }
    if (found_ptr == NULL) {
        if (tmp5->child != NULL)
            find(tmp5->child, old_key, key, val);
        if ((tmp5->right)->c != 'Y')
            find(tmp5->right, old_key, key, val);
    }
    tmp5->c = 'N';
    found = found_ptr;
}

void destroy(int val, int key)
{
    if (mini == NULL)
        ;
    else {
        int old_key = key;
        Node* del = NULL;
        for (Node* ptr = mini->right; ptr != mini; ptr = ptr->right) {
            if (ptr->key == key && ptr->val == val && ptr->child == NULL)
                del = ptr;
        }

        if (del) {
            del->left->right = del->right;
            del->right->left = del->left;
        } else {
            find(mini, key, -99999, val);
            int key, val;
            extract(&val, &key);
        }
    }
}

int x, y, z;
char opt[20];

int main()
{
    while (~scanf("%s", opt)) {
        if (!strcmp(opt, "insert"))
            scanf("%d%d", &x, &y), insert(y, x);
        else if (!strcmp(opt, "delete"))
            scanf("%d%d", &x, &y), destroy(y, x);
        else if (!strcmp(opt, "decrease"))
            scanf("%d%d%d", &x, &y, &z), find(mini, x, x - z, y);
        else if (!strcmp(opt, "extract") && mini)
            extract(&y, &x), printf("(%d)%d\n", x, y);
    }
}