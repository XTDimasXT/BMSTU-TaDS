#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "print.h"
#include "queue_array.h"
#include "queue_list.h"
#include "structs.h"
#include "times.h"

int get_random_num(void)
{
    srand(time(NULL));
    return rand() % 100 + 1;
}

int main(void)
{
    int option = -1;
    int rc = 0;

    arr_t queue_arr;
    init_arr_queue(&queue_arr);

    list_t queue_list;
    init_list_queue(&queue_list);

    arr_clear_t clear_arr = {.len = 0};

    while (option != 0)
    {
        print_menu();

        rc = scanf("%d", &option);

        if ((rc != 1) || (option < 0) || (option > 10))
        {
            puts("\nНомер меню - число от 0 до 10");
            return MENU_ERROR;
        }

        if (option == 1)
        {
            int num = get_random_num();

            if (!owerflow_arr_queue(queue_arr))
            {
                push_arr_queue(&queue_arr, num);
            }
            else
            {
                printf("\nОшибка: очередь переполнена\n\n");
                return OVERFLOW_ERROR;
            }
        }
        
        if (option == 2)
        {
            if (!clear_check_arr_queue(queue_arr))
            {
                pop_arr_queue(&queue_arr);
            }
            else
            {
                printf("\n\nОчередь пустая\n\n");
            }
            
        }

        if (option == 3)
        {
            print_arr_queue(queue_arr);
        }

        if (option == 4)
        {
            int num = get_random_num();
            push_list_queue(&queue_list, num);
            del_adress(&clear_arr, &queue_list);
        }
        
        if (option == 5)
        {
            if (!clear_check_list(queue_list))
            {
                add_adress(&clear_arr, &queue_list);
                pop_list_queue(&queue_list);
            }
            else
            {
                printf("\n\nОчередь пустая\n\n");
            }
        }

        if (option == 6)
        {
            print_list_queue(queue_list);
        }

        if (option == 7)
        {
            print_arr_adress(clear_arr);
        }

        if (option == 8)
        {
            task_arr();
        }

        if (option == 9)
        {
            task_list();
        }

        if (option == 10)
        {
            time_counting();
        }
    }
}