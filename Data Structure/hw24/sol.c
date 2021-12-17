#include "avl.c"
#include "rbt.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int idx = 0;
char opt[20];

int main()
{
    int x;
    scanf("%s", opt);
    if (!strcmp(opt, "red_black")) {
        RBT tmp;
        neel = (RBT)malloc(sizeof(struct rbt));
        neel->color = 1;
        neel->left = NULL;
        neel->right = NULL;
        neel->parent = NULL;
        root = neel;
        root->parent = neel;
        while (~scanf("%s", opt)) {
            // printf("%s\n", opt);
            if (!strcmp(opt, "insert")) {
                scanf("%d", &x), toInsert(x);
            } else if (!strcmp(opt, "search")) {
                scanf("%d", &x), tmp = search(x);
                if (tmp && tmp != neel) {
                    if (tmp->color == 1)
                        puts("black");
                    else
                        puts("red");
                } else
                    puts("Not found");
            } else if (!strcmp(opt, "delete")) {
                scanf("%d", &x), deleteRBT(x);
            } else if (!strcmp(opt, "exist")) {
                scanf("%d", &x), tmp = search(x);
                if (tmp && tmp != neel) {
                    puts("exist");
                } else
                    puts("Not exist");
            } else
                return 0;
        }
    } else {
        AVL root = NULL;
        while (~scanf("%s", opt)) {
            if (!strcmp(opt, "insert")) {
                scanf("%d", &x), root = insert(root, x);
            } else if (!strcmp(opt, "search")) {
                scanf("%d", &x), getF(root, x);
            } else if (!strcmp(opt, "delete")) {
                scanf("%d", &x), root = deleteAVL(root, x);
            } else if (!strcmp(opt, "exist")) {
                scanf("%d", &x), findKey(root, x);
            } else
                return 0;
        }
    }
}