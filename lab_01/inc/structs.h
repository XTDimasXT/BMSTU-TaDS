#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "constants.h"

typedef struct
{
	char sign;
	int mantissa[MANTISSA_LEN + 1];
    int order;
} float_t;

typedef struct
{
	char sign;
	int digits[MANTISSA_LEN];
} integer_t;

#endif // __STRUCTS_H__