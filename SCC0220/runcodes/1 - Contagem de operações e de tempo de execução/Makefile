CC = gcc
CFLAGS = -Wall -Werror
SRC=./src
INCLUDE=./includes

all: numgen algostat

numgen: $(SRC)/numgen.c args.o
	$(CC) $(CFLAGS) args.o -o numgen $(SRC)/numgen.c -I $(INCLUDE)

algostat: $(SRC)/main.c args.o
	$(CC) $(CFLAGS) args.o -o algostat $(SRC)/main.c -I $(INCLUDE)

args.o: $(SRC)/args.c
	$(CC) $(CFLAGS) -c $(SRC)/args.c -I $(INCLUDE)

.SILENT: test
test:
	./numgen $(N) -r -$(N) $(N) | ./algostat $(ALGO) -n $(N)

.SILENT: tests
tests:
	./numgen $(N) -r -100000 100000 > data/random_$(N).dat
	seq $(TESTS) | parallel '< data/random_$(N).dat ./algostat $(ALGO) -n $(N)'

clean:
	rm -f *.o
	rm -f numgen algostat
