#include "../inc/times.h"

unsigned long long milliseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;
    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

int compare_time(void)
{
    int action;
    int rc;
    int array[STACK_SIZE];
    stack_array_t stack_array;

    stack_array.len = 0;
    stack_array.p = array - 1;

    stack_list_t *stack_list = NULL;

    while(1)
    {
        print_menu_time();

        rc = read_action_time(&action);
        if (rc != EXIT_SUCCESS)
        {
            free_stack_list(&stack_list);
            return rc;
        }

        if (action == 1)
        {
            int num_elems;

            rc = read_num_elems_add_array(&num_elems, stack_array.len);
            if (rc != EXIT_SUCCESS)
                return rc;
            
            unsigned long long beg_common;
            unsigned long long end_common;

            if (stack_array.len != STACK_SIZE)
            {
                beg_common = milliseconds_now();
                for (int i = 0; i < 50; i++)
                {
                    fill_random_array(num_elems, &stack_array);
                    remove_elems_array(num_elems, &stack_array);
                }
                end_common = milliseconds_now();
                unsigned long long time_common = end_common - beg_common;

                printf("Затраченное время под стек-массив - %llu мc\n", time_common);
                printf("Затраченная память под стек-массив - %lu байт\n\n", STACK_SIZE * sizeof(stack_array_t));
                
                beg_common = milliseconds_now();
                for (int i = 0; i < 50; i++)
                {
                    fill_random_list(&stack_list, num_elems);
                    remove_elems_list(&stack_list, num_elems);
                }
                end_common = milliseconds_now();
                time_common = end_common - beg_common;

                printf("Затраченное время под стек-список - %llu мc\n", time_common);
                printf("Затраченная память под стек-список - %lu байт\n\n", num_elems * (sizeof(stack_list_t) + sizeof(int)));
            }
        }
        else if (action == 0)
        {
            free_stack_list(&stack_list);
            break;
        }
        
        if (rc != EXIT_SUCCESS)
        {
            free_stack_list(&stack_list);
            return rc;
        }
    }

    return EXIT_SUCCESS;
}