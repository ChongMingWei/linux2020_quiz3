#include "test4.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    int test_cnt = 1000;
    long timediff1 = 0, timediff2 = 0, timediff3 = 0;
    for(int i = 0; i < test_cnt; ++i){
        struct timespec time1 = {0, 0};
        struct timespec time2 = {0, 0};
        clock_gettime(CLOCK_REALTIME, &time1);
        uint64_t max = 0xffffffffffffffff;
        uint64_t a = rand() % max;
        uint64_t b = rand() % max;
        uint64_t result;
        clock_gettime(CLOCK_REALTIME, &time1);
        result = gcd64(a,b);    
        clock_gettime(CLOCK_REALTIME, &time2);
        
        timediff1 += (time2.tv_sec - time1.tv_sec)*1000000000 + time2.tv_nsec-time1.tv_nsec;
        //printf("%lu time: %ld ns\n", result, timediff1);
    
        clock_gettime(CLOCK_REALTIME, &time1);
        result = gcd64_modified(a,b);
        clock_gettime(CLOCK_REALTIME, &time2);
        
        timediff2 += (time2.tv_sec - time1.tv_sec)*1000000000 + time2.tv_nsec-time1.tv_nsec;
        //printf("%lu time: %ld ns\n", result, timediff2);

        clock_gettime(CLOCK_REALTIME, &time1);
        result = gcd64_improved(a,b);
        clock_gettime(CLOCK_REALTIME, &time2);
        
        timediff3 += (time2.tv_sec - time1.tv_sec)*1000000000 + time2.tv_nsec-time1.tv_nsec;
        //printf("%lu time: %ld ns\n", result, timediff3);
    }
    
    printf("gcd64: time=%ld ns\ngcd64_modified: time=%ld ns\ngcd64_improved: time= %ld ns\n", timediff1/1000, timediff2/1000, timediff3/1000);
    return 0;
}

