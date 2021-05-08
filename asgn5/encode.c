#include "bv.h"
#include "bm.h"
#include "hamming.h"
#include "hamming2.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>


// h = help, i = infile, o = outfile
#define OPTIONS "hi:o:"

void print_instructions();
uint8_t G_arr[] = {1, 0, 0, 0, 0, 1, 1, 1,
	           0, 1, 0, 0, 1, 0, 1, 1,
		   0, 0, 1, 0, 1, 1, 0, 1,
		   0, 0, 0, 1, 1, 1, 1, 0};


int main(int argc, char *argv[]) {
    int opt = 0; 
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int help = 0;
    int infile_given = 0;
    int outfile_given = 0;
    char input_byte; // where lines are stored
    BitMatrix *G = bm_create(4, 8);

    for (uint32_t i = 0; i < bm_rows(G); i++) {
        for (uint32_t j = 0; j < bm_cols(G); j++) {
	    // if val of G_arr[index] is 1, set that bit to 1
            if (G_arr[(i * bm_cols(G)) + j] == 1) {
                bm_set_bit(G, i, j);
            }
	    // else clear bit
	    else {
                bm_clr_bit(G, i, j);
	    }
        }
    }

    //user input loop
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        // help menu
        if (opt == 'h') {
            help = 1;
        }
        // provided input file
        if (opt == 'i') {
            infile_given = 1;
            infile = fopen(optarg, "r"); //r for read
            if (infile == NULL) {
                fprintf(stderr, "failed to open input file");
                return 1;
            }
        }
        // provided output file
        if (opt == 'o') {
            outfile_given = 1;
            outfile = fopen(optarg, "w"); //w for write
            if (outfile == NULL) {
                fprintf(stderr, "failed to open output file");
                return 1;
            }
        }
    }

    if (infile_given) {
         //  Getting  and  setting  file  permissions
	 struct  stat  statbuf;
         fstat(fileno(infile), &statbuf);
         fchmod(fileno(outfile), statbuf.st_mode);
    }


    //TODO: Transfer file permissions from infile to outfile
    while ((input_byte = fgetc(infile)) != EOF) {
        uint8_t lower = lower_nibble(input_byte);
	uint8_t upper = upper_nibble(input_byte);
	uint8_t code_lower = ham_encode(G, lower);
	//fputc(code_lower, outfile);
	printf("%" PRIu8, code_lower);
	uint8_t code_upper = ham_encode(G, upper);
	//fputc(code_upper, outfile);
	printf("%" PRIu8, code_upper);

    }

    return 0;
}


