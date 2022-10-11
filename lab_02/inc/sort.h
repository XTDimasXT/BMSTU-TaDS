#ifndef __SORT_H__
#define __SORT_H__

#include "info.h"
#include "print.h"
#include "errors.h"

int compare_t(const theatres_t *arg_1, const theatres_t *arg_2);
int compare_k(const keys_t *arg_1, const keys_t *arg_2);
void sort_qsort(table_t *table);
void sort_choice(table_t *table);
void sort_keys_qsort(table_t *table);
void sort_keys_choice(table_t *table);
void sort_keys(table_t *table);

#endif // __SORT_H__