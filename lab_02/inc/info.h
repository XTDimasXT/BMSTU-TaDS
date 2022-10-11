#ifndef __INFO_H__
#define __INFO_H__

#define COMPOSER_NAME_LEN 14
#define COUNTRY_LEN 10
#define THEATRE_NAME_LEN 14
#define PERFORMANCE_LEN 14
#define PRODUCER_NAME_LEN 14
#define STR_LEN 20
#define TYPE_LEN 20
#define TABLE_SIZE 500
#define HZ 230000
#define RUNS_OF_PROGRAMM 1000
#define MIN_AGE 0
#define MAX_AGE 18
#define MIN_DURATION 0
#define MIN_COMMAND 0
#define MAX_COMMAND 12


typedef struct
{
    int min_age;
    char type[TYPE_LEN + 1];
} child_t;

typedef struct
{
    char type[TYPE_LEN + 1];
} adult_t;

typedef struct
{
    char composer[COMPOSER_NAME_LEN + 1];
    char country[COUNTRY_LEN + 1];
    int min_age;
    int duration;
} music_t;

typedef union
{
    child_t child;
    adult_t adult;
    music_t music;
} type_of_performance_t;

typedef struct
{
    char name_theatre[THEATRE_NAME_LEN + 1];
    char performance[PERFORMANCE_LEN + 1];
    char producer[PRODUCER_NAME_LEN + 1];
    int min_price;
    int max_price;
    char str_type_of_performance[TYPE_LEN + 1];
    type_of_performance_t type_of_performance;
} theatres_t;

typedef struct
{
    int index;
    char arr[STR_LEN + 1];
} keys_t;

typedef struct
{
    theatres_t theatres[TABLE_SIZE];
    keys_t keys[TABLE_SIZE];
    int size;
} table_t;

#endif // __INFO_H__