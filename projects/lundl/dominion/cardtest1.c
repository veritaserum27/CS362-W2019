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
 * Name: checkHandDifferences()
 * Parameters: a gameState struct pointer to a struct holding the result of
 * 	a call to cardEffect(smithy) and a gameState struct pointer to a struct
 * 	holding the original hand.
 * Description: This helper function compares values of two hand to check
 * 	whether the altered hand has the expected changes (smithy replaced by
 * 	a new card, two new cards inserted at the next available indices).
 * Return Value: If the altered hand holds new values at the expected indices, 
 * 	return 1. Otherwise, return 0.
 * ***************************************************************************/
int checkHandDifferences(struct gameState* test, struct gameState* copy, int handPos, int handCountBefore, int handCount, int expectedDiff)
{
 
    int i;
    int numDiff = 0;

    // handPos must now hold a non-smithy value
    if (test->hand[0][handPos] != smithy)
    {
        // if smithy was originally at handPos
        if (copy->hand[0][handPos] == smithy)
        {
	     //printf("test->hand[0][handPos]: %i, copy->hand[0][handPos]: %i, handPos: %i\n", test->hand[0][handPos], copy->hand[0][handPos], handPos);

            // increment difference count 
	    numDiff += 1;
        }
        // There must be the expected number of differences
        // compare the struct we passed to the struct we copied earlier
        for (i = handCountBefore; i < handCount; i++)
        {
            //printf("test->hand[0][i]: %i, copy->hand[0][i]: %i, i: %i\n", test->hand[0][i], copy->hand[0][i], i);
	    // If the cards in this position do not match
	    if(test->hand[0][i] != copy->hand[0][i])
	    {
               // Increment count of differences
	       numDiff += 1;
            }  
        }
    }
    

    //printf("numDiff: %i\n", numDiff);
    if(numDiff == expectedDiff)
    {
        // These two hands are different at 3 indices; difference == true
        return 1;
    }

    // These two hands are not sufficiently different; difference == false
    return 0;
}


/******************************************************************************
 * Name: testSmithy()
 * Parameters: none
 * Description: This unit test checks whether calling cardEffect() with 
 * 	smithy as the card parameter, the smithy effect causes 3 cards to be
 * 	drawn into the player's hand and the smithy card to be discarded.
 * Return Value: none
 * ***************************************************************************/

