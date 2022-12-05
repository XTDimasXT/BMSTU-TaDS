#ifndef __COMPARE_H__
#define __COMPARE_H__

#include "binary_tree.h"
#include "structs.h"
#include "read_print.h"

unsigned long long milliseconds_now(void);
int compare_time(void);
int search_file(FILE *f, char *str);

#endif // __COMPARE_H__