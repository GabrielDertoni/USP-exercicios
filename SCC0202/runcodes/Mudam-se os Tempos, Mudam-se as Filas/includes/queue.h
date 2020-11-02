#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <person.h>

#define assert(condition) ({\
    if (!condition) {\
        printf("Assertion Error: "#condition" (%s:%d)\n", __FILE__, __LINE__);\
        exit(EXIT_FAILURE);\
    }\
})

typedef person_t *elem_t;
typedef struct _queue queue_t;

queue_t *createQueue(unsigned int size);
void deleteQueue(queue_t *queue);
void pushQueue(queue_t *queue, elem_t value);
elem_t popQueue(queue_t *queue);
unsigned int getQueueSize(queue_t *queue);
int isFullQueue(queue_t *queue);
int isEmptyQueue(queue_t *queue);

#endif
