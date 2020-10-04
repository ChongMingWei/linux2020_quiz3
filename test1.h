#ifndef TEST1_H
#define TEST1_H
#include <stdint.h>
/* macro using for different datatype input */
#define get_logical(datatype) (((datatype) -1) >> 1) > 0
#define get_fixu(logical, m) -(logical & (m < 0))
#define get_fix(datatype, fixu) (*(datatype *) &(fixu))
#define get_result(fix, m, n) (m >> n) | (fix ^ (fix>>n))
int asr_i(signed int m, unsigned int n);
#endif
