#ifndef __STRUCTS_H__
#define __STRUCTS_H__

typedef struct binary_tree
{
    struct branch *head;
    int size;
} binary_tree_t;

typedef struct branch
{
    char *word;
    struct branch *parent;
    struct branch *left;
    struct branch *right;
} branch_t;

#endif // __STRUCTS_H__