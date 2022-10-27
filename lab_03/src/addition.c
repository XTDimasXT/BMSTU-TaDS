#include "../inc/addition.h"

int addition_common_matrix(void)
{
    printf("\nОбработка матрицы A\n\n");
    matrix_t matrix_a;
    int rc = read_num_rows_and_columns(&matrix_a.rows, &matrix_a.cols);
    if (rc != EXIT_SUCCESS)
        return rc;
    
    rc = create_common_matrix(&matrix_a);
    if (rc != EXIT_SUCCESS)
        return rc;
    
    int mode;
    int perc;
    rc = read_mode_input_common_matrix(&mode, &perc);
    if (rc != EXIT_SUCCESS)
    {
        free_matrix(matrix_a.matrix, matrix_a.rows);
        return rc;
    }
    
    if (mode == 1)
    {
        rc = read_nonzero_elems(&matrix_a);
        if (rc != EXIT_SUCCESS)
        {
            free_matrix(matrix_a.matrix, matrix_a.rows);
            return rc;
        }
    }

    else if (mode == 2)
    {
        rc = read_full_matrix(&matrix_a);
        if (rc != EXIT_SUCCESS)
        {
            free_matrix(matrix_a.matrix, matrix_a.rows);
            return rc;
        }
    }

    else if (mode == 3)
    {
        rc = random_common_matrix(&matrix_a, perc);
        if (rc != EXIT_SUCCESS)
        {
            free_matrix(matrix_a.matrix, matrix_a.rows);
            return rc;
        }
    }

    printf("\nОбработка матрицы B\n\n");
    matrix_t matrix_b;
    rc = read_num_rows_and_columns(&matrix_b.rows, &matrix_b.cols);
    if (rc != EXIT_SUCCESS)
    {
        free_matrix(matrix_a.matrix, matrix_a.rows);
        return rc;
    }
    
    if (matrix_a.rows != matrix_b.rows || matrix_a.cols != matrix_b.cols)
    {
        printf("В матрицах A и B разное количество строк/столбцов\n");
        free_matrix(matrix_a.matrix, matrix_a.rows);
        return DIFFERENT_SIZE_ERROR;
    } 

    rc = create_common_matrix(&matrix_b);
    if (rc != EXIT_SUCCESS)
    {
        free_matrix(matrix_a.matrix, matrix_a.rows);
        return rc;
    }
    
    rc = read_mode_input_common_matrix(&mode, &perc);
    if (rc != EXIT_SUCCESS)
    {
        free_matrix(matrix_a.matrix, matrix_a.rows);
        free_matrix(matrix_b.matrix, matrix_b.rows);
        return rc;
    }
    
    if (mode == 1)
    {
        rc = read_nonzero_elems(&matrix_b);
        if (rc != EXIT_SUCCESS)
        {
            free_matrix(matrix_a.matrix, matrix_a.rows);
            free_matrix(matrix_b.matrix, matrix_b.rows);
            return rc;
        }
    }

    else if (mode == 2)
    {
        rc = read_full_matrix(&matrix_b);
        if (rc != EXIT_SUCCESS)
        {
            free_matrix(matrix_a.matrix, matrix_a.rows);
            free_matrix(matrix_b.matrix, matrix_b.rows);
            return rc;
        }
    }

    else if (mode == 3)
    {
        rc = random_common_matrix(&matrix_b, perc);
        if (rc != EXIT_SUCCESS)
        {
            free_matrix(matrix_a.matrix, matrix_a.rows);
            free_matrix(matrix_b.matrix, matrix_b.rows);
            return rc;
        }
    }

    matrix_t matrix_res;
    matrix_res.rows = matrix_a.rows;
    matrix_res.cols = matrix_a.cols;

    rc = create_common_matrix(&matrix_res);
    if (rc != EXIT_SUCCESS)
    {
        free_matrix(matrix_a.matrix, matrix_a.rows);
        free_matrix(matrix_b.matrix, matrix_b.rows);
        return rc;
    }

    for (int i = 0; i < matrix_res.rows; i++)
        for (int j = 0; j < matrix_res.cols; j++)
            matrix_res.matrix[i][j] = matrix_a.matrix[i][j] + matrix_b.matrix[i][j];
    
    printf("Матрица A:\n");
    print_common_matrix(&matrix_a);
    printf("Матрица B:\n");
    print_common_matrix(&matrix_b);
    printf("Результат сложения матриц A и B:\n");
    print_common_matrix(&matrix_res);

    free_matrix(matrix_a.matrix, matrix_a.cols);
    free_matrix(matrix_b.matrix, matrix_b.cols);
    free_matrix(matrix_res.matrix, matrix_res.cols);

    return EXIT_SUCCESS;
}

int addition_sparse_matrix(void)
{
    return EXIT_SUCCESS;
}