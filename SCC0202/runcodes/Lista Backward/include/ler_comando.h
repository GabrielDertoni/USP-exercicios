#ifndef __LER_COMANDO_H__
#define __LER_COMANDO_H__

// Todos os comandos possuem tipo como primeiro item do struct o que significa
// que o struct Comando pode servir como um genérico sobre ComandoInserir e
// ComandoRemover. Ou seja, um ComandoInserir sempre pode ser seguramente 
// convertido em Comando e Comando pode ser convertido em ComandoInserir se
// tipo == INSERIR. Similarmente para os outros comandos.

typedef enum {
    INSERIR,
    REMOVER,
    FINALIZAR
} TipoComando;

typedef struct {
    TipoComando tipo;
    int chave;
    int back;
} ComandoInserir;

typedef struct {
    TipoComando tipo;
    int chave;
} ComandoRemover;

typedef struct {
    TipoComando tipo;
} Comando;

// Lê o comando inserir, se falhar em fazer isso, retorna NULL.
ComandoInserir *ler_comando_inserir();

// Lê o comando remover, se falhar em fazer isso, retorna NULL.
ComandoRemover *ler_comando_remover();

// Lê o comando finalizar, se falhar em fazer isso, retorna NULL.
Comando *ler_comando_finalizar();

// Lê quailquer comando dentre inserir, remover e finalizar. Retorna NULL
// apenas se nenhum desses for encontrado.
Comando *ler_comando();

#endif
