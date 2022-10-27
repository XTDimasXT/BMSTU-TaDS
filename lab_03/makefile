CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra

SRCS_DIR := ./src
SRCS := $(wildcard $(SRCS_DIR)/*.c)
HDRS_DIR := ./inc
HDRS := $(wildcard $(HDRS_DIR)/*.h)
OBJS_DIR := ./out
OBJS := $(OBJS_DIR)/addition.o $(OBJS_DIR)/dynamic_matrix.o $(OBJS_DIR)/main.o $(OBJS_DIR)/print.o $(OBJS_DIR)/random.o $(OBJS_DIR)/read.o

.PHONY = build clean

app.exe : $(OBJS)
	$(CC) $^ -o $@

$(OBJS_DIR):
	@mkdir $@

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c $(HDRS_DIR) $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

build: app.exe

clean:
	$(RM) $(OBJS_DIR)/* *.exe
	@rmdir $(OBJS_DIR)