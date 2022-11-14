#include "../inc/array.h"
#include "../inc/errors.h"
#include "../inc/list.h"
#include "../inc/print.h"
#include "../inc/read.h"
#include "../inc/structs.h"

int main(void)
{
    int rc;
    int method;

    while (1)
    {
        print_choise();
        rc = read_method(&method);
        if (rc != EXIT_SUCCESS)
            return rc;
        
        if (method == 1)
            rc = process_stack_as_list();
        else if (method == 2)
            rc = process_stack_as_array();
        else if (method == 3)
            //rc = compare_time();
            continue;
        else if (method == 0)
            break;
        
        if (rc != EXIT_SUCCESS)
            return rc;
    }

    return EXIT_SUCCESS;
}