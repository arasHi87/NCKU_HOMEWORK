#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    struct Node* next;
    float e, c;
} * nodes[5];

float x;
int n, t, idx;
char str1[15], str2[15], str3[15];

struct Node* read()
{
    struct Node *head = malloc(sizeof(struct Node)), *s = head;
    head->next = NULL;
    while (t--) {
        scanf("%f%f", &s->c, &s->e);
        if (t) {
            s->next = malloc(sizeof(struct Node));
            s = s->next;
        } else {
            s->next = NULL;
        }
    }
    puts("ok");
    return head;
}

void write(struct Node* head)
{
    while (head->next) {
        printf("%0.fx^%0.f", head->c, head->e);
        head = head->next;
        if (head->c >= 0)
            printf("+");
    }
    printf("%0.fx^%0.f\n", head->c, head->e);
}

struct Node* add(struct Node* a, struct Node* b)
{
    struct Node* head = malloc(sizeof(struct Node));
    head->next = NULL;
    struct Node *p1 = a, *p2 = b, *tmp, *last = head;
    while (p1 && p2) {
        tmp = malloc(sizeof(struct Node));
        tmp->next = NULL;
        if (p1->e > p2->e) {
            tmp->c = p1->c;
            tmp->e = p1->e;
            p1 = p1->next;
        } else if (p1->e < p2->e) {
            tmp->c = p2->c;
            tmp->e = p2->e;
            p2 = p2->next;
        } else {
            tmp->c = p1->c + p2->c;
            tmp->e = p1->e;
            if (!tmp->c)
                tmp = NULL;
            p1 = p1->next;
            p2 = p2->next;
        }
        if (tmp) {
            last->next = tmp;
            last = last->next;
        }
    }
    if (p1 && p1->c)
        last->next = p1;
    if (p2 && p2->c)
        last->next = p2;

    return head->next;
}

void sub(struct Node* r, struct Node* a, struct Node* b)
{
    while (a) {
        r->c = a->c - b->c;
        r->e = a->e;
        a = a->next, b = b->next;
        if (a) {
            r->next = malloc(sizeof(struct Node));
            r = r->next;
        } else {
            r->next = NULL;
        }
    }
    puts("substracted");
}

struct Node* smul(struct Node* a, struct Node* b)
{
    struct Node* head = malloc(sizeof(struct Node));
    head->next = NULL;
    struct Node *p1 = a, *p2 = b, *tmp, *last = head;
    while (p2) {
        tmp = malloc(sizeof(struct Node));
        tmp->next = NULL;
        tmp->c = p1->c * p2->c;
        tmp->e = p1->e + p2->e;
        last->next = tmp;
        last = last->next;
        p2 = p2->next;
    }
    return head->next;
}

struct Node* mul(struct Node* a, struct Node* b)
{
    struct Node *head = malloc(sizeof(struct Node)), *tmp;
    head->next = NULL;

    for (struct Node *p1 = a, *p2 = b; p1; p1 = p1->next) {
        tmp = smul(p1, p2);
        head = add(head, tmp);
    }
    puts("multiplied");
    return head;
}

float eval(struct Node* a, float x)
{
    float sum = 0.0;
    while (a) {
        sum += (a->c * powf(x, a->e));
        a = a->next;
    }
    return sum;
}

int main()
{
    scanf("%d", &n);
    while (n--) {
        scanf("%s", str1);
        if (!strcmp(str1, "pread")) {
            scanf("%s%d", str1, &t), idx = str1[10] - 'A';
            nodes[idx] = read();
        } else if (!strcmp(str1, "pwrite")) {
            scanf("%s", str1);
            if (str1[0] == 'e')
                write(nodes[str1[10] - 'A']);
            else
                write(nodes[str1[6] - 'A']);
        } else if (!strcmp(str1, "padd")) {
            scanf("%s%s%s", str1, str2, str3);
            nodes[str1[6] - 'A'] = add(nodes[str2[10] - 'A'], nodes[str3[10] - 'A']);
            puts("added");
        } else if (!strcmp(str1, "perase")) {
            scanf("%s", str1);
            nodes[str1[6] - 'A'] = malloc(sizeof(struct Node));
            nodes[str1[6] - 'A']->next = NULL;
            puts("erased");
        } else if (!strcmp(str1, "psub")) {
            scanf("%s%s%s", str1, str2, str3);
            nodes[str1[6] - 'A'] = malloc(sizeof(struct Node));
            sub(nodes[str1[6] - 'A'], nodes[str2[10] - 'A'], nodes[str3[10] - 'A']);
        } else if (!strcmp(str1, "pmult")) {
            scanf("%s%s%s", str1, str2, str3);
            nodes[str1[6] - 'A'] = mul(nodes[str2[10] - 'A'], nodes[str3[10] - 'A']);
        } else {
            scanf("%s%f", str1, &x);
            printf("%0.2f", eval(nodes[str1[6] - 'A'], x));
        }
    }
}