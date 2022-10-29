#include "../inc/times.h"

unsigned long long milliseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;
    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

int test_time(int perc, int len)
{
    srand(time(NULL));
    
    matrix_t matrix_a;
    matrix_a.rows = len;
    matrix_a.cols = len;

    int rc = create_common_matrix(&matrix_a);
    if (rc != EXIT_SUCCESS)
        return rc;
    
    rc = random_common_matrix(&matrix_a, perc);
    if (rc != EXIT_SUCCESS)
    {
        free_matrix(matrix_a.matrix, matrix_a.rows);
        return rc;
    }

    matrix_t matrix_b;
    matrix_b.rows = len;
    matrix_b.cols = len;

    rc = create_common_matrix(&matrix_b);
    if (rc != EXIT_SUCCESS)
    {
        free_matrix(matrix_a.matrix, matrix_a.rows);
        return rc;
    }
    
    rc = random_common_matrix(&matrix_b, perc);
    if (rc != EXIT_SUCCESS)
    {
        free_matrix(matrix_a.matrix, matrix_a.rows);
        free_matrix(matrix_b.matrix, matrix_b.rows);
        return rc;
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

    unsigned long long beg_common = milliseconds_now();
    for (int i = 0; i < 100; i++)
        common_matrix_addition(&matrix_a, &matrix_b, &matrix_res);
    unsigned long long end_common = milliseconds_now();
    unsigned long long time_common = end_common - beg_common;

    free_matrix(matrix_a.matrix, len);
    free_matrix(matrix_b.matrix, len);
    free_matrix(matrix_res.matrix, len);

    printf("Затраченное время под обычную матрицу %d на %d при заполненности %d%% - %llu мc\n", len, len, perc, time_common);
    printf("Затраченная память под обычную матрицу %d на %d - %lu байт\n", len, len, sizeof(matrix_a.matrix[0][0]) * len * len);


    sparse_matrix_t sparse_matrix_a;
    sparse_matrix_a.rows = len;
    sparse_matrix_a.cols = len;

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

    sparse_matrix_t sparse_matrix_b;
    sparse_matrix_b.rows = len;
    sparse_matrix_b.cols = len;

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

    sparse_matrix_t sparse_matrix_res;
    sparse_matrix_res.rows = sparse_matrix_a.rows;
    sparse_matrix_res.cols = sparse_matrix_a.cols;
    sparse_matrix_res.nonzero_elems = sparse_matrix_a.rows * sparse_matrix_a.cols;

    rc = create_sparse_matrix(&sparse_matrix_res);
    if (rc != EXIT_SUCCESS)
    {
        free_sparse_matrix(&sparse_matrix_a);
        free_sparse_matrix(&sparse_matrix_b);
        return rc;
    }

    unsigned long long beg_sparse = milliseconds_now();
    for (int i = 0; i < 100; i++)
        sparse_matrix_addition(&sparse_matrix_a, &sparse_matrix_b, &sparse_matrix_res);
    unsigned long long end_sparse = milliseconds_now();
    unsigned long long time_sparse = end_sparse - beg_sparse;

    free_sparse_matrix(&sparse_matrix_a);
    free_sparse_matrix(&sparse_matrix_b);
    free_sparse_matrix(&sparse_matrix_res);

    printf("Затраченное время под разреженную матрицу %d на %d при заполненности %d%% - %llu мc\n", len, len, perc,time_sparse);
    printf("Затраченная память под разреженную матрицу %d на %d - %lu байт\n", len, len, sizeof(sparse_matrix_a.a[0]) * sparse_matrix_a.rows + 
            sizeof(sparse_matrix_a.ja[0]) * sparse_matrix_a.nonzero_elems + sizeof(sparse_matrix_a.ia[0]) * sparse_matrix_a.nonzero_elems);
    

    return EXIT_SUCCESS;
}

int print_stats(void)
{
    for (int i = 100; i < 1000; i += 50)
    {
        for (int j = 10; j <= 100; j += 15)
        {
            int rc = test_time(j, i);
            if (rc != EXIT_SUCCESS)
                return rc;
        }
    }
    return EXIT_SUCCESS;
}