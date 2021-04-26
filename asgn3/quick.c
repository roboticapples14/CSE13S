#include "quick.h"
#include "stack.h"
#include "queue.h"
#include "queue.c"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static uint64_t partition(uint32_t *A, uint32_t lo, uint32_t hi);

static bool less_than(uint32_t el_1, uint32_t el_2);

// Declare all extern vars
int compares;
int moves;

void quick_sort_stack(uint32_t *A, uint32_t n) {
    // Declares external variables compares and moves
    extern int compares;
    extern int moves;
    extern uint32_t max_stack_size;
    int64_t lo = 0;
    int64_t hi = n - 1;
    uint64_t p;
    // resets compares and moves to 0
    compares = 0;
    moves = 0;
    
    Stack *s = stack_create(n);
    stack_push(s, lo);
    stack_push(s, hi);
    while (stack_size(s) != 0) {
	//ASSERT = false -> GOOD
	//assert(stack_size(s) == 0);
        stack_pop(s, &hi); // pops into hi
	stack_pop(s, &lo); // pops into lo
	// update extern stack size var after pops
	max_stack_size = (stack_size(s) > max_stack_size) ? stack_size(s) : max_stack_size; // updates max stack size if current's > old

        // itterative call to partition with new hi & lo boundaries
	p = partition(A, lo, hi);

        // keeps itterative loop going until sub-arrays are sufficently small (when lo and hi == pivot, meaning sub-arrays are only 1 or 0 items long)
	if (less_than(lo, p)) {
            stack_push(s, lo);
	    stack_push(s, p);
	    // update extern stack size var
	    max_stack_size = (stack_size(s) > max_stack_size) ? stack_size(s) : max_stack_size; // updates max stack size if current's > old
	}
        if (less_than(p + 1, hi)) { // comparison
            stack_push(s, p + 1);
	    stack_push(s, hi);
	    // update extern stack size var
	    max_stack_size = (stack_size(s) > max_stack_size) ? stack_size(s) : max_stack_size; // updates max stack size if current's > old
	}
    }
}

void quick_sort_queue(uint32_t *A, uint32_t n) {
    // Declares external variables compares and moves
    extern int compares;
    extern int moves;
    extern uint32_t max_queue_size;
    int64_t lo = 0;
    int64_t hi = n - 1;
    int64_t p;
    // resets compares and moves to 0
    compares = 0;
    moves = 0;
  
    Queue *q = queue_create(n);
    enqueue(q, lo);
    enqueue(q, hi);
    while (queue_size(q) != 0) {
	dequeue(q, &lo);
        dequeue(q, &hi);
        // update queue size after dequeues
	max_queue_size = (queue_size(q) > max_queue_size) ? queue_size(q) : max_queue_size; // updates max queue size if current's > old
        
	// itterative call to partition with new hi & lo boundaries
	p = partition(A, lo, hi);
        
	// keeps itterative loop going until sub-arrays are sufficently small (when lo and hi == pivot, meaning sub-arrays are only 1 or 0 items long)
	if (less_than(lo, p)) { // comparison
            enqueue(q, lo);
            enqueue(q, p);
	    // update queue size after enqueues
	    max_queue_size = (queue_size(q) > max_queue_size) ? queue_size(q) : max_queue_size; // updates max queue size if current's > old
        }
        if (less_than(p + 1, hi)) { // comparison
            enqueue(q, p + 1);
            enqueue(q, hi);
	    // update queue size after enqueues
	    max_queue_size = (queue_size(q) > max_queue_size) ? queue_size(q) : max_queue_size; // updates max queue size if current's > old
        }
    }
}

static uint64_t partition(uint32_t *A, uint32_t lo, uint32_t hi) {
    // Declares external variables compares and moves, but not resetting to preserve count in sort
    extern int compares;
    extern int moves;
    int32_t pivot = A[lo + ((hi - lo) / 2)]; //prevent overflow
    moves += 1;
    // i and j should be signed in order to rep -1 (lo - 1)
    int i = lo - 1;
    int j = hi + 1;
    
    while (i < j) {
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
    }
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
