#include "bubble.h"
#include "shell.h"
#include "quick.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "absqQr:n:p:"

void print_instructions();
int compares;
int moves;
uint32_t max_stack_size;
uint32_t max_queue_size;

int main(int argc, char **argv) {
    int opt = 0;
    extern int compares;
    extern int moves;
    extern uint32_t max_stack_size;
    extern uint32_t max_queue_size;
    // int markers for which functions to run
    int bubble = 0;
    int shell = 0;
    int quick_stack = 0;
    int quick_queue = 0;
    int seed = 13371453;
    uint32_t size = 100;
    uint32_t elements = 100;
    uint32_t num_to_print = elements;

    //user input loop
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        // sorts
	if (opt == 'a') {
            bubble = 1;
	    shell = 1;
	    quick_stack = 1;
	    quick_queue = 1;
	}
        if (opt == 'b') {
            bubble = 1;
	}
        if (opt == 's') {
            shell = 1;
	}
        if (opt == 'q') {
            quick_stack = 1;
	}
        if (opt == 'Q') {
            quick_queue = 1;
	}
	// output prefrences (optarg = value passed through with argument)
        if (opt == 'r') {
            seed = atoi(optarg);
	}
        if (opt == 'n') {
            size = atoi(optarg);
	}
        if (opt == 'p') {
            elements = atoi(optarg);
	}
	// if opt != any OPTIONS
	if (opt != 'a' && opt != 'b' && opt != 's' && opt != 'q' && opt != 'Q' && opt != 'r' && opt != 'n' && opt != 'p') {
	    // print error and instructions if user didn't enter valid input, then quit
            printf("./sorting: invalid option -- '%c'\n", opt);
	    print_instructions();
	    return 1;
	}
    }

    // if no sorting was selected
    if (!(bubble || shell || quick_stack || quick_queue))  {
	// Instructions
        printf("Select at least one sort to perform.\n");
        print_instructions();
	return 1;
    }


    // set random seed to given seed
    srandom(seed);
    
    // if elements to print is larger than size of array, set elements = size to prevent overflow 
    if (elements > size) {
        num_to_print = size;
    }
    else {
        num_to_print = elements;
    }
    

    // Executes sorts
    if (bubble == 1) {
        // set random seed to given seed
        srandom(seed);
        // Generates new (unsorted) array to be sorted of len size
        uint32_t arr[size];  
        for (uint32_t i = 0; i < size; i++) {
            arr[i] = random(); 
        }

	// bubble sort array
        bubble_sort(arr, size);
        printf("Bubble Sort\n");
	printf("%i elements, %i moves, %i compares\n", size, moves, compares);
        for (uint32_t j = 0; j < num_to_print; j++) {
            // newline every 5th element
	    if (j % 5 == 0) {
                printf("\n");
	    }
	    printf("%13" PRIu32, arr[j]);
	}
	printf("\n");
    }
    
    if (shell == 1) {
        // re-set random seed to given seed (to ensure all randomly generated arrays are the same)
        srandom(seed);
        // Generates new (unsorted) array to be sorted of len size
        uint32_t arr[size];  
        for (uint32_t i = 0; i < size; i++) {
            arr[i] = random(); 
        }

        shell_sort(arr, size);
	// TODO: implement moves, compares, and stack/queue size vars
	// Use extern vars?
        printf("Shell Sort\n");
	printf("%i elements, %i moves, %i compares\n", size, moves, compares);
        for (uint32_t j = 0; j < num_to_print; j++) {
            if (j % 5 == 0) {
                printf("\n");
	    }
            printf("%13" PRIu32, arr[j]);
	}
	printf("\n");
    }

    if (quick_stack == 1) {
        // re-set random seed to given seed (to ensure all randomly generated arrays are the same)
        srandom(seed);
        // Generates new (unsorted) array to be sorted of len size
        uint32_t arr[size];  
        for (uint32_t i = 0; i < size; i++) {
            arr[i] = random(); 
        }
	
	// sort arr
        quick_sort_stack(arr, size);
        printf("Quick Sort (Stack)\n");
	// use extern vars moves, compares to keep track of sort stats
	printf("%i elements, %i moves, %i compares\n", size, moves, compares);
        printf("Max stack size: %i", max_stack_size);
	for (uint32_t j = 0; j < num_to_print; j++) {
            // newline every 5th element printed
            if (j % 5 == 0) {
                printf("\n");
	    }
            printf("%13" PRIu32, arr[j]);
	}
	printf("\n");
    }

    if (quick_queue == 1) {
        // re-set random seed to given seed (to ensure all randomly generated arrays are the same)
        srandom(seed);
        // Generates new (unsorted) array to be sorted of len size
        uint32_t arr[size];  
        for (uint32_t i = 0; i < size; i++) {
            arr[i] = random(); 
        }
	
	//DEBUG PRINT
	printf("UNSORTED ARRAY:\n");
        for (uint32_t j = 0; j < num_to_print; j++) {
            // newline every 5th element printed
            if (j % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, arr[j]);
        }
        printf("\n");

	// sort arr
	quick_sort_queue(arr, size);
        printf("Quick Sort (Queue)\n");
	// use extern vars moves, compares to keep track of sort stats
	printf("%i elements, %i moves, %i compares\n", size, moves, compares);
        printf("Max queue size: %i", max_queue_size);
        for (uint32_t j = 0; j < num_to_print; j++) {
            // newline every 5th element printed
	    if (j % 5 == 0) { 
                printf("\n");
	    }
            printf("%13" PRIu32, arr[j]);
	}
	printf("\n");
    }
}


void print_instructions() {
    // Instructions
    printf("SYNOPSIS\n");
    printf("   A collection of comparison-based sorting algorithms.\n\n");
    printf("USAGE\n");
    printf("   ./sorting [-absqQ] [-n length] [-p elements] [-r seed]\n\n");
    printf("OPTIONS\n");
    printf("   -a              Enable all sorts.\n");
    printf("   -b              Enable Bubble Sort.\n");
    printf("   -s              Enable Shell Sort.\n");
    printf("   -q              Enable Quick Sort (Stack).\n");
    printf("   -Q              Enable Quick Sort (Queue).\n");
    printf("   -n length       Specify number of array elements.\n");
    printf("   -p elements     Specify number of elements to print.\n");
    printf("   -r seed         Specify random seed.\n");
}

