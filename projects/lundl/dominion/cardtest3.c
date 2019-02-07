/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 3
 * Description: This is a unit test for the card village in dominion.c.
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
	printf("village: FAIL %s\n", testCase);
    }
    else
    {
	printf("village: PASS %s\n", testCase);
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
 * Name: checkForDiscard()
 * Parameters: a gameState struct pointer to a struct holding the result of
 * 	a call to cardEffect() and the value that should have been discarded
 * Description: This helper function checks whether or not the given card is in
 * 	the current hand.
 * Return Value: If the current hand holds this card, return 1. Otherwise, 
 * 	return 0.
 * ***************************************************************************/
int checkForDiscard(struct gameState* test, int card)
{
 
    int i;
    for(i=0; i < test->handCount[0]; i++)
    {
	// if this card is in this hand
	if(test->hand[0][i] == card)
	{
	    return 1;
	}
    }
    return 0;
}


/******************************************************************************
 * Name: testVillage()
 * Parameters: none
 * Description: This unit test checks whether calling cardEffect() with 
 * 	village as the card parameter, the village effect causes 2 actions to
 * 	be gained, the village card to be discarded, and a new card to be drawn
 *      into the hand. Thus, the hand count remains the same before and after
 *      the call and the numActions count increases by 2.
 * Return Value: none
 * ***************************************************************************/

void testVillage()
{
    printf("\n\nUNIT TESTS FOR VILLAGE CARD EFFECT\n");
    // Initialize a gameState struct with values we need for this test
    struct gameState* testGame = newGame();
    testGame->numPlayers = 2;

    // set player 0 in whoseTurn
    testGame->whoseTurn = 0;

    // set card = village
    int card = village;

    /* Test Case 1: 5 cards in hand, village in position 4, numActions starts at 1 */
    printf("village Test Case 1\n"); 
  
    // initialize deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numActions = 1;

    // Set up deck for player 0
    int i;
    // Deck holds card values < smithy
    for(i=curse; i <= remodel ; i++)
    {
        testGame->deck[0][i] = i;
        testGame->deckCount[0] += 1;
    }
 
    // Discard pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->discard[0][i] = i; 
    }


    // Played card pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->playedCards[i] = i;
    }


    // Set up hand for player 0
    int j = 0;
    while(j < 5)
    {
	// get cards from second half of card values
	for(i = baron; i <= treasure_map; i++)
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


    // put village in position 4
    testGame->hand[0][4] = village;
    int handPos = 4;


    // Save current hand count and action count
    int handCountBefore = testGame->handCount[0];
    int actionCountBefore = testGame->numActions;

    // call cardEffect
    int returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase1 = "village effect with hand count of 5, village position of 4, numActions starts at 1";

    int assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore + 1 - 1, returnVal, 0);

    // Verify that village is not in the hand
    int discardResult = checkForDiscard(testGame, village);

    // Assert that after playing village, there are 2 more actions and that village not in hand
    int assertActionDiscard = assertTrue(testGame->numActions, actionCountBefore + 2, discardResult, 0);
  
    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, assertActionDiscard, 1))
    {
	printResults(testCase1, 1);
    }
    else
    {
	printResults(testCase1, 0);
    }

    /* Test Case 2: 5 cards in hand, village in position 0, numActions starts at 1 */
    printf("\nvillage Test Case 2\n"); 
    // reset deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numActions = 1;

    // Set up deck for player 0
    
    // Deck holds card values < smithy
    for(i=curse; i <= remodel ; i++)
    {
        testGame->deck[0][i] = i;
        testGame->deckCount[0] += 1;
    }
 
    // Discard pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->discard[0][i] = i; 
    }


    // Played card pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->playedCards[i] = i;
    }

    // Set up hand for player 0
 
    j = 0;
    while(j < 5)
    {
	// get cards from second half of card values
	for(i = baron; i <= treasure_map; i++)
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


    // put village in position 0
    testGame->hand[0][0] = village;
    handPos = 0;


    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    actionCountBefore = testGame->numActions;

    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase2 = "village effect with hand count of 5, village position of 0, numActions starts at 1";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore + 1 - 1, returnVal, 0);

    // Verify that village is not in the hand
    discardResult = checkForDiscard(testGame, village);

    // Assert that after playing village, there are 2 more actions and that village not in hand
    assertActionDiscard = assertTrue(testGame->numActions, actionCountBefore + 2, discardResult, 0);
  
    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, assertActionDiscard, 1))
    {
	printResults(testCase2, 1);
    }
    else
    {
	printResults(testCase2, 0);
    }


    /* Test Case 3: 5 cards in hand, village in position 0, numActions is 3 */
    printf("\nvillage Test Case 3\n"); 

    // reset deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numActions = 3;

    // Set up deck for player 0
    
    // Deck holds card values < smithy
    for(i=curse; i <= remodel ; i++)
    {
        testGame->deck[0][i] = i;
        testGame->deckCount[0] += 1;
    }
 
    // Discard pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->discard[0][i] = i; 
    }


    // Played card pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->playedCards[i] = i;
    }
    // Set up hand for player 0
    j = 0;
    while(j < 5)
    {
	// get cards from second half of card values
	for(i = baron; i <= treasure_map; i++)
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


    // put village in position 0
    testGame->hand[0][0] = village;
    handPos = 0;


    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    actionCountBefore = testGame->numActions;

    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase3 = "village effect with hand count of 5, village position of 0, and numActions initial value of 3";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore + 1 - 1, returnVal, 0);

    // Verify that village is not in the hand
    discardResult = checkForDiscard(testGame, village);

    // Assert that after playing village, there are 2 more actions and that village not in hand
    assertActionDiscard = assertTrue(testGame->numActions, actionCountBefore + 2, discardResult, 0);
  
    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, assertActionDiscard, 1))
    {
	printResults(testCase3, 1);
    }
    else
    {
	printResults(testCase3, 0);
    }


    /* Test Case 4: 1 card in hand, village in position 0, numActions is 4 */
    printf("\nvillage Test Case 4\n");

    // reset deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numActions = 4;

    // Set up deck for player 0
    
    // Deck holds card values < smithy
    for(i=curse; i <= remodel ; i++)
    {
        testGame->deck[0][i] = i;
        testGame->deckCount[0] += 1;
    }
 
    // Discard pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->discard[0][i] = i; 
    }


    // Played card pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->playedCards[i] = i;
    }
  
    // Set up hand for player 0
   
    // put village in position 0
    testGame->hand[0][0] = village;
    testGame->handCount[0]++;
    handPos = 0;


    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    actionCountBefore = testGame->numActions;

    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase4 = "village effect with hand count of 1, village position of 0, and numActions initial value of 4";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore + 1 - 1, returnVal, 0);

    // Verify that village is not in the hand
    discardResult = checkForDiscard(testGame, village);

    // Assert that after playing village, there are 2 more actions and that village not in hand
    assertActionDiscard = assertTrue(testGame->numActions, actionCountBefore + 2, discardResult, 0);
  
    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, assertActionDiscard, 1))
    {
	printResults(testCase4, 1);
    }
    else
    {
	printResults(testCase4, 0);
    }

    /* Test Case 5: MAX_HAND cards in hand, village in position 217, numActions is 1 */
    printf("\nvillage Test Case 5\n"); 

    // reset deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numActions = 1;

    // Set up deck for player 0
    
    // Deck holds card values < smithy
    for(i=curse; i <= remodel ; i++)
    {
        testGame->deck[0][i] = i;
        testGame->deckCount[0] += 1;
    }
 
    // Discard pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->discard[0][i] = i; 
    }


    // Played card pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->playedCards[i] = i;
    }
    // Set up hand for player 0
    j = 0;
    while(j < MAX_HAND)
    {
	// get cards from second half of card values
	for(i = baron; i <= treasure_map; i++)
        {
	    testGame->hand[0][j] = i;
            testGame->handCount[0]++;   
            j++;
            
            if(j >= MAX_HAND)
            {
		break;
	    }
        }
    }


    // put village in position 217
    testGame->hand[0][217] = village;
    handPos = 217;


    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    actionCountBefore = testGame->numActions;

    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase5 = "village effect with hand count of MAX_HAND, village position of 217, and numActions initial value of 1";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore + 1 - 1, returnVal, 0);

    // Verify that village is not in the hand
    discardResult = checkForDiscard(testGame, village);

    // Assert that after playing village, there are 2 more actions and that village not in hand
    assertActionDiscard = assertTrue(testGame->numActions, actionCountBefore + 2, discardResult, 0);
  
    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, assertActionDiscard, 1))
    {
	printResults(testCase5, 1);
    }
    else
    {
	printResults(testCase5, 0);
    }


    /* Test Case 6: MAX_HAND cards in hand, village in position 217, numActions is 500 */
    printf("\nvillage Test Case 6\n"); 

    // reset deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numActions = 500;

    // Set up deck for player 0
    
    // Deck holds card values < smithy
    for(i=curse; i <= remodel ; i++)
    {
        testGame->deck[0][i] = i;
        testGame->deckCount[0] += 1;
    }
 
    // Discard pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->discard[0][i] = i; 
    }


    // Played card pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->playedCards[i] = i;
    }
    // Set up hand for player 0
    j = 0;
    while(j < MAX_HAND)
    {
	// get cards from second half of card values
	for(i = baron; i <= treasure_map; i++)
        {
	    testGame->hand[0][j] = i;
            testGame->handCount[0]++;   
            j++;
            
            if(j >= MAX_HAND)
            {
		break;
	    }
        }
    }


    // put village in position 217
    testGame->hand[0][217] = village;
    handPos = 217;


    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    actionCountBefore = testGame->numActions;

    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase6 = "village effect with hand count of MAX_HAND, village position of 217, and numActions initial value of 500";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore + 1 - 1, returnVal, 0);

    // Verify that village is not in the hand
    discardResult = checkForDiscard(testGame, village);

    // Assert that after playing village, there are 2 more actions and that village not in hand
    assertActionDiscard = assertTrue(testGame->numActions, actionCountBefore + 2, discardResult, 0);
  
    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, assertActionDiscard, 1))
    {
	printResults(testCase6, 1);
    }
    else
    {
	printResults(testCase6, 0);
    }

    /* Test Case 7: MAX_HAND cards in hand, village in position 217, numActions is 0 */
    printf("\nvillage Test Case 7\n"); 

    // reset deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numActions = 0;

    // Set up deck for player 0
    
    // Deck holds card values < smithy
    for(i=curse; i <= remodel ; i++)
    {
        testGame->deck[0][i] = i;
        testGame->deckCount[0] += 1;
    }
 
    // Discard pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->discard[0][i] = i; 
    }


    // Played card pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->playedCards[i] = i;
    }
    // Set up hand for player 0
    j = 0;
    while(j < MAX_HAND)
    {
	// get cards from second half of card values
	for(i = baron; i <= treasure_map; i++)
        {
	    testGame->hand[0][j] = i;
            testGame->handCount[0]++;   
            j++;
            
            if(j >= MAX_HAND)
            {
		break;
	    }
        }
    }


    // put village in position 217
    testGame->hand[0][217] = village;
    handPos = 217;


    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    actionCountBefore = testGame->numActions;

    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase7 = "village effect with hand count of MAX_HAND, village position of 217, and numActions initial value of 0";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore + 1 - 1, returnVal, 0);

    // Verify that village is not in the hand
    discardResult = checkForDiscard(testGame, village);

    // Assert that after playing village, there are 2 more actions and that village not in hand
    assertActionDiscard = assertTrue(testGame->numActions, actionCountBefore + 2, discardResult, 0);
  
    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, assertActionDiscard, 1))
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
    testVillage();
    return 0;
}
