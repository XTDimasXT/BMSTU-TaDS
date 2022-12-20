#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

#define MAX_NODES_COUNT 1000

#define MATRIX_READ_ERROR 1
#define GRAPH_READ_ERROR 2
#define APPEND_ERROR 3

typedef struct
{
    list_t *arr[MAX_NODES_COUNT];
    size_t len;
} list_graph_t;

typedef struct
{
    size_t arr[MAX_NODES_COUNT][MAX_NODES_COUNT];
    size_t len;
} matrix_graph_t;

int list_graph_add(list_graph_t *graph, node_t *start, node_t *end);
void list_graph_to_dot(FILE *f, list_graph_t *graph);
list_graph_t *list_graph_create(void);
size_t min_distance(size_t dist[], bool sptSet[], size_t len);
int list_graph_are_nodes_incident(list_graph_t *graph, int u, int v);
size_t *list_graph_dijkstra(list_graph_t *graph, size_t src);
size_t *matrix_graph_dijkstra(matrix_graph_t *graph, size_t src);
int matrix_graph_read(FILE *f, matrix_graph_t *graph);
matrix_graph_t *matrix_graph_create(void);
void matirx_graph_to_dot(FILE *f, matrix_graph_t *graph);
void list_graph_clear(list_graph_t *graph);
int list_graph_read(FILE *f, list_graph_t *graph);
int list_graph_read_matrix(FILE *f, list_graph_t *graph);

#endif // __GRAPH_H__