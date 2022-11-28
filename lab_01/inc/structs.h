#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "constants.h"

typedef struct 
{
    char sign;
    int mantissa[ARR_LEN];
    size_t size;
    int order;
} num_t;

#endif // __STRUCTS_H__