#define _GNU_SOURCE
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "hashtable_list.h"

const size_t BUCKETS_SIZES_LIST[] = {
    7, 17, 37, 73, 149, 251, 509, 1021, 2027, 5003, 10837
};
const size_t MAX_LEN = 5;

hashtable_list_t createHashTable_list(size_t (*hasher)(const char *, size_t))
{
    hashtable_list_t result = { .buckets = NULL, .buckets_count = 0,
    .buckets_sizes_list_idx = 0, .items_count = 0, .hasher = hasher, .coeff = 43 };
    return result;
}

void editcoeff_list(hashtable_list_t *hashtable, size_t coeff)
{
    hashtable->coeff = coeff;   
}

void deleteHashTable_list(hashtable_list_t *hashtable)
{
    for (size_t i = 0; i < hashtable->buckets_count; ++i)
    {
        node_list_t *cur = hashtable->buckets[i];
        while (cur)
        {
            node_list_t *tmp = cur;
            cur = cur->next;
            free(tmp->key);
            free(tmp);
        }
    }
    free(hashtable->buckets);
}

bool hasHashTable_list(hashtable_list_t *hashtable, const char *key, size_t *comp_count)
{
    if (!hashtable->buckets)
        return false;
    
    size_t idx = hashtable->hasher(key, hashtable->coeff) % hashtable->buckets_count;
    node_list_t *cur = hashtable->buckets[idx];
    while (cur)
    {
        ++(*comp_count);
        if (strcmp(cur->key, key) == 0)
            return true;
        cur = cur->next;
    }
    return false;
}

int rehash_list(hashtable_list_t *hashtable)
{
    node_list_t **new_buckets = calloc(hashtable->buckets_count, sizeof(node_list_t *));
    if (new_buckets == NULL)
        return EXIT_FAILURE;
    for (size_t i = 0; i < hashtable->buckets_count; ++i)
    {
        node_list_t *cur = hashtable->buckets[i];
        while (cur)
        {
            node_list_t *tmp = cur;
            cur = cur->next;
            size_t new_idx = hashtable->hasher(tmp->key, hashtable->coeff) % hashtable->buckets_count;
            tmp->next = new_buckets[new_idx];
            new_buckets[new_idx] = tmp;
        }
    }
    free(hashtable->buckets);
    hashtable->buckets = new_buckets;
    return EXIT_SUCCESS;
}

static int grow(hashtable_list_t *hashtable)
{
    size_t new_buckets_count = BUCKETS_SIZES_LIST[hashtable->buckets_sizes_list_idx++];
    node_list_t **new_buckets = calloc(new_buckets_count, sizeof(node_list_t *));
    if (new_buckets == NULL)
        return EXIT_FAILURE;
    for (size_t i = 0; i < hashtable->buckets_count; ++i)
    {
        node_list_t *cur = hashtable->buckets[i];
        while (cur)
        {
            node_list_t *tmp = cur;
            cur = cur->next;
            size_t new_idx = hashtable->hasher(tmp->key, hashtable->coeff) % new_buckets_count;
            tmp->next = new_buckets[new_idx];
            new_buckets[new_idx] = tmp;
        }
    }
    free(hashtable->buckets);
    hashtable->buckets = new_buckets;
    hashtable->buckets_count = new_buckets_count;
    return EXIT_SUCCESS;
}

int addHashTable_list(hashtable_list_t *hashtable, const char *key, size_t *comp_count)
{
    if (hasHashTable_list(hashtable, key, comp_count))
        return EXIT_SUCCESS;
    
    if (hashtable->buckets_count * MAX_LEN <= hashtable->items_count)
    {
        if (grow(hashtable))
            return EXIT_FAILURE;
    }

    size_t idx = hashtable->hasher(key, hashtable->coeff) % hashtable->buckets_count;
    node_list_t *new_node = malloc(sizeof(node_list_t));
    if (new_node == NULL || (new_node->key = strdup(key)) == NULL)
    {
        free(new_node);
        return EXIT_FAILURE;
    }
    new_node->next = hashtable->buckets[idx];
    hashtable->buckets[idx] = new_node;
    ++hashtable->items_count;
    return EXIT_SUCCESS;
}

void deleteStartswith_list(hashtable_list_t *hashtable, char target, size_t *count_comp)
{
    for (size_t i = 0; i < hashtable->buckets_count; ++i)
    {
        node_list_t *cur = hashtable->buckets[i];
        node_list_t *prev = NULL;
        while (cur)
        {
            ++(*count_comp);
            if (cur->key[0] == target)
            {
                if (prev == NULL)
                    hashtable->buckets[i] = cur->next;
                else
                    prev->next = cur->next;
                hashtable->items_count--;
                node_list_t *tmp = cur;
                cur = cur->next;
                free(tmp->key);
                free(tmp);
            }
            else
            {
                prev = cur;
                cur = cur->next;
            }
        }
    }
}

void printHashTable_list(hashtable_list_t *hashtable)
{
    for (size_t i = 0; i < hashtable->buckets_count; ++i)
    {
        node_list_t *cur = hashtable->buckets[i];
        while (cur)
        {
            printf("%s -> ", cur->key);
            cur = cur->next;
        }
        printf("NIL\n");
    }
}

void remove_list(hashtable_list_t *hashtable, const char *key, size_t *count_comp)
{
    if (!hashtable->buckets)
        return;
    size_t idx = hashtable->hasher(key, hashtable->coeff) % hashtable->buckets_count;
    node_list_t *cur = hashtable->buckets[idx];
    node_list_t *prev = NULL;
    while (cur)
    {
        ++(*count_comp);
        if (strcmp(key, cur->key) == 0)
        {
            if (prev == NULL)
                hashtable->buckets[idx] = cur->next;
            else
                prev->next = cur->next;
            hashtable->items_count--;
            free(cur->key);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}
