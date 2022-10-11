#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/sort.h"
#include "../inc/commands.h"

int compare_t(const theatres_t *arg_1, const theatres_t *arg_2)
{
    return (strcmp((*arg_1).performance, (*arg_2).performance));
}

int compare_k(const keys_t *arg_1, const keys_t *arg_2)
{
    return (strcmp((*arg_1).arr, (*arg_2).arr));
}

void sort_keys_qsort(table_t *table)
{
    if ((*table).size == 0)
    {
        printf("Таблица пустая\n");
        return;
    }
    qsort((*table).keys, (*table).size, sizeof(keys_t), (int(*) (const void *, const void *)) compare_k);
}

void sort_keys_choice(table_t *table)
{
    if ((*table).size == 0)
    {
        printf("Таблица пустая\n");
        return;
    }

    int min;
    keys_t temp;
    for (int i = 0; i < (*table).size - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < (*table).size; j++)
            if (strcmp((*table).keys[j].arr, (*table).keys[min].arr) < 0)
                min = j;
        temp = (*table).keys[i];
        (*table).keys[i] = (*table).keys[min];
        (*table).keys[min] = temp;
    }
}

void sort_qsort(table_t *table)
{
    if ((*table).size == 0)
    {
        printf("Таблица пустая\n");
        return;
    }
    qsort((*table).theatres, (*table).size, sizeof(theatres_t), (int(*) (const void *, const void *)) compare_t);
    create_array_of_keys(table);
}

void sort_choice(table_t *table)
{
    if ((*table).size == 0)
    {
        printf("Таблица пустая\n");
        return;
    }

    int min;
    theatres_t temp;
    for (int i = 0; i < (*table).size - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < (*table).size; j++)
            if (strcmp((*table).theatres[j].performance, (*table).theatres[min].performance) < 0)
                min = j;
        temp = (*table).theatres[i];
        (*table).theatres[i] = (*table).theatres[min];
        (*table).theatres[min] = temp;
    }
    create_array_of_keys(table);
}

void sort_keys(table_t *table)
{
    char str_1[] = "Theatre";
    char str_2[] = "Performance";
    char str_3[] = "Producer";
    char str_4[] = "Min_pr";
    char str_5[] = "Max_pr";
    char str_6[] = "Type";
    char str_7[] = "Age_ch";
    char str_8[] = "Type_ch";
    char str_9[] = "Type_ad";
    char str_10[] = "Composer";
    char str_11[] = "Country";
    char str_12[] = "Age_mus";
    char str_13[] = "Duration";

    if ((*table).size == 0)
    {
        printf("Таблица пустая\n");
        return;
    }
    
    printf("| %-13s | %-13s | %-13s | %-6s | %-6s | %-6s | %-7s | %-8s | %-8s | %-13s | %-9s | %-8s | %-8s |\n",
           str_1, str_2, str_3, str_4, str_5, str_6, str_7, str_8, str_9, str_10, str_11, str_12, str_13);
    for (int i = 0; i < (*table).size; i++)
        print_line((*table).keys[i].index, (*table).theatres);
    printf("\n");
}