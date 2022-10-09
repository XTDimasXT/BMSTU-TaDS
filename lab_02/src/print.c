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
           "5 - Вывести список всех музыкальных спектаклей для детей указанного возраста с продолжительностью меньше указанной\n"
           "6 - Вывести массив ключей (ключ - название спектакля)\n"
           "7 - Отсортировать массив ключей методом qsort\n"
           "8 - Отсортировать массив ключей методом выбором\n"
           "9 - Отсортировать таблицу методом qsort\n"
           "10 - Отсортировать таблицу методом выбором\n"
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

    printf("| %-13s | %-13s | %-13s | %-6s | %-6s | %-6s | %-7s | %-8s | %-8s | %-13s | %-9s | %-8s | %-8s |\n",
           str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, str11, str12, str13);
    
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
    
    printf("| %-13s | %-13s | %-13s | %-6s | %-6s | %-6s | %-7s | %-8s | %-8s | %-13s | %-9s | %-8s | %-8s |\n",
           str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, str11, str12, str13);
    for (int i = 0; i < (*table).size; i++)
        if ((*table).theatres[i].str_type_of_performance[0] == 'm' &&
            (*table).theatres[i].type_of_performance.music.min_age >= min_age &&
            (*table).theatres[i].type_of_performance.music.duration <= duration)
                print_line(i, (*table).theatres);
    printf("\n Количество подходящих спектаклей - %d\n", count);
    return EXIT_SUCCESS;
}

void print_keys(table_t *table)
{
    if ((*table).size == 0)
    {
        printf("Таблица пустая\n");
        return;
    }
    char str1[] = "Index";
    char str2[] = "Performance";
    printf("| %-5s | %-13s |", str1, str2);
        for (int i = 0; i < (*table).size; i++)
            printf("\n| %-5d | %-13s |\n", (*table).keys[i].index, (*table).keys[i].arr);
}