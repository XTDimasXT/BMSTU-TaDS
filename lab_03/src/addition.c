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

    common_matrix_addition(&matrix_a, &matrix_b, &matrix_res);
    
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
    printf("\nОбработка матрицы A\n\n");
    sparse_matrix_t sparse_matrix_a;
    int rc = read_num_rows_and_columns(&sparse_matrix_a.rows, &sparse_matrix_a.cols);
    if (rc != EXIT_SUCCESS)
        return rc;
    
    int mode;
    int perc;
    rc = read_mode_input_sparse_matrix(&mode, &perc);
    if (rc != EXIT_SUCCESS)
        return rc;
    
    if (mode == 1)
    {
        rc = read_num_nonzero_elems(&sparse_matrix_a);
        if (rc != EXIT_SUCCESS)
            return rc;
        rc = create_sparse_matrix(&sparse_matrix_a);
        if (rc != EXIT_SUCCESS)
            return rc;
        rc = read_sparse_matrix(&sparse_matrix_a);
        if (rc != EXIT_SUCCESS)
        {
            free_sparse_matrix(&sparse_matrix_a);
            return rc;
        }
    }
    else if (mode == 2)
    {
        rc = find_num_nonzero_elems(&sparse_matrix_a, perc);
        if (rc != EXIT_SUCCESS)
            return rc;
        rc = create_sparse_matrix(&sparse_matrix_a);
        if (rc != EXIT_SUCCESS)
            return rc;
        rc = random_sparse_matrix(&sparse_matrix_a, perc);
        if (rc != EXIT_SUCCESS)
        {
            free_sparse_matrix(&sparse_matrix_a);
            return rc;
        }
    }

    printf("\nОбработка матрицы B\n\n");
    sparse_matrix_t sparse_matrix_b;
    rc = read_num_rows_and_columns(&sparse_matrix_b.rows, &sparse_matrix_b.cols);
    if (rc != EXIT_SUCCESS)
    {
        free_sparse_matrix(&sparse_matrix_a);
        return rc;
    }
    
    rc = read_mode_input_sparse_matrix(&mode, &perc);
    if (rc != EXIT_SUCCESS)
    {
        free_sparse_matrix(&sparse_matrix_a);
        return rc;
    }

    if (mode == 1)
    {
        rc = read_num_nonzero_elems(&sparse_matrix_b);
        if (rc != EXIT_SUCCESS)
        {
            free_sparse_matrix(&sparse_matrix_a);
            return rc;
        }
        rc = create_sparse_matrix(&sparse_matrix_b);
        if (rc != EXIT_SUCCESS)
        {
            free_sparse_matrix(&sparse_matrix_a);
            return rc;
        }
        rc = read_sparse_matrix(&sparse_matrix_b);
        if (rc != EXIT_SUCCESS)
        {
            free_sparse_matrix(&sparse_matrix_a);
            free_sparse_matrix(&sparse_matrix_b);
            return rc;
        }
    }
    else if (mode == 2)
    {
        rc = find_num_nonzero_elems(&sparse_matrix_b, perc);
        if (rc != EXIT_SUCCESS)
        {
            free_sparse_matrix(&sparse_matrix_a);
            return rc;
        }
        rc = create_sparse_matrix(&sparse_matrix_b);
        if (rc != EXIT_SUCCESS)
        {
            free_sparse_matrix(&sparse_matrix_a);
            return rc;
        }
        rc = random_sparse_matrix(&sparse_matrix_b, perc);
        if (rc != EXIT_SUCCESS)
        {
            free_sparse_matrix(&sparse_matrix_a);
            free_sparse_matrix(&sparse_matrix_b);
            return rc;
        }
    }

    sparse_matrix_t sparse_matrix_res;
    sparse_matrix_res.rows = sparse_matrix_a.rows;
    sparse_matrix_res.cols = sparse_matrix_a.cols;
    sparse_matrix_res.nonzero_elems = sparse_matrix_a.nonzero_elems + sparse_matrix_b.nonzero_elems;

    rc = create_sparse_matrix(&sparse_matrix_res);
    if (rc != EXIT_SUCCESS)
    {
        free_sparse_matrix(&sparse_matrix_a);
        free_sparse_matrix(&sparse_matrix_b);
        return rc;
    }

    sparse_matrix_addition(&sparse_matrix_a, &sparse_matrix_b, &sparse_matrix_res);

    printf("Матрица A:\n");
    print_sparse_matrix(&sparse_matrix_a);
    printf("Матрица B:\n");
    print_sparse_matrix(&sparse_matrix_b);
    printf("Результат сложения матриц A и B:\n");
    print_sparse_matrix(&sparse_matrix_res);

    free_sparse_matrix(&sparse_matrix_a);
    free_sparse_matrix(&sparse_matrix_b);
    free_sparse_matrix(&sparse_matrix_res);

    return EXIT_SUCCESS;
}

