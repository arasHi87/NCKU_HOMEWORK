#include "xc.h"

extern unsigned int divide_signed(unsigned char a, unsigned char b);

void main(void)
{
    volatile unsigned int res = divide_signed(-20, -4);
    volatile char quotient = (unsigned char)(res >> 8);
    volatile char remainder = (unsigned char)((res << 8) >> 8);
    while (1)
        ;
    return;
}