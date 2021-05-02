#include "stack.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t size;
    uint64_t *items;
};

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

bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) {
        s->capacity *= 2;
        s->items = (uint64_t *) realloc(s->items, s->capacity * sizeof(uint64_t));
    }
    s->items[s->top] = x; // set top of stack to x
    s->top += 1; // itterate stack pointer
    s->size += 1; // increase stack size
    return true;
}

bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    s->size -= 1;
    return true;
}

//TODO
bool stack_peek(Stack *s, uint32_t *x) {
    //Peeking into a stack is synonymous with querying a stack about the element at the top of the stack. If the stack is empty prior to peeking into it, return false to indicate failure.
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    s->top += 1;
    return true;
}
//TODO
void stack_copy(Stack *dst, Stack *src) {
    //Assuming that the destination stack dst is properly initialized, make dst a copy of the source stack src.This means making the contents of dst->items the same as src->items. The top of dst should also match the top of src
    for (uint32_t i = 0; i < src->top; i += 1) {
        dst->items[i] = src->items[i];
    }
    dst->top = src->top;
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, "->");
        }
    }
    fprintf(outfile, "\n");
}
