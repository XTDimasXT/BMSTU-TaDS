#include "../inc/read.h"

int read_num_command(int *num_command)
{
    printf("Введите номер команды:\n");
    if (scanf("%d", num_command) != 1)
    {
        printf("Ошибка ввода: номер команды не цифра\n");
        return SCAN_ERROR;
    }
    if (*num_command < 0 || *num_command > 3)
    {
        printf("Номер команды - цифра от 0 до 3\n");
        return NUM_COMMAND_ERROR;
    }
    return EXIT_SUCCESS;
}

int read_num_rows_and_columns(int *rows, int *cols)
{
    printf("Введите количество строк:\n");
    if (scanf("%d", rows) != 1)
    {
        printf("Количество строк - не число\n");
        return SCAN_ROWS_ERROR;
    }
    if (*rows <= 0)
    {
        printf("Количество строк - натуральное число\n");
        return NUM_ROWS_ERROR;
    }

    printf("Введите количество столбцов:\n");
    if (scanf("%d", cols) != 1)
    {
        printf("Количество столбцов - не число\n");
        return SCAN_COLUMNS_ERROR;
    }
    if (*cols <= 0)
    {
        printf("Количество столбцов - натуральное число\n");
        return NUM_COLUMNS_ERROR;
    }

    return EXIT_SUCCESS;
}

int read_mode_input_common_matrix(int *mode, int *perc)
{
    print_menu_mode_input_common_matrix();

    if (scanf("%d", mode) != 1)
    {
        printf("Способ ввода - целое число\n");
        return SCAN_MODE_ERROR;
    }
    if (*mode <= 0 || *mode > 3)
    {
        printf("Способ ввода - число от 1 до 3\n");
        return MODE_ERROR;
    }

    if (*mode == 3)
    {
        printf("Введите процент заполнения матрицы ненулевыми элементами:\n");
        if (scanf("%d", perc) != 1)
        {
            printf("Процент заполнения - целое число\n");
            return SCAN_PERC_ERROR;
        }
        if (*perc <= 0 || *perc > 100)
        {
            printf("Процент заполнения - целое число от 1 до 100\n");
            return PERC_ERROR;
        }
    }

    return EXIT_SUCCESS;
}

int read_full_matrix(matrix_t *matrix)
{
    printf("Введите матрицу размером %d на %d\n", matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->cols; j++)
            if (scanf("%d", (matrix->matrix)[i] + j) != 1)
            {
                printf("Ошибка в чтении элемента\n");
                return SCAN_MATRIX_ERROR;
            }
    return EXIT_SUCCESS;
}

int read_nonzero_elems(matrix_t *matrix)
{
    int nonzero_elems;
    int max_elems = matrix->rows * matrix->cols;

    printf("Введите количество ненулевых элементов (от 1 до %d):\n", max_elems);
    if (scanf("%d", &nonzero_elems) != 1)
    {
        printf("Число ненулевых элементов - целое число\n");
        return SCAN_NONZERO_ELEMS_ERROR;
    }
    if (nonzero_elems <= 0 || nonzero_elems > max_elems)
    {
        printf("Количество ненулевых элементов - число от 1 до %d\n", max_elems);
        return NONZERO_ELEMS_ERROR;
    }

    printf("Введите три параметра (значение, cтроку, столбец) для каждого ненулевого элемента\n");
    printf("Вводить нужно через пробел или с новой строки\n");
    int elem;
    int str_num;
    int col_num;
    for (int i = 0; i < nonzero_elems; i++)
    {
        if (scanf("%d", &elem) != 1)
        {
            printf("Элемент матрицы - целое число\n");
            return SCAN_ELEM_ERROR;
        }
        if (elem == 0)
        {
            printf("Ненулевой элемент должен быть не равен 0");
            return ZERO_ELEM_ERROR;
        }
        if (scanf("%d", &str_num) != 1)
        {
            printf("Номер строки - целое число\n");
            return SCAN_STR_ERROR;
        }
        if (str_num < 0 || str_num > matrix->rows - 1)
        {
            printf("Номер строки - число от 0 до %d\n", matrix->rows - 1);
            return STR_ERROR;
        }
        if (scanf("%d", &col_num) != 1)
        {
            printf("Номер столбца - целое число\n");
            return SCAN_COL_ERROR;
        }
        if (col_num < 0 || col_num > matrix->cols - 1)
        {
            printf("Номер столбца - число от 0 до %d\n", matrix->rows - 1);
            return COL_ERROR;
        }
        matrix->matrix[str_num][col_num] = elem;
    }
    
    return EXIT_SUCCESS;
}

