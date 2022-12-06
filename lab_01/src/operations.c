#include <stdio.h>
#include <stdlib.h>

#include "operations.h"

void reverse_mantissa(char mant[], size_t len)
{
    char temp;
    for (size_t i = 0; i < len / 2; i++)
    {
        temp = mant[len - i - 1];
        mant[len - i - 1] = mant[i];
        mant[i] = temp;
    }
}


void big_float_remove_leading_zeroes(big_float_t *num)
{
    while (num->mantissa_len > 1 && num->mantissa[num->mantissa_len - 1] == 0)
        num->mantissa_len--;
    
    if (num->mantissa_len == 1 && num->mantissa[0] == 0)
        num->is_negative = 0;
}


void big_int_remove_leading_zeroes(big_int_t *num)
{
    while (num->mantissa_len > 1 && num->mantissa[num->mantissa_len - 1] == 0)
        num->mantissa_len--;
    
    if (num->mantissa_len == 1 && num->mantissa[0] == 0)
        num->is_negative = 0;
}

void big_float_print(big_float_t num)
{
    if (num.mantissa_len == 0 || (num.mantissa_len == 1 && num.mantissa[0] == 0))
    {
        printf("+0.0E+0\n");
        return;   
    }
    reverse_mantissa(num.mantissa, num.mantissa_len);
    if (num.is_negative)
        printf("-0.");
    else 
        printf("+0.");

    for (size_t i = 0; i < num.mantissa_len; i++)
        printf("%d", num.mantissa[i]);
    printf("E%+d\n", num.exponent);
    reverse_mantissa(num.mantissa, num.mantissa_len);
}


int big_float_equal(big_float_t l, big_float_t r)
{
    if (l.is_negative != r.is_negative)
        return 0;
    if (l.mantissa_len != r.mantissa_len)
        return 0;

    for (size_t i = 0; i < l.mantissa_len; ++i)
        if (l.mantissa[i] != r.mantissa[i])
            return 0;

    return 1;    
}


int big_nums_equal(big_int_t l, big_float_t r)
{
    if (l.is_negative != r.is_negative)
        return 0;
    if (l.mantissa_len != r.mantissa_len)
        return 0;

    for (size_t i = 0; i < l.mantissa_len; ++i)
        if (l.mantissa[i] != r.mantissa[i])
            return 0;

    return 1;    
}


int big_nums_less(big_float_t l, big_float_t r)
{
    if (big_float_equal(l, r))
        return 0;
    
    if (l.is_negative)
    {
        if (r.is_negative)
        {
            big_float_t a = l;
            a.is_negative = 0;
            big_float_t b = r;
            b.is_negative = 0;
            return big_nums_less(b, a);
        }
        else 
            return 1;
    }
    else if (r.is_negative)
        return 0;
    else
    {
        if (l.mantissa_len < r.mantissa_len)
            return l.mantissa_len < r.mantissa_len;
        else
        {
            for (int i = l.mantissa_len - 1; i >= 0; --i)
                if (l.mantissa[i] != r.mantissa[i])
                    return l.mantissa[i] < r.mantissa[i];
            return 0;
        }
    }
}


void big_float_round(big_float_t *l)
{
    if (l->mantissa[0] >= 5)
    {
        l->mantissa[1]++;
        for (size_t j = 1; j < l->mantissa_len - 1; j++)
        {
            l->mantissa[j + 1] += l->mantissa[j] / 10; 
            l->mantissa[j] %= 10;   
            if (l->mantissa[j + 1] < 10)
                break;
        }
    }

    for (size_t i = 0; i < l->mantissa_len - 1; i++)
        l->mantissa[i] = l->mantissa[i + 1];
    l->mantissa_len--;
}


void big_float_strip_zeroes(big_float_t *num)
{
    while (!num->mantissa[0])
    {
        for (size_t j = 0; j < num->mantissa_len - 1; j++)
            num->mantissa[j] = num->mantissa[j + 1];
        num->mantissa_len--;
    }
    
}


big_float_t multiply_big_float_num(big_float_t l, char r)
{
    big_float_t res = l;
    res.mantissa_len++;
    char temp = 0;
    res.mantissa[res.mantissa_len - 1] = 0;
    for (size_t i = 0; i < res.mantissa_len; i++)
    {
        res.mantissa[i] *= r;
        res.mantissa[i] += temp;
        temp = res.mantissa[i] / 10;
        res.mantissa[i] %= 10;
    }   
    if (res.mantissa_len > MANTISSA_LEN)
        big_float_round(&res);
    
    if (res.mantissa[res.mantissa_len - 1] == 0)
        big_float_remove_leading_zeroes(&res);
    else
        res.exponent++;
    
    return res;
}


