all:
	gcc -Wall -Werror -o filter source/main.c source/parsing.c source/bmp.c

run:
	./filter

test:
	make clean-test
	cp Casos\ de\ Teste/Caso$(CASE)/* ./
	./filter < ./$(CASE).in > ./$(CASE).test.out
	diff ./$(CASE).test.out ./$(CASE).out

clean-test:
	rm -f ./*.out
	rm -f ./*.in
	rm -f ./*.bmp

clean:
	rm -f filter
