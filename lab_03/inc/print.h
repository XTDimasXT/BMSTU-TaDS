#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

void print_menu(void);
void print_menu_mode_input_common_matrix(void);
void print_common_matrix(matrix_t *matrix);
void print_menu_mode_input_sparse_matrix(void);
void print_sparse_matrix(sparse_matrix_t *sparse_matrix);

#endif // __PRINT_H__