#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/read.h"

int read_num_of_records(FILE *f, int *size, int max_size)
{
    char ch;
    if ((fscanf(f, "%d%c", size, &ch) != 2) || ch != '\n')
    {
        printf("Не удалось прочитать количество записей\n");
        return STRUCT_ERROR;
    }
    if (*size <= 0 || *size > max_size)
    {
        printf("Неверное количество записей\n");
        return STRUCT_ERROR;
    }
    return EXIT_SUCCESS;
}

int read_word(FILE *f, int max_len, char word[])
{
    int i = 0;
    while (i <= max_len)
    {
        if (fscanf(f, "%c", &word[i]) != 1)
            return READ_ERROR;
        else if (word[i] == ' ')
        {
            if (i == 0)
                continue;
            else
                break;
        }
        else if (!((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z') ||
                ((word[i] == '-' || word[i] == '_') && i != 0)))
            return SYMBOL_ERROR;
        i++;
    }
    if (word[i] != ' ' && i == max_len + 1)
        return SIZE_ERROR;
    word[i] = '\0';
    return EXIT_SUCCESS;
}

int read_prices(FILE *f, int *min_price, int *max_price)
{
    if (fscanf(f, "%d", min_price) != 1)
    {
        printf("Недопустимая минимальная цена билета\n");
        return SCAN_ERROR;
    }
    if (*min_price <= 0)
    {
        printf("Цена должна быть больше нуля\n");
        return PRICE_ERROR;
    }
    if (fscanf(f, "%d", max_price) != 1)
    {
        printf("Недопустимая максимальная цена билета\n");
        return SCAN_ERROR;
    }
    if (*max_price <= 0)
    {
        printf("Цена должна быть больше нуля\n");
        return PRICE_ERROR;
    }
    if (*max_price < *min_price)
    {
        printf("Максимальная цена билета должна быть больше минимальной\n");
        return RANGE_PRICE_ERROR;
    }
    return EXIT_SUCCESS;
}

int fill_info_child(FILE *f, child_t *child)
{
    if (fscanf(f, "%d", &(*child).min_age) != 1)
    {
        printf("Недопустимый минимальный возраст\n");
        return SCAN_ERROR;
    }
    if ((*child).min_age < MIN_AGE)
    {
        printf("Возраст должен быть больше нуля\n");
        return AGE_ERROR;
    }
    if ((*child).min_age > MAX_AGE)
    {
        printf("Возраст должен быть не более 18\n");
        return AGE_ERROR;
    }
    if (fscanf(f, "%6s", (*child).type) != 1)
    {
        printf("Недопустимый тип спектакля\n");
        return SCAN_ERROR;
    }
    if (strcmp((*child).type, "tale") && strcmp((*child).type, "piece"))
    {
        printf("Неверный тип спектакля\n");
        return TYPE_ERROR;
    }

    char ch;
    if (fscanf(f, "%c", &ch) == 1 && ch != '\n')
    {
        printf("Содержится лишняя информация\n");
        return EXTRA_INFO_ERROR;
    }
    return EXIT_SUCCESS;
}

int fill_info_adult(FILE *f, adult_t *adult)
{
    if (fscanf(f, "%7s", (*adult).type) != 1)
    {
        printf("Недопустимый тип спектакля\n");
        return SCAN_ERROR;
    }
    if (strcmp((*adult).type, "piece") && strcmp((*adult).type, "drama") && strcmp((*adult).type, "comedy"))
    {
        printf("Неверный тип спектакля\n");
        return TYPE_ERROR;
    }

    char ch;
    if (fscanf(f, "%c", &ch) == 1 && ch != '\n')
    {
        printf("Содержится лишняя информация\n");
        return EXTRA_INFO_ERROR;
    }
    return EXIT_SUCCESS;
}

int fill_info_music(FILE *f, music_t *music)
{
    int temp = read_word(f, COMPOSER_NAME_LEN, (*music).composer);
    if (temp == READ_ERROR)
    {
        printf("Не удается прочесть фамилию композитора\n");
        return READ_ERROR;
    }
    else if (temp == SYMBOL_ERROR)
    {
        printf("Недопустимый символ в фамилии композитора\n");
        return SYMBOL_ERROR;
    }
    else if (temp == SIZE_ERROR)
    {
        printf("Превышен размер фамилии композитора");
        return SIZE_ERROR;
    }
    
    temp = read_word(f, COUNTRY_LEN, (*music).country);
    if (temp == READ_ERROR)
    {
        printf("Не удается прочесть страну");
        return READ_ERROR;
    }
    else if (temp == SYMBOL_ERROR)
    {
        printf("Недопустимый символ в названии страны");
        return SYMBOL_ERROR;
    }
    else if (temp == SIZE_ERROR)
    {
        printf("Превышен размер названия страны");
        return SIZE_ERROR;
    }

    if (fscanf(f, "%d", &(*music).min_age) != 1)
    {
        printf("Недопустимый минимальный возраст\n");
        return SCAN_ERROR;
    }
    if ((*music).min_age < MIN_AGE)
    {
        printf("Возраст должен быть больше нуля\n");
        return AGE_ERROR;
    }
    if ((*music).min_age > MAX_AGE)
    {
        printf("Возраст должен быть не более 18\n");
        return AGE_ERROR;
    }

    if (fscanf(f, "%d", &(*music).duration) != 1)
    {
        printf("Недопустимая длительность\n");
        return SCAN_ERROR;
    }
    if ((*music).duration <= MIN_DURATION)
    {
        printf("Длительность должна быть больше нуля\n");
        return AGE_ERROR;
    }

    char ch;
    if (fscanf(f, "%c", &ch) == 1 && ch != '\n')
    {
        printf("Содержится лишняя информация\n");
        return EXTRA_INFO_ERROR;
    }
    return EXIT_SUCCESS;
}

int fill_theatre_repertoire(FILE *f, theatres_t *theatre)
{
    int temp = read_word(f, THEATRE_NAME_LEN, (*theatre).name_theatre);
    if (temp == READ_ERROR)
    {
        printf("Не удается прочесть название театра\n");
        return READ_ERROR;
    }
    else if (temp == SYMBOL_ERROR)
    {
        printf("Недопустимый символ в названии театра\n");
        return SYMBOL_ERROR;
    }
    else if (temp == SIZE_ERROR)
    {
        printf("Превышен размер названия театра\n");
        return SIZE_ERROR;
    }

    temp = read_word(f, PERFORMANCE_LEN, (*theatre).performance);
    if (temp == READ_ERROR)
    {
        printf("Не удается прочесть название спектакля\n");
        return READ_ERROR;
    }
    else if (temp == SYMBOL_ERROR)
    {
        printf("Недопустимый символ в названии спектакля\n");
        return SYMBOL_ERROR;
    }
    else if (temp == SIZE_ERROR)
    {
        printf("Превышен размер названия спектакля\n");
        return SIZE_ERROR;
    }

    temp = read_word(f, COMPOSER_NAME_LEN, (*theatre).producer);
    if (temp == READ_ERROR)
    {
        printf("Не удается прочесть фамилию режиссера\n");
        return READ_ERROR;
    }
    else if (temp == SYMBOL_ERROR)
    {
        printf("Недопустимый символ в фамилии режиссера\n");
        return SYMBOL_ERROR;
    }
    else if (temp == SIZE_ERROR)
    {
        printf("Превышен размер фамилии режиссера\n");
        return SIZE_ERROR;
    }
    
    temp = read_prices(f, &(*theatre).min_price, &(*theatre).max_price);
    temp = read_type_of_performance(f, (*theatre).str_type_of_performance, &(*theatre).type_of_performance);
    return EXIT_SUCCESS;
}

int read_type_of_performance(FILE *f, char str_type_of_performance[], type_of_performance_t *type_of_performance)
{
    int temp;
    if (fscanf(f, "%6s", str_type_of_performance) != 1)
    {
        printf("Неверный тип спектакля\n");
        return TYPE_ERROR;
    }
    if (!strcmp(str_type_of_performance, "child"))
        temp = fill_info_child(f, &(*type_of_performance).child);
    else if (!strcmp(str_type_of_performance, "adult"))
        temp = fill_info_adult(f, &(*type_of_performance).adult);
    else if (!strcmp(str_type_of_performance, "music"))
        temp = fill_info_music(f, &(*type_of_performance).music);
    else
    {
        printf("Неверный тип спектакля\n");
        return TYPE_ERROR;
    }
    if (temp)
        return temp;
    return EXIT_SUCCESS;
}

int read_option(int *option)
{
    printf("Введите номер команды: ");
    if (scanf("%d", option) != 1)
    {
        printf("Недопустимый номер команды\n");
        return SCAN_ERROR;
    }
    if (*option < MIN_COMMAND || *option > MAX_COMMAND)
    {
        printf("Номера команды - от 0 до 12\n");
        return OPTION_ERROR;
    }
    return EXIT_SUCCESS;
}