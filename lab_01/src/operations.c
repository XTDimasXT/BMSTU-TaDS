#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/structs.h"
#include "../inc/operations.h"
#include "../inc/constants.h"
#include "../inc/errors.h"

int normalize(float_t *a)
{
    int deletion_order = 0;
    for (int i = 0; i < MANTISSA_LEN; i++)
    {
        if (a->mantissa[i] == 0)
            deletion_order++;
        else
            break;
    }

    if (deletion_order != 0)
    {
        for (int i = 0; i < MANTISSA_LEN - deletion_order; i++)
            a->mantissa[i] = a->mantissa[i + deletion_order];
        for (int i = MANTISSA_LEN - deletion_order; i <= MANTISSA_LEN; i++)
            a->mantissa[i] = 0;
    }

    a->order -= deletion_order;
    
    return EXIT_SUCCESS;
}

int pre_division(int a_digits[], int b_digits[], int a_signif, int b_signif)
{
    int a[MANTISSA_LEN + 1] = {0};
    for (int i = 0; i < a_signif; i++)
        a[i] = a_digits[i];
    int res = -1;
    int flag = 1;
    for (; flag; res++)
    {
        for (int i = 1; (i < b_signif + 1) && flag; i++)
        {
            if (a[a_signif - i] >= b_digits[b_signif - i])
                a[a_signif - i] -= b_digits[b_signif - i];
            else
            {
                for (int j = i + 1; (j < a_signif + 1) && (a[a_signif - i] < 10); j++)
                    if (a[a_signif - j] > 0)
                    {
                        a[a_signif - j]--;
                        for (int k = j - 1; k != i; k--)
                            a[a_signif - k] += 9;
                        a[a_signif - i] += 10;
                    }
                if (a[a_signif - i] >= b_digits[b_signif - i])
                    a[a_signif - i] -= b_digits[b_signif - i];
                else
                    flag = 0;
            }
        }
        if (flag != 0)
            for (int i = 0; i < a_signif; i++)
                a_digits[i] = a[i];
    }
    return res;
}

void division(float_t *a, integer_t b, int b_signif, float_t *res)
{
    int beg;
    int end;
    int cur;
    int cur_res;
    if (a->sign == b.sign)
        res->sign = '+';
    else
        res->sign = '-';
    res->order = a->order;
    
    for (beg = 0, end = 0, cur = 0; end < MANTISSA_LEN; end++, cur++)
    {
        cur_res = pre_division(&(a->mantissa[beg]), b.digits, end - beg + 1, b_signif);
        res->mantissa[cur] = cur_res;
        if ((a->mantissa[beg]) == 0)
            beg++;
    }
}

int round_res(float_t *a)
{
    if ((a->mantissa[MANTISSA_LEN]) >= 5)
    {
        a->mantissa[MANTISSA_LEN - 1]++;
        for (int i = MANTISSA_LEN - 1; i > 0; i--)
        {
            if ((a->mantissa[i] > 9))
            {
                a->mantissa[i] = 0;
                (a->mantissa[i - 1])++;
            }
            else
                break;
        }
        if ((a->mantissa[0]) > 9)
        {
            for (int i = MANTISSA_LEN; i > 1; i--)
                a->mantissa[i] = a->mantissa[i - 1];
            a->mantissa[0] = 1;
            a->mantissa[1] = 0;
            a->order++;
        }
    }
    if (a->order < MIN_ORDER)
    {
        printf("Порядок результата меньше критического значения\n");
        return ORDER_ERROR;
    }
    /*
    else if (a->order > MAX_ORDER)
    {
        printf("Порядок результата больше критического значения\n");
        return ORDER_ERROR;
    }
    */
    a->mantissa[MANTISSA_LEN] = 0;

    return EXIT_SUCCESS;
}

void print_res(float_t a)
{
    printf("%c", a.sign);
    printf("0.");
    for (int i = MANTISSA_LEN - 1; i > 1; i--)
        if (a.mantissa[i])
        {
            for (int j = 0; j <= i; j++)
                printf("%d", a.mantissa[j]);
            i = -1;
        }
    printf("E");
    if (a.order > 0)
        printf("+");
    printf("%d\n", a.order);
}

void print_integer(integer_t b, int int_len)
{
    printf("%c", b.sign);
    for (int i = int_len - 1; i > 0; i--)
        if (b.digits[i])
        {
            for (int j = 0; j <= i; j++)
                printf("%d", b.digits[j]);
            i = -1;
        }
}