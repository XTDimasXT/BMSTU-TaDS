#ifndef __DYNAMIC_MATRIX__
#define __DYNAMIC_MATRIX__

#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "errors.h"

int **allocate_matrix(int rows, int cols);
void free_matrix(int **data, int rows);
int create_common_matrix(matrix_t *matrix);

#endif // __DYNAMIC_MATRIX__