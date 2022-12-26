#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>

#include "avl_tree.h"
#include "tree.h"
#include "hashtable_arr.h"
#include "hashtable_list.h"
#include "timeit.h"

void skip_wrong_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

FILE *fopen_from_stdin(char *modes)
{
    printf("Введите путь до файла:\n");
    char *path = NULL;
    size_t len = 0;
    ssize_t read = getline(&path, &len, stdin);
    if (read == -1)
    {
        printf("Произошла ошибка при считывании символов\n");
        free(path);
        return NULL;
    }
    if (read < 2)
    {
        printf("Нельзя вводить пустую строку\n");
        free(path);
        return NULL;
    }
    path[read - 1] = '\0';
    FILE *f = fopen(path, modes);
    free(path);
    if (f == NULL)
    {
        printf("При открытии файла произошла ошибка\n");
        return NULL;
    }
    return f;
}

void print_menu_binary_tree()
{
    printf("\nМеню:\n");
    printf("1. Считать слова из файла в бинарное дерево\n");
    printf("2. Удалить все слова, начинающиеся на заданную букву из бинарного дерева\n");
    printf("3. Добавить слово в бинарное дерево\n");
    printf("4. Проверить существование слова в дереве\n");
    printf("5. Удалить введеное слово из бинарного дерева\n");
    printf("6. Вывести бинарное дерево\n");
    printf("0. Выйти в главное меню\n");
}

void print_menu_avl_tree()
{
    printf("\nМеню:\n");
    printf("1. Считать слова из файла в АВЛ дерево\n");
    printf("2. Удалить все слова, начинающиеся на заданную букву из АВЛ дерева\n");
    printf("3. Добавить слово в АВЛ дерево\n");
    printf("4. Проверить существование слова в АВЛ дереве\n");
    printf("5. Удалить введеное слово из АВЛ дерева.\n");
    printf("6. Вывести АВЛ дерево\n");
    printf("0. Выйти в главное меню\n");
}

void print_menu_hashtable_arr()
{
    printf("\nМеню:\n");
    printf("1. Считать слова из файла в хеш-таблицу с открытой адресацией\n");
    printf("2. Удалить все слова, начинающиеся на заданную букву из хеш-таблицы с открытой адресацией\n");
    printf("3. Добавить слово в хеш-таблицу с открытой адресацией\n");
    printf("4. Проверить существование слова в хеш-таблице с открытой адресацией\n");
    printf("5. Удалить введеное слово из хеш-таблицы с открытой адресацией\n");
    printf("6. Вывести хеш-таблицу\n");
    printf("7. Выполнить перехеширование\n");
    printf("0. Выйти в главное меню\n");
}

void print_menu_hashtable_list()
{
    printf("\nМеню:\n");
    printf("1. Считать слова из файла в хеш-таблицу с закрытой адресацией\n");
    printf("2. Удалить все слова, начинающиеся на заданную букву из хеш-таблицы с закрытой адресацией\n");
    printf("3. Добавить слово в хеш-таблицу с закрытой адресацией\n");
    printf("4. Проверить существование слова в в хеш-таблице с закрытой адресацией\n");
    printf("5. Удалить введеное слово из хеш-таблицы с закрытой адресацией\n");
    printf("6. Вывести хеш-таблицу\n");
    printf("7. Выполнить перехеширование\n");
    printf("0. Выйти в главное меню\n");
}

void print_menu()
{
    printf("\nМеню:\n");
    printf("1. Меню по работе с бинарными деревьями\n");
    printf("2. Меню по работе с АВЛ деревьями\n");
    printf("3. Меню по работе с хеш-таблицей с открытой адресацией\n");
    printf("4. Меню по работе с хеш-таблицей с закрытой адресацией\n");
    printf("5. Замерный эксперимент\n");
    printf("0. Завершить программу\n");
}

