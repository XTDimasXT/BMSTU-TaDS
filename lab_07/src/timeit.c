#define _GNU_SOURCE
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "timeit.h"
#include "avl_tree.h"
#include "tree.h"
#include "hashtable_arr.h"
#include "hashtable_list.h"
#include "vector.h"

uint64_t milliseconds_now(void)
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

int compare_avl_and_default(char *filename)
{
    avl_tree_node_t *avl_root = NULL;
    tree_node_t *root = NULL;

    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("%s", filename);
        printf("Произошла ошибка при открытии файла\n");
        return EXIT_FAILURE;
    }

    char *buf = NULL;
    size_t buf_size = 0;
    ssize_t read;

    size_t count_comp_tree = 0;

    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        root = tree_insert(root, buf, &count_comp_tree);
        if (root == NULL)
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }
    count_comp_tree = 0;
    uint64_t start_tree = milliseconds_now();
    root = remove_startswith(root, 'a', &count_comp_tree);
    uint64_t time_tree = milliseconds_now() - start_tree;
    tree_clear(root);

    rewind(f);
    size_t count_comp_avl = 0;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        avl_root = avl_tree_insert(avl_root, buf, &count_comp_avl);
        if (avl_root == NULL)
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }
    free(buf);
    fclose(f);

    count_comp_avl = 0;
    uint64_t start_avl = milliseconds_now();
    avl_root = avl_remove_startswith(avl_root, 'a', &count_comp_avl);
    uint64_t time_avl = milliseconds_now() - start_avl;

    avl_tree_clear(avl_root);


    int size_int;
    char size[8];
    size_t i = 0;
    for (; filename[i + 7] != '_' && i < 7; ++i)
        size[i] = filename[i + 7];
    size[i] = '\0';
    sscanf(size, "%d", &size_int);

    size_t size_avl = size_int * sizeof(avl_tree_node_t);
    size_t size_tree = size_int * sizeof(tree_node_t);

    char sorted = '0';
    if (filename[strlen(filename) - 1] == 'r')
        sorted = '-';
    else if (filename[strlen(filename) - 1] == 's')
        sorted = '+';

    printf("|%7d|%9c|%19"PRIu64"|%19"PRIu64"|%18.2lf%%|%19zu|%19zu|%18.2lf%%|\n", 
    size_int, sorted, time_tree, time_avl, (double)time_tree / time_avl * 100,
    size_tree, size_avl, (double)size_tree / size_avl * 100);
    return EXIT_SUCCESS;
}

int compare_avl_hashtable(char *filename)
{
    tree_node_t *bst_root = NULL;
    avl_tree_node_t *avl_root = NULL;
    hashtable_arr_t hashtable_arr = createHashTable_arr(gorner_hasher);
    hashtable_list_t hashtable_list = createHashTable_list(gorner_hasher);

    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Произошла ошибка при открытии файла\n");
        return EXIT_FAILURE;
    }

    char *buf = NULL;
    size_t buf_size = 0;
    ssize_t read;
    size_t count_comp_avl = 0;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        avl_root = avl_tree_insert(avl_root, buf, &count_comp_avl);
        if (avl_root == NULL)
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }
    count_comp_avl = 0;
    uint64_t start_avl = milliseconds_now();
    avl_root = avl_remove_startswith(avl_root, 'a', &count_comp_avl);
    uint64_t time_avl = milliseconds_now() - start_avl;

    avl_tree_clear(avl_root);
    rewind(f);

    size_t count_comp_bst = 0;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        bst_root = tree_insert(bst_root, buf, &count_comp_bst);
        if (bst_root == NULL)
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }
    count_comp_bst = 0;
    uint64_t start_bst = milliseconds_now();
    bst_root = remove_startswith(bst_root, 'a', &count_comp_bst);
    uint64_t time_bst = milliseconds_now() - start_bst;

    tree_clear(bst_root);
    rewind(f);

    size_t count_comp_arr = 0;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        if (addHashTable_arr(&hashtable_arr, buf, &count_comp_arr))
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }

    count_comp_arr = 0;
    uint64_t start_arr = milliseconds_now();
    removeStartswith_arr(&hashtable_arr, 'a', &count_comp_arr);
    uint64_t time_arr = milliseconds_now() - start_arr;

    deleteHashTable_arr(&hashtable_arr);
    rewind(f);
    size_t count_comp_list = 0;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        if (addHashTable_list(&hashtable_list, buf, &count_comp_list))
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }
    free(buf);
    fclose(f);

    count_comp_list = 0;
    uint64_t start_list = milliseconds_now();
    deleteStartswith_list(&hashtable_list, 'a', &count_comp_list);
    uint64_t time_list = milliseconds_now() - start_list;

    deleteHashTable_list(&hashtable_list);

    int size_int;
    char size[8];
    size_t i = 0;
    for (; filename[i + 7] != '_' && i < 7; ++i)
        size[i] = filename[i + 7];
    size[i] = '\0';
    sscanf(size, "%d", &size_int);

    char sorted = '0';
    if (filename[strlen(filename) - 1] == 'r')
        sorted = '-';
    else if (filename[strlen(filename) - 1] == 's')
        sorted = '+';
    printf("|%5d|%8c|%11lu|%11lu|%11lu|%11lu|%9.2lf%%|%9.2lf%%|%9.2lf%%|%8.2lf%%|%8.2lf%%|%8.2lf%%|%8zu|%6zu|%6zu|%6zu|\n", size_int, sorted, time_bst,
           time_avl, time_arr, time_list, (double)time_bst / time_avl * 100, (double)time_bst / time_arr * 100,
           (double)time_bst / time_list * 100, (double)time_avl / time_arr * 100,
           (double)time_avl/time_list * 100, (double)time_list/time_arr * 100,
           count_comp_bst, count_comp_avl, count_comp_arr, count_comp_list);
    return EXIT_SUCCESS;
}

