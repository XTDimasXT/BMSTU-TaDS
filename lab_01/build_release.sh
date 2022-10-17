#!/bin/bash
gcc -std=gnu99 -Wall -Wextra -c ./src/*.c
gcc -o app.exe ./*.o -lm
