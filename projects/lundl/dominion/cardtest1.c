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
	printf("shuffle(): FAIL %s\n", testCase);
    }
    else
    {
	printf("shuffle(): PASS %s\n", testCase);
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
    testGame->deckCount[0] = 0;

    // This gameStruct pointer is used for copies
    struct gameState* testCopy = newGame();
 
    // Set up deck for player 0
    // Set up hand for player 0
    // Set up deck for player 1
    // Set up hand for player 1
    // set this player in whoseTurn
    // set card = smithy
    // set hand position (what is this?)

 
    //set up random number generator
    int randomSeed = time(NULL) % 86400;
    SelectStream(1);
    PutSeed((long)randomSeed);
  

    /* Test Case 1: 3 estate, 7 copper 
     * The original order is 3 estate, 7 copper. We expect shuffle to change
     * this to some other order. */

    printf("\nshuffle() Test Case 1\n");

    // Set up deck for player 0 
    int i;
    for(i = 0; i < 3; i++)
    {
	testGame->deck[0][i] = estate;
        testGame->deckCount[0]++;
    }
    for(i = 3; i < 10; i++)
    {
        testGame->deck[0][i] = copper;
	testGame->deckCount[0]++;
    }

    // Save a copy of this test struct
    memcpy(testCopy->deck[0], testGame->deck[0], sizeof(testGame->deck[0]));
    testCopy->deckCount[0] = testGame->deckCount[0];

    // Pass this gameState struct along with a valid player num to shuffle()
    int returnVal = shuffle(0, testGame);

    // Check the restults of this test case
    char* testCase1 = "shuffling deck of 3 estate and 7 copper";

    // Assert that the two decks differ and that shuffle returnval is 0
    if(assertTrue(checkDeckDifferences(testGame, testCopy), 1, returnVal, 0))
    {
	printResults(testCase1, 1);
    }
    else
    {
	printResults(testCase1, 0);
    }

    /* Test Case 2: an empty deck, deckCount 0 
     * We expect that shuffle() will return -1. */

    printf("\nshuffle() Test Case 2\n");

    // Edge Case: deck is empty, pass if returns -1; fail if returns 0
 
    testGame->deckCount[0] = 0;

    returnVal = shuffle(0, testGame);

    // Check the restults of this test case
    char* testCase2 = "shuffling empty deck";

    // Assert that the returnval is -1
    if(assertTrue(0, 0, returnVal, -1))
    {
	printResults(testCase2, 1);
    }
    else
    {
	printResults(testCase2, 0);
    }

    /* Test Case 3: 20 of the same card
     * We expect the shuffled order and the original order to be the same. */

    printf("\nshuffle() Test Case 3\n");
    char* testCase3 = "shuffling deck of 20 gardens";

    // Deck holds all same values
    for(i=0; i < 20; i++)
    {
	testGame->deck[0][i] = gardens;
    }
    testGame->deckCount[0] = 20;

    // Save a copy of this test struct
    memcpy(testCopy->deck[0], testGame->deck[0], sizeof(testGame->deck[0]));
    testCopy->deckCount[0] = testGame->deckCount[0];


    // Pass this gameState struct along with a valid player num to shuffle()
    returnVal = shuffle(0, testGame);

    // Check the results of this test case

    // Assert that the two decks are the same and that shuffle returnval is 0
    if(assertTrue(checkDeckDifferences(testGame, testCopy), 0, returnVal, 0))
    {
	printResults(testCase3, 1);
    }
    else
    {
	printResults(testCase3, 0);
    }

   /* Test Case 4: a deck comprised of one of each card
    * The original order is the same as the enum list (curse, estate, etc.)
    * We expect the shuffled order to be in any other order. */

    printf("\nshuffle() Test Case 4\n");
    char* testCase4 = "shuffling deck of one of each card";

    // reset deck count
    testGame->deckCount[0]=0;

    // Deck holds all different values
    for(i=curse; i <= treasure_map ; i++)
    {
	testGame->deck[0][i] = i;
	testGame->deckCount[0] += 1;
    }
  

    // Save a copy of this test struct
    memcpy(testCopy->deck[0], testGame->deck[0], sizeof(testGame->deck[0]));
    testCopy->deckCount[0] = testGame->deckCount[0];
 

    // Pass this gameState struct along with a valid player num to shuffle()
    returnVal = shuffle(0, testGame);

    // Check the results of this test case

    // Assert that the two decks are different and that shuffle returnval is 0
    if(assertTrue(checkDeckDifferences(testGame, testCopy), 1, returnVal, 0))
    {
	printResults(testCase4, 1);
    }
    else
    {
	printResults(testCase4, 0);
    }


   /* Test Case 5: a max size deck holding at least one of each card 
    * The original order is the repeated pattern of curse ... treasure_map
    * until 500 cards are stored in the deck. We expect the shuffled order
    * to be any other order.*/
  
    printf("\nshuffle() Test Case 5\n");
    char* testCase5 = "shuffling max size deck of assorted cards";

    // reset deck count
    testGame->deckCount[0]=0;

    // Deck holds 500 cards of assorted values
    i = 0;
    while(i < MAX_DECK)
    {
	int j;
        for(j = curse; j <= treasure_map; j++)
	{
	    if(i < MAX_DECK)
	    {
		testGame->deck[0][i] = j;
		testGame->deckCount[0] += 1;
	        i++;
            }
            else
	    {
		break;
	    }
	}
    }
  

    // Save a copy of this test struct
    memcpy(testCopy->deck[0], testGame->deck[0], sizeof(testGame->deck[0]));
    testCopy->deckCount[0] = testGame->deckCount[0];
 

    // Pass this gameState struct along with a valid player num to shuffle()
    returnVal = shuffle(0, testGame);

    // Check the restults of this test case

    // Assert that the two decks are different and that shuffle returnval is 0
    if(assertTrue(checkDeckDifferences(testGame, testCopy), 1, returnVal, 0))
    {
	printResults(testCase5, 1);
    }
    else
    {
	printResults(testCase5, 0);
    }
    
    /* Test Case 6: a deck of one card
     * The original order is baron. We expect the shuffled order to also be
     * a single baron. */
    printf("\nshuffle() Test Case 6\n");

    // Edge Case: deck holds 1 card, pass if returns 0; fail if returns -1
    testGame->deck[0][0] = baron; 
    testGame->deckCount[0] = 1;

    // Save a copy of this test struct
    memcpy(testCopy->deck[0], testGame->deck[0], sizeof(testGame->deck[0]));
    testCopy->deckCount[0] = testGame->deckCount[0];
 
    returnVal = shuffle(0, testGame);

    // Check the restults of this test case
    char* testCase6 = "shuffling deck of 1 card";

    // Assert that the decks match and returnval is 0
    if(assertTrue(checkDeckDifferences(testGame, testCopy), 0, returnVal, 0))
    {
	printResults(testCase6, 1);
    }
    else
    {
	printResults(testCase6, 0);
    }



}

/******************************************************************************
 * Description: This is the main function. It calls testShuffle().
 * ***************************************************************************/

int main(int argc, char *argv[])
{
    testShuffle();
    return 0;
}
