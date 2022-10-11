#include <stdio.h>
#include <stdlib.h>

#include "../inc/info.h"
#include "../inc/errors.h"

void print_menu()
{
    printf("\nМеню:\n"
           "1 - Загрузить список из файла\n"
           "2 - Вывести всю таблицу\n"
           "3 - Добавить спектакль\n"
           "4 - Удалить спектакли, минимальная цена билетов которых больше указанного значения\n"
           "5 - Вывести музыкальные спектакли для детей указанного возраста с продолжительностью меньше указанной\n"
           "6 - Вывести массив ключей (ключ - название спектакля)\n"
           "7 - Отсортировать массив ключей (сортировка qsort)\n"
           "8 - Отсортировать массив ключей (сортировка выбором)\n"
           "9 - Отсортировать таблицу (сортировка qsort)\n"
           "10 - Отсортировать таблицу (сортировка выбором)\n"
           "11 - Вывести отсортированную таблицу, используя упорядоченный массив ключей\n"
           "12 - Оценка эффективности\n"
           "0 - Выйти\n");
}

void print_line(int i, theatres_t *theatres)
{
    printf("| %-13s | %-13s | %-13s | %-6d | %-6d | %-6s | ", theatres[i].name_theatre,
           theatres[i].performance, theatres[i].producer,
           theatres[i].min_price, theatres[i].max_price,
           theatres[i].str_type_of_performance);
    
    if (theatres[i].str_type_of_performance[0] == 'c')
    {
        printf("%-7d | %-8s | %-8c | %-13c | %-9c | %-8c | %-8c |\n",
               theatres[i].type_of_performance.child.min_age,
               theatres[i].type_of_performance.child.type, ' ', ' ', ' ', ' ', ' ');
    }
    else if (theatres[i].str_type_of_performance[0] == 'a')
    {
        printf("%-7c | %-8c | %-8s | %-13c | %-9c | %-8c | %-8c |\n",
               ' ', ' ', theatres[i].type_of_performance.adult.type, ' ', ' ', ' ', ' ');
    }
    else
    {
        printf("%-7c | %-8c | %-8c | %-13s | %-9s | %-8d | %-8d |\n", ' ', ' ', ' ',
               theatres[i].type_of_performance.music.composer,
               theatres[i].type_of_performance.music.country,
               theatres[i].type_of_performance.music.min_age,
               theatres[i].type_of_performance.music.duration);
    }
}

void print_table(table_t *table)
{
    if ((*table).size == 0)
    {
        printf("Таблица пустая\n");
        return;
    }

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

    printf("| %-13s | %-13s | %-13s | %-6s | %-6s | %-6s | %-7s | %-8s | %-8s | %-13s | %-9s | %-8s | %-8s |\n",
           str_1, str_2, str_3, str_4, str_5, str_6, str_7, str_8, str_9, str_10, str_11, str_12, str_13);
    
    for (int i = 0; i < (*table).size; i++)
        print_line(i, (*table).theatres);
    printf("\n");
}

int print_required_performances(table_t *table)
{
    int min_age;
    printf("Введите минимально допустимый возраст для посещения спектакля: ");
    if (scanf("%d", &min_age) != 1)
    {
        printf("Возраст введен некорректно\n");
        return SCAN_ERROR;
    }
    if (min_age < MIN_AGE)
    {
        printf("Возраст не может быть меньше нуля\n");
        return AGE_ERROR;
    }
    else if (min_age > MAX_AGE)
    {
        printf("Минимальный возраст должен быть не больше 18");
        return AGE_ERROR;
    }
    
    int duration;
    printf("Введите максимальную продолжительность спектакля: ");
    if (scanf("%d", &duration) != 1)
    {
        printf("Длительность введена некорректно\n");
        return SCAN_ERROR;
    }
    if (duration < MIN_DURATION)
    {
        printf("Длительность не может быть меньше нуля");
        return DURATION_ERROR;
    }

    int count = 0;
    for (int i = 0; i < (*table).size; i++)
        if ((*table).theatres[i].str_type_of_performance[0] == 'm' &&
            (*table).theatres[i].type_of_performance.music.min_age <= min_age &&
            (*table).theatres[i].type_of_performance.music.duration <= duration)
                count++;
    if (count == 0)
    {
        printf("Подходящие спектакли отсутствуют в таблице\n");
        return EXIT_SUCCESS;
    }

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

    printf("| %-13s | %-13s | %-13s | %-6s | %-6s | %-6s | %-7s | %-8s | %-8s | %-13s | %-9s | %-8s | %-8s |\n",
           str_1, str_2, str_3, str_4, str_5, str_6, str_7, str_8, str_9, str_10, str_11, str_12, str_13);
    
    for (int i = 0; i < (*table).size; i++)
        if ((*table).theatres[i].str_type_of_performance[0] == 'm' &&
            (*table).theatres[i].type_of_performance.music.min_age <= min_age &&
            (*table).theatres[i].type_of_performance.music.duration <= duration)
                print_line(i, (*table).theatres);
    printf("\nКоличество подходящих спектаклей - %d\n", count);
    return EXIT_SUCCESS;
}

void print_keys(table_t *table)
{
    if ((*table).size == 0)
    {
        printf("Таблица пустая\n");
        return;
    }
    char str_1[] = "Index";
    char str_2[] = "Performance";
    printf("| %-5s | %-13s |", str_1, str_2);
        for (int i = 0; i < (*table).size; i++)
            printf("\n| %-5d | %-13s |\n", (*table).keys[i].index, (*table).keys[i].arr);
}