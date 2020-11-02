CC=gcc
BIN=main
SRC=src
HDR=includes
CFLAGS=-Wall -Werror
SRCS=$(wildcard $(SRC)/*.c)

all:
	$(CC) $(CFLAGS) -o $(BIN) $(SRCS) -I $(HDR)

run: $(BIN)
	./$(BIN)

debug:
	$(CC) $(CFLAGS) -DDEBUG -o $(BIN) $(SRCS) -I $(HDR)

clean:
	rm $(BIN)