#include "queue.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

//TODO CHANGE THIS TO LINKED LIST IMPLEMENTATION IF NEEDED

// Code inspired by lecture-11-Stacks.pdf and the leacture on stacks/queues


//Struct code adopted from code given in asgn3 doc
typedef struct Queue {
    uint32_t head;	// Index of head of the queue
    uint32_t tail;	// Index of the tail of the queue
    uint32_t size;	// The number of elements in the queue
    uint32_t capacity;	// Capacity of the queue
    int64_t *items; 	//Holds the items
} Queue;

Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue)); // creates new queue using malloc to allocate space
    if (q) {
        q->head = 0; 
	q->tail = 0;
	q->size = 0;
	q->capacity = capacity; // set initial size of queue to given capacity
        q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
	if (!q->items) {
	    free(q);
	    q = NULL;
	}
    }
    return q;
}

void queue_delete(Queue **q) {
    if (q) {
        free((*q)->items);
	free(q);
    }
}

bool queue_empty(Queue *q) {
    if (q) {
        return q->size == 0;
    }
    return true;
}

bool queue_full(Queue *q) {
    if (q) {
        return q->capacity == q->tail;
    }
    return true;
}

uint32_t queue_size(Queue *q) {
    return q->size;
}

bool enqueue(Queue *q, int64_t x) {
    if (q) {
        if (queue_full(q)) {
            return false;
	}
        q->size += 1;
	q->items[q->tail] = x;
        q->tail = (q->tail + 1) % q->capacity;
	return true;
    }
    return false;

}

bool dequeue(Queue *q, int64_t *x) {
    if (q) {
        if (queue_empty(q)) {
            return false;
	}
        q->size -= 1;
        *x = q->items[q->head];
        q->head = (q->head + 1) % q->capacity;
	return true;
    }
    return false;

}

void queue_print(Queue *q) {
    printf("[");
    for (uint32_t i = 0; i < q->head; i++) {
        printf("%" PRId64, q->items[i]);
        if (i + 1 != q->head) {
            printf(", ");
        }
    }
    printf("]\n");
}
