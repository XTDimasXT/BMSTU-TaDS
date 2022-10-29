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
    matrix_t matrix;
    matrix.rows = sparse_matrix->rows;
    matrix.cols = sparse_matrix->cols;
    matrix.matrix = allocate_matrix(matrix.rows, matrix.cols);
    if (matrix.matrix == NULL)
        return MALLOC_ERROR;
    
    for (int i = 0; i < matrix.rows; i++)
        for (int j = 0; j < matrix.cols; j++)
            matrix.matrix[i][j] = 0;
    
    int count_elems = matrix.rows * matrix.cols;
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
        rand1 = rand() % (matrix.rows);
        rand2 = rand() % (matrix.cols);
        if (matrix.matrix[rand1][rand2] == 0)
        {
            matrix.matrix[rand1][rand2] = rand() % (matrix.rows) + 1;
            nonzero_elems--;
        }
    }

    int count = 0;
    int nums_in_row;
    for (int i = 0; i < matrix.rows; i++)
    {
        nums_in_row = 0;
        for (int j = 0; j < matrix.cols; j++)
        {
            if (matrix.matrix[i][j] != 0)
            {
                sparse_matrix->ja[count] = j;
                sparse_matrix->ia[count] = matrix.matrix[i][j];
                count++;
                nums_in_row++;
            }
        }
        sparse_matrix->a[i] = nums_in_row;
    }
    free_matrix(matrix.matrix, matrix.rows);

    return EXIT_SUCCESS;
}