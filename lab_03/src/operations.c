#include "../inc/operations.h"

int find_num_nonzero_elems(sparse_matrix_t *sparse_matrix, int perc)
{
    int count_elems = sparse_matrix->rows * sparse_matrix->cols;
    sparse_matrix->nonzero_elems = count_elems * perc / 100;
    if (sparse_matrix->nonzero_elems == 0)
    {
        printf("При выбранном проценте все элементы будут нулевыми\n");
        return EMPTY_MATRIX_ERROR;
    }
    return EXIT_SUCCESS;
}

int convert_common_to_sparse(matrix_t *matrix)
{
    sparse_matrix_t sparse_matrix;
    sparse_matrix.rows = matrix->rows;
    sparse_matrix.cols = matrix->cols;

    sparse_matrix.a = calloc(sparse_matrix.rows, sizeof(int));
    if (sparse_matrix.a == NULL)
        return CALLOC_ERROR;
    sparse_matrix.ja = calloc(sparse_matrix.rows * sparse_matrix.cols, sizeof(int));
    if (sparse_matrix.ja == NULL)
        return CALLOC_ERROR;
    sparse_matrix.ia = calloc(sparse_matrix.rows * sparse_matrix.cols, sizeof(int));
    if (sparse_matrix.ia == NULL)
        return CALLOC_ERROR;
    
    int count = 0;
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            if (matrix->matrix[i][j] != 0)
            {
                sparse_matrix.a[i]++;
                sparse_matrix.ja[count] = j;
                sparse_matrix.ia[count] = matrix->matrix[i][j];
                count++;
            }
        }
    }

    sparse_matrix.nonzero_elems = count;

    print_sparse_matrix(&sparse_matrix);
    free_sparse_matrix(&sparse_matrix);
    
    return EXIT_SUCCESS;
}