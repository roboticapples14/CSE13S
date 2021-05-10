#include "bm.h"
#include "bv.h"
#include "hamming.h"
#include "hamming2.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// h = help, i = infile, o = outfile
#define OPTIONS "hvi:o:"

void print_instructions();
uint8_t Ht_arr[] = { 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 1 };

int main(int argc, char *argv[]) {
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int total_bytes; // total bytes read
    int corrected_bytes; // num of corrected error bits
    int uncorrected_bytes; // num of uncorrected error bits
    double error_rate; // rate of uncorrected errors for given input
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
        if (opt != 'o' && opt != 'i' && opt != 'h' && opt != 'v') {
            print_instructions();
            return 1;
        }
    }

    if (help) {
        print_instructions();
        return 1;
    }

    // Transfer file permissions from infile to outfile
    if (infile_given && outfile_given) {
        struct stat statbuf;
        fstat(fileno(infile), &statbuf);
        fchmod(fileno(outfile), statbuf.st_mode);
    }

    uint8_t byte1; // holds lower nibble of decrypted byte
    uint8_t byte2; // holds upper nibble of decrypted byte
    uint8_t full_decrypted_byte;
    while (!(feof(infile))) {
        HAM_STATUS status;
        input_byte = fgetc(infile);
        status = ham_decode(Ht, input_byte, &byte1);
        if (status == HAM_ERR) {
            uncorrected_bytes += 1;
        } else if (status == HAM_CORRECT) {
            corrected_bytes += 1;
        }
        total_bytes += 1;

        input_byte = fgetc(infile);
        status = ham_decode(Ht, input_byte, &byte2);
        if (status == HAM_ERR) {
            uncorrected_bytes += 1;
        } else if (status == HAM_CORRECT) {
            corrected_bytes += 1;
        }

        full_decrypted_byte = pack_byte(byte2, byte1);
        if ((char) full_decrypted_byte == EOF) {
            break;
        }
        fputc(full_decrypted_byte, outfile);
        total_bytes += 1;
    }

    fprintf(outfile, "\n");

    error_rate = (float) uncorrected_bytes / (float) total_bytes;
    if (verbose) {
        //fputc(...);
        fprintf(outfile, "Total bytes processed: %i\n", total_bytes);
        fprintf(outfile, "Uncorrected errors: %i\n", uncorrected_bytes);
        fprintf(outfile, "Corrected errors: %i\n", corrected_bytes);
        fprintf(outfile, "Error rate: %f\n", error_rate);
    }

    // close any opened files
    if (infile_given) {
        fclose(infile);
    }
    if (outfile_given) {
        fclose(outfile);
    }
    // free allocated data
    bm_delete(&Ht);

    return 0;
}

void print_instructions() {
    // Instructions
    printf("SYNOPSIS\n");
    printf("  A Hamming(8, 4) systematic code decoder.\n\n");
    printf("USAGE\n");
    printf("  ./decode [-h] [-v] [-i infile] [-o outfile]\n\n");
    printf("OPTIONS\n");
    printf("  -h             Program usage and help.\n");
    printf("  -v             Print statistics of decoding to stderr.\n");
    printf("  -i infile      Input data to encode.\n");
    printf("  -o outfile     Output of encoded data.\n");
}
