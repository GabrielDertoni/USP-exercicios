BIN=main

CC=gcc
CFLAGS=-Wall -Werror
HDR=include
SRC=src
OBJ=obj

SRCS=$(wildcard $(SRC)/*.c)
HDRS=$(wildcard $(HDR)/*.h)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
LIBS=-lm

all: $(BIN)

# Linking all .o
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) $(LIBS)

# Runs binary
run:
	./$(BIN)

# Compiling to .o
$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR)

# Creates a new directory for all .o
$(OBJ):
	mkdir -p $(OBJ)

# Cleaning.
clean:
	rm $(OBJ)/*
	rmdir $(OBJ)
	rm $(BIN)


zip:
	rm -f Envio.zip
	zip -r Envio.zip README.md $(SRC) $(HDR) Makefile

# Simulates runcodes environment.
runcodes: $(BIN)
	find . -regex ".*\.in" | \
	parallel "cat {} | \
		  ./$(BIN) | \
		  diff --color=always -u -Z --label GOT --label \"EXPECTED ({/})\" - {.}.out" && \
	echo "\033\033[1;32mTudo certo!\033[0m" || \
	echo "\033\033[1;31mAlguns erros... Verifique acima.\033[0m"

testcase: $(BIN)
	./$(BIN) < "$(CASE).in" | diff --color=always -u -Z --label GOT --label "EXPECTED ($(CASE))" - "$(CASE).out"

