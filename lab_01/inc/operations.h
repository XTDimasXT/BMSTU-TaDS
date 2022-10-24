#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

void normalize(float_t *a);
int pre_division(int a_res[], int b[], int a_len, int b_len);
void division(float_t *a, integer_t b, int b_len, float_t *res);
void round_res(float_t *a);
void print_res(float_t a);
void print_integer(integer_t b, int int_len);

#endif // __OPERATIONS_H__