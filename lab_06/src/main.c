#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_tree.h"
#include "compare.h"
#include "errors.h"
#include "read_print.h"
#include "structs.h"

int main(void)
{
    binary_tree_t binary_tree;
    binary_tree.head = NULL;
    int rc;
    int action;

    while (1)
    {
        print_choice();
        rc = read_action(&action);
        if (rc != EXIT_SUCCESS)
            return rc;
        
        if (action == 1)
        {
            FILE *f = fopen("./data/tree.txt", "r");
            int rc = read_file(f, &binary_tree);
            if (rc == FOPEN_ERROR)
            {
                printf("Файл не найден\n");
                return FOPEN_ERROR;
            }
            printf("Дерево успешно инициализировано\n");
        }
        else if (action == 2)
        {
            if (binary_tree.head != NULL)
            {
                printf("Введите удаляемое слово:\n");
                char str[STR_LEN];
                if (scanf("%s", str) != 1)
                    return SCAN_STR_ERROR;
                if (str[strlen(str) - 1] == '\n')
                    str[strlen(str) - 1] = '\0';
                
                rc = delete_word(binary_tree.head, str);
                if (rc != EXIT_SUCCESS)
                    printf("Слово не найдено\n");
                else
                    printf("Слово удалено\n");
            }
            else
                printf("Дерево не было инициализировано\n");
        }
        else if (action == 3)
        {
            if (binary_tree.head != NULL)
            {
                printf("Введите слово, которое нужно найти:\n");
                char str[STR_LEN];
                if (scanf("%s", str) != 1)
                    return SCAN_STR_ERROR;
                if (str[strlen(str) - 1] == '\n')
                    str[strlen(str) - 1] = '\0';
                
                int flag = find_word(binary_tree.head, str);
                if (flag == EXIT_SUCCESS)
                    printf("Слово НАЙДЕНО в дереве\n");
                else
                {
                    printf("Слово НЕ НАЙДЕНО в дереве\n");
                    printf("Если хотите добавить его - введите 1, если нет - любое целое число\n");
                    int flag_add;
                    if (scanf("%d", &flag_add) != 1)
                        return SCAN_FLAG_ERROR;
                    if (flag_add == 1)
                    {
                        insert_tree(&binary_tree.head, str);
                        FILE *f = fopen("./data/tree.txt", "a");
                        insert_file(f, str);
                        fclose(f);
                        printf("Слово добавлено в файл и дерево\n");
                    }
                }
            }
            else
                printf("Дерево не было инициализировано\n");
        }
        else if (action == 4)
        {
            if (binary_tree.head != NULL)
            {
                FILE *f = fopen("tree.gv", "w");
                export_to_dot(f, "test_bin", binary_tree.head);
                fclose(f);
                system("./print_tree.sh");
            }
            else
                printf("Дерево не было инициализировано\n");
        }
        else if (action == 5)
            compare_time();
        else if (action == 0)
            break;
    }

    return EXIT_SUCCESS;
}