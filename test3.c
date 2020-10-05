#include "test3.h"

int numberOfSteps (int num)
{
    // If num == 0, directly return. Otherwise, count the number of steps
    // https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/
    return num ? __builtin_popcount(num) + 31 - __builtin_clz(num) : 0; //AAA BBB
}
int numberOfSteps_m (int num)
{
    /* Compute population count */
    uint32_t popcount = num;
    uint32_t tmp;
    tmp = (popcount>>1)&0x77777777;
    popcount -= tmp;
    tmp = (tmp>>1)&0x77777777;
    popcount -= tmp;
    tmp = (tmp>>1)&0x77777777;
    popcount -= tmp;

    popcount += (popcount >> 4);
    popcount &= 0x0f0f0f0f;
    popcount *= 0x01010101;
    popcount >>= 24;
    /* Compute clz */
    uint32_t n = 32, c = 16, l, r = num;
    do {
        l = r >> c;
        if (l) { 
            n -= c; 
            r = l; 
        }
        c >>= 1;
    } while (c);
    
    return num ? popcount + 31 - (n - r) : 0; //AAA BBB
}

int numberOfSteps_branchless (int num)
{
    int numofminus=0;//要做-1的次數
    int numofdiv=0;
    while(num){
        int isodd = num&0x1;//確認目前 bit0 是否為1
        int iseven = (num&0x1)^0x1;//確認目前 bit0 是否為0
        numofminus += isodd;
        numofdiv += iseven;
        num -= (isodd-iseven)>0;//是奇數做-1
        num >>= (iseven-isodd)>0;//是偶數做/2
    }
    return numofminus+numofdiv;
}
