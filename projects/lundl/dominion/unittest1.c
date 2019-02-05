/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 3
 * Description: This is a unit test the suffle() function in dominion.c.
 * ***************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h" 
#include "rngs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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


int assertTrue(int actualVal, int expectedVal, int actualReturn, int expectedReturn)
{
    if((actualVal == expectedVal) && (actualReturn == expectedReturn))
    {
	return 1;
    }
    return 0;
}


int checkDeckDifferences(struct gameState* test, struct gameState* copy)
{
    int i;
    int numDiff = 0;
    // compare the struct we passed to the struct we copied earlier
    for (i = 0; i < test->deckCount[0]; i++)
    {
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

void testShuffle()
{
    // Initialize a gameState struct with values we need for this test
    struct gameState* testGame = newGame();
    testGame->numPlayers = 2;
    testGame->deckCount[0] = 0;

    // This gameStruct pointer is used for copies
    struct gameState* testCopy = newGame();
  
    //set up random number generator
    int randomSeed = time(NULL) % 86400;
    SelectStream(1);
    PutSeed((long)randomSeed);
  

    /* Test Case 1: 3 estate, 7 copper */
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

    /* Test Case 2 */
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

    /* Test Case 3 */
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

    // Check the restults of this test case

    // Assert that the two decks are the same and that shuffle returnval is 0
    if(assertTrue(checkDeckDifferences(testGame, testCopy), 0, returnVal, 0))
    {
	printResults(testCase3, 1);
    }
    else
    {
	printResults(testCase3, 0);
    }

   /* Test Case 4 */
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

    // Check the restults of this test case

    // Assert that the two decks are different and that shuffle returnval is 0
    if(assertTrue(checkDeckDifferences(testGame, testCopy), 1, returnVal, 0))
    {
	printResults(testCase4, 1);
    }
    else
    {
	printResults(testCase4, 0);
    }


   /* Test Case 5 */
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
    
    /* Test Case 6 */
    printf("\nshuffle() Test Case 6\n");

    // Edge Case: deck holds 1 card, pass if returns 0; fail if returns -1
 
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

int main(int argc, char *argv[])
{
    testShuffle();
    return 0;
}
