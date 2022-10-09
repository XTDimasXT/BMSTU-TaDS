#ifndef __PRINT_H__
#define __PRINT_H__

#include "info.h"

void print_menu(void);
void print_table(table_t *table);
void print_line(int i, theatres_t *theatres);
int print_required_performances(table_t *table);
void print_keys(table_t *table);

#endif // __PRINT_H__