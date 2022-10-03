#ifndef __FUNC_H__
#define __FUNC_H__

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define LEN_NUMBER 100
#define MANTISS_SIZE 31
#define MAX_POWER 99999

#define SCAN_ERROR 1
#define MANTISSA_ERROR 2

typedef struct
{
	char sign;
	short mantissa[MANTISS_SIZE];
    unsigned short position;
    unsigned int order;
} number_t;

#endif __FUNC_H__