int read_mode_input_sparse_matrix(int *mode, int *perc)
{
    print_menu_mode_input_sparse_matrix();

    if (scanf("%d", mode) != 1)
    {
        printf("Способ ввода - целое число\n");
        return SCAN_MODE_ERROR;
    }
    if (*mode <= 0 || *mode > 2)
    {
        printf("Способ ввода - число от 1 до 2\n");
        return MODE_ERROR;
    }

    if (*mode == 2)
    {
        printf("Введите процент заполнения матрицы ненулевыми элементами:\n");
        if (scanf("%d", perc) != 1)
        {
            printf("Процент заполнения - целое число\n");
            return SCAN_PERC_ERROR;
        }
        if (*perc <= 0 || *perc > 100)
        {
            printf("Процент заполнения - целое число от 1 до 100\n");
            return PERC_ERROR;
        }
    }

    return EXIT_SUCCESS;
}

int read_sparse_matrix(sparse_matrix_t *sparse_matrix)
{

    printf("Матрица размером %d на %d, кол-во ненулевых элементов - %d\n", sparse_matrix->rows, sparse_matrix->cols, sparse_matrix->nonzero_elems);
    printf("Введите три параметра (номер строки, номер столбца, значение)\n");
    printf("Вводить нужно через пробел или с новой строки\n");

    int elem;
    int row_num;
    int col_num;
    int count = 0;
    for (int i = 0; i < sparse_matrix->nonzero_elems; i++)
        sparse_matrix->a[i] = 0;
    for (int i = 0; i < sparse_matrix->nonzero_elems; i++)
    {
        if (scanf("%d", &row_num) != 1)
        {
            printf("Номер строки - целое число\n");
            return SCAN_STR_ERROR;
        }
        if (row_num < 0 || row_num > sparse_matrix->cols)
        {
            printf("Номер строки - число от 0 до %d\n", sparse_matrix->cols - 1);
            return STR_ERROR;
        }
        if (scanf("%d", &col_num) != 1)
        {
            printf("Номер столбца - целое число\n");
            return SCAN_COL_ERROR;
        }
        if (col_num < 0 || col_num > sparse_matrix->cols - 1)
        {
            printf("Номер столбца - число от 0 до %d\n", sparse_matrix->rows - 1);
            return COL_ERROR;
        }
        if (scanf("%d", &elem) != 1)
        {
            printf("Элемент матрицы - целое число\n");
            return SCAN_ELEM_ERROR;
        }
        if (elem == 0)
        {
            printf("Ненулевой элемент должен быть не равен 0");
            return ZERO_ELEM_ERROR;
        }
        
        sparse_matrix->a[row_num]++;
        sparse_matrix->ja[count] = col_num;
        sparse_matrix->ia[count] = elem;
        count++;
    }
    
    return EXIT_SUCCESS;
}

int read_num_nonzero_elems(sparse_matrix_t *sparse_matrix)
{
    int max_elems = sparse_matrix->rows * sparse_matrix->cols;

    printf("Введите количество ненулевых элементов (от 1 до %d):\n", max_elems);
    if (scanf("%d", &sparse_matrix->nonzero_elems) != 1)
    {
        printf("Число ненулевых элементов - целое число\n");
        return SCAN_NONZERO_ELEMS_ERROR;
    }
    if (sparse_matrix->nonzero_elems <= 0 || sparse_matrix->nonzero_elems > max_elems)
    {
        printf("Количество ненулевых элементов - число от 1 до %d\n", max_elems);
        return NONZERO_ELEMS_ERROR;
    }

    return EXIT_SUCCESS;
}

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