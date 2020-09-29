#include "test1.h"

int asr_i(signed int m, unsigned int n)
{
    // Check if the compiler supports arithmetic right shift
    const int logical = (((int) -1) >>1) > 0;//OP1
    // To get 0xffffffff for the bit reverse
    unsigned int fixu = -(logical & (m<0));//OP2
    int fix = *(int *) &fixu;
    return (m >> n) | (fix ^ (fix >> n));
}
