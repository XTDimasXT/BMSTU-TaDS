#define _GNU_SOURCE
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "hashtable_arr.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

const double kLoadFactor = 3.0 / 4.0;
const size_t kDefaultCapacity = 8;

size_t gorner_hasher(const char *str, size_t coeff)
{
    size_t result = 0;
    for (size_t i = 0; str[i] != '\0'; ++i)
    {
        result = result * coeff + str[i];
    }
    return result;
}

void editcoeff_arr(hashtable_arr_t *hashtable, size_t coeff)
{
    hashtable->coeff = coeff;
}

hashtable_arr_t createHashTable_arr(size_t (*hasher)(const char *, size_t))
{
    hashtable_arr_t res = { .arr = NULL, .capacity = 0, .size = 0,
                            .hasher = hasher, .coeff = 43};
    return res;
}

void deleteHashTable_arr(hashtable_arr_t *hashtable)
{
    for (size_t i = 0; i < hashtable->capacity; ++i)
    {
        if (hashtable->arr[i].nodeStatus == FILLED)
        {
            hashtable->arr[i].nodeStatus = DELETED;
            free(hashtable->arr[i].key);
        }
    }
    free(hashtable->arr);
}

int rehash_arr(hashtable_arr_t *hashtable)
{
    size_t new_capacity = hashtable->capacity;
    node_arr_t *new_arr = calloc(new_capacity, sizeof(node_arr_t));
    if (new_arr == NULL)
        return EXIT_FAILURE;

    size_t old_capacity = hashtable->capacity;
    node_arr_t *old_arr = hashtable->arr;

    hashtable->arr = new_arr;
    hashtable->capacity = new_capacity;
    hashtable->size = 0;
    size_t count_comp = 0;
    for (size_t i = 0; i < old_capacity; ++i)
    {
        if (old_arr[i].nodeStatus == FILLED)
        {
            addHashTable_arr(hashtable, old_arr[i].key, &count_comp);
            free(old_arr[i].key);
        }
    }
    free(old_arr);
    return EXIT_SUCCESS;
}

static int grow(hashtable_arr_t *hashtable, size_t *count_comp)
{
    size_t new_capacity = MAX(kDefaultCapacity, hashtable->capacity * 2);
    node_arr_t *new_arr = calloc(new_capacity, sizeof(node_arr_t));
    if (new_arr == NULL)
        return EXIT_FAILURE;

    size_t old_capacity = hashtable->capacity;
    node_arr_t *old_arr = hashtable->arr;

    hashtable->arr = new_arr;
    hashtable->capacity = new_capacity;
    hashtable->size = 0;

    for (size_t i = 0; i < old_capacity; ++i)
    {
        if (old_arr[i].nodeStatus == FILLED)
        {
            addHashTable_arr(hashtable, old_arr[i].key, count_comp);
            free(old_arr[i].key);
        }
    }
    free(old_arr);
    return EXIT_SUCCESS;
}

int addHashTable_arr(hashtable_arr_t *hashtable, const char *key, size_t *count_comp)
{
    assert(hashtable != NULL);
    if (hashtable->capacity == 0 || (double)hashtable->size / hashtable->capacity >= kLoadFactor)
    {
        if (grow(hashtable, count_comp))
            return EXIT_FAILURE;
    }
    size_t idx = hashtable->hasher(key, hashtable->coeff) % hashtable->capacity;
    size_t prob_num = 0;
    node_arr_t *first_to_add = NULL;
    while (hashtable->arr[idx].nodeStatus != EMPTY && prob_num < hashtable->capacity)
    {
        if (first_to_add == NULL && hashtable->arr[idx].nodeStatus != FILLED)
        {
            first_to_add = hashtable->arr + idx;
        }
        if (hashtable->arr[idx].nodeStatus == FILLED && strcmp(hashtable->arr[idx].key, key) == 0)
        {
            *count_comp += prob_num + 1;
            return EXIT_SUCCESS;
        }
        idx = (idx + prob_num++ + 1) % hashtable->capacity;
    }
    node_arr_t to_add = { .nodeStatus = FILLED, .key = strdup(key) };
    *count_comp += prob_num;
    if (to_add.key == NULL)
        return EXIT_FAILURE;
    if (first_to_add == NULL)
    {
        hashtable->arr[idx] = to_add;
    }
    else
    {
        *first_to_add = to_add;
    }
    ++hashtable->size;
    return EXIT_SUCCESS;
}

void removeStartswith_arr(hashtable_arr_t *hashtable, char target, size_t *count_comp)
{
    for (size_t i = 0; i < hashtable->capacity; ++i)
    {
        *count_comp += 1;
        if (hashtable->arr[i].nodeStatus == FILLED && hashtable->arr[i].key[0] == target)
        {
            hashtable->arr[i].nodeStatus = DELETED;
            free(hashtable->arr[i].key);
            hashtable->arr[i].key = NULL;
        }
    }
}

void printHashTable_arr(hashtable_arr_t *hashtable)
{
    for (size_t i = 0; i < hashtable->capacity; ++i)
    {
        if (hashtable->arr[i].nodeStatus == FILLED)
        {
            printf("INDEX: %zu, VALUE: %s\n", i, hashtable->arr[i].key);
        }
    }
}

bool hasHashTable_arr(hashtable_arr_t *hashtable, const char *key, size_t *count_comp)
{
    if (hashtable->size == 0)
        return false;
    size_t idx = hashtable->hasher(key, hashtable->coeff) % hashtable->capacity;
    size_t prob_num = 0;
    while (hashtable->arr[idx].nodeStatus != EMPTY && prob_num < hashtable->capacity)
    {
        if (hashtable->arr[idx].nodeStatus == FILLED && strcmp(hashtable->arr[idx].key, key) == 0)
        {
            *count_comp += prob_num += 1;
            return true;
        }
        idx = (idx + prob_num++ + 1) % hashtable->capacity;
    }
    *count_comp += prob_num;
    return false;
}

void remove_arr(hashtable_arr_t *hashtable, const char *key, size_t *count_comp)
{
    if (hashtable->size == 0)
        return;
    size_t idx = hashtable->hasher(key, hashtable->coeff) % hashtable->capacity;
    size_t prob_num = 0;
    while (hashtable->arr[idx].nodeStatus != EMPTY && prob_num < hashtable->capacity)
    {
        if (hashtable->arr[idx].nodeStatus == FILLED && strcmp(hashtable->arr[idx].key, key) == 0)
        {
            prob_num++;
            break;
        }
        idx = (idx + prob_num++ + 1) % hashtable->capacity;
    }
    *count_comp += prob_num;
    if (hashtable->arr[idx].nodeStatus == EMPTY)
        return;
    --hashtable->size;
    hashtable->arr[idx].nodeStatus = DELETED;
    free(hashtable->arr[idx].key);
    hashtable->arr[idx].key = NULL;
    return;
}
