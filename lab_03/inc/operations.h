#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "errors.h"
#include "dynamic_matrix.h"
#include "print.h"

int find_num_nonzero_elems(sparse_matrix_t *sparse_matrix, int perc);
int convert_common_to_sparse(matrix_t *matrix);

#endif // __OPERATIONS_H__