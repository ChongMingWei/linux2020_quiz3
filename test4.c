#include "test4.h"

uint64_t gcd64(uint64_t u, uint64_t v) 
{
    if (!u || !v) return u | v;
    while (v) {                               
        uint64_t t = v;
        v = u % v;
        u = t;
    }
    return u;
}

uint64_t gcd64_modified(uint64_t u, uint64_t v) 
{
    if (!u || !v) return u | v;
    int shift;
    for (shift = 0; !((u | v) & 1); shift++) {
        u /= 2, v /= 2;
    }
    while (!(u & 1))
        u /= 2;
    do {
        while (!(v & 1))
            v /= 2;
        if (u < v) {
            v -= u;
        } else {
            uint64_t t = u - v;
            u = v;
            v = t;
        }
    } while (v); //XXX
    return u<<shift; //YYY
}

uint64_t gcd64_improved(uint64_t u, uint64_t v)
{
    if (!u || !v) return u | v;
    int shift;
    shift = __builtin_ctz(u) > __builtin_ctz(v)?__builtin_ctz(v):__builtin_ctz(u);
    u >>= shift;
    v >>= shift;
    
    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if (u < v) {
            v -= u;
        } else {
            uint64_t t = u - v;
            u = v;
            v = t;
        }
    } while (v);
    return u<<shift;    
}

