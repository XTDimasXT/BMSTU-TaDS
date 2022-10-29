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
        return ALLOCATE_MATRIX_ERROR;
    }
    return EXIT_SUCCESS;
}

int create_sparse_matrix(sparse_matrix_t *sparse_matrix)
{
    sparse_matrix->a = calloc(sparse_matrix->rows * sizeof(int), sizeof(int));
    if (sparse_matrix->a == NULL)
    {
        printf("Ошибка выделения памяти под массив ненулевых элементов\n");
        return ALLOCATE_NONZERO_ELEMS_ERROR;
    }

    sparse_matrix->ja = calloc(sparse_matrix->nonzero_elems * sizeof(int), sizeof(int));
    if (sparse_matrix->ja == NULL)
    {
        printf("Ошибка выделения памяти под массив номеров столбцов ненулевых элементов\n");
        free(sparse_matrix->a);
        return ALLOCATE_COLUMNS_ERROR;
    }

    sparse_matrix->ia = calloc(sparse_matrix->nonzero_elems * sizeof(int), sizeof(int));
    if (sparse_matrix->ia == NULL)
    {
        printf("Ошибка выделения памяти под массив значений ненулевых элементов\n");
        free(sparse_matrix->a);
        free(sparse_matrix->ja);
        return ALLOCATE_LIST_ERROR;
    }

    return EXIT_SUCCESS;
}

void free_sparse_matrix(sparse_matrix_t *sparse_matrix)
{
    free(sparse_matrix->a);
    free(sparse_matrix->ja);
    free(sparse_matrix->ia);
}