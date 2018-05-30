/*
    AUTHORS: Siddharth Mahendraker, Shimi Smith, J. W. Sheridan
*/

#include <stdint.h>

#define MAX_STACK_SIZE 10
#define STACK_DATA_SIZE 8

typedef struct {
    uint8_t size;
    uint8_t index;
    uint8_t content[MAX_STACK_SIZE][STACK_DATA_SIZE];
} stack_t;

void init_stack(stack_t*);
uint8_t is_full(stack_t*);
uint8_t is_empty(stack_t*);
uint8_t push(stack_t*, uint8_t*);
uint8_t pop(stack_t*, uint8_t*);