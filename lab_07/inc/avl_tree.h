#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <stdio.h>
#include <stdbool.h>

typedef struct avl_tree_node avl_tree_node_t;

struct avl_tree_node
{
    int height;
    avl_tree_node_t *left;
    avl_tree_node_t *right;
    char *val;
};

avl_tree_node_t *avl_tree_insert(avl_tree_node_t *root, char *val, size_t *count_comp);
avl_tree_node_t *avl_find_min(avl_tree_node_t *node);
avl_tree_node_t *avl_remove_startswith(avl_tree_node_t *root, char start, size_t *count_comp);
void avl_tree_clear(avl_tree_node_t *root);
void avl_save_as_dot(FILE *f, avl_tree_node_t *root);
bool avl_tree_has(avl_tree_node_t *root, const char *key, size_t *count_comp);
avl_tree_node_t *avl_tree_remove(avl_tree_node_t *node, const char *key, size_t *count_comp);

#endif