#ifndef __LIST_H__
#define __LIST_H__

#include "structs.h"
#include "read.h"
#include "print.h"

#include <stdio.h>
#include <stdlib.h>

int process_stack_as_list(void);
void free_stack_list(stack_list_t **stack_list);
int add_elems_list(stack_list_t **stack_list, int num_elems);
int fill_random_list(stack_list_t **stack_list, int num_elems);
int add_addresses_removed_elems(int num_elems, stack_list_t *stack_list, arr_free_area_t *arr);
void remove_elems_list(stack_list_t **stack_list, int num_elems);

#endif // __LIST_H__