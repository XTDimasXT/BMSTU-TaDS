#!/bin/bash
gcc -std=gnu99 -Wall -Wextra -c -ggdb ./src/input.c ./src/main.c ./src/operations.c
gcc -o app.exe ./*.o -lm -g
