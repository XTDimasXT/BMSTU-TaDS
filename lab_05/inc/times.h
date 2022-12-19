#ifndef __TIMES_H__
#define __TIMES_H__

#include <inttypes.h>

#include "print.h"
#include "queue_array.h"
#include "queue_list.h"
#include "structs.h"

#define RUNS 1000
#define HZ 2900

#define T1_IN_B 1
#define T1_IN_E 5
#define T2_IN_B 0
#define T2_IN_E 3
#define T1_OUT_B 0
#define T1_OUT_E 4
#define T2_OUT_B 0
#define T2_OUT_E 1

uint64_t tick(void);
float rand_time(int min, int max);
void print_time(int64_t start1, int64_t end1, int64_t start2, int64_t end2);
int create_rand_num(void);
void time_add(int count);
void time_del(int count);
void time_counting(void);

#endif // __TIMES_H__