#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include "../inc/times.h"
#include "../inc/commands.h"

int64_t tick(void)
{
    int32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );
    int64_t ticks = ((int64_t)high << 32) | low;
    return ticks;
}

void print_result(int64_t start, int64_t end)
{
    printf("%.3lf мс", (double)(end - start)/HZ);
}

int compare_sorts(const char name_file[], table_t *table)
{
    int64_t start = 0;
    int64_t end = 0;
    int temp = fill_table(name_file, table);
    if (temp)
        return temp;
    
    printf("====Сравнение методов сортировки====\n");
    printf("           |   qsort   |   choice  |\n");

    printf("  Таблица  | ");
    for (int i = 0; i < RUNS_OF_PROGRAMM; i++)
    {
        start += tick();
        sort_qsort(table);
        end += tick();
        temp = fill_table(name_file, table);
    }
    double a = (double)(end - start)/HZ;
    print_result(start, end);
    printf(" | ");
    
    start = 0;
    end = 0;
    for (int i = 0; i < RUNS_OF_PROGRAMM; i++)
    {
        start += tick();
        sort_choice(table);
        end += tick();
        temp = fill_table(name_file, table);
    }
    double b = (double)(end - start)/HZ;
    print_result(start, end);

    double diff1 = (double)(b / a);
    double diff1_perc = (diff1 - 1) * 100;
    printf(" |\n");
    printf("   Ключи   | ");

    start = 0;
    end = 0;
    for (int i = 0; i < RUNS_OF_PROGRAMM; i++)
    {
        start += tick();
        sort_keys_qsort(table);
        end += tick();
        temp = fill_table(name_file, table);
    }
    double c = (double)(end - start)/HZ;
    print_result(start, end);
    printf(" | ");

    start = 0;
    end = 0;
    for (int i = 0; i < RUNS_OF_PROGRAMM; i++)
    {
        start += tick();
        sort_keys_choice(table);
        end += tick();
        temp = fill_table(name_file, table);
    }
    double d = (double)(end - start)/HZ;
    print_result(start, end);
    double diff2 = (double)(d / c);
    double diff2_perc = (diff2 - 1) * 100;
    printf(" |\n");

    printf("\nСортировка таблицы методом qsort быстрее методом сортировки выбором в %.3lf раз(а)\n", diff1);
    printf("Сортировка таблицы методом qsort быстрее методом сортировки выбором на %.3lf %%\n", diff1_perc);
    printf("Сортировка таблицы ключей методом qsort быстрее методом сортировки выбором в %.3lf раз(а)\n", diff2);
    printf("Сортировка таблицы ключей методом qsort быстрее методом сортировки выбором на %.3lf %%\n", diff2_perc);
    printf("\nПамять для хранения таблицы - %lu байт\n", (*table).size * sizeof(*(*table).theatres));
    printf("Память для хранения массива ключей - %lu байт\n", (*table).size * sizeof(*(*table).keys));
    return EXIT_SUCCESS;
}