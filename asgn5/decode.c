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

uint8_t  lower_nibble(uint8_t val);
uint8_t  upper_nibble(uint8_t  val);
void print_instructions();
uint8_t Ht_arr[] = {0, 1, 1, 1,
		    1, 0, 1, 1,
		    1, 1, 0, 1,
		    1, 1, 1, 0,
		    1, 0, 0, 0,
		    0, 1, 0, 0,
		    0, 0, 1, 0,
		    0, 0, 0, 1};

int main(int argc, char *argv[]) {
    int opt = 0; 
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int total_bytes;		// total bytes read
    int corrected_bytes; 	// num of corrected error bits
    int uncorrected_bytes;	// num of uncorrected error bits
    int error_rate;		// rate of uncorrected errors for given input
    int help = 0;
    int verbose = 0;
    int infile_given = 0;
    int outfile_given = 0;
    char input_byte; // where lines are stored
    BitMatrix *Ht = bm_create(8, 4);
    total_bytes = 0;
    corrected_bytes = 0;
    uncorrected_bytes = 0;
    error_rate = 0;

    for (uint32_t i = 0; i < bm_rows(Ht); i++) {
        for (uint32_t j = 0; j < bm_cols(Ht); j++) {
	    // if val of G_arr[index] is 1, set that bit to 1
            if (Ht_arr[(i * bm_cols(Ht)) + j] == 1) {
                bm_set_bit(Ht, i, j);
            }
	    // else clear bit
	    else {
                bm_clr_bit(Ht, i, j);
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
            infile = fopen(optarg, "rb"); //r for read
            if (infile == NULL) {
                fprintf(stderr, "failed to open input file");
                return 1;
            }
        }
        // provided output file
        if (opt == 'o') {
            outfile_given = 1;
            outfile = fopen(optarg, "wb"); //w for write
            if (outfile == NULL) {
                fprintf(stderr, "failed to open output file");
                return 1;
            }
        }
        // verbose - print debug stats
        if (opt == 'v') {
            verbose = 1;
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
        uint8_t lower_msg;
	uint8_t upper_msg;
	uint8_t lower = lower_nibble(input_byte);
	uint8_t upper = upper_nibble(input_byte);
	HAM_STATUS lower_status = ham_decode(Ht, lower, &lower_msg);
	HAM_STATUS upper_status = ham_decode(Ht, upper, &upper_msg);
	uint8_t decode_full = pack_byte(upper_msg, lower_msg);
	if (lower_status == HAM_CORRECT) {
            corrected_bytes += 1;
	}
	else if (lower_status == HAM_ERR) {
            uncorrected_bytes += 1;
	}
	if (upper_status == HAM_CORRECT) {
            corrected_bytes += 1;
	}
	else if (upper_status == HAM_ERR) {
            uncorrected_bytes += 1;
	}	
	
	//fputc(decode_full, outfile);
	printf("%8" PRIu8, decode_full);
	total_bytes += 1;
    }
    return 0;
}

