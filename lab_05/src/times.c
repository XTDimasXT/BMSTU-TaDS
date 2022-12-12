#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "times.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}


float rand_time(int min, int max)
{
    return (max - min) * (float)(rand()) / (float)RAND_MAX + min;
}

void print_time(int64_t start1, int64_t end1, int64_t start2, int64_t end2)
{
    printf("Очередь массивом: %ld тактов, %.3lf мкс\n", end1 - start1, (double)(end1 - start1)/HZ);
    printf("Очередь списком: %ld тактов, %.3lf мкс\n", end2 - start2, (double)(end2 - start2)/HZ);
}


int create_rand_num(void)
{
    srand(time(NULL));

    return rand() % 100 + 1;
}


void time_add(int count)
{
    int64_t start1 = 0, end1 = 0, start2= 0, end2 = 0;

    arr_t queue_arr;
    init_arr_queue(&queue_arr);

    list_t queue_list;
    init_list_queue(&queue_list);

    int num;

    for (int j = 0; j < RUNS; j++)
    {
        num = create_rand_num();

        start1 += tick();
        for (int i = 0; i < count; i++)
        {
            push_arr_queue(&queue_arr, num);
        }
        end1 += tick();

        start2 += tick();
        for (int i = 0; i < count; i++)
        {
            push_list_queue(&queue_list, num);
        }
        end2 += tick();

        for (int i = 0; i < count; i++)
        {
            pop_arr_queue(&queue_arr);
            pop_list_queue(&queue_list);
        }
    }

    puts("\nЗамеры добавления элементов");
    print_time(start1 / RUNS, end1 / RUNS, start2 / RUNS, end2 / RUNS);
}


void time_del(int count)
{
    int64_t start1 = 0, end1 = 0, start2 = 0, end2 = 0;

    arr_t queue_arr;
    init_arr_queue(&queue_arr);

    list_t queue_list;
    init_list_queue(&queue_list);

    int num;

    for (int j = 0; j < RUNS; j++)
    {

        for (int i = 0; i < count; i++)
        {
            num = create_rand_num();
            push_arr_queue(&queue_arr, num);
            push_list_queue(&queue_list, num);
        }

        start1 += tick();
        for (int i = 0; i < count; i++)
        {
            pop_arr_queue(&queue_arr);
        }
        end1 += tick();

        start2 += tick();
        for (int i = 0; i < count; i++)
        {
            pop_list_queue(&queue_list);
        }
        end2 += tick();
    }


    puts("\nЗамеры удаления элементов");
    print_time(start1 / RUNS, end1 / RUNS, start2 / RUNS, end2 / RUNS);
}

void time_counting(void)
{
    puts("\nВведите количество элементов (от 1 до 1000):");
    int count;

    int rc = scanf("%d", &count);

    if ((rc != 1) || (count < 1) || (count > 1000))
    {
        puts("\nОшибка: неверно введено количество элементов\n\n");
        return;
    }

    time_add(count);
    time_del(count);

    printf("\nЗамеры памяти для %d элементов \
        \nПод массив: %ld байт\
        \nПод список: %ld байт\n", count, sizeof(int) * MAX_ELEMS + sizeof(int) * 3, count * sizeof(node_t));
}