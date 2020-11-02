BIN=main

CC=gcc
CFLAGS=-Wall -Werror
HDR=include
SRC=src
OBJ=obj

SRCS=$(wildcard $(SRC)/*.c)
HDRS=$(wildcard $(HDR)/*.h)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: $(BIN)

debug:
	$(CC) $(CFLAGS) -g -DDEBUG $(SRCS) -o $(BIN) -I $(HDR)

# Linking all .o
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

# Runs binary
run:
	./$(BIN)

# Compiling to .o
$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR)

test: $(TESTS)
	echo $(TESTS) | xargs -n 1 sh -c

zip:
	rm -f Envio.zip
	zip -r Envio.zip $(SRC) $(HDR) Makefile

# Simulates runcodes environment.
runcodes: $(BIN)
	find . -regex ".*\.in" | \
	parallel "cat {} | \
		  ./$(BIN) | \
		  diff --color=always -u -Z --label GOT --label \"EXPECTED ({/})\" - {.}.out" && \
	echo "\033\033[1;32mTudo certo!\033[0m" || \
	echo "\033\033[1;31mAlguns erros... Verifique acima.\033[0m"

# Creates a new directory for all .o
$(OBJ):
	mkdir -p $(OBJ)

# Cleaning.
clean:
	rm $(OBJ)/*
	rmdir $(OBJ)
	rm $(BIN)
	rm -f Envio.zip
