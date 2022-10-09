#include <stdio.h>
#include <stdlib.h>

#include "../inc/sort.h"
#include "../inc/errors.h"
#include "../inc/print.h"
#include "../inc/times.h"
#include "../inc/info.h"
#include "../inc/read.h"
#include "../inc/commands.h"


int main(void)
{
    int option;
    int temp;
    char name_file[] = "test.txt";
    table_t table;
    table.size = 0;

    while (1)
    {
        print_menu();
        temp = read_option(&option);
        if (temp)
            return temp;
        if (option == 1)
            temp = fill_table(name_file, &table);
        else if (option == 2)
            print_table(&table);
        else if (option == 3)
            temp = add_performance(&table);
        else if (option == 4)
            temp = delete_lines(&table);
        else if (option == 5)
            temp = print_required_performances(&table);
        else if (option == 6)
            print_keys(&table);
        else if (option == 7)
            sort_keys_qsort(&table);
        else if (option == 8)
            sort_keys_choice(&table);
        else if (option == 9)
            sort_qsort(&table);
        else if (option == 10)
            sort_choice(&table);
        else if (option == 11)
            sort_keys(&table);
        else if (option == 12)
            compare_sorts(name_file, &table);
        else if (option == 0)
            break;
    }
    return EXIT_SUCCESS;
}