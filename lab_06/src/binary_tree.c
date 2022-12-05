#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_tree.h"

branch_t *allocate_node(char *val, branch_t *branch)
{
    branch_t *tmp = malloc(sizeof(branch_t));
    if (tmp == NULL)
        return NULL;

    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = branch;
    tmp->word = val;

    return tmp;
}

int comparator(char *word_1, char *word_2)
{
    return strcmp(word_1, word_2);
}

void insert_tree(branch_t **head, char *val)
{
    if (!(*head))
    {
        *head = allocate_node(val, NULL);
        return;
    }

    branch_t *tmp = *head;

    while (tmp)
        if (comparator(val, tmp->word) > 0)
        {
            if (tmp->right)
            {
                tmp = tmp->right;
                continue;
            }
            else
            {
                tmp->right = allocate_node(val, tmp);
                return;
            }
        }
        else if (comparator(val, tmp->word) < 0)
        {
            if (tmp->left)
            {
                tmp = tmp->left;
                continue;
            }
            else
            {
                tmp->left = allocate_node(val, tmp);
                return;
            }
        }
        else
            return;
}

int find_word(branch_t *root, char *str)
{
    branch_t *target = get_node(root, str);
    if (!target)
        return FIND_ERROR;
    return EXIT_SUCCESS;
}

void delete(branch_t *cur)
{
    if (cur->left != NULL && cur->right != NULL)
    {
        branch_t *tmp = get_deep_node(cur->left);
        cur->word = tmp->word;
        delete(tmp);
        return;
    }
    else if (cur->left != NULL)
    {
        if (cur == cur->parent->left)
            cur->parent->left = cur->left;
        else
            cur->parent->right = cur->right;
    }
    else if (cur->right != NULL)
    {
        if (cur == cur->parent->right)
            cur->parent->right = cur->right;
        else
            cur->parent->left = cur->right;
    }
    else
    {
        if (cur == cur->parent->left)
            cur->parent->left = NULL;
        else
            cur->parent->right = NULL;
    }

    free(cur);
}

int delete_word(branch_t *root, char *str)
{
    branch_t *target = get_node(root, str);
    if (!target)
        return DELETE_ERROR;
    delete(target);

    return EXIT_SUCCESS;
}

branch_t *get_deep_node(branch_t *root)
{
    while (root->right != NULL)
        root = root->right;
    return root;
}

branch_t *get_node(branch_t *root, char *str) 
{
    while (root)
    {
        if (comparator(root->word, str) > 0)
        {
            root = root->left;
            continue;
        }
        else if (comparator(root->word, str) < 0)
        {
            root = root->right;
            continue;
        } 
        else
            return root;
    }
    return NULL;
}