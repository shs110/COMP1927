// DracView.c ... DracView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "DracView.h"
// #include "Map.h" ... if you decide to use the Map ADT
     
struct dracView {
	int currScore;
	int currPlayer;
	int currRound;
	int currHealth;
	int trail[NUM_PLAYERS][TRAIL_SIZE];
	int location;
	int hunterlocation [NUM_PLAYERS];
	int Vamps[TRAIL_SIZE]; //Temporary Values
	int Traps[TRAIL_SIZE]; //Temporary Values
	PlayerMessage messages[]; 
};
     

// Creates a new DracView to summarise the current state of the game
DracView newDracView(char *pastPlays, PlayerMessage messages[])
{
	GameView newg = newGameView(pastPlays, messages[]);
	
    DracView dracView = malloc(sizeof(struct dracView));
	dracView->currScore = newg->currScore;
    dracView->currPlayer = newg->currPlayer;
	dracView->currRound = newg->currRound;
	dracView->currHealth = newg->currHealth[PLAYER_DRACULA];
	dracView->trail[][] = newg->trail[][];
	dracView->location = newg->location;
	dracView->hunterlocation = newg->trail[0..3][0];
	
	//The new Gameview is implemented 
    return dracView;
}
     
     
// Frees all memory previously allocated for the DracView toBeDeleted
void disposeDracView(DracView toBeDeleted)
{
    assert(toBeDeleted != NULL)
    free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(DracView currentView)
{
    assert(currentView != NULL);
    return currentView->currRound;
}

// Get the current score
int giveMeTheScore(DracView currentView)
{
    assert(currentView != NULL);
    return currentView->currScore;
}

// Get the current health points for a given player
int howHealthyIs(DracView currentView, PlayerID player)
{
	assert(currentView != NULL)
    int health;
	playerhp = currentView->currHealth[player];
    return playerhp;
}

// Get the current location id of a given player
LocationID whereIs(DracView currentView, PlayerID player)
{
    assert(currentView != NULL);
	int location;
	playerloc = currentView->hunterlocation[player]
    return playerloc;
}

// Get the most recent move of a given player
void lastMove(DracView currentView, PlayerID player,
                 LocationID *start, LocationID *end)
{
	assert(currentView != NULL)
	start = currentView->trail[player][1]
	end = currentView->trail[player][0]
    return;
}

// Find out what minions are placed at the specified location
void whatsThere(DracView currentView, LocationID where,
                         int *numTraps, int *numVamps)
{
	assert(currentView != NULL)
	int i = 0;
    for (i=0 ; i < TRAIL_SIZE; i++){
		if (currentView->Vamps[i] == where){
			numVamps = 1;
		}
		if (currentView->Traps[i] == where){
			numTraps = 1;
		}
	}
    
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(DracView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    assert(currentView != NULL)
}

//// Functions that query the map to find information about connectivity

// What are my (Dracula's) possible next moves (locations)
LocationID *whereCanIgo(DracView currentView, int *numLocations, int road, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return NULL;
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(DracView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return NULL;
}


