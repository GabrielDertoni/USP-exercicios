#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stack.h>

void printStack(stack_t *stack) {
    if (isEmptyStack(stack)) {
        printf("(empty)\n");
        return;
    }
    stack_t *tmp = createStack(getStackSize(stack));
    printf("|");
    while (!isEmptyStack(stack)) {
        int el = popStack(stack);
        pushStack(tmp, el);
        printf(" %d |", el);
    }
    printf("\n");

    while(!isEmptyStack(tmp))
        pushStack(stack, popStack(tmp));
}

int main(void) {
    int n;
    scanf(" %d", &n);

    stack_t *deck = createStack(n); // Monte de compra.
    stack_t *discard = createStack(n); // Monte de descarte.
    stack_t *final = createStack(n); // Monte de morte.
    int currCardNumber = 1; // Carta que se procura.
    int nTurns = 1; // Quantidade de rodadas.
    for (int i = 0; i < n; i++) {
        // Segue as regras do jogo comprando as cartas da entrada padrão.
        int card;
        scanf(" %d", &card);
        if (card == currCardNumber) {
            currCardNumber++;
            pushStack(final, card);
        } else
            pushStack(discard, card);
    }

    while (currCardNumber <= n) {
        nTurns++;
        // Vira o monte de descarte e o torna o monte de compras.
        while (!isEmptyStack(discard))
            pushStack(deck, popStack(discard));

        // Segue as regras do jogo comprando cartas do monte de compras.
        while (!isEmptyStack(deck)) {
            int card = popStack(deck);
            if (card == currCardNumber) {
                currCardNumber++;
                pushStack(final, card);
            } else
                pushStack(discard, card);
        }
    }
    printf("%d\n", nTurns);

    deleteStack(deck);
    deleteStack(discard);
    deleteStack(final);

    return EXIT_SUCCESS;
}
