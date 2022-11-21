#include "../inc/print.h"

void print_menu_arr(void)
{
    printf("1. Добавить элементы в стек\n");
    printf("2. Добавить элементы в стек случайным образом\n");
    printf("3. Удалить элементы из стека\n");
    printf("4. Вывести текущий стек\n");
    printf("5. Распечатать убывающие серии последовательности целых чисел в обратном порядке\n");
    printf("0. Выход\n");
}

void print_menu_list(void)
{
    printf("1. Добавить элементы в стек\n");
    printf("2. Добавить элементы в стек случайным образом\n");
    printf("3. Удалить элементы из стека\n");
    printf("4. Вывести текущий стек\n");
    printf("5. Распечатать убывающие серии последовательности целых чисел в обратном порядке\n");
    printf("6. Показать список свободных адресов\n");
    printf("0. Выход\n");
}

void print_menu_time(void)
{
    printf("1. Сравнение времени и памяти для добавления\n");
    printf("2. Сравнение времени и памяти для удаления\n");
    printf("0. Выход\n");
}

void print_choice(void)
{
    printf("1. Заполнение стека с помощью списка\n");
    printf("2. Заполнение стека с помощью массива\n");
    printf("3. Сравнение по времени и памяти двух представлений\n");
    printf("0. Выход\n");
}

void print_array(stack_array_t *stack_array)
{
    printf("Размер стека - %d\n", stack_array->len);
    int *ptmp = stack_array->p;
    for (int i = stack_array->len; i > 0; i--)
        printf("%d ", *(ptmp--));
    printf("\n");
}

void print_series_nums_array(stack_array_t *stack_array)
{
    if (stack_array->len == 0)
    {
        printf("Стек пуст\n");
        return;
    }

    int prev_elem = *stack_array->p;
    stack_array->p--;
    int flag = 0;
    while (stack_array->len > 0)
    {
        if (*stack_array->p > prev_elem)
        {
            printf("%d ", prev_elem);
            flag = 1;
        }
        else if (flag == 1)
        {
            printf("%d\n", prev_elem);
            flag = 0;
        }
        prev_elem = *stack_array->p;
        stack_array->p--;
        stack_array->len--;
    }
    printf("\n");
}

void print_list(stack_list_t **stack_list)
{
    if (*stack_list == NULL)
    {
        printf("Размер стека - 0\n");
        return;
    }
    else
        printf("Размер стека - %d\n", (*stack_list)->num_elem);
    
    stack_list_t *ptmp = *stack_list;
    while (ptmp != NULL)
    {
        printf("%d ", ptmp->elem);
        ptmp = ptmp->next;
    }
    printf("\n");
}

void print_series_nums_list(stack_list_t *stack_list)
{
    if (stack_list == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    int prev_elem = stack_list->elem;
    stack_list = stack_list->next;
    int flag = 0;
    while (stack_list != NULL)
    {
        if (stack_list->elem > prev_elem)
        {
            printf("%d ", prev_elem);
            flag = 1;
        }
        else if (flag == 1)
        {
            printf("%d\n", prev_elem);
            flag = 0;
        }
        if (stack_list->next == NULL)
            break;
            
        prev_elem = stack_list->elem;
        stack_list = stack_list->next;
    }

    if (stack_list->elem > prev_elem)
        printf("%d\n", stack_list->elem);
}

void print_addresses_array(arr_free_area_t *arr)
{
    for (int i = 0; i < arr->len; i++)
        printf("%d %p\n", i, (void *)arr->arr[i]);
    printf("\n");
}