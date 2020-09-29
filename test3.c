#include "test3.h"

int numberOfSteps (int num)
{
    // If num == 0, directly return. Otherwise, count the number of steps
    // https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/
    return num ? __builtin_popcount(num) + 31 - __builtin_clz(num) : 0; //AAA BBB
}
