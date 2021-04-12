/*
############################################################
#                                                          #
#             Made by: Leonardo Tórtoro Pereira            #
#                   leonardop@usp.br                       #
#                                                          #
#      “you have something called "determination."         #
#       so as long as you hold on...                       #
#       so as long as you do what's in your heart...       #
#       i believe you can do the right thing.”             #
#                                                          #
#                   'll0MMMMMMMMMMMMMOll'                  #
#                 .OMMMMMMMMMMMMMMMMMMM0l'                 #
#                'OMMMMMMMMMMMMMMMMMMMMMM0'                #
#               '0MMMMMMMMMMMMMMMMMMMMMMMM0'               #
#              '0MMMMMMMMMMMMMMMMMMMMMMMMMM0'              #
#              lMMMMMMMMMMMMMMMMMMMMMMMMMMMMl              #
#              0MMMMMMMMMMMMMMMMMMMMMMMMMMMM0              #
#              MMMMMMMMMMMMMMMMMMMMMMMMMMMMMM              #
#              MMMMMMMMMMMMMMMMMMMMMMMMMMMMMM              #
#              MMMM0lllllOMMMMMMMM0lllll0MMMM              #
#              MM0l'     .OMMMMMM0'     'l0MM              #
#              M0'        lMMMMMMl        '0M              #
#              Ml    'l'  lMMMMMMl  'l'    lM              #
#              Ml    lMl  lMMMMMMl  lMl    lM              #
#              00'   'l' '0M0ll0M0' 'l'   '00              #
#              lM0l'     lMMl  lMMl     'l0Ml              #
#              '0MM0lll''0M0'  '0M0''lll0MM0'              #
#               lMMMM0ll0MMl    lMM0ll0MMMMl               #
#              '0MM000l0MMMl    lMMM0lOO0MMO.              #
#              lMM0'lMMMMMMOllll0MMMMMMl'0MMl              #
#              lM0' 'l0MMMMMMMMMMMMMM0l' '0Ml              #
#              lM0l' 'llllllllllllllll' 'l0Ml              #
#              lMMMl ll              ll lMMMl              #
#              '0MM0'll'l''l''lll''l'll'0MM0'              #
#               lMMM0l'lMllMllMMMllMl'l0MMMl               #
#               '0MMMO''0llMllMMMll0''0MMM0'               #
#                '0MMM0ll''l''lll''ll0MMM0'                #
#                 'l0MMM0llllllllll0MMMOl'                 #
#                   'l0MMMMMMMMMMMMMM0l'                   #
#                     lMMMMMMMMMMMMMMl                     #
#                                                          #
############################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utils.h"
#include "PokeType.h"
#include "Pokemon.h"
#include "PokeDex.h"
#include "Sorting.h"

#define QUICK_SORT 1
#define HEAP_SORT 2
#define TIM_SORT 3

static int compare_dex_number(void *a, void *b) {
    pokemon_t *poke_a = *(pokemon_t **)a;
    pokemon_t *poke_b = *(pokemon_t **)b;
    return poke_a->dexNumber - poke_b->dexNumber;
}

static int compare_atk(void *a, void *b) {
    pokemon_t *poke_a = *(pokemon_t **)a;
    pokemon_t *poke_b = *(pokemon_t **)b;
    return poke_a->atk - poke_b->atk;
}

static int compare_main_type(void *a, void *b) {
    pokemon_t *poke_a = *(pokemon_t **)a;
    pokemon_t *poke_b = *(pokemon_t **)b;
    return poke_a->mainType - poke_b->mainType;
}

int main() {
    pokemon_t** pkdex = NULL;
    int totalPkmn = 0;

    int sort;
    char *attribute, *fname;

    scanf(" %d", &sort);
    attribute = readline(stdin);
    fname = readline(stdin);

    pkdex = readPkDex(&totalPkmn, fname);
    comp_t comp_fn;

    if (!strcmp(attribute, "dexNumber"))
        comp_fn = compare_dex_number;
    else if (!strcmp(attribute, "atk"))
        comp_fn = compare_atk;
    else if (!strcmp(attribute, "mainType"))
        comp_fn = compare_main_type;
    else
        exit(1); // Nunca deveria ocorrer.

    switch (sort) {
        case QUICK_SORT:
            quick_sort_with(pkdex, totalPkmn, sizeof(pokemon_t *), comp_fn);
            break;

        case HEAP_SORT:
            heap_sort_with(pkdex, totalPkmn, sizeof(pokemon_t *), comp_fn);
            break;

        case TIM_SORT:
            tim_sort_with(pkdex, totalPkmn, sizeof(pokemon_t *), comp_fn);
            break;

        default:
            exit(1); // Nunca deveria ocorrer.
    }

    for(int i = 0; i < totalPkmn; ++i) {
        printPokemon(pkdex[i]);
        free(pkdex[i]);
    }
    free(pkdex);

    free(attribute);
    free(fname);

	return 0;
}