void common_matrix_addition(matrix_t *matrix_a, matrix_t *matrix_b, matrix_t *matrix_res)
{
    for (int i = 0; i < matrix_res->rows; i++)
        for (int j = 0; j < matrix_res->cols; j++)
            matrix_res->matrix[i][j] = matrix_a->matrix[i][j] + matrix_b->matrix[i][j];
}

void sparse_matrix_addition(sparse_matrix_t *sparse_matrix_a, sparse_matrix_t *sparse_matrix_b, sparse_matrix_t *sparse_matrix_res)
{
    int count_a = 0;
    int count_b = 0;
    int count_res = 0;
    for (int i = 0; i < sparse_matrix_a->rows; i++)
    {
        sparse_matrix_res->a[i] = sparse_matrix_a->a[i] + sparse_matrix_b->a[i];
        if (sparse_matrix_a->a[i] != 0 && sparse_matrix_b->a[i] != 0)
        {
            int temp_count_a = count_a;
            int temp_count_b = count_b;
            while ((count_a < temp_count_a + sparse_matrix_a->a[i]) && (count_b < temp_count_b + sparse_matrix_b->a[i]))
            {
                if (sparse_matrix_a->ja[count_a] == sparse_matrix_b->ja[count_b])
                {
                    sparse_matrix_res->a[i]--;
                    sparse_matrix_res->nonzero_elems--;
                    sparse_matrix_res->ja[count_res] = sparse_matrix_a->ja[count_a];
                    sparse_matrix_res->ia[count_res] = sparse_matrix_a->ia[count_a] + sparse_matrix_b->ia[count_b];
                    count_a++;
                    count_b++;
                    count_res++;
                }
                else if (sparse_matrix_a->ja[count_a] < sparse_matrix_b->ja[count_b])
                {
                    sparse_matrix_res->ja[count_res] = sparse_matrix_a->ja[count_a];
                    sparse_matrix_res->ia[count_res] = sparse_matrix_a->ia[count_a];
                    count_a++;
                    count_res++;
                }
                else if (sparse_matrix_b->ja[count_b] < sparse_matrix_a->ja[count_a])
                {
                    sparse_matrix_res->ja[count_res] = sparse_matrix_b->ja[count_b];
                    sparse_matrix_res->ia[count_res] = sparse_matrix_b->ia[count_b];
                    count_b++;
                    count_res++;
                }
            }
            if ((count_a < temp_count_a + sparse_matrix_a->a[i]) && (count_b >= temp_count_b + sparse_matrix_b->a[i]))
            {
                while (count_a < temp_count_a + sparse_matrix_a->a[i])
                {
                    sparse_matrix_res->ja[count_res] = sparse_matrix_a->ja[count_a];
                    sparse_matrix_res->ia[count_res] = sparse_matrix_a->ia[count_a];
                    count_a++;
                    count_res++;
                }
            }
            else if ((count_b < temp_count_b + sparse_matrix_b->a[i]) && (count_a >= temp_count_a + sparse_matrix_a->a[i]))
            {
                while (count_b < temp_count_b + sparse_matrix_b->a[i])
                {
                    sparse_matrix_res->ja[count_res] = sparse_matrix_b->ja[count_b];
                    sparse_matrix_res->ia[count_res] = sparse_matrix_b->ia[count_b];
                    count_b++;
                    count_res++;
                }
            }
        }
        else if ((sparse_matrix_a->a[i] != 0) && (sparse_matrix_b->a[i] == 0))
        {
            for (int j = 0; j < sparse_matrix_a->a[i]; j++)
            {
                sparse_matrix_res->ja[count_res] = sparse_matrix_a->ja[count_a];
                sparse_matrix_res->ia[count_res] = sparse_matrix_a->ia[count_a];
                count_a++;
                count_res++;
            }
        }
        else if ((sparse_matrix_a->a[i] == 0) && (sparse_matrix_b->a[i] != 0))
        {
            for (int j = 0; j < sparse_matrix_b->a[i]; j++)
            {
                sparse_matrix_res->ja[count_res] = sparse_matrix_b->ja[count_b];
                sparse_matrix_res->ia[count_res] = sparse_matrix_b->ia[count_b];
                count_b++;
                count_res++;
            }
        }
    }
}