void testSmithy()
{
    printf("\n\nUNIT TESTS FOR SMITHY CARD EFFECT\n");
    
    // Initialize a gameState struct with values we need for this test
    struct gameState* testGame = newGame();
    testGame->numPlayers = 2;

    // set player 0 in whoseTurn
    testGame->whoseTurn = 0;

    // initialize deck and card counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 

    // This gameStruct pointer is used for copies
    struct gameState* testCopy = newGame();
 
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

    /* Test Case 1: 5 cards in hand, smithy in position 4 */
    // Set up hand for player 0
    printf("smithy Test Case 1\n"); 
    int j = 0;
    while(j < 5)
    {
	// get cards from second half of card values
	for(i = village; i <= treasure_map; i++)
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


    // put smithy in position 4
    testGame->hand[0][4] = smithy;
    testGame->handCount[0]++;
    int handPos = 4;

    // set card = smithy
    int card = smithy;

    // Save current hand count
    int handCountBefore = testGame->handCount[0];

    // Save a copy of this test struct
    memcpy(testCopy->hand[0], testGame->hand[0], sizeof(testGame->hand[0]));
    testCopy->handCount[0] = testGame->handCount[0];

    // call cardEffect
    int returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that handCount is 3 - 1 more than current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase1 = "smithy effect with hand count of 5 and smithy position of 4";

    int assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore + 3 - 1, returnVal, 0);

    // Get the result of comparing the hands
    int comparisonResult = checkHandDifferences(testGame, testCopy, handPos, handCountBefore, testGame->handCount[0], 3);

    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, comparisonResult, 1))
    {
	printResults(testCase1, 1);
    }
    else
    {
	printResults(testCase1, 0);
    }


    /* Test Case 2: smithy as only card in hand */
    printf("\nsmithy Test Case 2\n"); 
    
    // reset deck and hand counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 


    // Reset deck for player 0

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
    // put smithy in position 0
    testGame->hand[0][0] = smithy;
    testGame->handCount[0]++;
    handPos = 0;

    // Save current hand count
    handCountBefore = testGame->handCount[0];

    // Save a copy of this test struct
    memcpy(testCopy->hand[0], testGame->hand[0], sizeof(testGame->hand[0]));
    testCopy->handCount[0] = testGame->handCount[0];

    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that handCount is 3 - 1 more than current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase2 = "smithy effect with hand count of 1 and smithy position of 0";

 
    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore + 3 - 1, returnVal, 0);

    // Get the result of comparing the hands
    comparisonResult = checkHandDifferences(testGame, testCopy, handPos, handCountBefore, testGame->handCount[0], 3);

    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, comparisonResult, 1))
    {
	printResults(testCase2, 1);
    }
    else
    {
	printResults(testCase2, 0);
    }


    /* Test Case 3: smithy as card parameter, but no cards in hand (invalid ints stored in hand), smithy at position 0 */
    printf("\nsmithy Test Case 3\n"); 
    
    // reset deck and hand counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 


    // Reset deck for player 0

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
        testGame->discardCount[0]++;
    }


    // Played card pile has valid cards
    for(i = curse; i < remodel; i++)
    {
	testGame->playedCards[i] = i;
    }

    // Set up hand for player 0
    // all invalid cards
    for(i = 0; i < 5; i++)
    {
	testGame->hand[0][i] = -1;
    }

    // set smithy position as 0
    handPos = 0;

    // Save current hand count
    handCountBefore = testGame->handCount[0];
   
    // Save a copy of this test struct
    memcpy(testCopy->hand[0], testGame->hand[0], sizeof(testGame->hand[0]));
    testCopy->handCount[0] = testGame->handCount[0];

    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that handCount is 3 - 1 more than current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase3 = "smithy effect with hand count of 0 and smithy position of 0";
 
    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore + 3 - 1, returnVal, 0);

    // Get the result of comparing the hands
    comparisonResult = checkHandDifferences(testGame, testCopy, handPos, handCountBefore, testGame->handCount[0], 2);

    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, comparisonResult, 1))
    {
	printResults(testCase3, 1);
    }
    else
    {
	printResults(testCase3, 0);
    }


    /* Test Case 4: smithy as card parameter, but no cards in hand, invalid index for hand pos */
    printf("\nsmithy Test Case 4\n"); 
    
    // reset deck and hand counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 


    // Reset deck for player 0

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
    // all invalid cards
    for(i = 0; i < 5; i++)
    {
	testGame->hand[0][i] = -1;
    }

    // put smithy in position -1
    handPos = -1;

    // Save current hand count
    handCountBefore = testGame->handCount[0];

    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that handCount is 3 - 1 more than current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase4 = "smithy effect with hand count of 0 and smithy position of -1";

 
    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore + 3 - 1, returnVal, 0);

    // Get the result of comparing the hands
    comparisonResult = checkHandDifferences(testGame, testCopy, handPos, handCountBefore, testGame->handCount[0], 2);

    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, comparisonResult, 1))
    {
	printResults(testCase4, 1);
    }
    else
    {
	printResults(testCase4, 0);
    }

    /* Test Case 5: smithy as card parameter, max number of cards in hand, smithy in position MAX_HAND-1 */
    printf("\nsmithy Test Case 5\n"); 
    
    // reset deck and hand counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 


    // Reset deck for player 0

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
    while(j < MAX_HAND - 1)
    {
	// get cards from second half of card values
	for(i = village; i <= treasure_map; i++)
        {
	    testGame->hand[0][j] = i;
            testGame->handCount[0]++;   
	    j++;
            
            if(j >= MAX_HAND - 1)
            {
		break;
	    }
        }
    }

   // put smithy in position MAX_HAND-1
    testGame->hand[0][MAX_HAND - 1] = smithy;
   
    testGame->handCount[0]++;
    handPos = MAX_HAND-1;

    // Save current hand count
    handCountBefore = testGame->handCount[0];
    
    // Save a copy of this test struct
    memcpy(testCopy->hand[0], testGame->hand[0], sizeof(testGame->hand[0]));
    testCopy->handCount[0] = testGame->handCount[0];


    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that handCount is MAX_HAND and that returnVal is 0
    // Check the restults of this test case
    char* testCase5 = "smithy effect with hand count of MAX_HAND and smithy position of MAX_HAND-1";
 
    assertHandCountReturnVal = assertTrue(testGame->handCount[0], MAX_HAND, returnVal, 0);

    // Get the result of comparing the hands--there should be only 1 card different (the replacement of smithy)
    comparisonResult = checkHandDifferences(testGame, testCopy, handPos, handCountBefore, testGame->handCount[0], 1);

    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, comparisonResult, 1))
    {
	printResults(testCase5, 1);
    }
    else
    {
	printResults(testCase5, 0);
    }


    /* Test Case 6: 12 cards in hand, smithy in position 5 */
     
    // reset deck and hand counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 


    // Reset deck for player 0

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
    printf("\nsmithy Test Case 6\n"); 
    j = 0;
    while(j < 12)
    {
	// get cards from second half of card values
	for(i = village; i <= treasure_map; i++)
        {
	    testGame->hand[0][j] = i;
            testGame->handCount[0]++;
            j++;
            
            if(j >= 12)
            {
		break;
	    }
        }
    }
    j = 12;
    while(j < MAX_HAND)
    {
	// set the rest of the hand to garbage values
	testGame->hand[0][j] = -1;
    	j++;
            
        if(j >= MAX_HAND)
        {
	  break;
	}
    }


    // put smithy in position 5
    testGame->hand[0][5] = smithy;
    handPos = 5;

    // Save current hand count
    handCountBefore = testGame->handCount[0];

    // Save a copy of this test struct
    memcpy(testCopy->hand[0], testGame->hand[0], sizeof(testGame->hand[0]));
    testCopy->handCount[0] = testGame->handCount[0];

    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that handCount is 3 - 1 more than current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase6 = "smithy effect with hand count of 12 and smithy position of 5";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore + 3 - 1, returnVal, 0);

    // Get the result of comparing the hands
    comparisonResult = checkHandDifferences(testGame, testCopy, handPos, handCountBefore, testGame->handCount[0], 3);

    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, comparisonResult, 1))
    {
	printResults(testCase6, 1);
    }
    else
    {
	printResults(testCase6, 0);
    }

    /* Test Case 7: 7 cards in hand, smithy in position 0 */
     
    // reset deck and hand counts
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 


    // Reset deck for player 0

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
    printf("\nsmithy Test Case 7\n"); 
    j = 0;
    while(j < 7)
    {
	// get cards from second half of card values
	for(i = village; i <= treasure_map; i++)
        {
	    testGame->hand[0][j] = i;
            testGame->handCount[0]++;   
	    j++;
            
            if(j >= 7)
            {
		break;
	    }
        }
    }
    j = 7;
    while(j < MAX_HAND)
    {
	// set the rest of the hand to garbage values
	testGame->hand[0][j] = -1;
    	j++;
            
        if(j >= MAX_HAND)
        {
	  break;
	}
    }


    // put smithy in position 0
    testGame->hand[0][0] = smithy;
    handPos = 0;

    // Save current hand count
    handCountBefore = testGame->handCount[0];

    // Save a copy of this test struct
    memcpy(testCopy->hand[0], testGame->hand[0], sizeof(testGame->hand[0]));
    testCopy->handCount[0] = testGame->handCount[0];

    // call cardEffect
    returnVal = cardEffect(card, 0, 0, 0, testGame, handPos, 0);
    
    // Assert that handCount is 3 - 1 more than current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase7 = "smithy effect with hand count of 7 and smithy position of 0";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore + 3 - 1, returnVal, 0);


    // Get the result of comparing the hands
    comparisonResult = checkHandDifferences(testGame, testCopy, handPos, handCountBefore, testGame->handCount[0], 3);

//    printf("assertHandCountReturnVal: %i, comaprisonResult: %i\n", assertHandCountReturnVal, comparisonResult);
    
    // Assert that both halves of the test pass
    if(assertTrue(assertHandCountReturnVal, 1, comparisonResult, 1))
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
    testSmithy();
    return 0;
}
