#include "bv.h"
#include "bf.h"
#include "ht.h"
#include "node.h"
#include "messages.h"
#include "ll.h"
#include "parser.h"
#include "speck.h"

#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <regex.h>
#include <ctype.h>

#define OPTIONS "hmst:f:"
#define BLOCK 4096
void print_instructions();


int main(int argc, char *argv[]) {
    char *badspeak;
    char *newspeak;
    int opt = 0;
    bool mtf = 0;
    int stats = 0;
    int help = 0;
    uint32_t ht_size = 10000;
    uint32_t bf_size = pow(2, 20); // 2 ^ 20
    char *new_word;
    FILE *infile = stdin;
    regex_t regex;
    LinkedList *bad = ll_create(false);	// for recording badspeak words
    LinkedList *old = ll_create(false);	// for recording oldspeak words
    int thoughtcrime = 0;		// for using badspeak
    int rightspeak = 0;			// for using oldspeak
    //user input loop
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        //help menu
        case 'h': 
	    help = 1; break;
        // verbpse: print compression stats
        case 'm': 
	    mtf = true; break;
        case 's':
            stats = 1;
	    break;
        // given size of ht
	case 't':
	    ht_size = (int) optarg;
            break;
	// given size of bf
        case 'f':
	    bf_size = (int) optarg;
            break;
        default: print_instructions(); break;
        }
    }
    if (help) {
        print_instructions();
        return 1;
    }

    // Initialize bloom filter
    BloomFilter *bf = bf_create(bf_size);
    // Initialize hash table
    HashTable *ht = ht_create(ht_size, mtf);

    // Open badspeak.txt
    infile = fopen("badspeak.txt", "r");
    if (infile == NULL) {
        fprintf(stderr, "failed to open badspeak input file");
        return 1;
    }
	
    // read in badspeak
    while ((fscanf(infile, "%s\n", badspeak)) != EOF) {
        bf_insert(bf, badspeak);
	ht_insert(ht, badspeak, NULL);
    }

    // Open newspeak
    infile = fopen("newspeak.txt", "r");
    if (infile == NULL) {
        fprintf(stderr, "failed to open newspeak input file");
        return 1;
    }

    // read in newspeak
    while ((fscanf(infile, "%s %s\n", badspeak, newspeak)) != EOF) {
        bf_insert(bf, badspeak);
	ht_insert(ht, badspeak, newspeak);
    }

    // set input stream to stdin
    infile = stdin;

    // read user input to filter
    //TODO: regex
    while ((new_word = next_word(infile, &regex)) != NULL) {
        // convert word to lower
        uint32_t j = 0;
	char word[strlen(new_word)];
	// for each char in word, convert to lower and add to new str
	while (j < strlen(new_word)) {
	    word[j] = tolower(new_word[j]);
	    j++;
	}
	
	// bloom filter check
	if (bf_probe(bf, word)) {
	    // hash table check
	    // n is the node containing that badword in hash table, or NULL if not a bad word
	    Node *n = ht_lookup(ht, word);
	    if (n != NULL) {
                // use of badspeak
		if (n->newspeak == NULL) {
		    // record badspeak behavior
		    ll_insert(bad, word, NULL);
		    thoughtcrime = 1;
		}
		else {
		    // record oldspeak behavior
		    ll_insert(old, word, n->newspeak);
		    rightspeak = 1;
		}
	    }
	}
    }
    if (thoughtcrime && rightspeak) {
        printf("%s", mixspeak_message);
	//TODO: output transgressions
	for (uint32_t i = 0; i < ll_length(old); i++) {
            
	}
    }
    else if (thoughtcrime) {
        printf("%s", badspeak_message);
	//TODO: output transgressions
    }
    else if (rightspeak) {
        printf("%s", goodspeak_message);
	//TODO: output transgressions
    }
}


void print_instructions() {
    // Instructions
    printf("SYNOPSIS\n");
    printf("  A word filtering program for the GPRSC.\n");
    printf("  Filters out and reports bad words parsed from stdin.\n\n");

    printf("USAGE\n");
    printf("  ./banhammer [-hsm] [-t size] [-f size]\n\n");

    printf("OPTIONS\n");
    printf("  -h             Program usage and help.");
    printf("  -s           Print program statistics.");
    printf("  -m           Enable move-to-front rule.\n");
    printf("  -t size      Specify hash table size (default: 10000).\n");
    printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
}

