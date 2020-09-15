CC=gcc
CFLAGS=-Wall -Werror -O2
BIN=main
SRC=src
OBJ=obj
HDR=includes
SRCS=$(wildcard $(SRC)/*.c)
HSRS=$(wildcard $(HDR)/*.h)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: $(OBJS)
	$(CC) $(OBJS) -o $(BIN) -I $(HDR)

.SILENT: run
run: $(BIN)
	./$(BIN)

debug:
	$(CC) $(SRCS) -DDEBUG -o $(BIN) -I $(HDR)

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR)

$(OBJ):
	mkdir -p $(OBJ)

.SILENT: tests
tests: $(BIN)
	find . -regex ".*\.in" | \
	parallel "cat {} | \
			  ./$(BIN) | \
			  diff --color=always -u -Z --label GOT --label \"EXPECTED ({/})\" - {.}.out" && \
	echo "\033\033[1;32mTudo certo!\033[0m" || \
	echo "\033\033[1;31mAlguns erros... Verifique acima.\033[0m"

clean:
	rm -f $(OBJS)
	rm -f $(BIN)
	rmdir $(OBJ)
