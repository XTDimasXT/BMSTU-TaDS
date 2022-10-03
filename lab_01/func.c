#include "func.h"

int str_to_bigfloat(char *src, bigfloat_t *bigfloat){
    init_bigfloat(bigfloat);
    src = set_sign(src, bigfloat);
    src = set_mantissa(src, bigfloat);
    if (src == NULL)
        return INCORRECT_MANTISSA;
    if (*src == '\0')
        return EXIT_SUCCESS; 
    if (*src == ' ')
        ++src;
    if (*src != 'E')
        return INCORRECT_ORDER;
    src++;
    if (*src == ' ')
        src++;
    if (set_order(src, bigfloat))
        return INCORRECT_ORDER;
    return EXIT_SUCCESS;
}