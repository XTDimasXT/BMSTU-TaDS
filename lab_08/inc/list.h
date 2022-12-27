#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>

#define MEMORY_ALLOCATION_ERROR 4

typedef struct
{
    int name;
    size_t weight;
} node_t;

typedef struct list list_t;

struct list
{
    list_t *next;
    node_t *data;
};

int list_push(list_t **head, node_t *data);
void list_free(list_t *list);

#endif // __LIST_H__