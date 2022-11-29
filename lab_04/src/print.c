#include "../inc/print.h"

void print_menu_arr(void)
{
    printf("\n");
    printf("1. Добавить элементы в стек\n");
    printf("2. Удалить элементы из стека\n");
    printf("3. Вывести текущий стек\n");
    printf("4. Распечатать убывающие серии последовательности целых чисел в обратном порядке\n");
    printf("0. Выход\n");
    printf("\n");
}

void print_menu_list(void)
{
    printf("\n");
    printf("1. Добавить элементы в стек\n");
    printf("2. Удалить элементы из стека\n");
    printf("3. Вывести текущий стек\n");
    printf("4. Распечатать убывающие серии последовательности целых чисел в обратном порядке\n");
    printf("5. Показать список свободных адресов\n");
    printf("0. Выход\n");
    printf("\n");
}

void print_menu_time(void)
{
    printf("\n");
    printf("1. Сравнение времени и памяти для добавления и удаления\n");
    printf("0. Выход\n");
    printf("\n");
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
    int *ptmp = stack_array->p;
    for (int i = stack_array->len; i > 0; i--)
        printf("%d ", *(ptmp--));
    printf("\n");
}

void print_series_nums_array(stack_array_t stack_array)
{
    if (stack_array.len == 0)
    {
        printf("Стек пуст\n");
        return;
    }

    if (stack_array.len == 1)
    {
        printf("%d\n", *stack_array.p);
        return;
    }

    int prev_elem = *stack_array.p;
    stack_array.p--;
    int flag = 0;
    int flag_count = 0;
    while (stack_array.len > 0)
    {
        if (*stack_array.p > prev_elem)
        {
            printf("%d ", prev_elem);
            flag = 1;
            flag_count = 1;
        }
        else if (flag == 1)
        {
            printf("%d\n", prev_elem);
            flag = 0;
        }
        prev_elem = *stack_array.p;
        stack_array.p--;
        stack_array.len--;
    }

    if (!flag_count)
        printf("Убывающих серий не найдено");
    printf("\n");
}

void print_list(stack_list_t **stack_list)
{
    if (*stack_list == NULL)
    {
        printf("Стек пуст\n");
        return;
    }
    
    stack_list_t *ptmp = *stack_list;
    while (ptmp != NULL)
    {
        printf("%d | %p\n", ptmp->elem, (void*)(ptmp));
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
    if (stack_list == NULL)
    {
        printf("%d\n", prev_elem);
        return;
    }

    int flag = 0;
    int flag_count = 0;
    while (stack_list != NULL)
    {
        if (stack_list->elem > prev_elem)
        {
            printf("%d ", prev_elem);
            flag = 1;
            flag_count = 1;
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

    if (!flag_count)
        printf("Убывающих серий не найдено\n");
}

void print_addresses_array(arr_adr_removed_elems_t *arr)
{
    if (arr->len == 0)
        printf("Элементы не удалялись\n");
    for (int i = 0; i < arr->len; i++)
        printf("%d | %p\n", i + 1, (void *)arr->arr[i]);
}
