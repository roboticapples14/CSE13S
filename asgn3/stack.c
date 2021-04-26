#include "stack.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t size;
    uint64_t *items;
} Stack;

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->size = 0;
        s->items = (uint64_t *) calloc(capacity, sizeof(uint64_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {
    return s->top == 0;
}

bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
    return s->size;
}

bool stack_push(Stack *s, int64_t x) {
    if (stack_full(s)) {
        s->capacity *= 2;
        s->items = (uint64_t *) realloc(s->items, s->capacity * sizeof(uint64_t));
    }
    s->items[s->top] = x; // set top of stack to x
    s->top += 1; // itterate stack pointer
    s->size += 1; // increase stack size
    return true;
}

bool stack_pop(Stack *s, int64_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    s->size -= 1;
    return true;
}

// funct given in Eugene's lab 4/22
void stack_print(Stack *s) {
    printf("[");
    for (uint32_t i = 0; i < s->top; i++) {
        printf("%" PRId64, s->items[i]);
        if (i + 1 != s->top) {
            printf(", ");
        }
    }
    printf("]\n");
}
