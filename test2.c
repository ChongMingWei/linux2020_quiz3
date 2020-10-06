#include "test2.h"

bool isPowerOfFour(int num)
{
    return num > 0 && (num & (num - 1))==0 && !(__builtin_ctz(num) & 0x1); //OPQ
}

bool isPowerOfFour_m(int num)
{
    return num > 0 && __builtin_popcount(num)==1 && (num&0x55555555);
}

int bitwiseComplement(int N)
{  
    return N==0?1:~N&~((0xfffffffe) << (31-__builtin_clz(N))); 
}

int firstMissingPositive(int* nums, int numsSize){
    int *tmp = malloc(sizeof(int)*numsSize);
    for (int i = 0;i < numsSize; ++i){
        if(nums[i]>0&&nums[i]<=numsSize)
            tmp[nums[i]-1] = 1;
    }
    for (int i = 0;i < numsSize; ++i){
        if(tmp[i]!=1)
            return i+1;
    }
    return numsSize+1;
}