int compare_avl_hashtable_append(char *filename)
{
    tree_node_t *bst_root = NULL;
    avl_tree_node_t *avl_root = NULL;
    hashtable_arr_t hashtable_arr = createHashTable_arr(gorner_hasher);
    hashtable_list_t hashtable_list = createHashTable_list(gorner_hasher);

    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Произошла ошибка при открытии файла\n");
        return EXIT_FAILURE;
    }

    char *buf = NULL;
    size_t buf_size = 0;
    ssize_t read;
    size_t count_comp_avl = 0;
    uint64_t time_avl = 0;
    uint64_t time_start, time_end;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        time_start = milliseconds_now();
        avl_root = avl_tree_insert(avl_root, buf, &count_comp_avl);
        time_end = milliseconds_now();
        time_avl += time_end - time_start;
        if (avl_root == NULL)
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }

    avl_tree_clear(avl_root);
    rewind(f);

    size_t count_comp_bst = 0;
    uint64_t time_bst = 0;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        time_start = milliseconds_now();
        bst_root = tree_insert(bst_root, buf, &count_comp_bst);
        time_end = milliseconds_now();
        time_bst += time_end - time_start;
        if (bst_root == NULL)
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }

    tree_clear(bst_root);
    rewind(f);

    size_t count_comp_arr = 0;
    size_t time_arr = 0;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        time_start = milliseconds_now();
        if (addHashTable_arr(&hashtable_arr, buf, &count_comp_arr))
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
        time_end = milliseconds_now();
        time_arr += time_end - time_start;
    }

    deleteHashTable_arr(&hashtable_arr);
    rewind(f);
    size_t count_comp_list = 0;
    uint64_t time_list = 0;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        time_start = milliseconds_now();
        if (addHashTable_list(&hashtable_list, buf, &count_comp_list))
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
        time_end = milliseconds_now();
        time_list += time_end - time_start;
    }
    free(buf);
    fclose(f);

    deleteHashTable_list(&hashtable_list);

    int size_int;
    char size[8];
    size_t i = 0;
    for (; filename[i + 7] != '_' && i < 7; ++i)
        size[i] = filename[i + 7];
    size[i] = '\0';
    sscanf(size, "%d", &size_int);


    char sorted = '0';
    if (filename[strlen(filename) - 1] == 'r')
        sorted = '-';
    else if (filename[strlen(filename) - 1] == 's')
        sorted = '+';
    printf("|%5d|%8c|%11lu|%11lu|%11lu|%11lu|%9.2lf%%|%9.2lf%%|%9.2lf%%|%8.2lf%%|%8.2lf%%|%8.2lf%%|%8zu|%6zu|%6zu|%6zu|\n", size_int, sorted, time_bst,
           time_avl, time_arr, time_list, (double)time_bst / time_avl * 100, (double)time_bst / time_arr * 100,
           (double)time_bst / time_list * 100, (double)time_avl / time_arr * 100,
           (double)time_avl/time_list * 100, (double)time_list/time_arr * 100,
           count_comp_bst, count_comp_avl, count_comp_arr, count_comp_list);
    return EXIT_SUCCESS;
}

