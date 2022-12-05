#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include "structs.h"

typedef void (*action_t)(void *node, void *arg);

branch_t *allocate_node(char *val, branch_t *branch);
int comparator(char *word_1, char *word_2);
void insert_tree(branch_t **head, char *val);
int find_word(branch_t *root, char *str);
void delete(branch_t *cur);
void delete_word(branch_t *root, char *str);
branch_t *get_deep_node(branch_t *root);
branch_t *get_node(branch_t *root, char *str);

#endif // __BINARY_TREE_H__