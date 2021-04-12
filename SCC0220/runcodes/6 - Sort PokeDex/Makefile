MAIN=Main.c
BINARY=main
LIB=Sorting.c Utils.c

all: obj
	gcc -Wall $(LIB) $(MAIN) -L. -l_pokemon -o $(BINARY)

run:
	./$(BINARY)

obj:
	gcc -Wall -Werror -c -fPIC $(LIB)

lib:
	ar -rc lib_pokemon.a *.o

ranlib:
	ranlib lib_pokemon.a
debug:
	gcc -g -DDEBUG -Wall $(MAIN) $(LIB) -L. -l_pokemon -o $(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm *.o
