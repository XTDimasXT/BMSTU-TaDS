#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int list_push(list_t **head, node_t *data)
{
    list_t *node = calloc(1, sizeof(list_t));
    if (!node)
        return MEMORY_ALLOCATION_ERROR;

    node->data = data;

    if (*head == NULL)
        *head = node;
    else
    {
        list_t *temp = *head;
        while (temp->next)
            temp = temp->next;

        temp->next = node;
    }

    return EXIT_SUCCESS;
}

void list_free(list_t *list)
{
    list_t *temp = list;
    for (; list; list = temp)
    {
        temp = list->next;
        free(list->data);
        free(list);
    }
}