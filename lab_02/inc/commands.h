#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "info.h"
#include "read.h"
#include "errors.h"

void create_array_of_keys(table_t *table);
int fill_table(const char *name_file, table_t *table);
int add_performance(table_t *table);
int delete_lines(table_t *table);

#endif // __COMMANDS_H__