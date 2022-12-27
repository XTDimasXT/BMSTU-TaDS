#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "tree.h"

void tree_clear(tree_node_t *root)
{
    if (root == NULL)
        return;
    tree_clear(root->left);
    tree_clear(root->right);
    free(root->val);
    free(root);
}

tree_node_t *tree_insert(tree_node_t *root, char *val, size_t *count_comp)
{
    assert(val != NULL);
    tree_node_t *inserted;
    if (!root)
    {
        inserted = calloc(1, sizeof(tree_node_t));
        if (inserted == NULL)
            return NULL;
        inserted->val = strdup(val);
        if (inserted->val == NULL)
        {
            free(inserted);
            return NULL;
        }
        return inserted;
    }
    int comp_res = strcmp(val, root->val);
    *count_comp += 1;
    if (comp_res == 0)
        return root;

    if (comp_res < 0)
    {
        tree_node_t *left = tree_insert(root->left, val, count_comp);
        if (left == NULL)
            return NULL;
        root->left = left;
    }
    else
    {
        tree_node_t *right = tree_insert(root->right, val, count_comp);
        if (right == NULL)
            return NULL;
        root->right = right;
    }

    return root;
}

tree_node_t *find_min(tree_node_t *node)
{
    tree_node_t *min = node;
    while (min->left != NULL)
        min = min->left;
    return min;
}

tree_node_t *find_max(tree_node_t *node)
{
    tree_node_t *max = node;
    while (max->right != NULL)
        max = max->right;
    return max;
}

static tree_node_t *remove_min(tree_node_t *node)
{
    if (node->left == NULL)
        return node->right;
    node->left = remove_min(node->left);
    return node;
}

tree_node_t *tree_remove(tree_node_t *node, const char *key, size_t *count_comp)
{
    if (!node)
        return NULL;
    int comp_res = strcmp(key, node->val);
    *count_comp += 1;
    if (comp_res == 0)
    {
        tree_node_t *left = node->left;
        tree_node_t *right = node->right;
        free(node->val);
        free(node);
        if (left == NULL && right == NULL)
            return NULL;
        if (right == NULL)
            return left;
        tree_node_t *min = find_min(right);
        min->right = remove_min(right);
        min->left = left;
        return min;
    }
    if (comp_res < 0)
        node->left = tree_remove(node->left, key, count_comp);
    else
        node->right = tree_remove(node->right, key, count_comp);
    return node;
}

tree_node_t *remove_startswith(tree_node_t *root, char start, size_t *count_comp)
{
    if (root == NULL)
    {
        return NULL;
    }

    int comp_res = (int)start - root->val[0];
    *count_comp += 1;
    if (comp_res == 0)
    {
        tree_node_t *left = root->left;
        tree_node_t *right = root->right;
        free(root->val);
        free(root);

        if (left == NULL && right == NULL)
            return NULL;
        if (right == NULL)
            return remove_startswith(left, start, count_comp);
        tree_node_t *min = find_min(right);
        min->right = remove_min(right);
        min->left = left;
        return remove_startswith(min, start, count_comp);
        
    }
    if (comp_res < 0)
        root->left = remove_startswith(root->left, start, count_comp);
    else
        root->right = remove_startswith(root->right, start, count_comp);
    
    return root;
}

static void __tree_save_as_dot(FILE *f, tree_node_t *node, tree_node_t *parent)
{
    if (node == NULL)
        return;
    __tree_save_as_dot(f, node->left, node);
    __tree_save_as_dot(f, node->right, node);
    if (parent != NULL)
        fprintf(f, "%s -> %s;\n", parent->val, node->val);
    else
        fprintf(f, "%s;\n", node->val);
}

void tree_save_as_dot(FILE *f, tree_node_t *root)
{
    fprintf(f, "digraph Graph {\n");
    __tree_save_as_dot(f, root, NULL);
    fprintf(f, "}\n");
}

static tree_node_t *__tree_has(tree_node_t *node, const char *key, size_t *count_comp)
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

bool tree_has(tree_node_t *root, const char *key, size_t *count_comp)
{
    return __tree_has(root, key, count_comp) != NULL;
}
