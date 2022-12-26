#ifndef __HASHTABLE_ARR_H__
#define __HASHTABLE_ARR_H__

#include <stdlib.h>
#include <stdbool.h>

typedef enum { EMPTY, DELETED, FILLED } NodeStatus_t;

typedef struct {
    NodeStatus_t nodeStatus;
    char *key;
} node_arr_t;

typedef struct {
    size_t capacity;
    size_t size;
    size_t (*hasher)(const char *, size_t);
    node_arr_t *arr;

    size_t coeff;
} hashtable_arr_t;

int rehash_arr(hashtable_arr_t *hashtable);
void editcoeff_arr(hashtable_arr_t *hashtable, size_t coeff);
hashtable_arr_t createHashTable_arr(size_t (*hasher)(const char *, size_t coeff));
void deleteHashTable_arr(hashtable_arr_t *hashtable);
int addHashTable_arr(hashtable_arr_t *hashtable, const char *, size_t *count_comp);
size_t gorner_hasher(const char *str, size_t coeff);
void removeStartswith_arr(hashtable_arr_t *hashtable, char target, size_t *count_comp);
void printHashTable_arr(hashtable_arr_t *hashtable);
bool hasHashTable_arr(hashtable_arr_t *hashtable, const char *key, size_t *count_comp);
void remove_arr(hashtable_arr_t *hashtable, const char *key, size_t *count_comp);

#endif
