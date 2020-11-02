#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ler_comando.h>

ComandoInserir *ler_comando_inserir() {
    // Ignore \r, \n and ' '
    int c, chave, back;
    while (strchr(" \r\n", c = getchar()) && !feof(stdin));
    if (c == 'i' && scanf(" %d %d", &chave, &back) == 2) {
        ComandoInserir *comando = (ComandoInserir *)malloc(sizeof(ComandoInserir));
        comando->tipo = INSERIR;
        comando->chave = chave;
        comando->back = back;
        return comando;
    }
    if (c != EOF) ungetc(c, stdin);
    return NULL;
}

ComandoRemover *ler_comando_remover() {
    // Ignore \r, \n and ' '
    int c, chave;
    while (strchr(" \r\n", c = getchar()) && !feof(stdin));
    if (c == 'r' && scanf(" %d", &chave) == 1) {
        ComandoRemover *comando = (ComandoRemover *)malloc(sizeof(ComandoRemover));
        comando->tipo = REMOVER;
        comando->chave = chave;
        return comando;
    }
    if (c != EOF) ungetc(c, stdin);
    return NULL;
}

Comando *ler_comando_finalizar() {
    int c;
    while (strchr(" \r\n", c = getchar()) && !feof(stdin));
    if (c == 'f') {
        Comando *comando = (Comando *)malloc(sizeof(Comando));
        comando->tipo = FINALIZAR;
        return comando;
    }
    if (c != EOF) ungetc(c, stdin);
    return NULL;
}

Comando *ler_comando()  {
    Comando *comando;
    if (!((comando = (Comando *)ler_comando_inserir())
        ||(comando = (Comando *)ler_comando_remover())
        ||(comando = (Comando *)ler_comando_finalizar())))
        return NULL;

    return comando;
}
