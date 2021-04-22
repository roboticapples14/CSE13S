#include "queue.h"

//TODO CHANGE THIS TO LINKED LIST IMPLEMENTATION IF NEEDED

// Code inspired by lecture-11-Stacks.pdf and the leacture on stacks/queues


//Struct code adopted from code given in asgn3 doc
struct Queue {
    uint32_t head;	// Index of head of the queue
    uint32_t tail;	// Index of the tail of the queue
    uint32_t size;	// The number of elements in the queue
    uint32_t capacity;	// Capacity of the queue
    int64_t *items; 	//Holds the items
}

Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue)); // creates new queue using malloc to allocate space
    if (q) {
        q->head = q->tail = 0;
	q->capacity = capacity; // set initial size of queue to given capacity
        q->Q = (item *) calloc(size, sizeof(item));
	if (q->items) {
            return q;
	}
	free(q);
    }
    return q;
}

void queue_delete(Queue **q) {
    if (q) {
        free(q->Q);
	free(q);
    }
}

bool queue_empty(Queue *q) {
    if (q) {
        return q->head == q->tail;
    }
    return true;
}

bool queue_full(Queue *q) {
    if (q) {
        return succ(q, q->head) == q->tail;
    }
    return true;
}

uint32_t queue_size(Queue *q) {
    return q->size;
}


