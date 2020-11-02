#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>
#include <person.h>

char *parseUntill(char *stop, char *string) {
    int i;
    for (i = 0; !strchr(stop, string[i]); i++);
    return memcpy((char *)calloc(i + 1, sizeof(char)), string, i * sizeof(char));
}

int isPrefixOf(char *pref, char *str) {
    for (; *pref && *str && *pref == *str; pref++, str++);
    return !*pref;
}

person_t *parseEnqueue(char *string) {
    int index = 0;
    if (isPrefixOf("ENTRA", string)) {
        index += strlen("ENTRA") + 1;
        char *name = parseUntill(" ", string + index);
        index += strlen(name) + 1;

        char *agestr = parseUntill(" ", string + index);
        index += strlen(agestr) + 1;

        int age = atoi(agestr);
        char *hasCondStr = parseUntill(" \n\r", string + index);

        int hasCondition = atoi(hasCondStr);

        free(agestr);
        free(hasCondStr);

        return createPerson(name, age, hasCondition);
    }
    return NULL;
}

char *readline(FILE *fp) {
    int c, index = 0, allocated = 0;
    while (strchr("\r\n", c = getc(fp)));
    char *line = NULL;
    do {
        if (index + 1 >= allocated) {
            if (!(allocated *= 2))
                allocated = 32;

            line = (char *)realloc(line, allocated * sizeof(char));
        }
        line[index++] = c;
    } while ((c = getc(fp)) != EOF && !feof(fp) && !strchr("\n\r", (char)c));
    line = (char *)realloc(line, (index + 1) * sizeof(char));
    line[index] = '\0';
    return line;
}

void maybePushQueue(queue_t *queue, person_t *person) {
    if (!isFullQueue(queue))
        pushQueue(queue, person);
    else
        printf("FILA CHEIA\n");
}

void printPerson(person_t *person) {
    printf("%s %d %d\n",
           getPersonName(person),
           getPersonAge(person),
           getPersonHasCondition(person));
}

int main(void) {
    int n;
    scanf(" %d", &n);

    queue_t *priority1 = createQueue(n);
    queue_t *priority2 = createQueue(n);
    queue_t *priority3 = createQueue(n);
    queue_t *priority4 = createQueue(n);

    person_t *person;
    while (n--) {
        char *line = readline(stdin);
        person = parseEnqueue(line);
        if (person)
            if (getPersonAge(person) >= 60)
                if (getPersonHasCondition(person))
                    maybePushQueue(priority1, person);
                else
                    maybePushQueue(priority3, person);
            else
                if (getPersonHasCondition(person))
                    maybePushQueue(priority2, person);
                else
                    maybePushQueue(priority4, person);
        else
            if (!isEmptyQueue(priority1))
                printPerson(popQueue(priority1));

            else if (!isEmptyQueue(priority2))
                printPerson(popQueue(priority2));

            else if (!isEmptyQueue(priority3))
                printPerson(popQueue(priority3));

            else if (!isEmptyQueue(priority4))
                printPerson(popQueue(priority4));

            else
                printf("FILA VAZIA\n");
    }

    return EXIT_SUCCESS;
}
