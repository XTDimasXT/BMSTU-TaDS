#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include "constants.h"
#include "errors.h"
#include "structs.h"

void reverse_mantissa(char mant[], size_t len);
void big_float_remove_leading_zeroes(big_float_t *num);
void big_int_remove_leading_zeroes(big_int_t *num);
void big_float_print(big_float_t num);
int big_float_equal(big_float_t l, big_float_t r);
int big_nums_equal(big_int_t l, big_float_t r);
int big_nums_less(big_float_t l, big_float_t r);
void big_float_round(big_float_t *l);
void big_float_strip_zeroes(big_float_t *num);
big_float_t multiply_big_float_num(big_float_t l, char r);
big_float_t big_float_substract(big_float_t l, big_float_t r);
void big_float_shift_right(big_float_t *num);
void big_int_shift_right(big_int_t *num);
int big_nums_divide(big_int_t l, big_float_t r, big_float_t *result);

#endif // __OPERATIONS_H__