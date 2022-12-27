#ifndef __HASHTABLE_LIST_H__
#define __HASHTABLE_LIST_H__

#include <stdlib.h>

typedef struct node_list node_list_t;

struct node_list
{
    char *key;
    node_list_t *next;
};

typedef struct
{
    node_list_t **buckets;
    size_t buckets_count;

    size_t buckets_sizes_list_idx;
    size_t items_count;

    size_t (*hasher)(const char *, size_t);
    
    size_t coeff;
} hashtable_list_t;

int rehash_list(hashtable_list_t *hashtable);
void editcoeff_list(hashtable_list_t *hashtable, size_t coeff);
hashtable_list_t createHashTable_list(size_t (*hasher)(const char *, size_t));
void deleteStartswith_list(hashtable_list_t *hashtable, char target, size_t *count_comp);
int addHashTable_list(hashtable_list_t *hashtable, const char *key, size_t *count_comp);
void deleteHashTable_list(hashtable_list_t *hashtable);
void printHashTable_list(hashtable_list_t *hashtable);
bool hasHashTable_list(hashtable_list_t *hashtable, const char *key, size_t *count_comp);
void remove_list(hashtable_list_t *hashtable, const char *key, size_t *count_comp);

#endif
