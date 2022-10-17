#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/constants.h"
#include "../inc/errors.h"
#include "../inc/input.h"
#include "../inc/operations.h"
#include "../inc/structs.h"

int main(void)
{
    float_t a;
    integer_t b;
    float_t res;
    /*
    memset(&a, 0, sizeof(float_t));
    memset(&b, 0, sizeof(integer_t));
    memset(&res, 0, sizeof(float_t));
    */

    printf("Введите действительное число (делимое):\n");
    printf("Примеры ввода: +123.321E-24 или -15123.123 или +123\n");
    int rc = my_float_input(&a);
    print_res(a);
    printf("\n");
    if (rc != EXIT_SUCCESS)
        return rc;
    rc = normalize(&a);
    if (rc != EXIT_SUCCESS)
        return rc;
    
    int len = 0;
    printf("Введите целое число (делитель):\n");
    printf("Примеры ввода: +5351 или -125124\n");
    rc = my_integer_input(&b, &len);
    print_integer(b, len);

    printf("\n");
    if (rc != EXIT_SUCCESS)
        return rc;

    division(&a, b, len, &res);
    rc = round_res(&res);
    if (rc != EXIT_SUCCESS)
        return rc;
    rc = normalize(&res);
    if (rc != EXIT_SUCCESS)
        return rc;
    printf("Результат деления:\n");
        print_res(res);
    return EXIT_SUCCESS;
}