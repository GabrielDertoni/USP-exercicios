#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Se houver argumentos (além do nome do programa), procurar pelas notas
  if (argc > 1) {
    float sum = 0; // Soma de valores para cálculo da média
    // Itera por todos os valores nos argumentos e 
    for (int i = 1; i < argc; i++) {
      sum += (float)strtod(argv[i], NULL);
    }
    // Calcula a média aritmética e imprime resultado
    float avg = sum / ((float)argc - 1);
    printf("A media artimetica foi de %.2f, ", avg);
    if (avg >= 7)
      printf("aprovado\n");
    else if (avg >= 3)
      printf("exame\n");
    else
      printf("reprovado\n");
  }

  return 0;
}