CC=gcc
CFLAGS=-Wall -Werror
BIN=main
SRC=src
OBJ=obj
HDR=includes
SRCS=$(wildcard $(SRC)/*.c)
HDRS=$(wildcard $(HDR)/*.h)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

run:
	./$(BIN)

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR)

$(OBJ):
	mkdir -p $(OBJ)

clean:
	rm $(OBJ)/*
	rmdir $(OBJ)
	rm $(BIN)
