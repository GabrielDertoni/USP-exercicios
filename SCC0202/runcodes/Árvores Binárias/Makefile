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

# Linking all .o
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

# Runs binary
run:
	./$(BIN)

# Compiling to .o
$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR)

# Creates a new directory for all .o
$(OBJ):
	mkdir -p $(OBJ)


zip:
	zip -r Envio.zip $(SRC) $(HDR) Makefile

.SILENT=testcase
testcase: $(BIN)
	./$(BIN) < "$(CASE)" | diff --color=always -u -Z --label GOT --label "EXPECTED ($(CASE))" - "$(subst .in,.out,$(CASE))" && \
	echo "\033\033[1;32mTudo certo!\033[0m" || \
	echo "\033\033[1;31mAlguns erros... Verifique acima.\033[0m"

# Cleaning.
clean:
	rm $(OBJ)/*
	rmdir $(OBJ)
	rm $(BIN)
	rm -f Envio.zip


