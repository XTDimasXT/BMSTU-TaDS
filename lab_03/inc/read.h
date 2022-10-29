#ifndef __READ_H__
#define __READ_H__

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "print.h"
#include "struct.h"

int read_num_command(int *num_command);
int read_num_rows_and_columns(int *rows, int *cols);
int read_mode_input_common_matrix(int *mode, int *perc);
int read_full_matrix(matrix_t *matrix);
int read_nonzero_elems(matrix_t *matrix);
int read_mode_input_sparse_matrix(int *mode, int *perc);
int read_sparse_matrix(sparse_matrix_t *sparse_matrix);
int read_num_nonzero_elems(sparse_matrix_t *sparse_matrix);
int find_num_nonzero_elems(sparse_matrix_t *sparse_matrix, int perc);

#endif // __READ_H__