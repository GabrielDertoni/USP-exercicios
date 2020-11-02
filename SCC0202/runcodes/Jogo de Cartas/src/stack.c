#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stack.h>

struct _stack {
    elem_t *data;
    unsigned int size;
    unsigned int allocated;
};

stack_t *createStack(int n) {
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    assert(stack);
    stack->data = (elem_t *)malloc(n * sizeof(elem_t));
    stack->size = 0;
    stack->allocated = n;
    return stack;
}

void deleteStack(stack_t *stack) {
    if (!stack) return;
    if (stack->data) free(stack->data);
    free(stack);
}

void pushStack(stack_t *stack, elem_t val) {
    assert(stack);
    if (stack->size >= stack->allocated) {
        if (!(stack->allocated *= 2))
            stack->allocated = CHUNK;

        stack->data = (elem_t *)realloc(stack->data, stack->allocated * sizeof(elem_t));
    }
    stack->data[stack->size++] = val;
}

elem_t popStack(stack_t *stack) {
    assert(stack && !isEmptyStack(stack));
    if ((int)stack->size < (int)stack->allocated / 2 - CHUNK)
        stack->data = realloc(stack->data, (stack->allocated /= 2) * sizeof(elem_t));

    return stack->data[--stack->size];
}

elem_t peakStack(stack_t *stack) {
    assert(stack);
    return stack->data[stack->size - 1];
}

bool isEmptyStack(stack_t *stack) {
    assert(stack);
    return stack->size == 0;
}

unsigned int getStackSize(stack_t *stack) {
    assert(stack);
    return stack->size;
}
