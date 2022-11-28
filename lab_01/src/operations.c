#include <stdio.h>
#include <stdlib.h>

#include "operations.h"

void remove_zeroes(num_t *num)
{
    for (int i = num->size - 1; i >= 0 && !num->mantissa[i]; i--)
        num->size--;
}

void swap_right(int arr[ARR_LEN], int n)
{
    for (int i = n - 1; i >= 0; i--)
        arr[i + 1] = arr[i];
    arr[0] = 0;
}

void rounding(num_t *num, int n)
{
    int remainder = 0;
    int k = n - 1;
    num->mantissa[k]++;
    while ((num->mantissa[k] += remainder) > 9)
    {
        if (k == 0 && num->mantissa[k] > 9)
        {
            k = n - 1;
            swap_right(num->mantissa, n);
            num->mantissa[0] = num->mantissa[1] / 10;
            num->mantissa[1] %= 10;
            num->order++;
        }

        remainder = num->mantissa[k] / 10;
        num->mantissa[k] %= 10;
        k--;
    }
    num->order++;
}

void multiplication(num_t *num1, num_t *num2, num_t *res)
{
    int remainder = 0;
    int res_m = 0;

    for (int i = num2->size - 1; i >= 0; i--)
    {
        int flag = 0;
        remainder = 0;

        for (int j = num1->size - 1; j >= 0; j--)
        {
            int x = num2->mantissa[i] * num1->mantissa[j] + remainder;

            if (j == 0 && x > 9)
            {
                x += res->mantissa[j];
            
                res_m++;
                swap_right(res->mantissa, num1->size + res_m);
                res->mantissa[0] = x / 10;
                res->mantissa[1] = x % 10;
                if (num1->size + res_m > 30 && res->mantissa[num1->size + res_m - 1] >= 5)
                {
                    rounding(res, num1->size + res_m - 1);
                    res_m--;
                }
                else if (num1->size + res_m > 30 && res->mantissa[num1->size + res_m - 1] < 5)
                {
                    res->mantissa[num1->size + res_m - 1] = 0;
                    res_m--;
                    res->order++;
                }

                flag = 1;
                break;
            }
            remainder = (res->mantissa[j] + x) / 10;
            res->mantissa[j] = (res->mantissa[j] + x) % 10;
        }

        if (!flag && i && !remainder)
        {
            res_m++;
            swap_right(res->mantissa, num1->size + res_m);
            if (num1->size + res_m > 30 && res->mantissa[num1->size + res_m - 1] >= 5)
            {
                rounding(res, num1->size + res_m - 1);
                res_m--;
            }
            else if (num1->size + res_m > 30 && res->mantissa[num1->size + res_m - 1] < 5)
            {
                res->mantissa[num1->size + res_m - 1] = 0;
                res_m--;
                res->order++;
            }
        }
        else if (!flag && remainder)
        {
            res_m++;
            swap_right(res->mantissa, num1->size + res_m);
            res->mantissa[0] += remainder % 10;
            if (num1->size + res_m > 30 && res->mantissa[num1->size + res_m - 1] >= 5)
            {
                rounding(res, num1->size + res_m - 1);
                res_m--;
            }
            else if (num1->size + res_m > 30 && res->mantissa[num1->size + res_m - 1] < 5)
            {
                res->mantissa[num1->size + res_m - 1] = 0;
                res_m--;
                res->order++;
            }
        }
    }
    res->size = num1->size + res_m;
}

void print_res(num_t *num)
{
    printf("Результат:\n");
    printf("||0---------10--------20--------30\n");
    printf("|||---------|---------|---------|\n");
    printf("%c0.", num->sign);
    if (num->size == 0)
        printf("0");
    else
        for (size_t i = 0; i < num->size; i++)
            printf("%hd", num->mantissa[i]);
    printf("E");
    if (num->order >= 0)
        printf("+");
    printf("%d\n", num->order);
}

void print_error(int rc)
{
    switch (rc)
    {
    case INT_STR_ERROR:
        printf("Целое число не было введено\n");
        break;
    case FLOAT_STR_ERROR:
        printf("Вещественное число не было введено\n");
        break;
    case STRING_OVERFLOW_ERROR:
        printf("Переполнение строки\n");
        break;
    case EPS_ERROR:
        printf("Некорректное использование E\n");
        break;
    case SIGN_ERROR:
        printf("Некорректный ввод знака\n");
        break;
    case POINT_ERROR:
        printf("Некорректный ввод точки\n");
        break;
    case MANTISSA_OVERFLOW_ERROR:
        printf("Переполнение мантиссы\n");
        break;
    case ORDER_OVERFLOW_ERROR:
        printf("Порядок по модулю больше 100.000\n");
        break;
    case BAD_INTEGER_ERROR:
        printf("Целое число не соответствует формату\n");
        break;
    case BAD_FLOAT_ERROR:
        printf("Вещественное число не соответствует формату\n");
        break;
    default:
        printf("Неизвестная ошибка\n");
        break;
    }
}

void init_num(num_t *num)
{
    num->sign = '+';
    num->size = 0;
    num->order = 0;

    for (size_t i = 0; i < LEN; i++)
        num->mantissa[i] = 0;
}