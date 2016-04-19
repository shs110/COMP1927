// testHunterView.c ... test the HunterView ADT



#include <stdio.h>

#include <stdlib.h>

#include <assert.h>

#include <string.h>

#include "HunterView.h"



int main()

{

    int i;

    HunterView hv;



//NEW SET    

    printf("Test basic empty initialisation\n");

    PlayerMessage messages1[] = {};

    hv = newHunterView("", messages1);

    assert(whoAmI(hv) == PLAYER_LORD_GODALMING);

    assert(giveMeTheRound(hv) == 0);

    assert(howHealthyIs(hv,PLAYER_DR_SEWARD) == GAME_START_HUNTER_LIFE_POINTS);

    assert(howHealthyIs(hv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);

    assert(giveMeTheScore(hv) == GAME_START_SCORE);

    assert(whereIs(hv,PLAYER_LORD_GODALMING) == UNKNOWN_LOCATION);

    printf("passed\n");

    disposeHunterView(hv);



//NEW SET

    printf("Test for Dracula trail and basic functions\n");

    PlayerMessage messages2[] = {"Hello","Rubbish","Stuff","","Mwahahah"};

    hv = newHunterView("GST.... SAO.... HZU.... MBB.... DC?....", messages2);

    assert(whoAmI(hv) == PLAYER_LORD_GODALMING);

    assert(giveMeTheRound(hv) == 1);

    assert(whereIs(hv,PLAYER_LORD_GODALMING) == STRASBOURG);

    assert(whereIs(hv,PLAYER_DR_SEWARD) == ATLANTIC_OCEAN);

    assert(whereIs(hv,PLAYER_VAN_HELSING) == ZURICH);

    assert(whereIs(hv,PLAYER_MINA_HARKER) == BAY_OF_BISCAY);

    assert(whereIs(hv,PLAYER_DRACULA) == CITY_UNKNOWN);

    assert(howHealthyIs(hv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);

    printf("passed\n");

    disposeHunterView(hv);



//NEW SET

    printf("Test for encountering Dracula and hunter history\n");

    PlayerMessage messages3[] = {"Hello","Rubbish","Stuff","","Mwahahah","Aha!"};

    hv = newHunterView("GST.... SAO.... HCD.... MAO.... DGE.... GGED...", messages3);

    assert(whereIs(hv,PLAYER_DRACULA) == GENEVA);

    assert(howHealthyIs(hv,PLAYER_LORD_GODALMING) == 5);

    assert(howHealthyIs(hv,PLAYER_DRACULA) == 30);

    assert(whereIs(hv,PLAYER_LORD_GODALMING) == GENEVA);

    LocationID history[TRAIL_SIZE];

    giveMeTheTrail(hv,PLAYER_DRACULA,history);

    assert(history[0] == GENEVA);

    assert(history[1] == UNKNOWN_LOCATION);

    giveMeTheTrail(hv,PLAYER_LORD_GODALMING,history);

    assert(history[0] == GENEVA);

    assert(history[1] == STRASBOURG);

    assert(history[2] == UNKNOWN_LOCATION);

    giveMeTheTrail(hv,PLAYER_DR_SEWARD,history);

    assert(history[0] == ATLANTIC_OCEAN);

    assert(history[1] == UNKNOWN_LOCATION);

    printf("passed\n");        

    disposeHunterView(hv);



//NEW SET

    printf("Test for Dracula doubling back at sea, and losing blood points (Hunter View)\n");

    PlayerMessage messages4[] = {"Hello","Rubbish","Stuff","","Mwahahah","Aha!","","","","Back I go"};

    hv = newHunterView("GGE.... SGE.... HGE.... MGE.... DS?.... "

                       "GST.... SST.... HST.... MST.... DD1....", messages4);

    assert(whereIs(hv,PLAYER_DRACULA) == DOUBLE_BACK_1);

    giveMeTheTrail(hv,PLAYER_DRACULA,history);

    assert(history[0] == DOUBLE_BACK_1);

    assert(history[1] == SEA_UNKNOWN);

    assert(howHealthyIs(hv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 4);

    assert(whoAmI(hv) == 0);

    printf("passed\n");

    disposeHunterView(hv);



//NEW SET

    printf("Test for connections\n");

    int size, seen[NUM_MAP_LOCATIONS], *edges;



    printf("Checking Galatz road connections\n");

    PlayerMessage messages5[] = {"Gone to Galatz"};

    hv = newHunterView("GGA....", messages5);    

    edges = whereCanTheyGo(hv,&size,PLAYER_LORD_GODALMING,1,0,0);

    memset(seen, 0, NUM_MAP_LOCATIONS*sizeof(int));

    for (i = 0; i< size ; i++) seen[edges[i]] = 1;

    assert(size == 5); assert(seen[GALATZ]); assert(seen[CONSTANTA]);

    assert(seen[BUCHAREST]); assert(seen[KLAUSENBURG]); assert(seen[CASTLE_DRACULA]);

    free(edges);

    disposeHunterView(hv);



    printf("Checking Ionian Sea sea connections\n");

    PlayerMessage messages6[] = {"Sailing the Ionian"};

    hv = newHunterView("GIO....", messages6);

    edges = whereCanTheyGo(hv,&size,PLAYER_LORD_GODALMING,0,0,1);

    memset(seen, 0, NUM_MAP_LOCATIONS*sizeof(int));

    for (i = 0; i < size; i++) seen[edges[i]] = 1;

    assert(size == 7); assert(seen[IONIAN_SEA]); assert(seen[BLACK_SEA]);

    assert(seen[ADRIATIC_SEA]); assert(seen[TYRRHENIAN_SEA]);

    assert(seen[ATHENS]); assert(seen[VALONA]); assert(seen[SALONICA]);

    free(edges);

    disposeHunterView(hv);



    printf("Checking Athens rail connections (none)\n");

    PlayerMessage messages7[] = {"Leaving Athens by train"};

    hv = newHunterView("GAT....", messages7);

    edges = whereCanTheyGo(hv,&size,PLAYER_LORD_GODALMING,0,1,0);

    assert(size == 1);

    assert(edges[0] == ATHENS);

    free(edges);

    disposeHunterView(hv);

    printf("passed\n");



//NEW SET

    printf("Test for hunter going to hospital after losing blood points (hunter view)\n");

    PlayerMessage messages8[] = {"something"};

    hv= newHunterView("GST.... SAO.... HCD.... MAO.... DC?T... "

                      "GGETD.. SMS.... HCD.... MMS.... DC?T... "

                      "GZUTD.. SMR.... HCD.... MMR.... DTP....", messages8);


    assert(whereIs(hv,PLAYER_DRACULA) == CASTLE_DRACULA);    

    giveMeTheTrail(hv,PLAYER_DRACULA,history);

    assert(history[0] == TELEPORT);

    assert(history[1] == CITY_UNKNOWN); 

    assert(history[2] == CITY_UNKNOWN);  

    assert(history[3] == UNKNOWN_LOCATION);    

    giveMeTheTrail(hv,PLAYER_DR_SEWARD,history);

    assert(history[0] == MARSEILLES);

    assert(history[1] == MEDITERRANEAN_SEA);

    assert(history[2] == ATLANTIC_OCEAN);

    giveMeTheTrail(hv,PLAYER_LORD_GODALMING,history);

    assert(history[0] == ZURICH);

    assert(history[1] == GENEVA);

    assert(history[2] == STRASBOURG);

    giveMeTheTrail(hv,PLAYER_VAN_HELSING,history);

    assert(history[0] == CASTLE_DRACULA);

    assert(history[1] == CASTLE_DRACULA);

    assert(history[2] == CASTLE_DRACULA);

    assert(history[3] == UNKNOWN_LOCATION);

    assert(history[4] == UNKNOWN_LOCATION);

    assert(history[5] == UNKNOWN_LOCATION);

    //has encountered hunters twice, heals at home base

    assert(howHealthyIs(hv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 10);

    assert(whoAmI(hv) == 0);

    //dracula just finished 3 turns

    assert(giveMeTheRound(hv) == 3);

    //dracula finishes 3 turns, hunter goes to hospital

    assert(giveMeTheScore(hv) == GAME_START_SCORE -3 -6);

    //full health after going to hospital
    //printf("\nhp %d\n", howHealthyIs(hv,PLAYER_LORD_GODALMING));
    //assert(howHealthyIs(hv,PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS);

    printf("passed\n");

    disposeHunterView(hv);



//NEW SET

    printf("test for exposed dracula move\n");

    PlayerMessage messages9[] = {"eyyyyy"};

    hv = newHunterView("GST.... SAO.... HCD.... MBO.... DLET... " 

                       "GST.... SAO.... HCD.... MNA.... DC?T... " 

                       "GST.... SAO.... HCD.... MCF.... DC?T... " 

                       "GSTT... SAO.... HCD.... MGE.... DC?T... " 

                       "GST.... SAO.... HCD.... MZUTD.. DTPT... " 

                       "GST.... SAO.... HCDTD.. MZU.... DC?T... " 

                       "GST.... SAO.... HCD.... MZU....", messages9);

    //assert(whereIs(hv,PLAYER_DRACULA) == GALATZ); 

    giveMeTheTrail(hv,PLAYER_DRACULA,history);

    assert(history[0] == CITY_UNKNOWN);

    assert(history[1] == TELEPORT); 

    assert(history[2] == CITY_UNKNOWN);  

    assert(history[3] == CITY_UNKNOWN);   

    assert(history[4] == CITY_UNKNOWN); 

    //all the players rested for last round, 

    //thus the sixth move in the trail is revealed

    assert(history[5] == LE_HAVRE);

    assert(howHealthyIs(hv,PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS);

    assert(howHealthyIs(hv,PLAYER_VAN_HELSING) == GAME_START_HUNTER_LIFE_POINTS-3);

    assert(howHealthyIs(hv,PLAYER_MINA_HARKER) == GAME_START_HUNTER_LIFE_POINTS);   

    printf("passed\n");

    disposeHunterView(hv);



//NEW SET

    printf("test for rail travel 1\n");

    PlayerMessage messages10[] = {"in the zeroth & first round"};

    hv = newHunterView("GST.... SFL.... HSZ.... MBB.... DC?.... "

                     "GFR.... SNP.... HVE....", messages10);

    //LG:(0+1)%4=1 -->move 1 rail (although there is road between strasbourg and frankfurt

    //DS:(1+1)%4=2 -->move 2 rail (florence-->rome-->naples)

    //VH:(2+1)%4=3 -->move 3 rail (szeged-->budapest-->vienna-->venice)

    //MN:(3+1)%4=0 -->can't rail

    assert(giveMeTheRound(hv) == 1);

    assert(giveMeTheScore(hv) == GAME_START_SCORE -1);

    assert(whereIs(hv,PLAYER_LORD_GODALMING) == FRANKFURT);

    assert(whereIs(hv,PLAYER_DR_SEWARD) == NAPLES);

    assert(whereIs(hv,PLAYER_VAN_HELSING) == VENICE);

    assert(whereIs(hv,PLAYER_MINA_HARKER) == BAY_OF_BISCAY);

    assert(whereIs(hv,PLAYER_DRACULA) == CITY_UNKNOWN);

    disposeHunterView(hv);



    printf("test for rail travel 2\n");

    PlayerMessage messages11[] = {"in the first & second rounds"};

    hv = newHunterView("GST.... SFL.... HSZ.... MBB.... DC?.... "

                     "GFR.... SNP.... HVE.... MSN.... DC?.... "

                     "GBU.... SBI.... HVE.... MMA....", messages11);

    //LG: (0+2)%4=2 -->move 2 rail (frankfurt-->cologne-->brussels)

    //DS: (1+2)%4=3 -->move up to 3 rail (naples-->bari)

    //VH: (2+2)%4=0 -->can't rail

    //MH: (3+2)%4=1 -->1 rail (santander-->madrid)

    assert(giveMeTheRound(hv) == 2);

    assert(giveMeTheScore(hv) == GAME_START_SCORE -2);

    assert(whereIs(hv,PLAYER_LORD_GODALMING) == BRUSSELS);

    assert(whereIs(hv,PLAYER_DR_SEWARD) == BARI);

    assert(whereIs(hv,PLAYER_VAN_HELSING) == VENICE);

    assert(whereIs(hv,PLAYER_MINA_HARKER) == MADRID);

    assert(whereIs(hv,PLAYER_DRACULA) == CITY_UNKNOWN);

    giveMeTheTrail(hv,PLAYER_LORD_GODALMING,history); 

    assert(history[0] == BRUSSELS);

    assert(history[1] == FRANKFURT);

    assert(history[2] == STRASBOURG);

    assert(history[3] == UNKNOWN_LOCATION);

    giveMeTheTrail(hv,PLAYER_DR_SEWARD,history); 

    assert(history[0] == BARI);

    assert(history[1] == NAPLES);

    assert(history[2] == FLORENCE);

    assert(history[3] == UNKNOWN_LOCATION);

    giveMeTheTrail(hv,PLAYER_VAN_HELSING,history); 

    assert(history[0] == VENICE);

    assert(history[1] == VENICE);

    assert(history[2] == SZEGED);

    assert(history[3] == UNKNOWN_LOCATION);

    giveMeTheTrail(hv,PLAYER_MINA_HARKER,history); 

    assert(history[0] == MADRID);

    assert(history[1] == SANTANDER);

    assert(history[2] == BAY_OF_BISCAY);

    assert(history[3] == UNKNOWN_LOCATION);

    printf("passed\n");



//NEW SET

    printf("testing dracula paths from hunter view (with no paths)\n");

    edges = whereCanIgo(hv, &size, 1,0,0);

    assert(size==0); //no road connections as location is city unknown

    free(edges);

    edges = whereCanIgo(hv, &size, 0,0,1);

    assert(size==0); //no boat connections same reason as above

    free(edges);

    printf("passed\n");

    disposeHunterView(hv);



//NEW SET

    printf("testing dracula paths from hunter view (with some paths)\n");

    PlayerMessage messages12[] ={"something"};

    hv= newHunterView("GST.... SAO.... HCD.... MBO.... DCDT...", messages12);

    edges = whereCanIgo(hv, &size, 1,0,0); //road connects

    memset(seen, 0, NUM_MAP_LOCATIONS*sizeof(int));

    for (i = 0; i< size ; i++) seen[edges[i]] = 1;

    assert(size==9);

    //assert(seen[CASTLE_DRACULA]); 

    //assert(seen[GALATZ]); 

    //assert(seen[KLAUSENBURG]);

    free(edges);

    edges = whereCanIgo(hv, &size, 0,0,1); //boat connections

    memset(seen, 0, NUM_MAP_LOCATIONS*sizeof(int));

    for (i = 0; i< size ; i++) seen[edges[i]] = 1;

    printf ("%d\n", edges[0]);

    assert(size==1);

    assert(seen[STRASBOURG]); 

    free(edges);  

    printf("passed\n");

    disposeHunterView(hv);

    return 0;

}



