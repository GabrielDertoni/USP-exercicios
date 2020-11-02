#include <stdio.h>
#include <stdlib.h>
#include <person.h>

struct _person {
    char *name;
    unsigned short age;
    int hasCondition;
};

person_t *createPerson(char *name, unsigned short age, int hasCondition) {
    person_t *person = (person_t *)malloc(sizeof(person_t));
    person->name = name;
    person->age = age;
    person->hasCondition = hasCondition;
    return person;
}

void deletePerson(person_t *person) {
    if (person) {
        if (person->name) free(person->name);
        free(person);
    }
}

unsigned short getPersonAge(person_t *person) { return person->age; }
char *getPersonName(person_t *person) { return person->name; }
int getPersonHasCondition(person_t *person) { return person->hasCondition; }
