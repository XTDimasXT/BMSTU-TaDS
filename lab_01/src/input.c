#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "input.h"

int get_float_num(num_t *num)
{
    char str[STR_LEN];
    int n = 0;
    int m = 0;
    int order = 0;
    int order_p = 0;
    int sign = 0;
    int eps = 0;
    int point = 0;

    int flag = 0;
    size_t i = 0;

    if (fgets(str, STR_LEN + 2, stdin) == NULL)
        return FLOAT_STR_ERROR;
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
    if (strlen(str) > STR_LEN)
        return STRING_OVERFLOW_ERROR;
    if (strlen(str) == 0)
        return FLOAT_STR_ERROR;
    if (str[i] == 'e' || str[i] == 'E')
        return EPS_ERROR;
    if (str[i] == '-' || str[i] == '+')
    {
        num->sign = str[i];
        i++;
        sign = 1;
    }

    while (i < (size_t)(LEN + point + sign + 1) && str[i] != '\0' && !eps)
    {
        if (!point && (str[i] == '.' || str[i] == ','))
            point = 1;
        else if (str[i] == 'e' || str[i] == 'E')
            eps = 1;
        else if (isdigit(str[i]))
        {
            if (str[i] == '0' && !flag)
            {
                if (point)
                    order_p--;
                i++;
                continue;
            }
            if (str[i] != '0')
            {
                if (!flag)
                    flag = 1;
            }
            num->mantissa[m + n] = (int)(str[i] - '0');
            if (point)
                n++;
            else
                m++;
        }
        else
        {
            if (str[i] == '-' || str[i] == '+')
                return SIGN_ERROR;
            if (str[i] == '.' || str[i] == ',')
                return POINT_ERROR;
            else
                return BAD_FLOAT_ERROR;
        }
        i++;
    }

    if ((i - point - eps - sign) > LEN)
        return MANTISSA_OVERFLOW_ERROR;

    num->size = m + n;

    if (eps)
    {
        if (str[i] == '-' || str[i] == '+')
        {
            if (str[i] == '-')
                sign = 1;
            i++;
        }
        for (; str[i] != '\0'; i++)
        {
            if (isdigit(str[i]))
                order = order * 10 + (int)(str[i] - '0');
            else
                if (str[i] == '+' || str[i] == '-')
                    return SIGN_ERROR;
                else if (str[i] == 'E' || str[i] == 'e')
                    return EPS_ERROR;
                else
                    return BAD_FLOAT_ERROR;
        }
        if (sign)
            order *= -1;
    }
    if (num->size)
        num->order = order_p + order + m;
    else
        num->size = 1;
    if (order >= MAX_ORDER || order <= MIN_ORDER)
        return ORDER_OVERFLOW_ERROR;

    return 0;
}

int get_int_num(num_t *num)
{
    char str[STR_LEN];
    size_t i = 0;
    int m = 0;
    int sign = 0;

    if (fgets(str, STR_LEN + 2, stdin) == NULL)
        return INT_STR_ERROR;
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
    if (strlen(str) > STR_LEN)
        return STRING_OVERFLOW_ERROR;
    if (strlen(str) == 0)
        return INT_STR_ERROR;
    if (str[i] == '-' || str[i] == '+')
    {
        sign = 1;
        num->sign = str[i];
        i++;
    }

    for (; str[i] != '\0'; i++)
    {
        if (isdigit(str[i]))
            num->mantissa[m++] = (int)(str[i] - '0');
        else
            return BAD_INTEGER_ERROR;
        if ((i - sign) >= LEN)
            return MANTISSA_OVERFLOW_ERROR;
    }

    num->size = m;
    
    return EXIT_SUCCESS;
}