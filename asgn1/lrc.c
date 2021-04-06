#include <stdio.h>
#include "philos.h"

int main() {
    int total_players;
    int max_name_len = 100;
    
    // prompt user for number of players
    printf("Please enter number of players: ");
    scanf("%d", &total_players); // get user input of # of players
    
    int active_players = total_players; 
    char players[total_players][max_name_len];

    for (int i = 0; i < total_players; i++) {
	// assign philosophers to player array
        players[i] = philosophers[i]; // philosophers array comes from philos.h
    }

}
