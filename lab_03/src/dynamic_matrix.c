#include "../inc/dynamic_matrix.h"

int **allocate_matrix(int rows, int cols)
{
    int **data = calloc(rows, sizeof(int*));
    if (!data)
        return NULL;
    for (int i = 0; i < rows; i++)
    {
        data[i] = malloc(cols * sizeof(int));
        if (!data[i])
        {
            free_matrix(data, rows);
            return NULL;
        }
    }
    return data;
}

void free_matrix(int **data, int rows)
{
    for (int i = 0; i < rows; i++)
        free(data[i]);
    free(data);
}

int create_common_matrix(matrix_t *matrix)
{
    matrix->matrix = allocate_matrix(matrix->rows, matrix->cols);
    if (matrix->matrix == NULL)
    {
        printf("Память под матрицу не была выделена\n");
        return ALLOCATE_ERROR;
    }
    return EXIT_SUCCESS;
}