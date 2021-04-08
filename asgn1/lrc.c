// Natalie Valett, nvalett
// UCSC CSE13S spring 2021

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
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
    char *players[num_players]; // list of character names
    int money[num_players]; // array representing money held by each player
    int pos = 0;

    // instantiate player array with names and money array with starting values
    for (int i = 0; i < num_players; i++) {
	// assign philosophers to player array
        players[i] = philosophers[i]; // philosophers array comes from philos.h
        money[i] = 3; //populate money array with starting $3 value
    }

    
    /* GAMELOOP */
    while (alive > 1) {
        if (money[pos] > 0) { // only roll if still in the game
	    int start_money = money[pos];
	    for (int rolls = 0; rolls <= (start_money < 3) ? start_money : 3; rolls++) { // if player has < $3, roll that # of times, else roll 3 times
                faces roll = die[roll(6)];
		if (roll == LEFT) {
                    //LEFT
		    int left = left(pos, num_players); // index of player to the left
		    money[pos] -= 1; // Deduct $1 from current player
                    if (money[left] <= 0) {
                        alive += 1; // if left player was out, bring them back in
		    }
                    money[left] += 1;
		    printf(" gives $1 to %s", players[left]);
		}
		else if (roll == RIGHT) {
                    //RIGHT
		    int right = right(pos, num_players); // index of player to the left
		    money[pos] -= 1; // Deduct $1 from current player
                    if (money[right] <= 0) {
                        alive += 1; // if left player was out, bring them back in
		    }
                    money[right] += 1;
		    printf(" gives $1 to %s", players[right]);
		}
		else if (roll == CENTER) {
                    //CENTER
		    money[pos] -= 1; // Deduct $1 from current player
                    pot += 1;
		    printf(" puts $1 in the pot");

		}
		else {
                    //PASS
		}
	    }
	    // check if player lost
	    if (money[pos] <= 0) {
                alive -= 1;
	    }
	}
        // itterate pos to next player
	pos = right(pos, num_players);
    }

    if (alive == 1) {
        for (int i = 0; i < num_players; i++) {
            if (money[i] > 0) {
                printf("%s wins the $%i pot with $%i left in the bank!", players[i], pot, money[i]);
	    }
	}
    }
    return 0;
}
