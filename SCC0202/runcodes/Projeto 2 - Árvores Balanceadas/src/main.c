#include <stdio.h>
#include <stdlib.h>
#include <llrb_tree.h>

#define OP_INSERT 1
#define OP_SUCCESSOR 2
#define OP_PREDECESSOR 3
#define OP_MAX 4
#define OP_MIN 5
#define OP_PREORDER 6
#define OP_INORDER 7
#define OP_POSTORDER 8

int int_compare(void *a, void *b);
void print_element(void *el, void *args);

int main(void) {
    int n, op, val;

    scanf(" %d", &n);

    llrb_tree_t *tree = llrb_create(sizeof(int), int_compare);
    int *result;
    for (int i = 0; i < n; i++) {
        scanf(" %d", &op);
        switch (op) {
            case OP_INSERT:
                scanf(" %d", &val);
                if (!llrb_insert(tree, &val))
                    printf("erro\n");

                break;

            case OP_SUCCESSOR:
                scanf(" %d", &val);
                result = llrb_successor(tree, &val);
                if (!result)
                    printf("erro\n");
                else
                    printf("%d\n", *result);

                break;

            case OP_PREDECESSOR:
                scanf(" %d", &val);
                result = llrb_predecessor(tree, &val);
                if (!result)
                    printf("erro\n");
                else
                    printf("%d\n", *result);

                break;

            case OP_MAX:
                printf("%d\n", *(int *)llrb_max(tree));
                break;

            case OP_MIN:
                printf("%d\n", *(int *)llrb_min(tree));
                break;

            case OP_PREORDER:
                llrb_preorder_foreach(tree, print_element, NULL);
                printf("\n");
                break;

            case OP_INORDER:
                llrb_inorder_foreach(tree, print_element, NULL);
                printf("\n");
                break;

            case OP_POSTORDER:
                llrb_postorder_foreach(tree, print_element, NULL);
                printf("\n");
                break;

            default:
                printf("Operacao invalida\n");
        }

    }

    llrb_delete(tree, free);

    return EXIT_SUCCESS;
}

void print_element(void *el, void *args) {
    printf("%d ", *(int *)el);
}

int int_compare(void *a, void *b) {
    int ia = *(int *)a;
    int ib = *(int *)b;
    return ia - ib;
}
