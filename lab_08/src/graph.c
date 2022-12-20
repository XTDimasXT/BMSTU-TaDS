#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"

int list_graph_add(list_graph_t *graph, node_t *start, node_t *end)
{
    int error = 0;
    if (graph->arr[start->name] == NULL)
    {
        error = list_push(&graph->arr[start->name], start);
        error += list_push(&graph->arr[start->name], end);
        graph->len++;
        return error;
    }

    for (list_t *temp = graph->arr[start->name]; temp; temp = temp->next)
        if (temp->data->name == end->name)
            return APPEND_ERROR;

    error = list_push(&graph->arr[start->name], end);
    return error;
}

void list_graph_to_dot(FILE *f, list_graph_t *graph)
{
    fprintf(f, "digraph {\n");

    for (size_t i = 0; i < graph->len; i++)
    {
        if (graph->arr[i] != NULL)
        {
            for (list_t *temp = graph->arr[i]->next; temp; temp = temp->next)
            {
                if (temp != NULL)
                    fprintf(f, "\"%d\" -> \"%d\" [label = \"%zu\"];\n", graph->arr[i]->data->name, temp->data->name, temp->data->weight);
            }
        }
    }
    fprintf(f, "}\n");
}

list_graph_t *list_graph_create(void)
{
    list_graph_t *temp = calloc(1, sizeof(list_graph_t));
    return temp;
}

size_t min_distance(size_t dist[], bool sptSet[], size_t len)
{

    size_t min = -1,
           min_index;

    for (size_t v = 0; v < len; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

int list_graph_are_nodes_incident(list_graph_t *graph, int u, int v)
{
    if (graph->arr[u] == NULL)
        return 0;
    else
        for (list_t *temp = graph->arr[u]; temp; temp = temp->next)
        {
            if (temp->data->name == v)
                return temp->data->weight;
        }
    return 0;
}

size_t *list_graph_dijkstra(list_graph_t *graph, size_t src)
{
    size_t *dist = calloc(graph->len, sizeof(size_t));
    if (dist == NULL)
        return dist;
    bool sptSet[MAX_NODES_COUNT];

    for (size_t i = 0; i < graph->len; i++)
        dist[i] = -1,
        sptSet[i] = false;

    dist[src] = 0;

    for (size_t count = 0; count < graph->len - 1; count++)
    {
        size_t u = min_distance(dist, sptSet, graph->len);
        sptSet[u] = true;

        for (size_t v = 0; v < graph->len; v++)
            if (!sptSet[v] && list_graph_are_nodes_incident(graph, u, v) && dist[u] != (size_t)-1 && dist[u] + list_graph_are_nodes_incident(graph, u, v) < dist[v])
                dist[v] = dist[u] + list_graph_are_nodes_incident(graph, u, v);
    }

    return dist;
}

size_t *matrix_graph_dijkstra(matrix_graph_t *graph, size_t src)
{
    size_t *dist = calloc(graph->len, sizeof(size_t));
    if (dist == NULL)
        return dist;
    bool sptSet[MAX_NODES_COUNT];

    for (size_t i = 0; i < graph->len; i++)
        dist[i] = -1,
        sptSet[i] = false;

    dist[src] = 0;

    for (size_t count = 0; count < graph->len - 1; count++)
    {
        size_t u = min_distance(dist, sptSet, graph->len);
        sptSet[u] = true;

        for (size_t v = 0; v < graph->len; v++)
            if (!sptSet[v] &&
                graph->arr[u][v] &&
                dist[u] != (size_t)-1 &&
                dist[u] + graph->arr[u][v] < dist[v])
                dist[v] = dist[u] + graph->arr[u][v];
    }

    return dist;
}

int matrix_graph_read(FILE *f, matrix_graph_t *graph)
{
    int len;
    if (fscanf(f, "%d", &len) != 1 || len <= 0)
        return GRAPH_READ_ERROR;
    graph->len = len;
    for (size_t i = 0; i < graph->len; i++)
    {
        for (size_t j = 0; j < graph->len; j++)
        {
            int temp;
            if (fscanf(f, "%d", &temp) != 1 || temp < 0)
                return MATRIX_READ_ERROR;
            if (i == j && temp != 0)
                return GRAPH_READ_ERROR;

            graph->arr[i][j] = temp;
        }
    }

    return EXIT_SUCCESS;
}

matrix_graph_t *matrix_graph_create(void)
{
    matrix_graph_t *temp = calloc(1, sizeof(matrix_graph_t));

    return temp;
}

void matirx_graph_to_dot(FILE *f, matrix_graph_t *graph)
{
    fprintf(f, "digraph {\n");

    for (size_t i = 0; i < graph->len; i++)
    {
        for (size_t j = 0; j < graph->len; j++)
        {
            if (graph->arr[i][j] != 0)
                fprintf(f, "\"%zu\" -> \"%zu\" [label = \"%zu\"];\n", i, j, graph->arr[i][j]);
        }
    }
    fprintf(f, "}\n");
}

void list_graph_clear(list_graph_t *graph)
{
    for (size_t i = 0; i < graph->len; i++)
    {
        if (graph->arr[i] != NULL)
        {
            list_free(graph->arr[i]);
            graph->arr[i] = NULL;
        }
    }

    graph->len = 0;
}

int list_graph_read(FILE *f, list_graph_t *graph)
{
    int len;
    if (fscanf(f, "%d", &len) != 1 || len <= 0)
        return GRAPH_READ_ERROR;

    if (graph->len != 0)
        list_graph_clear(graph);

    graph->len = len;
    int start_temp, end_temp, weight;
    while (fscanf(f, "%d %d %d", &start_temp, &weight, &end_temp) == 3)
    {
        if (weight <= 0 || start_temp == end_temp || start_temp > len || end_temp > len)
        {
            list_graph_clear(graph);
            return GRAPH_READ_ERROR;
        }

        node_t *start = calloc(1, sizeof(node_t));
        node_t *end = calloc(1, sizeof(node_t));

        if (!start || !end)
        {
            list_graph_clear(graph);
            free(start);
            free(end);
            return GRAPH_READ_ERROR;
        }
        start->name = start_temp;
        end->name = end_temp;
        end->weight = weight;
        if (list_graph_add(graph, start, end))
        {
            list_graph_clear(graph);
            free(start);
            free(end);
            return GRAPH_READ_ERROR;
        }
    }
    char *tmp;
    scanf("%s", tmp);

    return EXIT_SUCCESS;
}

int list_graph_read_matrix(FILE *f, list_graph_t *graph)
{
    int len;
    if (fscanf(f, "%d", &len) != 1 || len <= 0)
        return GRAPH_READ_ERROR;

    if (graph->len != 0)
        list_graph_clear(graph);

    for (size_t i = 0; i < (size_t)len; i++)
    {
        for (size_t j = 0; j < (size_t)len; j++)
        {
            int temp;
            if (fscanf(f, "%d", &temp) != 1 || temp < 0)
                return MATRIX_READ_ERROR;
            if (i == j && temp != 0)
                return GRAPH_READ_ERROR;

            node_t *start = calloc(1, sizeof(node_t));
            node_t *end = calloc(1, sizeof(node_t));
            if (!start || !end)
            {
                list_graph_clear(graph);
                free(start);
                free(end);
                return GRAPH_READ_ERROR;
            }

            start->name = i;
            end->name = j;
            end->weight = temp;
            if (temp != 0)
            {
                if (list_graph_add(graph, start, end))
                {
                    list_graph_clear(graph);
                    free(start);
                    free(end);
                    return GRAPH_READ_ERROR;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}