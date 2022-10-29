#ifndef __TIMES_H__
#define __TIMES_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "struct.h"
#include "dynamic_matrix.h"
#include "errors.h"
#include "random.h"
#include "addition.h"

unsigned long long milliseconds_now(void);
int test_time(int perc, int len);
int print_stats(void);

#endif // __TIMES_H__