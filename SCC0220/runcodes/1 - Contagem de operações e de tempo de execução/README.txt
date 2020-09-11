Trabalho: 1 - Contagem de operações e de tempo de execução

1. Geral
O trabalho possui dois programas importantes: numgen e algostat, o primeiro é
responsável por gerar números aleatórios e o segundo gera estatísticas de
tempo execução do algoritmo de inverter uma lista ou do bubble sort.

2. Compilando
Para compilar ambos os programas basta executar:
"make all" ou simplesmente "make"

3. Executando
Para executar o algostat é necessário fornecer primeiro como argumento o algoritmo
a ser testado que pode ser um de "sort" (bubble sort) ou "reverse". Além disso
tembém precisa ser fornecido o número de entradas a serem lidas via stdin após
uma opção "-n", dessa forma um exemplo de execução seria:
"seq 10 | ./algostat reverse -n 10"
A saída será o tempo de execução em segundos.

Para executar o numgen apenas um argumento é necessário: a quantidade de números
alatórios a serem gerados. Por exemplo:
"./numgen 10"
A saída será 10 números aleatórios (por padrão de 0 a RAND_MAX, ver --help)

4. Testando com make
Para testar o tempo de execução de um programa pode-se executar:
"make test N=<tamanho da entrada> ALGO=<algoritmo a ser testdado>"
Isso é similar a:
"./numgen <tamanho> | ./algostat <algoritmo> -n <tamanho>"

4.1 Múltiplas execuções
"make tests TESTS=<quantidade> N=<tamanho> ALGO=<algoritmo>"

5. Obtendo ajuda
"./numgen --help" ou "./numgen -h"
"./algostat --help" ou "./algostat -h"
