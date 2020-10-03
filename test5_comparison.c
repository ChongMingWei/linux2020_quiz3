#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main()
{
    struct timespec time1 = {0, 0};
    struct timespec time2 = {0, 0};
    long timediff = 0;
    long timediff2 = 0;
    char *density[] = {"BITMAP_DOT", "BITMAP_DASH", "BITMAP_DOTDASH", "BITMAP_LDASH", "BITMAP_DOTLDASH", "BITMAP_DOTDOT", "BITMAP_DOTDOTLDASH", "BITMAP_LLDASH"};
    uint64_t bitmap[] = {0xc0c0c0c0c0c0c0c0,//BITMAP_DOT
                         0xf0f0f0f0f0f0f0f0,//BITMAP_DASH
                         0xf0c0f0c0f0c0f0c0,//BITMAP_DOTDASH
                         0xfcfcfcfcfcfcfcfc,//BITMAP_LDASH
                         0xfc30fc30fc30fc30,//BITMAP_DOTLDASH
                         0xcccccccccccccccc,//BITMAP_DOTDOT
                         0xfcccfcccfcccfccc,//BITMAP_DOTDOTLDASH
                         0xfff0fff0fff0fff0};//BITMAP_LLDASH
    uint32_t *out1;
    out1 = malloc(sizeof(uint32_t)*1024);
    int pos = 0;
    for (int h = 0; h < 8; ++h){
        int pos = 0;
        printf("Test case %d (%s):\n", h, density[h]);
        printf("Original version:\n");
        clock_gettime(CLOCK_REALTIME, &time1);
        clock_gettime(CLOCK_REALTIME, &time1);

        for (int k = h; k < h + 1; ++k) {
            uint64_t bitset = bitmap[k];
            size_t p = k * 64;
            for (int i = 0; i < 64; i++) {
                if ((bitset >> i) & 0x1)
                    out1[pos++] = p + i;
            }
        }
        clock_gettime(CLOCK_REALTIME, &time2);
        timediff = (time2.tv_sec - time1.tv_sec)*1000000000 + time2.tv_nsec-time1.tv_nsec;
        printf("Result: %d\n", pos);
        printf("Time: %ld ns\n", timediff);
        pos = 0;
        printf("Modified version:\n");
        clock_gettime(CLOCK_REALTIME, &time1);

        for (int k = h; k < h + 1; ++k) {
            uint64_t bitset = bitmap[k];
            while (bitset != 0) {
                uint64_t t = bitset & -bitset;//KKK
                int r = __builtin_ctzll(bitset);
                out1[pos++] = k * 64 + r;
                bitset ^= t;                           
            }
        }   
        clock_gettime(CLOCK_REALTIME, &time2);
        timediff2 = (time2.tv_sec - time1.tv_sec)*1000000000 + time2.tv_nsec-time1.tv_nsec;
        printf("Result: %d\n", pos);
        printf("Time: %ld ns\n", timediff2);
        printf("Speed up: %fx\n", (float)timediff/(float)timediff2);
    }
    return 0;
}
