#include "test2.h"

bool isPowerOfFour(int num)
{
    return num > 0 && (num & (num - 1))==0 && !(__builtin_ctz(num) & 0x1); //OPQ
}
