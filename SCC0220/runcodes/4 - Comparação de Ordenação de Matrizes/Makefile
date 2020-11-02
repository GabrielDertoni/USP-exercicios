BIN=main
CC=gcc
CFLAGS=-Wall -Werror
SRC=src
HDR=include
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
HDRS=$(wildcard $(HDR)/*.h)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: $(BIN)

run:
	./$(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

report:
	$(CC) $(CFLAGS) -DMEASURE_TIME $(SRCS) -o $(BIN) -I $(HDR)

debug:
	$(CC) $(CFLAGS) -DMEASURE_TIME $(SRCS) -o $(BIN) -I $(HDR)

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR)

$(OBJ):
	mkdir -p $(OBJ)

clean:
	rm -f $(BINS)
	rm -f $(OBJ)/*
	rmdir $(OBJ)
