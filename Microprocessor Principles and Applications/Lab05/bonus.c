#include "xc.h"

extern unsigned int mypow(unsigned int a, unsigned int b);

void main(void)
{
    volatile unsigned int res = mypow(5, 4);
    while (1)
        ;
    return;
}