void process_binary_trees()
{
    tree_node_t *root = NULL;
    int action = 0;
    while (1)
    {
        print_menu_binary_tree();
        printf("Введите номер пункта: ");
        if (scanf("%d", &action) != 1 || action < 0 || action > 6)
        {
            printf("Было введено неправильное значение\n");
            skip_wrong_input();
            continue;
        }
        skip_wrong_input();
        if (action == 1)
        {
            FILE *f = fopen_from_stdin("r");
            if (f == NULL)
                continue;
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read;
            size_t count_comp = 0;
            while ((read = getline(&buf, &buf_size, f)) != -1)
            {
                buf[read - 1] = '\0';
                root = tree_insert(root, buf, &count_comp);
                if (root == NULL)
                {
                    printf("Произошла ошибка при выделении памяти\n");
                    fclose(f);
                    free(buf);
                    return;
                }
            }
            free(buf);
            fclose(f);
            printf("При добавлении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 2)
        {
            char start_char;
            printf("Введите символ, с которого должны начинаться слова, которые подлежат удалению\n");
            if (scanf("%c", &start_char) != 1)
            {
                printf("Произошла ошибка при чтении символа\n");
                continue;
            }
            skip_wrong_input();
            size_t count_comp = 0;
            root = remove_startswith(root, start_char, &count_comp);
            printf("Все слова, начинающиеся с символа %c были удалены\n", start_char);
            printf("При удалении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 3)
        {
            printf("Введите слово, которое хотите добавить\n");
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read = getline(&buf, &buf_size, stdin);
            if (read == -1)
            {
                printf("Ошибка при чтении слова\n");
                continue;
            }
            buf[read - 1] = '\0';
            size_t count_comp = 0;
            root = tree_insert(root, buf, &count_comp);
            free(buf);
            if (root == NULL)
            {
                printf("Произошла ошибка выделения памяти\n");
                continue;
            }
            printf("При добавлении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 4)
        {
            printf("Введите слово, которое хотите проверить\n");
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read = getline(&buf, &buf_size, stdin);
            if (read == -1)
            {
                printf("Ошибка при чтении слова\n");
                continue;
            }
            buf[read - 1] = '\0';
            size_t count_comp = 0;
            if (tree_has(root, buf, &count_comp))
                printf("В дереве есть такой элемент\n");
            else
                printf("В дереве нет такого элемента\n");
            free(buf);
            printf("При поиске элемента было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 5)
        {
            printf("Введите слово, которое хотите удалить\n");
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read = getline(&buf, &buf_size, stdin);
            if (read == -1)
            {
                printf("Ошибка при чтении слова\n");
                continue;
            }
            buf[read - 1] = '\0';
            size_t count_comp = 0;
            root = tree_remove(root, buf, &count_comp);
            free(buf);
            printf("При удалении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 6)
        {
            if (root == NULL)
                printf("Нельзя сохранить пустое дерево\n");
            FILE *f = fopen_from_stdin("w");
            if (f == NULL)
                break;
            tree_save_as_dot(f, root);
            fclose(f);
        }
        else if (action == 0)
        {
            tree_clear(root);
            return;
        }
    }
}

void process_avl_trees()
{
    avl_tree_node_t *root = NULL;
    int action = 0;
    while (1)
    {
        print_menu_avl_tree();
        printf("Введите номер пункта: ");
        if (scanf("%d", &action) != 1 || action < 0 || action > 6)
        {
            printf("Было введено неправильное значение\n");
            skip_wrong_input();
            continue;
        }
        skip_wrong_input();
        if (action == 1)
        {
            FILE *f = fopen_from_stdin("r");
            if (f == NULL)
                continue;
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read;
            size_t count_comp = 0;
            while ((read = getline(&buf, &buf_size, f)) != -1)
            {
                buf[read - 1] = '\0';
                root = avl_tree_insert(root, buf, &count_comp);
                if (root == NULL)
                {
                    printf("Произошла ошибка при выделении памяти\n");
                    fclose(f);
                    free(buf);
                    return;
                }
            }
            printf("При добавлении было произведено %zu сравнений\n", count_comp);
            free(buf);
            fclose(f);
        }
        else if (action == 2)
        {
            char start_char;
            printf("Введите символ, с которого должны начинаться слова, которые подлежат удалению\n");
            if (scanf("%c", &start_char) != 1)
            {
                printf("Произошла ошибка при чтении символа\n");
                continue;
            }
            skip_wrong_input();
            size_t count_comp = 0;
            root = avl_remove_startswith(root, start_char, &count_comp);
            printf("Все слова, начинающиеся с символа %c были удалены\n", start_char);
            printf("При удалении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 3)
        {
            printf("Введите слово, которое хотите добавить\n");
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read = getline(&buf, &buf_size, stdin);
            if (read == -1)
            {
                printf("Ошибка при чтении слова\n");
                continue;
            }
            buf[read - 1] = '\0';
            size_t count_comp = 0;
            root = avl_tree_insert(root, buf, &count_comp);
            free(buf);
            if (root == NULL)
            {
                printf("Произошла ошибка выделения памяти\n");
                continue;
            }
            printf("При добавлении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 4)
        {
            printf("Введите слово, которое хотите проверить\n");
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read = getline(&buf, &buf_size, stdin);
            if (read == -1)
            {
                printf("Ошибка при чтении слова\n");
                continue;
            }
            buf[read - 1] = '\0';
            size_t count_comp = 0;
            if (avl_tree_has(root, buf, &count_comp))
                printf("В дереве есть такой элемент\n");
            else
                printf("В дереве нет такого элемента\n");
            free(buf);
            printf("При поиске элемента было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 5)
        {
            printf("Введите слово, которое хотите удалить\n");
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read = getline(&buf, &buf_size, stdin);
            if (read == -1)
            {
                printf("Ошибка при чтении слова\n");
                continue;
            }
            buf[read - 1] = '\0';
            size_t count_comp = 0;
            root = avl_tree_remove(root, buf, &count_comp);
            free(buf);
            printf("При удалении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 6)
        {
            if (root == NULL)
                printf("Нельзя сохранить пустое дерево\n");
            FILE *f = fopen_from_stdin("w");
            if (f == NULL)
                break;
            avl_save_as_dot(f, root);
            fclose(f);
        }
        else if (action == 0)
        {
            avl_tree_clear(root);
            return;
        }
    }
}

void process_hashtable_arr()
{
    hashtable_arr_t hashtable_arr = createHashTable_arr(gorner_hasher);
    int action = 0;
    while (1)
    {
        print_menu_hashtable_arr();
        printf("Введите номер пункта: ");
        if (scanf("%d", &action) != 1 || action < 0 || action > 7)
        {
            printf("Было введено неправильное значение\n");
            skip_wrong_input();
            continue;
        }
        skip_wrong_input();
        if (action == 1)
        {
            FILE *f = fopen_from_stdin("r");
            if (f == NULL)
                continue;
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read;
            size_t count_comp = 0;
            while ((read = getline(&buf, &buf_size, f)) != -1)
            {
                buf[read - 1] = '\0';
                if (addHashTable_arr(&hashtable_arr, buf, &count_comp))
                {
                    printf("Произошла ошибка при выделении памяти\n");
                    fclose(f);
                    free(buf);
                    return;
                }
            }
            free(buf);
            fclose(f);
            printf("При добавлении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 2)
        {
            char start_char;
            printf("Введите символ, с которого должны начинаться слова, которые подлежат удалению\n");
            if (scanf("%c", &start_char) != 1)
            {
                printf("Произошла ошибка при чтении символа\n");
                continue;
            }
            skip_wrong_input();
            size_t count_comp = 0;
            removeStartswith_arr(&hashtable_arr, start_char, &count_comp);
            printf("Все слова, начинающиеся с символа %c были удалены\n", start_char);
            printf("При удалении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 3)
        {
            printf("Введите слово, которое хотите добавить\n");
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read = getline(&buf, &buf_size, stdin);
            if (read == -1)
            {
                printf("Ошибка при чтении слова\n");
                continue;
            }
            buf[read - 1] = '\0';
            size_t count_comp = 0;
            if (addHashTable_arr(&hashtable_arr, buf, &count_comp))
            {
                free(buf);
                printf("Произошла ошибка выделения памяти\n");
                continue;
            }
            printf("При добавлении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 4)
        {
            printf("Введите слово, которое хотите проверить\n");
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read = getline(&buf, &buf_size, stdin);
            if (read == -1)
            {
                printf("Ошибка при чтении слова\n");
                continue;
            }
            buf[read - 1] = '\0';
            size_t count_comp = 0;
            if (hasHashTable_arr(&hashtable_arr, buf, &count_comp))
                printf("В хеш-таблице есть такой элемент\n");
            else
                printf("В хеш-таблице нет такого элемента\n");
            free(buf);
            printf("При поиске элемента было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 5)
        {
            printf("Введите слово, которое хотите удалить\n");
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read = getline(&buf, &buf_size, stdin);
            if (read == -1)
            {
                printf("Ошибка при чтении слова\n");
                continue;
            }
            buf[read - 1] = '\0';
            size_t count_comp = 0;
            remove_arr(&hashtable_arr, buf, &count_comp);
            free(buf);
            printf("При удалении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 6)
        {
            printHashTable_arr(&hashtable_arr);
        }
        else if (action == 7)
        {
            if (hashtable_arr.size == 0)
            {
                printf("Нельзя перехешировать пустую хеш-таблицу\n");
                continue;
            }
            printf("Введите коэффициент хеш-функции (сейчас %zu)\n", hashtable_arr.coeff);
            size_t coeff;
            if (scanf("%zu", &coeff) != 1)
            {
                printf("Ошибка при считывании значения коэффициента\n");
                continue;
            }
            editcoeff_arr(&hashtable_arr, coeff);
            if (rehash_arr(&hashtable_arr))
            {
                printf("Произошла ошибка выделения памяти\n");
                continue;
            }
            printf("Перехеширование выполнено успешно!\n");
        }
        else if (action == 0)
        {
            deleteHashTable_arr(&hashtable_arr);
            return;
        }
    }
}

void process_hashtable_list()
{
    hashtable_list_t hashtable_list = createHashTable_list(gorner_hasher);
    int action = 0;
    while (1)
    {
        print_menu_hashtable_list();
        printf("Введите номер пункта: ");
        if (scanf("%d", &action) != 1 || action < 0 || action > 7)
        {
            printf("Было введено неправильное значение\n");
            skip_wrong_input();
            continue;
        }
        skip_wrong_input();
        if (action == 1)
        {
            FILE *f = fopen_from_stdin("r");
            if (f == NULL)
                continue;
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read;
            size_t count_comp = 0;
            while ((read = getline(&buf, &buf_size, f)) != -1)
            {
                buf[read - 1] = '\0';
                if (addHashTable_list(&hashtable_list, buf, &count_comp))
                {
                    printf("Произошла ошибка при выделении памяти\n");
                    fclose(f);
                    free(buf);
                    return;
                }
            }
            free(buf);
            fclose(f);
            printf("При добавлении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 2)
        {
            char start_char;
            printf("Введите символ, с которого должны начинаться слова, которые подлежат удалению\n");
            if (scanf("%c", &start_char) != 1)
            {
                printf("Произошла ошибка при чтении символа\n");
                continue;
            }
            skip_wrong_input();
            size_t count_comp = 0;
            deleteStartswith_list(&hashtable_list, start_char, &count_comp);
            printf("Все слова, начинающиеся с символа %c были удалены\n", start_char);
            printf("При удалении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 3)
        {
            printf("Введите слово, которое хотите добавить\n");
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read = getline(&buf, &buf_size, stdin);
            if (read == -1)
            {
                printf("Ошибка при чтении слова\n");
                continue;
            }
            buf[read - 1] = '\0';
            size_t count_comp = 0;
            if (addHashTable_list(&hashtable_list, buf, &count_comp))
            {
                free(buf);
                printf("Произошла ошибка выделения памяти\n");
                continue;
            }
            printf("При добавлении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 4)
        {
            printf("Введите слово, которое хотите проверить\n");
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read = getline(&buf, &buf_size, stdin);
            if (read == -1)
            {
                printf("Ошибка при чтении слова\n");
                continue;
            }
            buf[read - 1] = '\0';
            size_t count_comp = 0;
            if (hasHashTable_list(&hashtable_list, buf, &count_comp))
                printf("В хеш-таблице есть такой элемент\n");
            else
                printf("В хеш-таблице нет такого элемента\n");
            free(buf);
            printf("При поиске элемента было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 5)
        {
            printf("Введите слово, которое хотите удалить\n");
            char *buf = NULL;
            size_t buf_size = 0;
            ssize_t read = getline(&buf, &buf_size, stdin);
            if (read == -1)
            {
                printf("Ошибка при чтении слова\n");
                continue;
            }
            size_t count_comp = 0;
            buf[read - 1] = '\0';
            remove_list(&hashtable_list, buf, &count_comp);
            free(buf);
            printf("При удалении было произведено %zu сравнений\n", count_comp);
        }
        else if (action == 6)
        {
            printHashTable_list(&hashtable_list);
        }
        else if (action == 7)
        {
            if (hashtable_list.items_count == 0)
            {
                printf("Нельзя перехешировать пустую хеш-таблицу\n");
                continue;
            }
            printf("Введите коэффициент хеш-функции (сейчас %zu)\n", hashtable_list.coeff);
            size_t coeff;
            if (scanf("%zu", &coeff) != 1)
            {
                printf("Ошибка при считывании значения коэффициента\n");
                continue;
            }
            editcoeff_list(&hashtable_list, coeff);
            if (rehash_list(&hashtable_list))
            {
                printf("Произошла ошибка выделения памяти\n");
                continue;
            }
            printf("Перехеширование выполнено успешно!\n");
        }
        else if (action == 0)
        {
            deleteHashTable_list(&hashtable_list);
            return;
        }
    }
}

int main(void)
{
    int action = 0;
    int rc = EXIT_SUCCESS;
    while (1)
    {
        print_menu();
        printf("Введите номер пункта: ");
        if (scanf("%d", &action) != 1 || action < 0 || action > 5)
        {
            printf("Было введено неправильное значение\n");
            skip_wrong_input();
            continue;
        }
        skip_wrong_input();
        if (action == 1)
        {
            process_binary_trees();
        }
        else if (action == 2)
        {
            process_avl_trees();
        }
        else if (action == 3)
        {
            process_hashtable_arr();
        }
        else if (action == 4)
        {
            process_hashtable_list();
        }
        else if (action == 5)
        {
            rc = timeit();
            if (rc)
                printf("Ошибка во время замеров\n");
        }
        else if (action == 0)
            break;
    }
    return rc;
}
