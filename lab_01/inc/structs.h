#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <stdio.h>

#include "constants.h"

typedef struct
{
    char mantissa[MANTISSA_LEN + 1];
    size_t mantissa_len;
    int exponent;
    int is_negative;
} big_float_t;

typedef struct
{
    char mantissa[MANTISSA_LEN + 1];
    size_t mantissa_len;
    int is_negative;
} big_int_t;

#endif // __STRUCTS_H__