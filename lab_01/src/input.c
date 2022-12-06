#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "input.h"

int big_int_input(big_int_t *num)
{
    num->is_negative = 0;
    size_t len = 0;
    char current = getc(stdin);

    if (current == '-')
        num->is_negative = 1;
    else if (current == '+')
        num->is_negative = 0;
    else if (isdigit(current))
    {
        num->mantissa[len] = current - '0';
        len++; 
    }
    else
        return NUM_READ_ERROR;
    
    current = getc(stdin);
    while (isdigit(current))
    {
        if (len > MANTISSA_LEN)
            return NUM_READ_ERROR;
        num->mantissa[len] = current - '0';
        len++;
        current = getc(stdin);
    }

    if (!isspace(current))
        return NUM_READ_ERROR;

    num->mantissa_len = len;

    reverse_mantissa(num->mantissa, num->mantissa_len);
    big_int_remove_leading_zeroes(num);

    return EXIT_SUCCESS;
}

int big_float_input(big_float_t *num)
{
    num->is_negative = 0;
    num->exponent = 0;

    size_t len = 0;
    int num_shift = -1;

    int dot_flag = 0;

    char current = getc(stdin);

    if (current == '-')
        num->is_negative = 1;
    else if (current == '+')
        num->is_negative = 0;
    else if (isdigit(current) && current != '0')
    {
        num->mantissa[len] = current - '0';
        len++; 
    }
    else if (current == '.')
    {
        num_shift = 0;
        dot_flag = 1;
    }
    else if (!isdigit(current))
        return NUM_READ_ERROR;
    
    current = getc(stdin);
    while (isdigit(current) || current == '.')
    {
        if (len > MANTISSA_LEN)
            return NUM_READ_ERROR;
        if (current == '.' && dot_flag == 1)
            return NUM_READ_ERROR;
        else if (current == '.' && dot_flag == 0)
        {
            num_shift = (int)len;
            current = getc(stdin);
            dot_flag = 1;
            continue;
        }

        num->mantissa[len] = current - '0';
        len++;
        current = getc(stdin);
    }
    if (!isspace(current))
        return NUM_READ_ERROR;

    num->mantissa_len = len;
    reverse_mantissa(num->mantissa, num->mantissa_len);

    if (num_shift == -1)
        num_shift = len;

    if (current == '\n')
    {
        if (num_shift != -1)
            num->exponent += num_shift;
        return EXIT_SUCCESS;
    }

    current = getc(stdin);
    char exp[15];
    if (current == 'E')
        {
            if (fgets(exp, 15, stdin) == NULL || exp[strlen(exp) - 1] != '\n')
                return NUM_READ_ERROR;
            exp[strlen(exp) - 1] = '\0';
            char *trash;
            num->exponent = strtol(exp, &trash, 10); 
            if (*trash != '\0')
                return NUM_READ_ERROR;
            
        }
    else 
        return NUM_READ_ERROR;

    //if (num->exponent > 99999 || num->exponent < -99999)
        //return EXPONENT_ERROR;
    
    if (num_shift != -1)
        num->exponent += num_shift;

    big_float_remove_leading_zeroes(num);

    return EXIT_SUCCESS;
}