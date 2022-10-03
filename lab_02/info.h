#ifndef __INFO_H__
#define __INFO_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define STR_LEN 30
#define TYPE_LEN 30

#define COUNT_TYPE_CHILD 2
#define COUNT_TYPE_ADULT 3


typedef struct
{
    int max_age;
    char type[TYPE_LEN + 1];
} child_t;

typedef struct
{
    char type[TYPE_LEN + 1];
} adult_t;

typedef struct
{
    char composer[STR_LEN + 1];
    char country[STR_LEN + 1];
    int min_age;
    int duration;
} music_t;

typedef union
{
    child_t child;
    adult_t adult;
    music_t music;
} type_of_perfomance_t;

typedef struct
{
    char name_theatre[STR_LEN + 1];
    char performance[STR_LEN + 1];
    char composer[STR_LEN + 1];
    int min_price;
    int max_price;
    char str_type_of_perfomance[STR_LEN + 1];
    type_of_perfomance_t type_of_performance;
} theatres_t;

typedef struct
{
    int index;
    char arr[STR_LEN + 1];
} keys_t;

typedef struct
{
    theatres_t theatres[STR_LEN];
    keys_t keys[STR_LEN];
    int size;
}

#endif //#ifndef __INFO_H__