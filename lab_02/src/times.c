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
    printf("\n%ld тактов, %.10lf секунд\n", end - start, (double)(end - start)/HZ);
}

int compare_sorts(const char name_file[], table_t *table)
{
    int64_t start = 0;
    int64_t end = 0;
    int temp = fill_table(name_file, table);
    if (temp)
        return temp;
    
    printf("===Сравнение методов сортировки===\n");
    
    printf("Сортировка методом qsort:");
    for (int i = 0; i < RUNS_OF_PROGRAMM; i++)
    {
        start += tick();
        sort_qsort(table);
        end += tick();
        temp = fill_table(name_file, table);
    }
    print_result(start / RUNS_OF_PROGRAMM, end / RUNS_OF_PROGRAMM);
    
    printf("Сортировка методом выбором:");
    start = 0;
    end = 0;
    for (int i = 0; i < RUNS_OF_PROGRAMM; i++)
    {
        start += tick();
        sort_choice(table);
        end += tick();
        temp = fill_table(name_file, table);
    }
    print_result(start / RUNS_OF_PROGRAMM, end / RUNS_OF_PROGRAMM);

    printf("Сортировка массива ключей методом qsort:");
    start = 0;
    end = 0;
    for (int i = 0; i < RUNS_OF_PROGRAMM; i++)
    {
        start += tick();
        sort_keys_qsort(table);
        end += tick();
        temp = fill_table(name_file, table);
    }
    print_result(start / RUNS_OF_PROGRAMM, end / RUNS_OF_PROGRAMM);

    printf("Сортировка массива ключей методом выбором:");
    start = 0;
    end = 0;
    for (int i = 0; i < RUNS_OF_PROGRAMM; i++)
    {
        start += tick();
        sort_keys_choice(table);
        end += tick();
        temp = fill_table(name_file, table);
    }
    print_result(start / RUNS_OF_PROGRAMM, end / RUNS_OF_PROGRAMM);

    printf("\nПамять для хранения таблицы - %lu\n", (*table).size * sizeof(*(*table).theatres));
    printf("Память для хранения массива ключей - %lu\n", (*table).size * sizeof(*(*table).keys));
    return EXIT_SUCCESS;
}