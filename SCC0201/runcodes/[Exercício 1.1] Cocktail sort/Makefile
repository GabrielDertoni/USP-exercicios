BIN=main

all: main.c
	gcc -Wall -Werror -o $(BIN) main.c

tests: $(BIN)
	find . -regex ".*\.in" | \
	parallel "cat {} | \
		  ./$(BIN) | \
		  diff --color=always -u -Z --label GOT --label \"EXPECTED ({/})\" - {.}.out" && \
	echo "\033\033[1;32mTudo certo!\033[0m" || \
	echo "\033\033[1;31mAlguns erros... Verifique acima.\033[0m"

clean:
	rm main
