CC := gcc
CFLAGS := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla
LDFLAGS := -lm
CHECK_FLAGS := $(shell pkg-config --cflags --libs check) -lpthread

INC_DIR := inc
OUT_DIR := out
SRC_DIR := src
UNIT_DIR := unit_tests

SOURCES := $(wildcard $(SRC_DIR)/*.c)
SOURCES_LIB := $(patsubst $(SRC_DIR)/main.c,,$(SOURCES))
SOURCES_TESTS := $(wildcard $(UNIT_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)%,$(OUT_DIR)%,$(patsubst %.c,%.o,$(SOURCES)))
OBJS_LIB := $(patsubst $(SRC_DIR)%,$(OUT_DIR)%,$(patsubst %.c,%.o,$(SOURCES_LIB)))
OBJS_TESTS := $(patsubst $(UNIT_DIR)%,$(OUT_DIR)%,$(patsubst %.c,%.o,$(SOURCES_TESTS)))
HEADERS := $(wildcard $(INC_DIR)/*.h)

$(shell mkdir -p $(OUT_DIR))

app.exe : $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -c -I$(INC_DIR) $(CFLAGS) $< -o $@

unit_tests.exe : $(OBJS_LIB) $(OBJS_TESTS)
	$(CC) $(CHECK_FLAGS) $^ -o $@ $(LDFLAGS)

$(OUT_DIR)/%.o : $(UNIT_DIR)/%.c
	$(CC) -c -I$(INC_DIR) $(CHECK_FLAGS) $(CFLAGS) $< -o $@

$(OUT_DIR)/%.d : $(SRC_DIR)/%.c
	echo -n $(OUT_DIR)/ > $@ && $(CC) -I$(INC_DIR) -M $< >> $@

$(OUT_DIR)/%.d : $(UNIT_DIR)/%.c
	echo -n $(OUT_DIR)/ > $@ && $(CC) -I$(INC_DIR) -M $< >> $@

include $(SOURCES:$(SRC_DIR)/%.c=$(OUT_DIR)/%.d)
include $(SOURCES_TESTS:$(UNIT_DIR)/%.c=$(OUT_DIR)/%.d)


.PHONY: clean func unit coverage debug realease

release: CFLAGS += -O2
release: app.exe

debug: CFLAGS += -O0 -ggdb
debug: app.exe

coverage: CFLAGS += --coverage
coverage: LDFLAGS += --coverage
coverage: func
coverage: unit
coverage:
	gcovr -r .

unit: unit_tests.exe
unit: CFLAGS += -O2 -ggdb
unit:
	./unit_tests.exe

func: app.exe
	cd func_tests/scripts/ && ./func_tests.sh

check_scripts:
	find *.sh -exec "shellcheck" {} \;

clean :
	rm -rf *exe *o *gcov *gcda *gcnp *log *d $(OUT_DIR)
