#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
 
#include "compare.h"
 
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
 
void print_result_file(int64_t start, int64_t end)
{
    printf("Затраченное время для файла - %.2lf мс\n", (double)(end - start)/HZ);
}
 
void print_result_tree(int64_t start, int64_t end)
{
    printf("Затраченное время для дерева - %.2lf мс\n", (double)(end - start)/HZ);
}
 
int compare_time_search(void)
{
    int name_flag;
    char *file_name;
 
    printf("Выберите размерность (1 - 10, 2 - 100, 3 - 1000, 4 - 10000):\n");
    if (scanf("%d", &name_flag) != 1)
        return SCAN_NAME_FLAG_ERROR;
    if (name_flag == 1)
        file_name = "./data/tree.txt";
    else if (name_flag == 2)
        file_name = "./data/tree2.txt";
    else if (name_flag == 3)
        file_name = "./data/tree3.txt";
    else if (name_flag == 4)
        file_name = "./data/tree4.txt";
    else
    {
        printf("Размерность - число от 1 до 4\n");
        return VALUE_NAME_FLAG_ERROR;
    }
 
    int64_t start = 0;
    int64_t end = 0;
    for (int i = 0; i < NUM_RUNS; i++)
    {
        FILE *f = fopen(file_name, "r");
        char *str = "darkside";
 
        start += tick();
        search_file(f, str);
        end += tick();
 
        fclose(f);
    }
    print_result_file(start, end);
 
    start = 0;
    end = 0;
 
    for (int i = 0; i < NUM_RUNS; i++)
    {
        binary_tree_t binary_tree;
        binary_tree.head = NULL;
        FILE *f = fopen(file_name, "r");
        read_file(f, &binary_tree);
        char *str = "darkside";
 
        start += tick();
        find_word(binary_tree.head, str);
        end += tick();
 
        fclose(f);
    }
    print_result_tree(start, end);
 
    return EXIT_SUCCESS;
}
 
int compare_time_insert(void)
{
    int name_flag;
    char *file_name;
 
    printf("Выберите размерность (1 - 10, 2 - 100, 3 - 1000, 4 - 10000):\n");
    if (scanf("%d", &name_flag) != 1)
        return SCAN_NAME_FLAG_ERROR;
    if (name_flag == 1)
        file_name = "./data/tree.txt";
    else if (name_flag == 2)
        file_name = "./data/tree2.txt";
    else if (name_flag == 3)
        file_name = "./data/tree3.txt";
    else if (name_flag == 4)
        file_name = "./data/tree4.txt";
    else
    {
        printf("Размерность - число от 1 до 4\n");
        return VALUE_NAME_FLAG_ERROR;
    }
 
    int64_t start = 0;
    int64_t end = 0;
    for (int i = 0; i < NUM_RUNS; i++)
    {
        FILE *f = fopen(file_name, "r");
        char *str = "darkside";
 
        start += tick();
        insert_file(f, str);
        end += tick();
 
        fclose(f);
    }
    print_result_file(start, end);
 
    start = 0;
    end = 0;
 
    for (int i = 0; i < NUM_RUNS; i++)
    {
        binary_tree_t binary_tree;
        binary_tree.head = NULL;
        FILE *f = fopen(file_name, "r");
        read_file(f, &binary_tree);
        char *str = "darkside";
 
        start += tick();
        insert_tree(&binary_tree.head, str);
        end += tick();
 
        fclose(f);
    }
    print_result_tree(start, end);
 
    return EXIT_SUCCESS;
}
 
int compare_time_delete(void)
{
    int name_flag;
    char *file_name;
 
    printf("Выберите размерность (1 - 10, 2 - 100, 3 - 1000, 4 - 10000):\n");
    if (scanf("%d", &name_flag) != 1)
        return SCAN_NAME_FLAG_ERROR;
    if (name_flag == 1)
        file_name = "./data/tree.txt";
    else if (name_flag == 2)
        file_name = "./data/tree2.txt";
    else if (name_flag == 3)
        file_name = "./data/tree3.txt";
    else if (name_flag == 4)
        file_name = "./data/tree4.txt";
    else
    {
        printf("Размерность - число от 1 до 4\n");
        return VALUE_NAME_FLAG_ERROR;
    }
 
    int64_t start = 0;
    int64_t end = 0;
    for (int i = 0; i < NUM_RUNS; i++)
    {
        FILE *f = fopen(file_name, "r");
        char *str = "darkside";
 
        start += tick();
        search_file(f, str);
        end += tick();
 
        fclose(f);
    }
    print_result_file(start, end);
 
    start = 0;
    end = 0;
 
    for (int i = 0; i < NUM_RUNS; i++)
    {
        binary_tree_t binary_tree;
        binary_tree.head = NULL;
        FILE *f = fopen(file_name, "r");
        read_file(f, &binary_tree);
        char *str = "darkside";
 
        start += tick();
        delete_word(binary_tree.head, str);
        end += tick();
 
        fclose(f);
    }
    print_result_tree(start, end);
 
    return EXIT_SUCCESS;
}
 
int search_file(FILE *f, char *str)
{
    rewind(f);
    while (!feof(f))
    {
        char cur[STR_LEN];
        fgets(cur, STR_LEN, f);
        if (cur[strlen(cur) - 1] == '\n')
            cur[strlen(cur) - 1] = '\0';
 
        if (strcmp(str, cur) == 0)
            return 1;
    }
 
    return EXIT_SUCCESS;
}