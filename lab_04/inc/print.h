#ifndef __PRINT_H__
#define __PRINT_H__

#include "array.h"

#include <stdio.h>
#include <stdlib.h>

void print_menu_arr(void);
void print_menu_list(void);
void print_menu_time(void);
void print_choice(void);
void print_array(stack_array_t *stack_array);
void print_series_nums_array(stack_array_t *stack_array);
void print_list(stack_list_t **stack_list);
void print_series_nums_list(stack_list_t *stack_list);
void print_addresses_array(arr_del_adresses_t *arr);

#endif // __PRINT_H__