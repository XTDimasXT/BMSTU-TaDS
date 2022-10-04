#!/bin/bash
gcc -std=gnu99 -Wall -Werror -Wextra -c ./*.c
gcc -o app.exe ./*.o -lm
