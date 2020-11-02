
BIN=main
OBJECTS=helpers.o
CC=gcc
SRC=./src
INCLUDES=./includes
CFLAGS=-Wall -Werror

all: $(SRC)/main.c helpers.o
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)/main.c $(OBJECTS) -I $(INCLUDES)

run:
	./$(BIN)

helpers.o: $(SRC)/helpers.c
	$(CC) $(CFLAGS) -c $(SRC)/helpers.c -I $(INCLUDES)

clean:
	rm -f *.o *.out *.in $(BIN)
