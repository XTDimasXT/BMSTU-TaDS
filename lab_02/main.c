#include "info.h"
#include "errors.h"
#include ""

int main(int argc, char **argv)
{
    if (argc != 2)
        return ARGS_ERROR;
    
    FILE *f;
    f = fopen(argv[1], "r");
    if (f == NULL)
        return OPEN_ERROR;
    
    int tmp = 1;
    print_menu();
    printf("Выберите пункт: ");
    while (scanf("%d", tmp) == 1 && tmp)
    {
        if (tmp == 1):
        {
            printf("Введите данные о театре: ");

        }
        else if (tmp == 2):
        {
            if (len != 0)
            {
                printf("Введите театр, который хотите удалить: ")

            }
            else
                printf("В файле нет театров.\n");
        }
        else if (tmp == 3):
        {
            if (len != 0)
            {

            }
            else   
                printf("В файле нет театров.\n");
        }
        else if (tmp == 4):
        {
            if (len != 0)
            {

            }
            else
                printf("В файле нет театров.\n");
        }
        else if (tmp == 5):
        {
            if (len != 0)
            {

            }
            else
                printf("В файле нет театров.\n");
        }
        else if (tmp == 6):
        {
            if (len != 0)
            {

            }
            else
                printf("В файле нет театров.\n");
        }
        else if (tmp == 0)
            break;
        else
            return MENU_ERROR;
        print_menu();
        printf("Выберите пункт: ");
    }
    if (!tmp)
        return SCAN_ERROR;
    return EXIT_SUCCESS;
}