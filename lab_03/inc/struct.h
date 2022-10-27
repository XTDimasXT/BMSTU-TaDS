#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct matrix
{
    int **matrix;
    int rows;
    int cols;
} matrix_t;

typedef struct sparse_matrix
{
    int *a;
    int *ja;
    int *ia;
    int nonzero_elems;
    int rows;
    int cols;
} sparse_matrix_t;

#endif // __STRUCT_H__