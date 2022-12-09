#ifndef __READ_PRINT_H__
#define __READ_PRINT_H__

#include "binary_tree.h"
#include "errors.h"
#include "structs.h"

int read_action(int *action);
void print_choice(void);
int read_file(FILE *f, binary_tree_t *binary_tree);
int read_line(FILE *f, binary_tree_t *binary_tree);
void apply(branch_t *tree, action_t f, void *arg);
void apply_pre(branch_t *tree, action_t f, void *arg);
void apply_after(branch_t *tree, action_t f, void *arg);
void print_tree(FILE *f, branch_t *head);
void to_dot(void *node, void *param);
void export_to_dot(FILE *f, char *tree_name, void *tree);
void insert_file(FILE *f, char *str);

#endif // __READ_PRINT_H__