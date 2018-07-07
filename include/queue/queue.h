#ifndef QUEUE_H
#define QUEUE_H

/*
    AUTHORS: J. W. Sheridan, Siddharth Mahendraker, Shimi Smith
*/

#include <stdint.h>

#define MAX_QUEUE_SIZE 5
#define QUEUE_DATA_SIZE 8

typedef struct {
    uint8_t head;
    uint8_t tail;
    uint8_t size;
    uint8_t content[MAX_QUEUE_SIZE][QUEUE_DATA_SIZE];
} queue_t;

void init_queue(queue_t*);
uint8_t is_full(queue_t*);
uint8_t is_empty(queue_t*);
uint8_t enqueue(queue_t*, uint8_t*);
uint8_t dequeue(queue_t*, uint8_t*);

#endif
