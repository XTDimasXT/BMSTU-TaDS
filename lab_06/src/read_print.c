#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_print.h"

static int cnt = 0;

int read_action(int *action)
{
    if (scanf("%d", action) != 1)
    {
        printf("Номер меню - целое число\n");
        return SCAN_ACTION_ERROR;
    }

    if (*action < 0 || *action > 7)
    {
        printf("Номер меню - целое число от 0 до 7\n");
        return VALUE_ACTION_ERROR;
    }

    return EXIT_SUCCESS;
}

void print_choice(void)
{
    printf("\n");
    printf("1. Инициализировать дерево из файла\n");
    printf("2. Исключить узел\n");
    printf("3. Найти указанное слово\n");
    printf("4. Вывести дерево\n");
    printf("5. Сравнить время поиска в дереве и файле\n");
    printf("6. Сравнить время добавления в дереве и файле\n");
    printf("7. Сравнить время удаления в дереве и файле\n");
    printf("0. Выход\n");
    printf("\n");
}

int read_file(FILE *f, binary_tree_t *binary_tree)
{
    if (f == NULL)
        return FOPEN_ERROR;
    
    while (1)
    {
        int rc = read_line(f, binary_tree);
        if (rc != EXIT_SUCCESS)
            return rc;
    }
}

int read_line(FILE *f, binary_tree_t *binary_tree)
{
    ssize_t read;
    size_t len = 0;
    char *line = NULL;

    read = getline(&line, &len, f);
    if (read == -1 || !line)
        return GETLINE_ERROR;
    
    if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';
    
    insert_tree(&binary_tree->head, line);

    return EXIT_SUCCESS;
}

void apply(branch_t *tree, action_t f, void *arg)
{
    if (tree == NULL)
        return;
    
    apply(tree->left, f, arg);
    f(tree, arg);
    apply(tree->right, f, arg);
}

/*
void apply_pre(branch_t *tree, action_t f, void *arg)
{
    if (tree == NULL)
        return;
    
    f(tree, arg);
    apply_pre(tree->left, f, arg);
    apply_pre(tree->right, f, arg);
}

void apply_after(branch_t *tree, action_t f, void *arg)
{
    if (tree == NULL)
        return;
    
    apply_after(tree->left, f, arg);
    apply_after(tree->right, f, arg);
    f(tree, arg);
}
*/

void print_tree(FILE *f, branch_t *head)
{
    fprintf(f, "%s\n", head->word);
    if (head->left != NULL)
        print_tree(f, head->left);
    if (head->right != NULL)
        print_tree(f, head->right);
}

void to_dot(void *node, void *param)
{
    branch_t *node_cur = node;
    FILE *out = param;

    if (node_cur->left != NULL)
        fprintf(out, "%s -> %s;\n", node_cur->word, node_cur->left->word);
    if (node_cur->right != NULL)
        fprintf(out, "%s -> %s;\n", node_cur->word, node_cur->right->word);
}

void export_to_dot(FILE *f, char *tree_name, void *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);
    apply(tree, to_dot, f);
    fprintf(f, "}\n");
    cnt = 0;
}

void insert_file(FILE *f, char *str)
{
    fprintf(f, "%s\n", str);
}