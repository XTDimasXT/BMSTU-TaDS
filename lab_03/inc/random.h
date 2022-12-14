#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "errors.h"
#include "dynamic_matrix.h"

int random_common_matrix(matrix_t *matrix, int perc);
int random_sparse_matrix(sparse_matrix_t *sparse_matrix, int perc);

#endif // __RANDOM_H__