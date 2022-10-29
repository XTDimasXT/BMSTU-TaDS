#ifndef __ADDITION_H__
#define __ADDITION_H__

#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "read.h"
#include "dynamic_matrix.h"
#include "random.h"
#include "operations.h"

int addition_common_matrix(void);
int addition_sparse_matrix(void);
void common_matrix_addition(matrix_t *matrix_a, matrix_t *matrix_b, matrix_t *matrix_res);
void sparse_matrix_addition(sparse_matrix_t *sparse_matrix_a, sparse_matrix_t *sparse_matrix_b, sparse_matrix_t *sparse_matrix_res);

#endif // __ADDITION_H__