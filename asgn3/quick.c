#include "quick.h"
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"

static uint64_t partition(uint32_t *A, uint32_t lo, uint32_t hi);

static bool less_than(uint32_t el_1, uint32_t el_2);
int compares;
int moves;


void quick_sort_stack(uint32_t *A, uint32_t n) {
    // Declares external variables compares and moves
    extern int compares;
    extern int moves;
    int64_t lo = 0;
    int64_t hi = n + 1;
    int64_t p;
    // resets compares and moves to 0
    compares = 0;
    moves = 0;
    
    Stack *s = stack_create(n);
    stack_push(s, lo);
    stack_push(s, hi);
    while (stack_size(s) != 0) {
        stack_pop(s, &hi); // pops into hi
	stack_pop(s, &lo); // pops into lo
        p = partition(A, lo, hi);
	if (lo < p) {
            stack_push(s, lo);
	    stack_push(s, p);
	}
        if (hi > p + 1) {
            stack_push(s, p + 1);
	    stack_push(s, hi);
	}
    }
}

void quick_sort_queue(uint32_t *A, uint32_t n) {
    // Declares external variables compares and moves
    extern int compares;
    extern int moves;
    int64_t lo = 0;
    int64_t hi = n + 1;
    int64_t p;
    // resets compares and moves to 0
    compares = 0;
    moves = 0;
  
    //TODO: change usage to queue
    Queue *q = queue_create(n);
    stack_push(s, lo);
    stack_push(s, hi);
    while (stack_size(s) != 0) {
        hi = stack_pop(s, &lo);
        lo = stack_pop(s, &hi);
        p = partition(A, lo, hi);
        if (lo < p) {
            stack_push(s, lo);
            stack_push(s, p);
        }
        if (hi > p + 1) {
            stack_push(s, p + 1);
            stack_push(s, hi);
        }
    }
}

static uint64_t partition(uint32_t *A, uint32_t lo, uint32_t hi) {
    // Declares external variables compares and moves, but not resetting to preserve count in sort
    extern int compares;
    extern int moves;
    uint32_t pivot = A[lo + ((hi -lo) / 2)]; //prevent overflow
    moves += 1;
    // i and j should be signed in order to rep -1 (lo - 1)
    int64_t j = hi + 1;
    int64_t i = lo - 1;
    do {
        i += 1;
        do { // itterate through values on left side of pivot until hitting value that's greater than pivot
	    i += 1;
	} while (less_than(A[i], pivot)); // using less_than function for compares increment
	
	j -= 1;
	do { // itterates thru right side of pivot until value is less than pivot
            j -= 1;
	} while (less_than(pivot, A[j])); // using less_than function for compares increment
	
	// now A[i] should be greater than A[j], so we swap them
	// but only if index i < j
	if (i < j) {
            uint32_t temp = A[i];
            A[i] = A[j];
	    A[j] = temp;
	    moves += 3; //swaps = 3 moves
	}
    } while( i < j);
    return j;
}

/* comparison function, created to ensure that every time comparison is completed
that external var compares is itterated
Function idea inspired by Eugene's lab section 4/22 timestamp ~18:00 */
static bool less_than(uint32_t el_1, uint32_t el_2) {
    extern int compares;
    compares += 1;
    return el_1 < el_2;
}
