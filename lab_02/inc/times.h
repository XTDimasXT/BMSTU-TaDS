#ifndef __TIMES_H__
#define __TIMES_H__

#include "info.h"
#include "errors.h"
#include "sort.h"

int64_t tick(void);
void print_result(int64_t start, int64_t end);
int compare_sorts(const char name_file[], table_t *table);

#endif // __TIMES_H__