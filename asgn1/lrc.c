// Natalie Valett, nvalett
// UCSC CSE13S spring 2021

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "philos.h"

//
//  Returns  the  position  of the  player  to the  left.
//
// pos:      The  position  of the  current  player.
//  players: The  number  of  players  in the  game.
//
static  inline  uint8_t  left(uint8_t pos , uint8_t  players) {
    return  ((pos + players  - 1) % players);
}

//
//  Returns  the  position  of the  player  to the  right.
//
// pos:      The  position  of the  current  player.
//  players: The  number  of  players  in the  game.
//
static  inline  uint8_t  right(uint8_t pos , uint8_t  players) {
    return  ((pos + 1) % players);
}

// Roll die with n sides
static inline uint32_t roll(uint32_t n) {
    return random() % n;
}


int main(void){
    typedef  enum  faciem { PASS , LEFT , RIGHT , CENTER } faces;
    faces  die[] = { LEFT , RIGHT , CENTER , PASS , PASS , PASS };
    int num_players;
    int seed = 2021;

    // Get num of players from user input: must be 1-14
    printf("Number of players: ");
    if ((scanf("%u", &num_players) < 1) || num_players < 2 || num_players > 14) {
        fprintf(stderr, "Invalid number of players.\n");
        return 1;
    }

    // Get random seed from user input
    printf("Random seed: ");
    if (scanf("%u", &seed) < 1) { // unsigned means it cannot be negative if valid
        fprintf(stderr, "Invalid random seed.\n");
        return 1;
    }
    srandom(seed); // Set starting point for pseudorandom number generator
    
    int pot = 0;
    int max_name_len = 100;
    int alive = num_players; // counter of players still in game
    char players[num_players][max_name_len]; // list of character names
    int money[num_players]; // array representing money held by each player

    // instantiate player array with names and money array with starting values
    for (int i = 0; i < num_players; i++) {
	// assign philosophers to player array
        players[i] = philosophers[i]; // philosophers array comes from philos.h
        money[i] = 3; //populate money array with starting $3 value
    }

    
    /* GAMELOOP */
    








}
