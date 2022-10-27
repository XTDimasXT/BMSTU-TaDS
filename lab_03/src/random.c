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