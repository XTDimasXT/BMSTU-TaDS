#ifndef __QUEUE_ARRAY_H__
#define __QUEUE_ARRAY_H__

#include "structs.h"
#include "times.h"

#define COUNT 1000
#define INTERVAL 100
#define OVERFLOW_ERROR 2

void init_arr_queue(arr_t *queue);
void push_arr_queue(arr_t *queue, int elem);
void pop_arr_queue(arr_t *queue);
void print_arr_queue(arr_t queue);
int task_arr(void);
int clear_check_arr_queue(arr_t queue);
int overflow_arr_queue(arr_t queue);

#endif // __QUEUE_ARRAY_H__