int compare_avl_hashtable_search(char *filename)
{
    avl_tree_node_t *avl_root = NULL;
    tree_node_t *bst_root = NULL;
    hashtable_arr_t hashtable_arr = createHashTable_arr(gorner_hasher);
    hashtable_list_t hashtable_list = createHashTable_list(gorner_hasher);

    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Произошла ошибка при открытии файла\n");
        return EXIT_FAILURE;
    }

    vector_t vector = create_vector(sizeof(char *));

    char *buf = NULL;
    size_t buf_size = 0;
    ssize_t read;
    size_t count_comp_avl = 0;

    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        avl_root = avl_tree_insert(avl_root, buf, &count_comp_avl);
        if (avl_root == NULL)
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
        if (vector_push_back(&vector, buf))
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }
    count_comp_avl = 0;
    uint64_t start_avl = milliseconds_now();
    char *target = NULL;
    size_t count_has = 0;
    for (size_t i = 0; i < vector.size; ++i)
    {
        target = vector_get_at(&vector, i);
        count_has += avl_tree_has(avl_root, target, &count_comp_avl);
    }
    uint64_t time_avl = milliseconds_now() - start_avl;

    avl_tree_clear(avl_root);
    rewind(f);

    size_t count_comp_bst = 0;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        bst_root = tree_insert(bst_root, buf, &count_comp_bst);
        if (bst_root == NULL)
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }
    count_comp_bst = 0;
    uint64_t start_bst = milliseconds_now();
    for (size_t i = 0; i < vector.size; ++i)
    {
        target = vector_get_at(&vector, i);
        count_has += tree_has(bst_root, target, &count_comp_bst);
    }
    uint64_t time_bst = milliseconds_now() - start_bst;

    tree_clear(bst_root);

    rewind(f);
    size_t count_comp_arr = 0;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        if (addHashTable_arr(&hashtable_arr, buf, &count_comp_arr))
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }

    count_comp_arr = 0;
    uint64_t start_arr = milliseconds_now();
    for (size_t i = 0; i < vector.size; ++i)
    {
        target = vector_get_at(&vector, i);
        count_has += hasHashTable_arr(&hashtable_arr, target, &count_comp_arr);
    }
    uint64_t time_arr = milliseconds_now() - start_arr;

    deleteHashTable_arr(&hashtable_arr);
    rewind(f);
    size_t count_comp_list = 0;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        if (addHashTable_list(&hashtable_list, buf, &count_comp_list))
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }
    free(buf);
    fclose(f);

    count_comp_list = 0;
    uint64_t start_list = milliseconds_now();
    for (size_t i = 0; i < vector.size; ++i)
    {
        target = vector_get_at(&vector, i);
        count_has += hasHashTable_list(&hashtable_list, target, &count_comp_list);
    }
    uint64_t time_list = milliseconds_now() - start_list;
    clear_vector(&vector);
    deleteHashTable_list(&hashtable_list);

    int size_int;
    char size[8];
    size_t i = 0;
    for (; filename[i + 7] != '_' && i < 7; ++i)
        size[i] = filename[i + 7];
    size[i] = '\0';
    sscanf(size, "%d", &size_int);


    char sorted = '0';
    if (filename[strlen(filename) - 1] == 'r')
        sorted = '-';
    else if (filename[strlen(filename) - 1] == 's')
        sorted = '+';
    printf("|%5d|%8c|%11lu|%11lu|%11lu|%11lu|%9.2lf%%|%9.2lf%%|%9.2lf%%|%8.2lf%%|%8.2lf%%|%8.2lf%%|%8zu|%6zu|%6zu|%6zu|\n", size_int, sorted, time_bst,
           time_avl, time_arr, time_list, (double)time_bst / time_avl * 100, (double)time_bst / time_arr * 100,
           (double)time_bst / time_list * 100, (double)time_avl / time_arr * 100,
           (double)time_avl/time_list * 100, (double)time_list/time_arr * 100,
           count_comp_bst, count_comp_avl, count_comp_arr, count_comp_list);
    return EXIT_SUCCESS;
}

