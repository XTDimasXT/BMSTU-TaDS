#ifndef __QUEUE_LIST_H__
#define __QUEUE_LIST_H__

#include "structs.h"
#include "times.h"

#define T1_IN_B 1
#define T1_IN_E 5
#define T2_IN_B 0
#define T2_IN_E 3
#define T1_OUT_B 0
#define T1_OUT_E 4
#define T2_OUT_B 0
#define T2_OUT_E 1

#define COUNT 1000
#define INTERVAL 100
#define OK_PUSH 0
#define ERR_ALLOCATE_MEMORY 5

void init_list_queue(list_t *queue);
void push_list_queue(list_t *queue, int elem);
void pop_list_queue(list_t *queue);
void print_list_queue(list_t queue);
void free_list(list_t *queue);
void add_adress(arr_clear_t *arr, list_t *list);
void print_arr_adress(arr_clear_t arr);
void del_adress(arr_clear_t *arr, list_t *list);
void task_list(void);
int clear_check_list(list_t queue);

#endif // __QUEUE_LIST_H__