big_float_t big_float_substract(big_float_t l, big_float_t r)
{
    int carry = 0;
    big_float_t res = l;
    for (size_t i = 0; i < r.mantissa_len || carry != 0; ++i)
    {
        res.mantissa[i] -= carry + (i < r.mantissa_len ? r.mantissa[i] : 0);
        carry = res.mantissa[i] < 0;
        if (carry != 0)
            res.mantissa[i] += 10;
    }

    big_float_remove_leading_zeroes(&res);
    return res;
}


void big_float_shift_right(big_float_t *num)
{
    num->mantissa_len++;
    for (size_t i = num->mantissa_len - 1; i > 0; --i)
        num->mantissa[i] = num->mantissa[i - 1];
    num->mantissa[0] = 0;
}

void big_int_shift_right(big_int_t *num)
{
    num->mantissa_len++;
    for (size_t i = num->mantissa_len - 1; i > 0; --i)
        num->mantissa[i] = num->mantissa[i - 1];
    num->mantissa[0] = 0;
}


int big_nums_divide(big_int_t l, big_float_t r, big_float_t *result)
{
    if (big_nums_equal(l, r))
    {
        result->mantissa_len = 1;
        result->mantissa[0] = 1;
        result->is_negative = l.is_negative ^ r.is_negative;     
        result->exponent = -r.exponent + r.mantissa_len + result->mantissa_len;
        if (result->exponent > 99999 || result->exponent < -99999)
            return EXPONENT_ERROR;
        return EXIT_SUCCESS;
    }

    big_float_t b = r;
    b.is_negative = 0;

    big_int_t l_temp = l;
    l_temp.is_negative = 0;

    big_float_remove_leading_zeroes(&b);
    big_int_remove_leading_zeroes(&l);

    if (b.mantissa_len == 0 || (b.mantissa_len == 1 && b.mantissa[0] == 0))
        return ZERO_DIVISION_ERROR;

    if (l.mantissa_len == 0 || (l.mantissa_len == 1 && l.mantissa[0] == 0))
    {
        result->mantissa_len = 1;
        result->mantissa[0] = 0;
        result->is_negative = 0;     
        result->exponent = 0;
        return EXIT_SUCCESS;
    }

    size_t num_shift = 0;

    while (l_temp.mantissa_len <= MANTISSA_LEN + 1)
        {
            big_int_shift_right(&l_temp);
            num_shift++;
        }

    result->mantissa_len = l_temp.mantissa_len;
    l_temp.is_negative = 0;

    big_float_t current;
    current.mantissa_len = 1;
    current.mantissa[0] = 0;
    current.exponent = 0;
    current.is_negative = 0;


    for (int i = l_temp.mantissa_len - 1; i >= 0; --i)
    {
        big_float_shift_right(&current);
        current.mantissa[0] = l_temp.mantissa[i];
        big_float_remove_leading_zeroes(&current);
        int x = 0, l = 0, r = 10;
        while (l <= r)
        {
            int m = (l + r) / 2;
            big_float_t t = multiply_big_float_num(b, m);
            if (!big_nums_less(current, t))
            {
                x = m;
                l = m + 1;
            }
            else
                r = m - 1;
        }

        result->mantissa[i] = x;
        big_float_t temp = multiply_big_float_num(b, x);
        current = big_float_substract(current, temp);
    }

    result->is_negative = l.is_negative ^ r.is_negative;
    big_float_remove_leading_zeroes(result);

    size_t deleated_nums = result->mantissa_len;
    big_float_strip_zeroes(result);
    deleated_nums -= result->mantissa_len;

    result->exponent = -r.exponent + r.mantissa_len + deleated_nums + result->mantissa_len - num_shift;
    
    if (current.mantissa[0] != 0 || result->mantissa_len == MANTISSA_LEN + 1)
        big_float_round(result);

    big_float_strip_zeroes(result);
    
    if (result->exponent > 99999 || result->exponent < -99999)
        return EXPONENT_ERROR;

    return EXIT_SUCCESS;
}