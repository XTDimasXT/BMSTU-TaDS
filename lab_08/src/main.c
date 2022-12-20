#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "list.h"
#include "graph.h"

#define TRIES 10000
#define MENU_ERROR 5

void show_menu(void)
{
    puts("==================МЕНЮ===================");
    puts("============Матрица смежности============");
    puts("1. Считать граф из файла");
    puts("2. Считать матрицу смежности вручную");
    puts("3. Вывести граф в DOT-файл");
    puts("4. Вывести граф на экран");
    puts("");
    puts("=============Список смежности============");
    puts("5. Считать граф из файла");
    puts("6. Считать списки смежности вручную");
    puts("7. Вывести граф в DOT-файл");
    puts("8. Вывести граф на экран");
    puts("");
    puts("================Задание==================");
    puts("9. Найти множество городов, расстояние от\n \
  которых до выделенного города больше Т");
    puts("0. Выход");
    puts("");
}

unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

int main(void)
{
    matrix_graph_t *matrix_graph = matrix_graph_create();
    list_graph_t *list_graph = list_graph_create();

    int menu;
    while (1)
    {
        show_menu();
        puts("Выберите номер команды:");
        if (scanf("%d", &menu) != 1)
        {
            puts("Номер команды - целое число от 0 до 9");
            return MENU_ERROR;
        }

        if (menu == 1)
        {
            char fname[200];
            printf("Введите имя файла: ");
            scanf("%s", fname);
            FILE *src = fopen(fname, "r");
            if (src == NULL)
            {
                puts("Введено неверное имя файла");
                continue;
            }
            if (matrix_graph_read(src, matrix_graph))
            {
                puts("При чтении из файла возникла ошибка");
                fclose(src);
                continue;
            }
            fclose(src);
            puts("\nФайл успешно прочитан\n");
        }
        else if (menu == 2)
        {
            puts("Сначала вводится количество вершин, затем сама матрица: ");
            if (matrix_graph_read(stdin, matrix_graph))
            {
                puts("При вводе возникла ошибка");
                continue;
            }
            puts("\nМатрица успешно прочитана\n");
        }
        else if (menu == 3)
        {
            if (matrix_graph->len == 0)
            {
                puts("Граф пуст");
                continue;
            }
            FILE *dist = fopen("matrix_graph.dot", "w");
            if (dist == NULL)
            {
                puts("Не удалось создать файл");
                continue;
            }
            matirx_graph_to_dot(dist, matrix_graph);
            fclose(dist);
        }
        else if (menu == 4)
        {
            if (matrix_graph->len == 0)
                {
                    puts("Граф пуст");
                    continue;
                }
            system("./scripts/print_matrix_graph.sh");
        }

        else if (menu == 5)
        {
            char fname[200];
            printf("Введите имя файла: ");
            scanf("%s", fname);
            FILE *src = fopen(fname, "r");
            if (src == NULL)
            {
                puts("Введено неверное имя файла");
                continue;
            }
            if (list_graph_read_matrix(src, list_graph))
            {
                puts("При чтении из файла возникла ошибка");
                fclose(src);
                continue;
            }
            fclose(src);
            puts("\nФайл успешно прочитан\n");
        }
        else if (menu == 6)
        {
            puts("Сначала вводится количество вершин, затем ребра в виде (СТАРТ ВЕС КОНЕЦ), для завершения ввода, вводится буква: ");
            if (matrix_graph_read(stdin, matrix_graph))
            {
                puts("При вводе возникла ошибка");
                continue;
            }
            puts("\nМатрица успешно прочитана\n");
        }
        else if (menu == 7)
        {
            if (list_graph->len == 0)
            {
                puts("Граф пуст");
                continue;
            }
            FILE *dist = fopen("list_graph.dot", "w");
            if (dist == NULL)
            {
                puts("Не удалось создать файл");
                continue;
            }
            list_graph_to_dot(dist, list_graph);
            fclose(dist);
        }
        else if (menu == 8)
        {
            if (list_graph->len == 0)
            {
                puts("Граф пуст");
                continue;
            }
            system("./scripts/print_list_graph.sh");
        }
        else if (menu == 9)
        {
            int num;
            printf("Введите длину пути Т: ");
            if (scanf("%d", &num) != 1 || num < 0)
            {
                puts("Введено неврное число");
                continue;
            }

            int capital;
            printf("Введите столицу: ");
            if (scanf("%d", &capital) != 1 || capital < 0 || (size_t)capital > matrix_graph->len)
            {
                puts("Введено неврное число");
                continue;
            }

            if (matrix_graph->len != 0)
            {
                size_t count = 0;
                for (int i = 0; i < (int)matrix_graph->len; i++)
                {
                    if (i != capital)
                    {
                        size_t *dist = matrix_graph_dijkstra(matrix_graph, i);
                        if (dist == NULL)
                        {
                            puts("Возникла ошибка выделения памяти");
                            return -1;
                        }
                        if (dist[capital] > (size_t)num && dist[capital] < (size_t)(-1))
                        {
                            printf("Вершина %d, длина пути %zu\n", i, dist[capital]);
                            count++;
                        }
                    }
                }

                if (count == 0)
                    puts("Искомое множество пусто");

                long long unsigned beg, end;
                beg = milliseconds_now();
                for (size_t j = 0; j < TRIES; j++)
                {
                    for (int i = 0; i < (int)matrix_graph->len; i++)
                    {
                        if (i != capital)
                        {
                            matrix_graph_dijkstra(matrix_graph, i);
                        }
                    }
                }
                end = milliseconds_now();
                printf("Время выполнения задачи для матрицы смежностей: %.4f сек, размер %zu байт\n", (double)(end - beg) / TRIES, sizeof(size_t) * matrix_graph->len * matrix_graph->len);
            }
            else
                puts("Граф на матрице смежностей пуст");

            if (list_graph->len != 0)
            {
                size_t count = 0;
                for (int i = 0; i < (int)list_graph->len; i++)
                {
                    if (i != capital && list_graph->arr[i] != NULL)
                    {
                        size_t *dist = list_graph_dijkstra(list_graph, i);
                        if (dist == NULL)
                        {
                            puts("Возникла ошибка выделения памяти");
                            return -1;
                        }
                        if (dist[capital] > (size_t)num && dist[capital] < (size_t)(-1))
                        {
                            printf("Вершина %d, длина пути %zu\n", i, dist[capital]);
                            count++;
                        }
                    }
                }
                if (count == 0)
                    puts("Искомое множество пусто");

                long long unsigned beg, end;
                beg = milliseconds_now();
                for (size_t j = 0; j < TRIES; j++)
                {
                    for (int i = 0; i < (int)list_graph->len; i++)
                    {
                        if (i != capital && list_graph->arr[i] != NULL)
                        {
                            list_graph_dijkstra(list_graph, i);
                        }
                    }
                }
                end = milliseconds_now();

                size_t size = 0;
                for (size_t j = 0; j < list_graph->len; j++)
                {
                    size += sizeof(list_t *);
                    for (list_t *temp = list_graph->arr[j]; temp; temp = temp->next)
                        size += (sizeof(list_t) + sizeof(node_t));
                }
                printf("Время выполнения задачи для списков смежности: %.4f сек, размер %zu байт\n", (double)(end - beg) / TRIES, size);
            }
            else
                puts("Граф на списках смежности пуст");
        }
        else if (menu == 0)
        {
            break;
        }
        else
            puts("Введен неверный пункт меню");
    }
}