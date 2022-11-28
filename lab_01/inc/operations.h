#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include "constants.h"
#include "errors.h"
#include "structs.h"

void print_borders();
void multiplication(num_t *num1, num_t *num2, num_t *res);
void rounding(num_t *num, int n);
void swap_right(int arr[ARR_LEN], int n);
void init_num(num_t *num);
void remove_zeroes(num_t *num);
void print_res(num_t *num);
void print_error(int error);

#endif // __OPERATIONS_H__