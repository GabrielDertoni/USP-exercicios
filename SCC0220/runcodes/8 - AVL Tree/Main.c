#include <stdio.h>
#include <stdlib.h>

#include "PokeType.h"
#include "Pokemon.h"
#include "PokeDex.h"
#include "AVL.h"
#include "Utils.h"

#define PRE_ORDER  1
#define IN_ORDER   2
#define POST_ORDER 3

/**
 * Compara dois valores de HP. Feita para poder ser usada com a implementação
 * da árvore AVL.
 */
int hp_compare(void *a, void *b) {
	pokemon_t *pokeA = *(pokemon_t **)a;
	pokemon_t *pokeB = *(pokemon_t **)b;
	return pokeA->hp - pokeB->hp;
}

/**
 * Wrapper para printPokemon() feita para poder ser usada com a implementação
 * da árvore AVL.
 *
 */
void printPokemonWrapper(void *element, void *arg) {
	printPokemon(*(pokemon_t **)element);
}

int main() {
    pokemon_t** pkdex = NULL;
    int totalPkmn = 0;
	int op;
	char *fname;
	avl_t *tree = avl_create(sizeof(pokemon_t *), hp_compare);
	
	scanf(" %d", &op);
	fname = readline(stdin);
	pkdex = readPkDex(&totalPkmn, fname);

	for (int i = 0; i < totalPkmn; ++i)
		avl_insert(tree, &pkdex[i]);
	
	switch (op) {
		case PRE_ORDER:
			avl_preorder_foreach(tree, printPokemonWrapper, NULL);
			break;

		case IN_ORDER:
			avl_inorder_foreach(tree, printPokemonWrapper, NULL);
			break;

		case POST_ORDER:
			avl_postorder_foreach(tree, printPokemonWrapper, NULL);
			break;

		default:
			printf("Operacao nao reconhecida\n");
	}
	
	avl_delete(tree, free);
	free(fname);
    for(int i = 0; i < totalPkmn; ++i)
        free(pkdex[i]);

    free(pkdex);

	return 0;
}
