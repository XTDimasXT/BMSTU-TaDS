#include "../inc/addition.h"
#include "../inc/dynamic_matrix.h"
#include "../inc/errors.h"
#include "../inc/operations.h"
#include "../inc/print.h"
#include "../inc/random.h"
#include "../inc/read.h"
#include "../inc/struct.h"
#include "../inc/times.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int num_command;
    int rc;

    while (1)
    {
        print_menu();
        rc = read_num_command(&num_command);
        if (rc != EXIT_SUCCESS)
            return rc;
        
        if (num_command == 1)
            rc = addition_sparse_matrix();
        else if (num_command == 2)
            rc = addition_common_matrix();
        else if (num_command == 3)
            rc = print_stats();
        else if (num_command == 0)
            break;
        
        if (rc != EXIT_SUCCESS)
            return rc;
    }

    return EXIT_SUCCESS;
}