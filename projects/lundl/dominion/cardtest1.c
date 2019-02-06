/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 3
 * Description: This is a unit test for the card smithy in dominion.c.
 * ***************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h" 
#include "rngs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/******************************************************************************
 * Name: printResults
 * Parameters: a char* holding a string to be printed, an int holding a test
 * 	result.
 * Description: This helper function prints to the console a message indicating
 * 	PASS or FAIL for a given test case. If the assertResult is 0, the test
 * 	failed. Otherwise, it passed.
 * Return Value: none
 * ***************************************************************************/
void printResults(char* testCase, int assertResult)
{
    if(assertResult == 0)
    {
	printf("smithy: FAIL %s\n", testCase);
    }
    else
    {
	printf("smithy: PASS %s\n", testCase);
    }
}


/******************************************************************************
 * Name: assertTrue()
 * Parameters: four ints: one holding the actual value of the test result, 
 * 	one holding the expected value of the test result, one holding the 
 * 	actual return value of a call to the tested function, and one holding
 * 	the expected return value of a call to the tested function.
 * Description: This helper function compares actual values to expected values.
 * 	If the actual values match the expected values, return 1. Otherwise, 
 * 	return 0.
 * Return Value: Returns 1 if the input values are "true." Returns 0 otherwise.
 * ***************************************************************************/
int assertTrue(int actualVal, int expectedVal, int actualReturn, int expectedReturn)
{
    if((actualVal == expectedVal) && (actualReturn == expectedReturn))
    {
	return 1;
    }
    return 0;
}

/******************************************************************************
 * Name: testSmithy()
 * Parameters: none
 * Description: This unit test proves that after calling cardEffect() with 
 * 	smithy as the card parameter, the smithy effect causes 3 cards to be
 * 	drawn and one card to be discarded.
 * Return Value: none
 * ***************************************************************************/

void testSmithy()
{
    // Initialize a gameState struct with values we need for this test
    struct gameState* testGame = newGame();
    testGame->numPlayers = 2;

    // set player 0 in whoseTurn
    testGame->whoseTurn = 0;

    // initialize deck and hand counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;

    // This gameStruct pointer is used for copies
   // struct gameState* testCopy = newGame();
 
    // Set up deck for player 0

    // Deck holds all different values except smithy
    int i;
    for(i=curse; i <= treasure_map ; i++)
    {
	if (i != smithy)
	{
	    testGame->deck[0][i] = i;
	    testGame->deckCount[0] += 1;
	}
    }


    /* Test Case 1: smithy in position 4 */
    // Set up hand for player 0
    printf("smithy Test Case 1\n"); 
    for(i = 0; i < 4; i++)
    {
	// draw card from deck
	drawCard(testGame->whoseTurn, testGame);	
    }

    // put smithy in position 4
    testGame->hand[0][4] = smithy;
    testGame->handCount[0]++;
    int handPos = 4;

    // Set up deck for player 1
    // Set up hand for player 1
    // set card = smithy
    int card = smithy;

  /*  printf("current hand:\n");
    for(i=0; i < testGame->handCount[0]; i++)
    {
	printf("Hand at position %i is %i\n", i, testGame->hand[0][i]);
    }
   */
    // Save current hand count
    int handCountBefore = testGame->handCount[0];
    //printf("handCount: %i\n", handCount);

    // call cardEffect
    int returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that handCount is 3 - 1 more than current handCount and that resultVal is 0
    // Check the restults of this test case
    char* testCase1 = "smithy effect with hand count of 5 and smithy position of 4";

    // Assert that the handcount is 3 - 1 more than current hand count and that cardEffect returnval is 0
    if(assertTrue(testGame->handCount[0], handCountBefore + 3 - 1, returnVal, 0))
    {
	printResults(testCase1, 1);
    }
    else
    {
	printf("actual handcount: %i, expected handcount: %i\n", testGame->handCount[0], handCountBefore + 3 - 1);
	printResults(testCase1, 0);
    }


    // set hand position for smithy so that it can be discarded successfully
    // have other cards in hand along with smithy
    // test smithy in different hand positions
    // check number of cards before and after playing smithy
    // test playing one smithy while also having other smithy cards in the hand

 
    //set up random number generator
 //   int randomSeed = time(NULL) % 86400;
 //   SelectStream(1);
 //   PutSeed((long)randomSeed);
  

      // Save a copy of this test struct
  //  memcpy(testCopy->deck[0], testGame->deck[0], sizeof(testGame->deck[0]));
 //   testCopy->deckCount[0] = testGame->deckCount[0];

    // Pass this gameState struct along with a valid player num to shuffle()
 //   int returnVal = shuffle(0, testGame);

    // Check the restults of this test case
//    char* testCase1 = "shuffling deck of 3 estate and 7 copper";

    // Assert that the two decks differ and that shuffle returnval is 0
//    if(assertTrue(checkDeckDifferences(testGame, testCopy), 1, returnVal, 0))
//    {
//	printResults(testCase1, 1);
//    }
//    else
//    {
//	printResults(testCase1, 0);
//    }

}

/******************************************************************************
 * Description: This is the main function. It calls testShuffle().
 * ***************************************************************************/

int main(int argc, char *argv[])
{
    testSmithy();
    return 0;
}
