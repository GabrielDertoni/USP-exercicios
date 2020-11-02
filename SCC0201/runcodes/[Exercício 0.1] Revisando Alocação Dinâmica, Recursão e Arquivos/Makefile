all:
	gcc -Wall -Werror -o main main.c -lm

test:
	cp Casos\ de\ Teste/$(CASE)* ./
	./main < $(CASE).in > $(CASE).test.out
	diff -u --color=always --label GOT --label EXPECTED $(CASE).test.out $(CASE).out

clean:
	rm -f main

clean_test:
	rm -f *.out *.in *.dat

test_all:
	@echo "Testing...."
	@find . -name \*.in | parallel \
		"cat {} | \
		cat | \
		./main | \
		diff -u --color=always --label 'GOT ({/.})' --label 'EXPECTED ({/.})' - {.}.out && \
		echo '========= {/.} all good ========='" | \
		tee diffs.out | \
		grep -E '\+\+\+ EXPECTED \(.+\)' | \
		wc -l | \
		xargs echo "NUMBER OF FAILS: "
	@grep -E '={9} .+? all good ={9}' < diffs.out | \
		wc -l | \
		xargs echo "NUMBER OF HITS: "
	@echo "Details:"
	@cat diffs.out
	@rm -f diffs.out

