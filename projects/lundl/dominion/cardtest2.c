/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 3
 * Description: This is a unit test for the card adventurer in dominion.c.
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
	printf("adventurer: FAIL %s\n", testCase);
    }
    else
    {
	printf("adventurer: PASS %s\n", testCase);
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
 * Name: checkForTreasure()
 * Parameters: a gameState struct pointer to a struct holding the result of
 * 	a call to cardEffect(adventurer) and a gameState struct pointer to a struct
 * 	holding the original hand.
 * Description: This helper function compares values of two hand to check
 * 	whether the altered hand holds two additional treasure cards.
 * Return Value: If the altered hand holds two new treasure cards, 
 * 	return 1. Otherwise, return 0.
 * ***************************************************************************/
int checkForTreasure(struct gameState* test, struct gameState* copy)
{
 
    int i;
    int treasure = 0;

    // Count all the treasure cards (original hand has no treasure cards)
    for(i = 0; i < test->handCount[0]; i++)
    {
	if((test->hand[0][i] == gold)||(test->hand[0][i] == silver)||(test->hand[0][i] == copper))
	{
	   treasure++;
	}
    }
   
    if(treasure == 2)
    {
        // The altered hand holds two new treasure cards
        return 1;
    }

    // The altered hand does not hold two new treasure cards
    return 0;
}


/******************************************************************************
 * Name: testAdventurer()
 * Parameters: none
 * Description: This unit test checks whether calling cardEffect() with 
 * 	adventurer as the card parameter causes 2 treasures to be drawn from 
 * 	the deck into the hand and the adventurer card to be discarded.
 * Return Value: none
 * ***************************************************************************/

void testAdventurer()
{
    printf("\n\nUNIT TESTS FOR ADVENTURER CARD EFFECT\n");
    // Initialize a gameState struct with values we need for this test
    struct gameState* testGame = newGame();
    testGame->numPlayers = 2;

    // set player 0 in whoseTurn
    testGame->whoseTurn = 0;

    // set card = adventurer
    int card = adventurer;
    int handPos = 0; 

    // This gameStruct pointer is used for copies
    struct gameState* testCopy = newGame();

    // initialize deck and card counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
 
    // Discard pile has valid cards
    int i;
    for(i = 0; i < 20; i++)
    {
	testGame->discard[0][i] = province; 
        testGame->discardCount[0]++;
    }


    /* Test Case 1: deck holds one of each type of treasure */
    printf("adventurer Test Case 1\n"); 

    // Set up deck for player 0
  
    // Deck holds one of each kind of treasure 
    testGame->deck[0][0] = gold;
    testGame->deck[0][1] = silver; 
    testGame->deck[0][2] = copper;
    testGame->deckCount[0] = 3;

    // Set up hand for player 0
    int j = 0;
    while(j < 5)
    {
	// get cards from second half of card values
	for(i = adventurer; i <= treasure_map; i++)
        {
	    testGame->hand[0][j] = i;
            testGame->handCount[0]++;   
            j++;
            
            if(j >= 5)
            {
		break;
	    }
        }
    }

    // Save a copy of this test struct
    memcpy(testCopy->hand[0], testGame->hand[0], sizeof(testGame->hand[0]));
    testCopy->handCount[0] = testGame->handCount[0];
 
  
    // call cardEffect
    int returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
 
    // Check the restults of this test case
    char* testCase1 = "adventurer effect with one of each kind of treasure in deck";

    // Assert the hand count is one card more than before and return value is 0
    int assertHandCountReturnVal = assertTrue(testGame->handCount[0], testCopy->handCount[0] + 1, returnVal, 0);

    // The new hand should have two treasure cards
    int treasureResult = checkForTreasure(testGame, testCopy);

    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, treasureResult, 1))
    {
	printResults(testCase1, 1);
    }
    else
    {
	printResults(testCase1, 0);
    }

    /* Test Case 2: deck holds one gold and one silver */
    printf("\nadventurer Test Case 2\n"); 

   // reset deck and card counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
 
    // Discard pile has valid cards
    for(i = 0; i < 20; i++)
    {
	testGame->discard[0][i] = province; 
        testGame->discardCount[0]++;
    }



    // Set up deck for player 0
  
    // Deck holds one gold and one silver
    testGame->deck[0][0] = gold;
    testGame->deck[0][1] = silver; 
    testGame->deckCount[0] = 2;


    // Set up hand for player 0
    j = 0;
    while(j < 5)
    {
	// get cards from second half of card values
	for(i = adventurer; i <= treasure_map; i++)
        {
	    testGame->hand[0][j] = i;
            testGame->handCount[0]++;   
            j++;
            
            if(j >= 5)
            {
		break;
	    }
        }
    }

    // Save a copy of this test struct
    memcpy(testCopy->hand[0], testGame->hand[0], sizeof(testGame->hand[0]));
    testCopy->handCount[0] = testGame->handCount[0];

  
    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
  
    // Check the restults of this test case
    char* testCase2 = "adventurer effect with one gold and one silver in deck";

    // Assert the hand count is one card more than before and return value is 0
    assertHandCountReturnVal = assertTrue(testGame->handCount[0], testCopy->handCount[0] + 1, returnVal, 0);


    // The new hand should have two treasure cards
    treasureResult = checkForTreasure(testGame, testCopy);

    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, treasureResult, 1))
    {
	printResults(testCase2, 1);
    }
    else
    {
	printResults(testCase2, 0);
    }

    /* Test Case 3: deck holds one gold and one silver and one curse */
    printf("\nadventurer Test Case 3\n"); 

   // reset deck and card counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
 
    // Discard pile has valid cards
    for(i = 0; i < 20; i++)
    {
	testGame->discard[0][i] = province; 
        testGame->discardCount[0]++;
    }



    // Set up deck for player 0
  
    // Deck holds one gold and one silver and one curse
    testGame->deck[0][0] = gold;
    testGame->deck[0][1] = silver; 
    testGame->deck[0][2] = curse;
    testGame->deckCount[0] = 3;


    // Set up hand for player 0

    j = 0;
    while(j < 5)
    {
	// get cards from second half of card values
	for(i = adventurer; i <= treasure_map; i++)
        {
	    testGame->hand[0][j] = i;
            testGame->handCount[0]++;   
            j++;
            
            if(j >= 5)
            {
		break;
	    }
        }
    }

    // Save a copy of this test struct
    memcpy(testCopy->hand[0], testGame->hand[0], sizeof(testGame->hand[0]));
    testCopy->handCount[0] = testGame->handCount[0];
  
    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
  
    // Check the restults of this test case
    char* testCase3 = "adventurer effect with one gold and one silver and one curse in deck";

    // Assert the hand count is one card more than before and return value is 0
    assertHandCountReturnVal = assertTrue(testGame->handCount[0], testCopy->handCount[0] + 1, returnVal, 0);


    // The new hand should have two treasure cards
    treasureResult = checkForTreasure(testGame, testCopy);

    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, treasureResult, 1))
    {
	printResults(testCase3, 1);
    }
    else
    {
	printResults(testCase3, 0);
    }

    /* Test Case 4: deck holds one gold */
    printf("\nadventurer Test Case 4\n"); 

   // reset deck and card counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
 
    // Discard pile has valid cards
    for(i = 0; i < 20; i++)
    {
	testGame->discard[0][i] = province; 
        testGame->discardCount[0]++;
    }




    // Set up deck for player 0
  
    // Deck holds one gold
    testGame->deck[0][0] = gold;
    testGame->deckCount[0] = 1;


    j = 0;
    while(j < 5)
    {
	// get cards from second half of card values
	for(i = adventurer; i <= treasure_map; i++)
        {
	    testGame->hand[0][j] = i;
            testGame->handCount[0]++;   
            j++;
            
            if(j >= 5)
            {
		break;
	    }
        }
    }

    // Save a copy of this test struct
    memcpy(testCopy->hand[0], testGame->hand[0], sizeof(testGame->hand[0]));
    testCopy->handCount[0] = testGame->handCount[0];
  
    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
  
    // Check the restults of this test case
    char* testCase4 = "adventurer effect with one gold in deck";

    // Assert the hand count is one card more than before and return value is 0
    assertHandCountReturnVal = assertTrue(testGame->handCount[0], testCopy->handCount[0] + 1, returnVal, 0);

    // The new hand should have two treasure cards
    treasureResult = checkForTreasure(testGame, testCopy);

    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, treasureResult, 1))
    {
	printResults(testCase4, 1);
    }
    else
    {
	printResults(testCase4, 0);
    }

    /* Test Case 5: deck holds one estate 
    printf("\nadventurer Test Case 5\n"); 

    // reset deck and card counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
 
    // Discard pile has valid cards
    for(i = 0; i < 20; i++)
    {
	testGame->discard[0][i] = province; 
        testGame->discardCount[0]++;
    }

    // Set up deck for player 0
  
    // Deck holds one estate
    testGame->deck[0][0] = estate;
    testGame->deckCount[0] = 1;

    printf("Printing deck:\n");

    // Set up hand for player 0
    for(i=0; i < testGame->deckCount[0]; i++)
    {
	printf("testGame->deck[0][i]: %i\n", testGame->deck[0][i]);
    }


    j = 0;
    while(j < 5)
    {
	// get cards from second half of card values
	for(i = adventurer; i <= treasure_map; i++)
        {
	    testGame->hand[0][j] = i;
            testGame->handCount[0]++;   
            j++;
            
            if(j >= 5)
            {
		break;
	    }
        }
    }

    // Save a copy of this test struct
    memcpy(testCopy->hand[0], testGame->hand[0], sizeof(testGame->hand[0]));
    testCopy->handCount[0] = testGame->handCount[0];
 
    printf("printing hand before card effect:\n");
    for(i=0; i < testGame->handCount[0]; i++)
    {
	printf("card: %i\n", testGame->hand[0][i]);
    }
  
    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    printf("returnVal: %i\n", returnVal); 
    printf("printing hand after card effect:\n");
    for(i=0; i < testGame->handCount[0]; i++)
    {
	printf("card: %i\n", testGame->hand[0][i]);
    }
  
    // Check the restults of this test case
    char* testCase5 = "adventurer effect with one estate";

    // Assert the hand count is one card more than before and return value is 0
    assertHandCountReturnVal = assertTrue(testGame->handCount[0], testCopy->handCount[0] + 1, returnVal, 0);

    printf("handCount before adventurer: %i, handCount after adventurer: %i, returnVal: %i\n", testCopy->handCount[0], testGame->handCount[0], returnVal);


    // The new hand should have two treasure cards
    treasureResult = checkForTreasure(testGame, testCopy);

    printf("assertHandCountReturnVal: %i, treasureResult: %i\n", assertHandCountReturnVal, treasureResult);

    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, treasureResult, 1))
    {
	printResults(testCase5, 1);
    }
    else
    {
	printResults(testCase5, 0);
    }
*/

    /* Test Case 6: deck holds 20 silver */
    printf("\nadventurer Test Case 6\n"); 

   // reset deck and card counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
 
    // Discard pile has valid cards
    for(i = 0; i < 20; i++)
    {
	testGame->discard[0][i] = province; 
        testGame->discardCount[0]++;
    }




    // Set up deck for player 0
  
    // Deck holds 10 silver
    for(i=0; i < 10; i++)
    {
        testGame->deck[0][i] = silver;
        testGame->deckCount[0]++;
    }
   


    // Set up hand for player 0

    j = 0;
    while(j < 5)
    {
	// get cards from second half of card values
	for(i = adventurer; i <= treasure_map; i++)
        {
	    testGame->hand[0][j] = i;
            testGame->handCount[0]++;   
            j++;
            
            if(j >= 5)
            {
		break;
	    }
        }
    }

    // Save a copy of this test struct
    memcpy(testCopy->hand[0], testGame->hand[0], sizeof(testGame->hand[0]));
    testCopy->handCount[0] = testGame->handCount[0];
 
    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
   
  
    // Check the restults of this test case
    char* testCase6 = "adventurer effect with 10 silver in deck";

    // Assert the hand count is one card more than before and return value is 0
    assertHandCountReturnVal = assertTrue(testGame->handCount[0], testCopy->handCount[0] + 1, returnVal, 0);

    // The new hand should have two treasure cards
    treasureResult = checkForTreasure(testGame, testCopy);

    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, treasureResult, 1))
    {
	printResults(testCase6, 1);
    }
    else
    {
	printResults(testCase6, 0);
    }


    /* Test Case 7: deck holds ten coppers and one silver */
    printf("\nadventurer Test Case 7\n"); 

   // reset deck and card counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
 
    // Discard pile has valid cards
    for(i = 0; i < 20; i++)
    {
	testGame->discard[0][i] = province; 
        testGame->discardCount[0]++;
    }




    // Set up deck for player 0
  
    // Deck holds 10 copper and 1 silver
    for(i=0; i < 10; i++)
    {
        testGame->deck[0][i] = copper;
        testGame->deckCount[0]++;
    }
    testGame->deck[0][10] = silver;
    testGame->deckCount[0]++;


    // Set up hand for player 0

    j = 0;
    while(j < 5)
    {
	// get cards from second half of card values
	for(i = adventurer; i <= treasure_map; i++)
        {
	    testGame->hand[0][j] = i;
            testGame->handCount[0]++;   
            j++;
            
            if(j >= 5)
            {
		break;
	    }
        }
    }

    // Save a copy of this test struct
    memcpy(testCopy->hand[0], testGame->hand[0], sizeof(testGame->hand[0]));
    testCopy->handCount[0] = testGame->handCount[0];
  
    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
  
    // Check the restults of this test case
    char* testCase7 = "adventurer effect with 10 copper and one silver in deck";

    // Assert the hand count is one card more than before and return value is 0
    assertHandCountReturnVal = assertTrue(testGame->handCount[0], testCopy->handCount[0] + 1, returnVal, 0);


    // The new hand should have two treasure cards
    treasureResult = checkForTreasure(testGame, testCopy);

    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, treasureResult, 1))
    {
	printResults(testCase7, 1);
    }
    else
    {
	printResults(testCase7, 0);
    }




}

/******************************************************************************
 * Description: This is the main function. It calls testShuffle().
 * ***************************************************************************/

int main(int argc, char *argv[])
{
    testAdventurer();
    return 0;
}
