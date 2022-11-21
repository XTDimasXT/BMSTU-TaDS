#include "../inc/read.h"

int read_method(int *method)
{
    if (scanf("%d", method) != 1)
    {
        printf("Номер меню - целое число\n");
        return SCAN_METHOD_ERROR;
    }

    if (*method < 0 || *method > 3)
    {
        printf("Номер меню - целое число от 0 до 3\n");
        return VALUE_METHOD_ERROR;
    }

    return EXIT_SUCCESS;
}

int read_action_arr(int *action)
{
    if (scanf("%d", action) != 1)
    {
        printf("Действие - целое число\n");
        return SCAN_ACTION_ERROR;
    }

    if (*action < 0 || *action > 5)
    {
        printf("Действие - целое число от 0 до 5\n");
        return VALUE_ACTION_ERROR;
    }

    return EXIT_SUCCESS;
}

int read_action_list(int *action)
{
    if (scanf("%d", action) != 1)
    {
        printf("Действие - целое число\n");
        return SCAN_ACTION_ERROR;
    }

    if (*action < 0 || *action > 6)
    {
        printf("Действие - целое число от 0 до 6\n");
        return VALUE_ACTION_ERROR;
    }

    return EXIT_SUCCESS;
}

int read_action_time(int *action)
{
    if (scanf("%d", action) != 1)
    {
        printf("Действие - целое число\n");
        return SCAN_ACTION_ERROR;
    }

    if (*action < 0 || *action > 2)
    {
        printf("Действие - целое число от 0 до 2\n");
        return VALUE_ACTION_ERROR;
    }

    return EXIT_SUCCESS;
}

int read_num_elems_add_array(int *num_elems, int len)
{
    if (len == STACK_SIZE)
    {
        printf("Стек заполнен\n");
        return EXIT_SUCCESS;
    }

    printf("Введите количество добавляемых элементов (не более %d):\n", STACK_SIZE - len);
    if (scanf("%d", num_elems) != 1)
    {
        printf("Количество добавляемых элементов - натуральное число\n");
        return SCAN_NUM_ELEMS_ERROR;
    }

    if (*num_elems <= 0)
    {
        printf("Количество добавляемых элементов - натуральное число\n");
        return VALUE_NUM_ELEMS_ERROR;
    }

    if (*num_elems + len > STACK_SIZE)
    {
        printf("Слишком много элементов для добавления\n");
        return OVERFLOW_ERROR;
    }

    return EXIT_SUCCESS;
}

int read_num_elems_remove_array(int *num_elems, int len)
{
    if (len == 0)
    {
        printf("Стек пуст\n");
        return EXIT_SUCCESS;
    }

    printf("Введите количество удаляемых элементов: (не более %d)\n", len);
    if (scanf("%d", num_elems) != 1)
    {
        printf("Количество удаляемых элементов - натуральное число\n");
        return SCAN_NUM_ELEMS_ERROR;
    }

    if (*num_elems <= 0)
    {
        printf("Количество удаляемых элементов - натуральное число\n");
        return VALUE_NUM_ELEMS_ERROR;
    }

    if (*num_elems > len)
    {
        printf("Слишком много элементов для удаления\n");
        return OVERFLOW_ERROR;
    }

    return EXIT_SUCCESS;
}

int read_num_elems_add_list(int *num_elems, stack_list_t *stack_list)
{
    if (stack_list != NULL && stack_list->num_elem == STACK_SIZE)
    {
        printf("Стек заполнен\n");
        return EXIT_SUCCESS;
    }

    if (stack_list == NULL)
        printf("Введите количество добавляемых элементов (не более %d)\n", STACK_SIZE);
    else
        printf("Введите количество добавляемых элементов (не более %d)\n", STACK_SIZE - stack_list->num_elem);
    
    if (scanf("%d", num_elems) != 1)
    {
        printf("Количество добавляемых элементов - натуральное число\n");
        return SCAN_NUM_ELEMS_ERROR;
    }

    if (*num_elems <= 0)
    {
        printf("Количество добавляемых элементов - натуральное число\n");
        return VALUE_NUM_ELEMS_ERROR;
    }

    if (stack_list == NULL && *num_elems > STACK_SIZE)
    {
        printf("Слишком много элементов для добавления\n");
        return OVERFLOW_ERROR;
    }

    if (stack_list != NULL && *num_elems + stack_list->num_elem > STACK_SIZE)
    {
        printf("Слишком много элементов для добавления\n");
        return OVERFLOW_ERROR;
    }

    return EXIT_SUCCESS;
}

int read_num_elems_remove_list(int *num_elems, stack_list_t *stack_list)
{
    if (stack_list == NULL)
    {
        printf("Стек пуст\n");
        return EXIT_SUCCESS;
    }

    printf("Введите количество удаляемых элементов: (не более %d)\n", stack_list->num_elem);
    if (scanf("%d", num_elems) != 1)
    {
        printf("Количество удаляемых элементов - натуральное число\n");
        return SCAN_NUM_ELEMS_ERROR;
    }

    if (*num_elems <= 0)
    {
        printf("Количество удаляемых элементов - натуральное число\n");
        return VALUE_NUM_ELEMS_ERROR;
    }

    if (*num_elems > stack_list->num_elem)
    {
        printf("Слишком много элементов для удаления\n");
        return OVERFLOW_ERROR;
    }

    return EXIT_SUCCESS;
}