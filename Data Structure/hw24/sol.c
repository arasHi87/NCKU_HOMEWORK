#include "avl.c"
#include "rbt.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char opt[20];

int main()
{
    int x;
    scanf("%s", opt);
    if (!strcmp(opt, "red_black")) {
        RBTNode* tmp;
        RBTInitTree();
        while (~scanf("%s", opt)) {
            if (!strcmp(opt, "insert")) {
                scanf("%d", &x), RBTInsert(x);
            } else if (!strcmp(opt, "search")) {
                scanf("%d", &x), tmp = RBTSearch(x);
                if (tmp && tmp != neel)
                    (tmp->color == 1) ? puts("black") : puts("red");
                else
                    puts("Not found");
            } else if (!strcmp(opt, "delete")) {
                scanf("%d", &x), RBTDelete(x);
            } else if (!strcmp(opt, "exist")) {
                scanf("%d", &x), tmp = RBTSearch(x);
                (tmp && tmp != neel) ? puts("exist") : puts("Not exist");
            } else
                return 0;
        }
        // } else {
        //     NODE root = NULL;
        //     while (~scanf("%s", opt)) {
        //         if (!strcmp(opt, "insert")) {
        //             scanf("%d", &x), insert(root, x);
        //         } else if (!strcmp(opt, "search")) {
        //             scanf("%d", &x), avlsearch(root, x);
        //         } else if (!strcmp(opt, "delete")) {
        //             scanf("%d", &x), destroy(root, x);
        //         } else if (!strcmp(opt, "exist")) {
        //             scanf("%d", &x), exist(root, x);
        //         } else
        //             return 0;
        //     }
    }
}