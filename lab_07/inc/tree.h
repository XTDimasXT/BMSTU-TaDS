#ifndef __TREE_H__
#define __TREE_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct tree_node tree_node_t;

struct tree_node
{
    tree_node_t *left;
    tree_node_t *right;
    char *val;
};

tree_node_t *tree_insert(tree_node_t *root, char *val, size_t *count_comp);
tree_node_t *find_min(tree_node_t *node);
tree_node_t *find_max(tree_node_t *node);
tree_node_t *remove_startswith(tree_node_t *root, char start, size_t *count_comp);
void tree_save_as_dot(FILE *f, tree_node_t *root);
void tree_clear(tree_node_t *root);
bool tree_has(tree_node_t *root, const char *key, size_t *count_comp);
tree_node_t *tree_remove(tree_node_t *node, const char *key, size_t *count_comp);

#endif