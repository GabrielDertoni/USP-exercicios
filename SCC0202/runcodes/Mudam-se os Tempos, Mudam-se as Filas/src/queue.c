#include <stdlib.h>
#include <queue.h>

struct _queue {
    elem_t *data;
    unsigned int size;
    unsigned int nelem;
    unsigned int start;
    unsigned int end;
};

queue_t *createQueue(unsigned int size) {
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    queue->size = size;
    queue->nelem = 0;
    queue->start = 0;
    queue->end = 0;
    queue->data = (elem_t *)malloc(size * sizeof(queue_t));

    return queue;
}

void deleteQueue(queue_t *queue) {
    if (queue) {
        if (queue->data) free(queue->data);
        free(queue);
    }
}

void pushQueue(queue_t *queue, elem_t value) {
    assert(queue && !isFullQueue(queue));
    queue->data[queue->end] = value;
    queue->end = (queue->end + 1) % queue->size;
    queue->nelem++;
}

elem_t popQueue(queue_t *queue) {
    assert(queue && !isEmptyQueue(queue));
    elem_t res = queue->data[queue->start];
    queue->start = (queue->start + 1) % queue->size;
    queue->nelem--;
    return res;
}

unsigned int getQueueSize(queue_t *queue) {
    return queue->nelem;
}

int isFullQueue(queue_t *queue) {
    assert(queue);
    return queue->nelem == queue->size;
}

int isEmptyQueue(queue_t *queue) {
    assert(queue);
    return queue->nelem == 0;
}
