PROG := main
BIN := bin
BUILD := build

CC := /usr/bin/gcc
CFLAGS := -Wall -Werror
DFLAGS := -g -DDEBUG
HDR := include
SRC := src
OBJ := obj

SRCS := $(wildcard $(SRC)/*.c)
HDRS := $(wildcard $(HDR)/*.h)
OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

TEST := tests
TESTFLAGS=-g -DDEBUG
TEST_HDR=$(TEST)/test_utils.h
TEST_SRCS=$(wildcard $(TEST)/*.c)
TESTS=$(patsubst $(TEST)/%.c, $(TEST_BIN)/%, $(TEST_SRCS))

BUILD_BIN := $(BIN)/$(BUILD)
TEST_BIN := $(BIN)/$(TEST)
PROG_BIN := $(BIN)/$(BUILD)/$(PROG)

BUILD_DIR := $(shell mkdir -p $(OBJ) $(BUILD_BIN) $(TEST_BIN))

all: $(PROG_BIN)

# Linking all .o
$(PROG_BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LFLAGS)

# Compiling to .o
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR)

# Runs binary
run:
	./$(PROG_BIN)

debug: $(SRCS) $(BUILD_BIN)
	$(CC) $(CFLAGS) $(DFLAGS) $(SRCS) -o $(PROG_BIN) -I $(HDR)

# Cleaning.
clean:
	rm -f $(PROG_BIN)
	rm -f *.log
	rm -f $(TESTS)
	rm -f $(OBJ)/*.o

cleanall: clean
	rm -rf $(BIN)
	rm -rf $(OBJ)

# UNIT testing
$(TEST_BIN)/%_test: CFLAGS := $(CFLAGS) -g
$(TEST_BIN)/%_test: $(TEST)/%_test.c $(filter-out $(OBJ)/main.o, $(OBJS))
	$(CC) $(CFLAGS) $^ -o $@ -I $(HDR)

test: $(TESTS)
	@echo $(TESTS) | xargs -n 1 sh -c

atest: $(TEST_BIN)/$(T)_test
	$(TEST_BIN)/$(T)_test

VFLAGS_L=--tool=massif
MS_FLAGS=--x=100 --y=25
LOG_FILENAME=massif.log
SED_FLAGS=-n -e 8,35p

vgd_log: debug
	@valgrind $(VFLAGS_L) ./$(PROG_BIN)
	@ms_print massif* $(MS_FLAGS) > $(LOG_FILENAME)
	@sed $(LOG_FILENAME) $(SED_FLAGS)

zip:
	rm -f Envio.zip
	zip -r Envio.zip $(SRC) $(TEST) $(HDR) README.md Makefile

# Simulates runcodes environment.
runcodes: $(PROG_BIN)
	find . -regex ".*\.in" | \
	parallel "cat {} | \
		  ./$(PROG_BIN) | \
		  diff --color=always -u -Z --label GOT --label \"EXPECTED ({/})\" - {.}.out" && \
	echo "\033\033[1;32mTudo certo!\033[0m" || \
	echo "\033\033[1;31mAlguns erros... Verifique acima.\033[0m"


