#ifndef __READ_H__
#define __READ_H__

#include "errors.h"
#include "array.h"

#include <stdio.h>
#include <stdlib.h>

int read_method(int *method);
int read_action_arr(int *action);
int read_action_list(int *action);
int read_action_time(int *action);
int read_num_elems_add_array(int *num_elems, int len);
int read_num_elems_remove_array(int *num_elems, int len);
int read_num_elems_add_list(int *num_elems, stack_list_t *stack_list);
int read_num_elems_remove_list(int *num_elems, stack_list_t *stack_list);

#endif // __READ_H__