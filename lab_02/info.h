#ifndef __INFO_H__
#define __INFO_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define STR_LEN 31
#define TYPE_LEN 31

#define COUNT_TYPE_CHILD 2
#define COUNT_TYPE_ADULT 3

typedef enum
{
    ADD_TO_END,
    REMOVE_BY_VALUE,
    SORT_TABLE_BY_KEY,
    SORT_TABLE_BY_FIELD,
    PERF_EVALUATION,
    PRINT
} options_t;

typedef struct
{
    int max_age;
    char type[TYPE_LEN];
} child_t;

typedef struct
{
    char type[TYPE_LEN];
} adult_t;

typedef struct
{
    char composer[STR_LEN];
    char country[STR_LEN];
    int min_age;
    int duration;
} music_t;

typedef struct
{
    bool theatre_child;
    bool theatre_adult;
    bool theatre_music;
    union union_theatre
    {
        child_t child;
        adult_t adult;
        music_t music;
    } theatre;
} theatre_t;

typedef struct
{
    struct data
    {
        char name_theatre[STR_LEN];
        char performance[STR_LEN];
        char composer[STR_LEN];
        int min_price;
        int max_price;
    } data_t;
    theatre_t theatre;
} repertoire_t;

#endif