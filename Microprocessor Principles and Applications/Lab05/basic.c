#include "xc.h"

extern unsigned int isprime(unsigned int a);

void main(void)
{
    volatile unsigned int res = isprime(29);
    while (1)
        ;
    return;
}