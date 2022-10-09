#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/sort.h"

int compare_t(const theatres_t *arg1, const theatres_t *arg2)
{
    return (strcmp((*arg1).performance, (*arg2).performance));
}

int compare_k(const keys_t *arg1, const keys_t *arg2)
{
    return (strcmp((*arg1).arr, (*arg2).arr));
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
}

void sort_keys(table_t *table)
{
    char str1[] = "Theatre";
    char str2[] = "Performance";
    char str3[] = "Producer";
    char str4[] = "Min_pr";
    char str5[] = "Max_pr";
    char str6[] = "Type";
    char str7[] = "Age_ch";
    char str8[] = "Type_ch";
    char str9[] = "Type_ad";
    char str10[] = "Composer";
    char str11[] = "Country";
    char str12[] = "Age_mus";
    char str13[] = "Duration";

    if ((*table).size == 0)
    {
        printf("Таблица пустая\n");
        return;
    }
    
    printf("| %-13s | %-13s | %-13s | %-6s | %-6s | %-6s | %-7s | %-8s | %-8s | %-13s | %-9s | %-8s | %-8s |\n",
           str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, str11, str12, str13);
    for (int i = 0; i < (*table).size; i++)
        print_line((*table).keys[i].index, (*table).theatres);
    printf("\n");
}