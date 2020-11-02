BIN=main
CC=gcc
CFLAGS=-Wall -Werror
HDR=include
SRC=src
OBJ=obj
HDRS=$(wildcard $(HDR)/*.h)
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: $(BIN)

run:
	./$(BIN)

$(BIN): $(OBJS)
	$(CC) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) $< -c -o $@ -I $(HDR)

$(OBJ):
	mkdir -p $(OBJ)
 
clean:
	rm -f $(OBJ)/*.o
	rmdir $(OBJ)
	rm -f $(BIN)