#include "../inc/list.h"

int process_stack_as_list(void)
{
    int rc;
    stack_list_t *stack_list = NULL;
    arr_free_area_t arr;
    arr.arr = NULL;
    arr.len = 0;
    int action;

    while (1)
    {
        print_menu_list();
        rc = read_action(&action);
        if (rc != EXIT_SUCCESS)
        {
            free_stack_list(&stack_list);
            free(arr.arr);
            return rc;
        }

        if (action == 1)
        {
            int num_elems;

            rc = read_num_elems_add_list(&num_elems, stack_list);
            if (rc != EXIT_SUCCESS)
            {
                free_stack_list(&stack_list);
                free(arr.arr);
                return rc;
            }
            
            if ((stack_list != NULL && stack_list->num_elem != STACK_SIZE) || stack_list == NULL)
                rc = add_elems_list(&stack_list, num_elems);
        }
        else if (action == 2)
        {
            int num_elems;

            rc = read_num_elems_add_list(&num_elems, stack_list);
            if (rc != EXIT_SUCCESS)
            {
                free_stack_list(&stack_list);
                free(arr.arr);
                return rc;
            }
            
            if ((stack_list != NULL && stack_list->num_elem != STACK_SIZE) || stack_list == NULL)
                fill_random_list(&stack_list, num_elems);
        }
        else if (action == 3)
        {
            int num_elems;

            rc = read_num_elems_remove_list(&num_elems, stack_list);
            if (rc != EXIT_SUCCESS)
            {
                free_stack_list(&stack_list);
                free(arr.arr);
                return rc;
            }

            if (stack_list != NULL)
            {
                rc = add_addresses_removed_elems(num_elems, stack_list, &arr);
                if (rc != EXIT_SUCCESS)
                {
                    free_stack_list(&stack_list);
                    return rc;
                }
                remove_elems_list(&stack_list, num_elems);
            }
        }
        else if (action == 4)
            print_list(&stack_list);
        else if (action == 5)
            print_series_nums_list(&stack_list);
        else if (action == 6)
            print_addresses_array(&arr);
        else if (action == 0)
        {
            free_stack_list(&stack_list);
            free(arr.arr);
            break;
        }

        if (rc != EXIT_SUCCESS)
        {
            free_stack_list(&stack_list);
            free(arr.arr);
            return rc;
        }
    }

    return EXIT_SUCCESS;
}

void free_stack_list(stack_list_t **stack_list)
{
    stack_list_t *ptmp;

    while (*stack_list != NULL)
    {
        ptmp = (*stack_list)->next;
        free(*stack_list);
        *stack_list = ptmp;
    }
}

int add_elems_list(stack_list_t **stack_list, int num_elems)
{
    stack_list_t *new_elem;

    for (int i = 0; i < num_elems; i++)
    {
        new_elem = malloc(sizeof(stack_list_t));
        if (new_elem == NULL)
        {
            printf("Ошибка выделения памяти\n");
            return MALLOC_ERROR;
        }

        if (scanf("%d", new_elem->elem) != 1)
        {
            printf("Ошибка в чтении элемента\n");
            free(new_elem);
            return SCAN_ELEM_ERROR;
        }

        if (*stack_list == NULL)
            new_elem->num_elem = 1;
        else
            new_elem->num_elem = (*stack_list)->num_elem++;
        
        new_elem->next = *stack_list;
        *stack_list = new_elem;
    }
    
    return EXIT_SUCCESS;
}

void fill_random_list(stack_list_t **stack_list, int num_elems)
{
    stack_list_t *new_elem;
    srand(time(NULL));

    for (int i = 0; i < num_elems; i++)
    {
        new_elem = malloc(sizeof(stack_list_t));
        if (new_elem == NULL)
        {
            printf("Ошибка выделения памяти\n");
            return MALLOC_ERROR;
        }

        new_elem->elem = rand() % RANDOM_CONST + 1;

        if (*stack_list == NULL)
            new_elem->num_elem = 1;
        else
            new_elem->num_elem = (*stack_list)->num_elem++;
        
        new_elem->next = *stack_list;
        *stack_list = new_elem;
    }
}

int add_addresses_removed_elems(int *num_elems, stack_list_t *stack_list, arr_free_area_t *arr)
{
    stack_list_t *ptmp;
    for (int i = 0; i < num_elems; i++)
    {
        ptmp = realloc(arr->arr, (arr->len + 1) * sizeof(stack_list_t*));
        if (ptmp == NULL)
        {
            free(arr->arr);
            printf("Ошибка выделения памяти\n");
            return REALLOC_ERROR;
        }

        arr->arr = ptmp;
        arr->arr[arr->len] = stack_list;
        arr->len++;
        stack_list = stack_list->next;
    }

    return EXIT_SUCCESS;
}

void remove_elems_list(stack_list_t **stack_list, int num_elems)
{
    stack_list_t *new_elem;
    for (int i = 0; i < num_elems; i++)
    {
        new_elem = (*stack_list)->next;
        free(*stack_list);
        *stack_list = new_elem;
    }
}