#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
 
#include "compare.h"
 
unsigned long long milliseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;
    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}
 
int compare_time(void)
{
    unsigned long long beg_common;
    unsigned long long end_common;
    unsigned long long time_common = 0;
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
    
    for (int i = 0; i < NUM_RUNS; i++)
    {
        FILE *f = fopen(file_name, "r");
        char *str = "darkside";

        beg_common = milliseconds_now();
        search_file(f, str);
        end_common = milliseconds_now();
        time_common += end_common - beg_common;

        fclose(f);
    }
    printf("Затраченное время для поиска в файле - %llu мс\n", time_common);
    time_common = 0;
 
    for (int i = 0; i < NUM_RUNS; i++)
    {
        binary_tree_t binary_tree;
        binary_tree.head = NULL;
        FILE *f = fopen(file_name, "r");
        read_file(f, &binary_tree);
        char *str = "darkside";

        beg_common = milliseconds_now();
        find_word(binary_tree.head, str);
        end_common = milliseconds_now();
        time_common += end_common - beg_common;

        fclose(f);
    }
    printf("Затраченное время для поиска в дереве - %llu мс\n\n", time_common);
 
 
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