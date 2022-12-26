#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "avl_tree.h"

int get_height(avl_tree_node_t *node)
{
    if (!node)
        return 0;
    return node->height;
}

void fix_height(avl_tree_node_t *node)
{
    int left = get_height(node->left);
    int right = get_height(node->right);
    if (left < right)
        node->height = right + 1;
    else
        node->height = left + 1;
}

int balance_factor(avl_tree_node_t *node)
{
    return get_height(node->right) - get_height(node->left);
}

avl_tree_node_t *rotate_right(avl_tree_node_t *node)
{
    avl_tree_node_t *new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    fix_height(node);
    fix_height(new_root);
    return new_root;
}

static avl_tree_node_t *rotate_left(avl_tree_node_t *node)
{
    avl_tree_node_t *new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    fix_height(node);
    fix_height(new_root);
    return new_root;
}

avl_tree_node_t *balance(avl_tree_node_t *node)
{
    if (node == NULL)
        return NULL;
    fix_height(node);
    if (balance_factor(node) == 2)
    {
        if (balance_factor(node->right) < 0)
            node->right = rotate_right(node->right);
        node = rotate_left(node);
    }
    else if (balance_factor(node) == -2)
    {
        if (balance_factor(node->left) > 0)
            node->left = rotate_left(node->left);
        node = rotate_right(node);
    }
    return node;
}

avl_tree_node_t *avl_tree_insert(avl_tree_node_t *root, char *val, size_t *count_comp)
{
    if (!root)
    {
        avl_tree_node_t *new_node = calloc(1, sizeof(avl_tree_node_t));
        if (new_node == NULL)
            return NULL;
        new_node->height = 1;
        new_node->val = strdup(val);
        if (new_node->val == NULL)
        {
            free(new_node);
            return NULL;
        }
        return new_node;
    }
    int comp_res = strcmp(val, root->val);
    *count_comp += 1;
    if (comp_res == 0)
        return root;
    if (comp_res < 0)
    {
        avl_tree_node_t *left = avl_tree_insert(root->left, val, count_comp);
        if (left == NULL)
            return left;
        root->left = left;
    }
    else
    {
        avl_tree_node_t *right = avl_tree_insert(root->right, val, count_comp);
        if (right == NULL)
            return right;
        root->right = right;
    }
    return balance(root);
}

avl_tree_node_t *avl_find_min(avl_tree_node_t *node)
{
    avl_tree_node_t *min = node;
    while (min->left != NULL)
        min = min->left;
    return min;
}


static avl_tree_node_t *avl_remove_min(avl_tree_node_t *node)
{
    if (node->left == NULL)
        return node->right;
    node->left = avl_remove_min(node->left);
    return node;
}

avl_tree_node_t *avl_remove_startswith(avl_tree_node_t *root, char start, size_t *count_comp)
{
    if (root == NULL)
        return NULL;

    int comp_res = (int)start - root->val[0];
    *count_comp += 1;
    if (comp_res == 0)
    {
        avl_tree_node_t *left = root->left;
        avl_tree_node_t *right = root->right;
        free(root->val);
        free(root);

        if (left == NULL && right == NULL)
            return NULL;
        if (right == NULL)
            return avl_remove_startswith(left, start, count_comp);
        avl_tree_node_t *min = avl_find_min(right);
        min->right = avl_remove_min(right);
        min->left = left;
        return balance(avl_remove_startswith(min, start, count_comp));
        
    }
    if (comp_res < 0)
        root->left = avl_remove_startswith(root->left, start, count_comp);
    else
        root->right = avl_remove_startswith(root->right, start, count_comp);
    
    return balance(root);
}

void avl_tree_clear(avl_tree_node_t *root)
{
    if (root == NULL)
        return;
    avl_tree_clear(root->left);
    avl_tree_clear(root->right);
    free(root->val);
    free(root);
}

static void __avl_save_as_dot(FILE *f, avl_tree_node_t *node, avl_tree_node_t *parent)
{
    if (node == NULL)
        return;
    __avl_save_as_dot(f, node->left, node);
    __avl_save_as_dot(f, node->right, node);
    if (parent != NULL)
        fprintf(f, "%s -> %s;\n", parent->val, node->val);
    else
        fprintf(f, "%s;\n", node->val);
}

void avl_save_as_dot(FILE *f, avl_tree_node_t *root)
{
    fprintf(f, "digraph Graph {\n");
    __avl_save_as_dot(f, root, NULL);
    fprintf(f, "}\n");
}

static avl_tree_node_t *__tree_has(avl_tree_node_t *node, const char *key, size_t *count_comp)
{
    if (!node)
        return NULL;
    int comp_res = strcmp(key, node->val);
    *count_comp += 1;
    if (comp_res == 0)
        return node;
    if (comp_res < 0)
        return __tree_has(node->left, key, count_comp);
    return __tree_has(node->right, key, count_comp);
}

bool avl_tree_has(avl_tree_node_t *root, const char *key, size_t *count_comp)
{
    return __tree_has(root, key, count_comp) != NULL;
}

avl_tree_node_t *avl_tree_remove(avl_tree_node_t *node, const char *key, size_t *count_comp)
{
    if (!node)
        return NULL;
    int comp_res = strcmp(key, node->val);
    *count_comp += 1;
    if (comp_res == 0)
    {
        avl_tree_node_t *left = node->left;
        avl_tree_node_t *right = node->right;
        free(node->val);
        free(node);
        if (left == NULL && right == NULL)
            return NULL;
        if (right == NULL)
            return left;
        avl_tree_node_t *min = avl_find_min(right);
        min->right = avl_remove_min(right);
        min->left = left;
        return balance(min);
    }
    if (comp_res < 0)
        node->left = avl_tree_remove(node->left, key, count_comp);
    else
        node->right = avl_tree_remove(node->right, key, count_comp);
    return balance(node);
}
