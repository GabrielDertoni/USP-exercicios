all:
	gcc -Werror -Wall -o main main.c

test:
	cp Casos\ de\ Teste/$(CASE).* ./
	./main < $(CASE).in > $(CASE).test.out
	diff $(CASE).test.out $(CASE).out

clean-test:
	rm -f *.out
	rm -f *.in

clean:
	make clean-test
	rm -f main
