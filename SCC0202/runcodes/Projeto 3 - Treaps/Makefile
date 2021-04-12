BIN=main

CC=gcc
CFLAGS=-Wall -Werror
HDR=include
SRC=src
OBJ=obj

SRCS=$(wildcard $(SRC)/*.c)
HDRS=$(wildcard $(HDR)/*.h)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

DIRS:=$(shell mkdir -p $(OBJ))

all: $(BIN)

# Linking all .o
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

# Runs binary
run:
	./$(BIN)

# Compiling to .o
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR)


# Cleaning.
clean:
	rm -rf $(OBJ)
	rm -f $(BIN)

zip:
	rm -f Envio.zip
	zip -r Envio.zip $(SRC) $(HDR) Makefile

# Simulates runcodes environment.
runcodes: $(BIN)
	@find "Casos Completos" -regex ".*\.in" | \
	parallel "cat {} | \
		  ./$(BIN) | \
		  diff --color=always -u -Z --label GOT --label \"EXPECTED ({/})\" - {.}.out" && \
	echo "\033\033[1;32mTudo certo!\033[0m" || \
	echo "\033\033[1;31mAlguns erros... Verifique acima.\033[0m"


