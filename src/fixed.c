/*
 * Twin - A Tiny Window System
 * Copyright © 2004 Keith Packard <keithp@keithp.com>
 * All rights reserved.
 */

#include "twinint.h"

#define uint32_lo(i) ((i) & 0xffff)
#define uint32_hi(i) ((i) >> 16)
#define uint32_carry16 ((1) << 16)

twin_fixed_t twin_fixed_sqrt(twin_fixed_t a)
{
    twin_fixed_t max, min, mid;
    twin_fixed_t sqr;

    max = a;
    min = 0;
    while (max > min) {
        mid = (max + min) >> 1;
        if (mid >= 181 * TWIN_FIXED_ONE) {
            max = mid - 1;
            continue;
        }
        sqr = twin_fixed_mul(mid, mid);
        if (sqr == a)
            return mid;
        if (sqr < a)
            min = mid + 1;
        else
            max = mid - 1;
    }
    return (max + min) >> 1;
}

twin_sfixed_t _twin_sfixed_sqrt(twin_sfixed_t as)
{
    twin_dfixed_t max = as, min = 0, mid;
    twin_dfixed_t a = twin_sfixed_to_dfixed(as);
    twin_dfixed_t sqr;

    while (max > min) {
        mid = (max + min) >> 1;
        sqr = mid * mid;
        if (sqr == a)
            return (twin_sfixed_t) mid;
        if (sqr < a)
            min = mid + 1;
        else
            max = mid - 1;
    }
    return (twin_sfixed_t) ((max + min) >> 1);
}