int compare_memory(char *filename)
{
    hashtable_arr_t hashtable_arr = createHashTable_arr(gorner_hasher);
    hashtable_list_t hashtable_list = createHashTable_list(gorner_hasher);

    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Произошла ошибка при открытии файла\n");
        return EXIT_FAILURE;
    }


    char *buf = NULL;
    size_t buf_size = 0;
    ssize_t read;


    size_t count_comp_arr = 0;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        if (addHashTable_arr(&hashtable_arr, buf, &count_comp_arr))
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }

    size_t size_arr = hashtable_arr.capacity * sizeof(node_arr_t);
    deleteHashTable_arr(&hashtable_arr);
    rewind(f);
    size_t count_comp_list = 0;
    while ((read = getline(&buf, &buf_size, f)) != -1)
    {
        buf[read - 1] = '\0';
        if (addHashTable_list(&hashtable_list, buf, &count_comp_list))
        {
            printf("Произошла ошибка при выделении памяти\n");
            fclose(f);
            free(buf);
            return EXIT_FAILURE;
        }
    }
    free(buf);
    fclose(f);

    size_t size_list = hashtable_list.buckets_count * sizeof(node_list_t *) + sizeof(node_list_t) * hashtable_list.items_count;
    deleteHashTable_list(&hashtable_list);

    int size_int;
    char size[8];
    size_t i = 0;
    for (; filename[i + 7] != '_' && i < 7; ++i)
        size[i] = filename[i + 7];
    size[i] = '\0';
    sscanf(size, "%d", &size_int);

    size_t size_avl = size_int * sizeof(avl_tree_node_t);
    size_t size_bst = size_int * sizeof(tree_node_t);

    printf("|%10d|%10zu|%10zu|%10zu|%10zu|%9.2lf%%|%9.2lf%%|%9.2lf%%|%9.2lf%%|%9.2lf%%|%9.2lf%%|\n",
           size_int, size_bst, size_avl, size_arr, size_list, (double)size_bst / size_avl * 100,
           (double)size_bst / size_arr * 100, (double)size_bst / size_list * 100, (double)size_avl / size_arr * 100,
           (double)size_avl / size_list * 100, (double)size_list / size_arr * 100);
    return EXIT_SUCCESS;
}

int timeit()
{
    char *filenames[] = { "timeit/100", "timeit/100_s", "timeit/100_r",
    "timeit/500", "timeit/500_s", "timeit/500_r", "timeit/1000", "timeit/1000_s",
    "timeit/1000_r" };
    size_t len_filenames = sizeof(filenames) / sizeof(filenames[0]);

    printf("\n\n                                                  MEMORY (bytes)\n");
    printf("|%10s|%10s|%10s|%10s|%10s|%10s|%10s|%10s|%10s|%10s|%10s|\n",
           "Size", "BST", "AVL", "ARR", "LIST", "BST/AVL", "BST/ARR", "BST/LIST", "AVL/ARR",
           "AVL/LIST", "LIST/ARR");
    for (size_t i = 0; i < len_filenames; i += 3)
        if (compare_memory(filenames[i]))
            return EXIT_FAILURE;

    printf("\n\n                                                  DELETING FROM AVL AND FROM HASH TABLE\n");
    printf("%15s|%110s|%29s|\n", "", "TIME", "COMPARES");
    printf("|%5s|%8s|%11s|%11s|%11s|%11s|%10s|%10s|%10s|%9s|%9s|%9s|%8s|%6s|%6s|%6s|\n", "Size", "Sorted?", "BST(ticks)",
           "AVL(ticks)", "ARR(ticks)", "LIST(ticks)", "BST/AVL", "BST/ARR", "BST/LIST", "AVL/ARR", "AVL/LIST", "LIST/ARR",
           "BST", "AVL", "ARR", "LIST");
    for (size_t i = 0; i < len_filenames; ++i)
        if (compare_avl_hashtable(filenames[i]))
            return EXIT_FAILURE;

    printf("\n\n                                                  INSERTING IN AVL AND HASH TABLE\n");
    printf("%15s|%110s|%29s|\n", "", "TIME", "COMPARES");
    printf("|%5s|%8s|%11s|%11s|%11s|%11s|%10s|%10s|%10s|%9s|%9s|%9s|%8s|%6s|%6s|%6s|\n", "Size", "Sorted?", "BST(ticks)",
           "AVL(ticks)", "ARR(ticks)", "LIST(ticks)", "BST/AVL", "BST/ARR", "BST/LIST", "AVL/ARR", "AVL/LIST", "LIST/ARR",
           "BST", "AVL", "ARR", "LIST");
    for (size_t i = 0; i < len_filenames; ++i)
        if (compare_avl_hashtable_append(filenames[i]))
            return EXIT_FAILURE;
    printf("\n\n                                                  SEARCHING IN AVL AND HASH TABLE\n");
    printf("%15s|%110s|%29s|\n", "", "TIME", "COMPARES");
    printf("|%5s|%8s|%11s|%11s|%11s|%11s|%10s|%10s|%10s|%9s|%9s|%9s|%8s|%6s|%6s|%6s|\n", "Size", "Sorted?", "BST(ticks)",
           "AVL(ticks)", "ARR(ticks)", "LIST(ticks)", "BST/AVL", "BST/ARR", "BST/LIST", "AVL/ARR", "AVL/LIST", "LIST/ARR",
           "BST", "AVL", "ARR", "LIST");
    for (size_t i = 0; i < len_filenames; ++i)
        if (compare_avl_hashtable_search(filenames[i]))
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}