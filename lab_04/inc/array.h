#ifndef __ARRAY_H__
#define __ARRAY_h__

#include "structs.h"
#include "read.h"
#include "print.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int process_stack_as_array(void);
int add_elems_array(int num_elems, stack_array_t *stack_array);
void fill_random_array(int num_elems, stack_array_t *stack_array);
void remove_elems_array(int num_elems, stack_array_t *stack_array);

#endif // __ARRAY_H__