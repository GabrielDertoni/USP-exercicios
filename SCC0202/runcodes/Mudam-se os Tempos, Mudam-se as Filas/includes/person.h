#ifndef __PERSON_H__
#define __PERSON_H__

typedef struct _person person_t;

person_t *createPerson(char *name, unsigned short age, int hasCondition);
void deletePerson(person_t *person);
unsigned short getPersonAge(person_t *person);
char *getPersonName(person_t *person);
int getPersonHasCondition(person_t *person);

#endif
