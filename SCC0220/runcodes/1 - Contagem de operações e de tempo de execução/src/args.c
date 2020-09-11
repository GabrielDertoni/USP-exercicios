#include <string.h>
#include <args.h>

int find_arg(char *argname, int argc, char *argv[]) {
    for (int i = 0; i < argc; i++)
        if (!strcmp(argv[i], argname)) return i;
    return -1;
}
