#include "../inc/random.h"

int random_common_matrix(matrix_t *matrix, int perc)
{
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->cols; j++)
            matrix->matrix[i][j] = 0;
    
    int count_elems = matrix->rows * matrix->cols;
    int nonzero_elems = count_elems * perc / 100;
    if (nonzero_elems == 0)
    {
        printf("При выбранном проценте все элементы будут нулевыми\n");
        return EMPTY_MATRIX_ERROR;
    }

    int rand1;
    int rand2;
    while (nonzero_elems != 0)
    {
        rand1 = rand() % (matrix->rows);
        rand2 = rand() % (matrix->cols);
        if (matrix->matrix[rand1][rand2] == 0)
        {
            matrix->matrix[rand1][rand2] = rand() % (matrix->rows) + 1;
            nonzero_elems--;
        }
    }

    return EXIT_SUCCESS;
}

int random_sparse_matrix(sparse_matrix_t *sparse_matrix, int perc)
{
    int count_elems = sparse_matrix->rows * sparse_matrix->cols;
    int nonzero_elems = count_elems * perc / 100;
    if (nonzero_elems == 0)
    {
        printf("При выбранном проценте все элементы будут нулевыми\n");
        return EMPTY_MATRIX_ERROR;
    }

    int count = 0;
    for (int i = 0; i < sparse_matrix->nonzero_elems; i++)
    {
        sparse_matrix->a[i] = rand() % sparse_matrix->cols;
        for (int j = 0; j < sparse_matrix->a[i]; j++)
        {
            sparse_matrix->ja[count] = rand() % sparse_matrix->cols;
            sparse_matrix->ia[count] = rand();
            count++;
        }
    }

    return EXIT_SUCCESS;
}