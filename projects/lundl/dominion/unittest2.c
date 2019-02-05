/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 3
 * Description: This is a unit test the numHandCards() function in dominion.c.
 * ***************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h" 
#include "rngs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printResults(char* testCase, int num, int assertResult)
{
    if(assertResult == 0)
    {
	printf("whoseTurn(): FAIL %s %i\n", testCase, num);
    }
    else
    {
	printf("whoseTurn(): PASS %s %i\n", testCase, num);
    }
}


int assertTrue(int actualVal, int expectedVal, int actualReturn, int expectedReturn)
{
    if((actualVal == expectedVal) && (actualReturn == expectedReturn))
    {
	return 1;
    }
    return 0;
}

/*
int checkDeckDifferences(struct gameState* test, struct gameState* copy)
{
    int i;
    int numDiff = 0;
    // compare the struct we passed to the struct we copied earlier
    for (i = 0; i < test->deckCount[0]; i++)
    {
//	printf("comparing testGame->deck[0][i] to testCopy->deck[0][i]: %i, %i\n", testGame->deck[0][i], testCopy->deck[0][i]);
        // If the cards in this position do not match
	if(test->deck[0][i] != copy->deck[0][i])
	{
	    // Increment count of differences
	    numDiff += 1;
        }  
    }
    if(numDiff > 0)
    {
        // These two decks are different; difference == true
        return 1;
    }

    // These two decks are the same; difference == false
    return 0;
}

*/

void testWhoseTurn()
{
    // Initialize a gameState struct with values we need for this test
    struct gameState* testGame = newGame();



    testGame->numPlayers = 4;
    testGame->whoseTurn = 0;

    // This gameStruct pointer is used for copies
//    struct gameState* testCopy = newGame();
  
/*
    //set up random number generator
    int randomSeed = time(NULL) % 86400;
    SelectStream(1);
    PutSeed((long)randomSeed);
  */

    /* Test Cases 1 - Max number of players */
    char* testMessage = "whose turn out of MAX_PLAYERS and player";
    int i;
    int testCaseNum = 1;
    for(i = 0; i < MAX_PLAYERS; i++)
    {
        printf("\nwhoseTurn() Test Case %i\n", testCaseNum);
 	testCaseNum++;
        // Max number of players, test each player's turn 
    	testGame->whoseTurn = i;

		
//	printf("length: %i\n", strlen(testMessage));

        // Call whoseTurn() and assert results
	int returnVal = whoseTurn(testGame);
	if(assertTrue(0, 0, returnVal, i))
	{
	    printResults(testMessage, i, 1);
	}
	else
	{
	    printResults(testMessage, i, 0);
	}
    }

    /* Next Batch of test Cases */
    testGame->numPlayers = 3;


}

int main(int argc, char *argv[])
{
    testWhoseTurn();
    return 0;
}
