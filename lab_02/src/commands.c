#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/commands.h"
#include "../inc/print.h"

void create_array_of_keys(table_t *table)
{
    for (int i = 0; i < (*table).size; i++)
    {
        (*table).keys[i].index = i;
        strcpy((*table).keys[i].arr, (*table).theatres[i].performance); 
    }
}

int fill_table(const char *name_file, table_t *table)
{
    FILE *f = fopen(name_file, "r");
    if (f == NULL)
    {
        printf("Неуспешное открытие файла\n");
        return OPEN_ERROR;
    }

    int temp = read_num_of_records(f, &((*table).size), TABLE_SIZE);
    if (temp)
        return temp;
    for (int i = 0; i < (*table).size; i++)
        temp = fill_theatre_repertoire(f, &((*table).theatres[i]));
    fclose(f);
    create_array_of_keys(table);
    return EXIT_SUCCESS;
}

int add_performance(table_t *table)
{
    if (++((*table).size) > TABLE_SIZE)
    {
        printf("Таблица содержит максимальное количество строк, нельзя добавить новый театр\n");
        return ADD_ERROR;
    }
    char ch;
    scanf("%c", &ch);

    printf("Введите репертуар театра по следующим правилам: \n"
           "- Название_театра Название_спектакля Фамилия_режиссера Мин_цена_билета Макс_цена_билета "
           "Тип_спектакля(child/adult/music)\n"
           "- Если 'child': Мин_возраст Тип(tale/piece)\n"
           "- Если 'adult': Тип(piece, drama, comedy)\n"
           "- Если 'music': Композитор Страна Мин_возраст Продолжительность\n"
           "- Cлова должны быть разделены пробелами\n");
    int temp = fill_theatre_repertoire(stdin, &((*table).theatres[(*table).size - 1]));
    if (temp)
        return temp;
    create_array_of_keys(table);
    printf("Добавление прошло успешно!\n");
    return EXIT_SUCCESS;
}

int delete_lines(table_t *table)
{
    int min_price;
    printf("Введите границу минимальной цены билета: ");
    if (scanf("%d", &min_price) != 1)
    {
        printf("Неудачное считывание границы минимальной цены билета");
        return SCAN_ERROR;
    }
    if (min_price <= 0)
    {
        printf("Граница должна быть больше 0");
        return PRICE_ERROR;
    }

    int count = 0;
    int i = 0;
    while (i < (*table).size)
    {
        if ((*table).theatres[i].min_price > min_price)
        {
            for (int j = i + 1; j < (*table).size; j++) 
                (*table).theatres[j - 1] = (*table).theatres[j];
            count++;
            (*table).size--;
        }
        else
            i++;
    }
    create_array_of_keys(table);
    printf("Количество удаленных спектаклей: %d\n", count);
    return EXIT_SUCCESS;
}