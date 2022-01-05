#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 1007
#define SIZE 2
#define GET_CHILD(i) p->next[key[i] - '0']

typedef struct node {
    int cnt, val;
    char str[maxN];
    struct node* next[SIZE];
} Node;

Node* init()
{
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->cnt = 1;
    memset(tmp->str, 0, sizeof(tmp->str));
    memset(tmp->next, 0, sizeof(tmp->next));
    return tmp;
}

int search(Node* root, char* key)
{
    int i = 0, x, y;
    Node* p = root;
    while (key[i]) {
        if (GET_CHILD(i)) {
            x = 0, y = i;
            while (key[y] && GET_CHILD(i)->str[x] && key[y] == GET_CHILD(i)->str[x])
                x++, y++;
            if (!key[y] && GET_CHILD(i)->cnt)
                return GET_CHILD(i)->val;
            else if (GET_CHILD(i)->str[x])
                return 0;
        } else
            return 0;
        p = GET_CHILD(i), i = y;
    }
    return 0;
}

void insert(Node* root, char* key, int val)
{
    int i = 0, x, y;
    Node* p = root;
    while (key[i]) {
        if (GET_CHILD(i)) {
            x = 0, y = i, GET_CHILD(i)->cnt++;
            while (key[y] && GET_CHILD(i)->str[x] && key[y] == GET_CHILD(i)->str[x])
                x++, y++;
            if (GET_CHILD(i)->str[x]) {
                Node* tmp = init();
                memcpy(tmp->str, (GET_CHILD(i)->str) + x, strlen((GET_CHILD(i)->str + x)) + 1);
                memcpy(tmp->next, GET_CHILD(i)->next, sizeof(GET_CHILD(i)->next));
                memset(GET_CHILD(i)->next, 0, sizeof(GET_CHILD(i)->next));
                tmp->cnt = GET_CHILD(i)->cnt - 1;
                tmp->val = GET_CHILD(i)->val;
                GET_CHILD(i)->next[GET_CHILD(i)->str[x] - '0'] = tmp;
                GET_CHILD(i)->str[x] = 0;
            }
        } else {
            GET_CHILD(i) = init();
            GET_CHILD(i)->val = val;
            memcpy(GET_CHILD(i)->str, key + i, strlen(key + i) + 1);
            return;
        }
        p = GET_CHILD(i), i = y;
    }
}

int destroy(Node* root, char* key)
{
    int i = 0, x, y;
    Node* p = root;
    while (key[i]) {
        if (GET_CHILD(i)) {
            x = 0, y = i;
            while (key[y] && GET_CHILD(i)->str[x] && key[y] == GET_CHILD(i)->str[x])
                x++, y++;
            if (!key[y]) {
                GET_CHILD(i)->cnt--;
                if (!GET_CHILD(i)->cnt)
                    GET_CHILD(i)->str[0] = -1;
                return GET_CHILD(i)->val;
            } else if (GET_CHILD(i)->str[x])
                return 0;
        } else
            return 0;
        p = GET_CHILD(i), i = y;
    }
    return 0;
}

int main()
{
    int n, tmp;
    char key[maxN];
    Node* root = init();
    scanf("%d", &n);
    while (~scanf("%s", key)) {
        if (!strcmp(key, "insert")) {
            scanf("%s%d", key, &n);
            if (search(root, key))
                puts("insert -> conflict");
            else
                insert(root, key, n), printf("insert -> %d\n", n);
        } else if (!strcmp(key, "search")) {
            scanf("%s", key), tmp = search(root, key);
            if (tmp)
                printf("search -> %d\n", tmp);
            else
                puts("search -> not found");
        } else if (!strcmp(key, "delete")) {
            scanf("%s", key), tmp = destroy(root, key);
            if (tmp)
                printf("delete -> %d\n", tmp);
            else
                puts("delete -> not found");
        }
    }
}