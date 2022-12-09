#ifndef __COMPARE_H__
#define __COMPARE_H__

#include <stdint.h>

#include "binary_tree.h"
#include "structs.h"
#include "read_print.h"

int64_t tick(void);
void print_result_file(int64_t start, int64_t end);
void print_result_tree(int64_t start, int64_t end);
int compare_time_search(void);
int compare_time_insert(void);
int compare_time_delete(void);
int search_file(FILE *f, char *str);

#endif // __COMPARE_H__