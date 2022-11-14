#include "../inc/array.h"

int process_stack_as_array(void)
{
    int rc;
    int array[STACK_SIZE];
    stack_array_t stack_array;
    stack_array.len = 0;
    stack_array.p = array - 1;
    int action;

    while(1)
    {
        print_menu_arr();
        rc = read_action_arr(&action);
        if (rc != EXIT_SUCCESS)
            return rc;

        if (action == 1)
        {
            int num_elems;

            rc = read_num_elems_add_array(&num_elems, stack_array.len);
            if (rc != EXIT_SUCCESS)
                return rc;
            
            if (stack_array.len != STACK_SIZE)
                rc = add_elems_array(num_elems, &stack_array);
        }
        else if (action == 2)
        {
            int num_elems;

            rc = read_num_elems_add_array(&num_elems, stack_array.len);
            if (rc != EXIT_SUCCESS)
                return rc;
            
            if (stack_array.len != STACK_SIZE)
                fill_random_array(num_elems, &stack_array);
        }
        else if (action == 3)
        {
            int num_elems;

            rc = read_num_elems_remove_array(&num_elems, stack_array.len);
            if (rc != EXIT_SUCCESS)
                return rc;
            
            if (stack_array.len != 0)
                remove_elems_array(num_elems, &stack_array);

        }
        else if (action == 4)
            print_array(&stack_array);
        else if (action == 5)
            print_series_nums_array(&stack_array);
        else if (action == 0)
            break;
        
        if (rc != EXIT_SUCCESS)
            return rc;
    }

    return EXIT_SUCCESS;
}

int add_elems_array(int num_elems, stack_array_t *stack_array)
{
    printf("Введите %d элементов(а):\n", num_elems);
    for (int i = 0; i < num_elems; i++)
    {
        stack_array->p++;
        if (scanf("%d", stack_array->p) != 1)
        {
            printf("Ошибка в чтении элемента\n");
            return SCAN_ELEM_ERROR;
        }
        stack_array->len++;
    }

    return EXIT_SUCCESS;
}

void fill_random_array(int num_elems, stack_array_t *stack_array)
{
    srand(time(NULL));
    for (int i = 0; i < num_elems; i++)
    {
        stack_array->p++;
        *stack_array->p = rand() % RANDOM_CONST + 1;
        stack_array->len++;
    }
}

void remove_elems_array(int num_elems, stack_array_t *stack_array)
{
    for (int i = 0; i < num_elems; i++)
    {
        stack_array->p--;
        stack_array->len--;
    }
}