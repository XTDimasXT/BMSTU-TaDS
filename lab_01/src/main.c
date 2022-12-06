#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "errors.h"
#include "input.h"
#include "operations.h"
#include "structs.h"

int main(void)
{
    big_int_t num1;
    big_float_t num2;
    int error;

    printf("Введите целое число: (Пример: +312, -123, 312)\n");
    if ((error = big_int_input(&num1)))
    {
        printf("Целое число введено неверно\n");
        return error;
    }

    printf("Введите действительное число: (Пример: +0.21, 0.2 E 999, -0.31 E -123)\n");
    if ((error = big_float_input(&num2)))
    {
        printf("Действительное число введено неверно\n");
        return error;
    }

    big_float_t res;
    error = big_nums_divide(num1, num2, &res);
    if (error == ZERO_DIVISION_ERROR)
    {
        printf("Деление на ноль\n");
        return error;
    }
    else if (error == EXPONENT_ERROR)
    {
        printf("Произошло переполнение порядка\n");
        return error;
    }
    printf("Результат:\n");
    printf("  0         10        20        30\n");
    printf("|||---------|---------|---------|\n");
    big_float_print(res);

    return EXIT_SUCCESS; 
}