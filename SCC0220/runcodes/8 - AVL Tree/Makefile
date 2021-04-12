UTIL=Utils.c AVL.c
MAIN=Main.c
BINARY=main

all:
	gcc -Wall $(UTIL) $(MAIN) -L. -l_pokemon -o $(BINARY)

run:
	./$(BINARY)

debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL) -L. -l_pokemon -o $(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm *.o
