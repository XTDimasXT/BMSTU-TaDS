CC := gcc

SRCS_DIR := ./src
SRCS := $(wildcard $(SRCS_DIR)/*.c)
HDRS_DIR := ./inc
HDRS := $(wildcard $(HDRS_DIR)/*.h)
OBJS_DIR := ./out
$(shell mkdir -p $(OBJS_DIR))
OBJS := $(OBJS_DIR)/binary_tree.o $(OBJS_DIR)/read_print.o

CFLAGS := -I$(HDRS_DIR) -std=c99 -Wall -Werror -Wpedantic -Wextra

.PHONY = release clean

app.exe : $(OBJS) $(OBJS_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	$(CC) -c -I$(HDRS_DIR) $(CFLAGS) $< -o $@

$(OBJS_DIR)/%.d : $(SRCS_DIR)/%.c
	@echo -n $(OBJS_DIR)/ > $@ && $(CC) -I$(HDRS_DIR) -M $< >> $@

include $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.d)

release: app.exe

clean:
	$(RM) $(SRCS_DIR)/*.d *.exe *.gv *.png
	$(RM) -r $(OBJS_DIR)