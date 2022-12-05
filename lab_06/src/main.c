#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            read_file(&binary_tree);
        else if (action == 2)
        {
            printf("Введите удаляемое слово:\n");
            char str[STR_LEN];
            if (scanf("%s", str) != 1)
                return SCAN_STR_ERROR;
            if (str[strlen(str) - 1] == '\n')
                str[strlen(str) - 1] = '\0';
            
            delete_word(binary_tree.head, str);
        }
        else if (action == 3)
        {
            printf("Введите слово, которое нужно найти:\n");
            char str[STR_LEN];
            if (scanf("%s", str) != 1)
                return SCAN_STR_ERROR;
            if (str[strlen(str) - 1] == '\n')
                str[strlen(str) - 1] = '\0';
            
            int flag = find_word(binary_tree.head, str);
            if (flag == 1)
                printf("Слово НАЙДЕНО в дереве\n");
            else
                printf("Слово НЕ НАЙДЕНО в дереве\n");
        }
        else if (action == 4)
        {
            FILE *f = fopen("tree.gv", "w");
            export_to_dot(f, "test_bin", binary_tree.head);
            fclose(f);
            system("./print_tree.sh");
        }
        else if (action == 0)
            break;
    }

    return EXIT_SUCCESS;
}