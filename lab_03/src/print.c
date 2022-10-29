#include "../inc/print.h"

void print_menu(void)
{
    printf("Меню:\n");
    printf("1. Сложение матриц, хранящихся в заданной форме\n");
    printf("2. Сложение матриц, применяя стандартный алгоритм\n");
    printf("3. Сравнение времени выполнения этих двух алгоритмов\n");
    printf("0. Выход\n");
}

void print_menu_mode_input_common_matrix(void)
{
    printf("Выбор способа заполнения матрицы:\n");
    printf("1. Заполнение вручную ненулевых элементов\n");
    printf("2. Заполнение вручную всей матрицы\n");
    printf("3. Заполнение автоматически\n");
}

void print_common_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
            printf("%-4d", matrix->matrix[i][j]);
        printf("\n");
    }
}

void print_menu_mode_input_sparse_matrix(void)
{
    printf("Выбор способа заполнения матрицы\n");
    printf("1. Заполнение вручную\n");
    printf("2. Заполнение автоматически\n");
}

void print_sparse_matrix(sparse_matrix_t *sparse_matrix)
{
    printf("Количество ненулевых элементов в строках:\n");
    for (int i = 0; i < sparse_matrix->rows; i++)
        printf("%d ", sparse_matrix->a[i]);
    printf("\n");
    
    printf("Номера столбцов ненулевых элементов:\n");
    for (int i = 0; i < sparse_matrix->nonzero_elems; i++)
        printf("%d ", sparse_matrix->ja[i]);
    printf("\n");
    
    printf("Значения соответствующих элементов:\n");
    for (int i = 0; i < sparse_matrix->nonzero_elems; i++)
        printf("%d ", sparse_matrix->ia[i]);
    printf("\n");
}