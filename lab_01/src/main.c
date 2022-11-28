#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "errors.h"
#include "input.h"
#include "operations.h"
#include "structs.h"

int main(void)
{
    num_t float_num;
    num_t int_num;
    num_t res;

    int rc;

    init_num(&float_num);
    init_num(&int_num);
    init_num(&res);

    printf("Введите действительное число (Например: +123.41E+14 | 123.41 | -123):\n");
    printf("---------10--------20--------30\n");
    printf("---------|---------|---------|\n");

    rc = get_float_num(&float_num);
    if (rc)
    {
        print_error(rc);
        return rc;
    }

    printf("Введите целое число: (Например: -1323 | 0 | 321)\n");

    rc = get_int_num(&int_num);
    if (rc)
    {
        print_error(rc);
        return rc;
    }

    if (float_num.sign ==  int_num.sign)
        res.sign = '+';
    else
        res.sign = '-';
    
    if (float_num.size > int_num.size)
        multiplication(&float_num, &int_num, &res);
    else
        multiplication(&int_num, &float_num, &res);

    if (!float_num.order || float_num.order == (int)float_num.size)
        res.order += res.size;
    else if (float_num.order && (float_num.order > 0 || res.size < int_num.size + float_num.size))
        res.order += int_num.size + float_num.order - 1;
    else if (float_num.order && float_num.order < 0)
        res.order += int_num.size + float_num.order;

    remove_zeroes(&res);
    int flag_zero = 1;
    for (int i = 0; i < 30; i++)
        if (res.mantissa[i] != 0)
            flag_zero = 0;

    if (!res.mantissa[0])
        res.sign = '+';
    if (flag_zero == 1)
    {
        printf("Результат:\n");
        printf("%c0.0E0\n", res.sign);
    }
    else if (res.order >= MAX_ORDER || res.order <= MIN_ORDER)
    {
        rc = ORDER_OVERFLOW_ERROR;
        print_error(rc);
        return rc;
    }
    else
        print_res(&res);

    return EXIT_SUCCESS;
}