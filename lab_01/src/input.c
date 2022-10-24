#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/structs.h"
#include "../inc/input.h"
#include "../inc/constants.h"
#include "../inc/errors.h"

int my_float_input(float_t *a)
{
    char symb = getchar();
    if (symb == '\n')
    {
        printf("Пустой ввод\n");
        return EMPTY_INPUT_ERROR;
    }
    if (symb != '+' && symb != '-')
    {
        printf("Ошибка ввода: вначале не был введен знак\n");
        return SIGN_ERROR;
    }
    a->sign = symb;

    int i;
    int addition_order = 0;
    int flag_dot = 0;
    int flag_digit = 0;

    for (i = 0, symb = getchar(); (symb != '\n') && (symb != 'e') && (symb != 'E'); symb = getchar())
    {
        if (i >= MANTISSA_LEN)
        {
            printf("Произошло переполнение\n");
            return OVERFLOW_ERROR;
        }
        if (symb == '.')
        {
            if (flag_dot == 0)
                flag_dot = 1;
            else
            {
                printf("Ошибка ввода: было введено более одной точки\n");
                return INPUT_DOT_ERROR;
            }
        }
        else
        {
            if ((symb >= '0') && (symb <= '9'))
            {
                if (flag_dot == 0)
                {
                    if ((symb > '0') || (i > 0))
                    {
                        a->mantissa[i] = atoi(&symb);
                        flag_digit = 1;
                        addition_order++;
                        i++;
                    }
                }
                else
                {
                    if ((symb > '0') || (flag_digit != 0))
                    {
                         a->mantissa[i] = atoi(&symb);
                         flag_digit = 1;
                         i++;
                    }
                    else
                        addition_order--;
                }
            }
            else
            {
                printf("Ошибка ввода: были введены не цифры\n");
                return INPUT_DIGIT_ERROR;
            }
        }
    }

    if ((symb == 'e') || (symb == 'E'))
    {
        if (scanf("%d", &(a->order)) != 1)
        {
            printf("Ошибка ввода: в порядке были введены не цифры\n");
            return TYPE_ERROR;
        }
        if (a->order < MIN_ORDER)
        {
            printf("Порядок меньше критического значения\n");
            return ORDER_ERROR;
        }
        else if (a->order > MAX_ORDER)
        {
            printf("Порядок больше критического значения\n");
            return ORDER_ERROR;
        }
        getchar();
    }

    if (i == 0 && a->order != 0)
    {
        printf("Если хотите ввести ноль - вводите его c нулевым порядком\n");
        return ZERO_ERROR;
    }
    a->order += addition_order;

    return EXIT_SUCCESS;
}

int my_integer_input(integer_t *b, int *int_len)
{
    char symb = getchar();
    if (symb == '\n')
    {
        printf("Пустой ввод");
        return EMPTY_INPUT_ERROR;
    }
    if (symb != '+' && symb != '-')
    {
        printf("Ошибка ввода: вначале не был введен знак\n");
        return SIGN_ERROR;
    }
    b->sign = symb;

    int i;
    int flag_zero = 1;
    symb = getchar();

    for (i = 0; symb != '\n'; symb = getchar())
    {
        if (i >= MANTISSA_LEN)
        {
            printf("Произошло переполнение");
            return OVERFLOW_ERROR;
        }
        if (symb >= '0' && symb <= '9')
        {
            if (symb > '0' || flag_zero == 0)
            {
                b->digits[(*int_len)] = atoi(&symb);
                (*int_len)++;
                flag_zero = 0;
                i++;
            }
        }
        else
        {
            printf("Ошибка ввода: были введены не цифры\n");
            return INPUT_DIGIT_ERROR;
        }
    }
    if (flag_zero == 1)
    {
        printf("Деление на ноль невозможно\n");
        return DIVISION_BY_ZERO;
    }
    
    return EXIT_SUCCESS;
}