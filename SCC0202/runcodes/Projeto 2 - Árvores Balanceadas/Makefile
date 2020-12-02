# Compilation
CC := gcc
CFLAGS := -Wall -Werror
TESTFLAGS := -g -DDEBUG

# Program
PROG := main

# Directories
BIN := bin
BUILD := build
HDR := include
SRC := src
OBJ := obj
TEST := tests

# Derived directories
BUILD_BIN := $(BIN)/$(BUILD)
PROG_BIN := $(BUILD_BIN)/$(PROG)
TEST_BIN := $(BIN)/$(TEST)

SRCS := $(wildcard $(SRC)/*.c)
HDRS := $(wildcard $(HDR)/*.h)
OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

BUILD_DIR := $(shell mkdir -p $(OBJ) $(BUILD_BIN))

all: $(PROG_BIN)

# Building programs
$(PROG_BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -I $(HDR)

# Compiling to .o
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR)

run:
	./$(PROG_BIN)

# Cleaning.
clean:
	rm -rf $(OBJ)
	rm -rf $(BIN)

zip:
	rm -f Envio.zip
	zip -r Envio.zip $(SRC) $(HDR) Makefile

# Simulates runcodes environment.
runcodes: $(BIN)
	@find "Casos Completos" -regex ".*\.in" | \
	parallel "cat {} | \
		  ./$(PROG_BIN) | \
		  diff --color=always -u -Z --label GOT --label \"EXPECTED ({/})\" - {.}.out" && \
	echo "\033\033[1;32mTudo certo!\033[0m" || \
	echo "\033\033[1;31mAlguns erros... Verifique acima.\033[0m"


