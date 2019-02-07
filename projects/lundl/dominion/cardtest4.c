/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 3
 * Description: This is a unit test for the card salvager in dominion.c.
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
 * Name: checkHand()
 * Parameters: a gameState struct pointer to a struct holding the result of
 * 	a call to cardEffect() and the value that should have been discarded
 * Description: This helper function checks whether or not the given card is in
 * 	the current hand.
 * Return Value: If the current hand holds this card, return 1. Otherwise, 
 * 	return 0.
 * ***************************************************************************/
int checkHand(struct gameState* test, int card)
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
 * Name: checkPlayedPile()
 * Parameters: a gameState struct pointer to a struct holding the result of
 * 	a call to cardEffect() and a card value
 * Description: This helper function checks whether or not the given card is in
 * 	the played pile.
 * Return Value: If the played pile holds this card, return 1. Otherwise, 
 * 	return 0.
 * ***************************************************************************/
int checkPlayedPile(struct gameState* test, int card)
{
 
    int i;
    for(i=0; i < test->playedCardCount; i++)
    {
  	// if this card is in the played pile
	if(test->playedCards[i] == card)
	{
	    return 1;
	}
    }
    return 0;
}


/******************************************************************************
 * Name: testSalvager()
 * Parameters: none
 * Description: This unit test checks whether calling cardEffect() with 
 * 	salvager as the card parameter causes the number of buys to increase by 
 *	1, a card chosen to be trashed (if any) increases the number of coins
 *	by the cost of the trashed card, the trashed card is not in the disacrd
 *	pile afterwared, and the salvager card is discarded from the hand.
 * Return Value: none
 * ***************************************************************************/

void testSalvager()
{
    printf("\n\nUNIT TESTS FOR SALVAGER CARD EFFECT\n");
    // Initialize a gameState struct with values we need for this test
    struct gameState* testGame = newGame();
    testGame->numPlayers = 2;

    // set player 0 in whoseTurn
    testGame->whoseTurn = 0;

    // set card = salvager
    int card = salvager;
    int handPos = 0;

    /* Test Case 1: 7 cards in hand, salvager in position 0, numBuys starts at 1, coins starts at 0, choice1 is province */
    printf("salvager Test Case 1\n"); 
  
    // initialize deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numBuys = 1;
    testGame->coins = 0;

    // Set up deck for player 0
    int i;
    int j = 0;
    // Deck holds card values curse and duchy, no salvager
    for(i=curse; i <= duchy; i++)
    {
    	if(i != estate)
	{
            testGame->deck[0][j] = i;
            testGame->deckCount[0] += 1;
            j++;
        }
    }
 
    // Played pile has valid cards that aren't in hand or deck, no salvager
    j = 0;
    for(i = sea_hag; i <= treasure_map; i++)
    {
	testGame->playedCards[j] = i;
	testGame->playedCardCount++; 
        j++;
    }


    // Set up hand for player 0
    // Cards in hand include salvager and cards not in deck or discard
    handPos = 0;
    testGame->hand[0][0] = salvager;
    testGame->hand[0][1] = copper; // cost 0
    testGame->hand[0][2] = province; // cost 8
    testGame->hand[0][3] = council_room; // cost 5
    testGame->hand[0][4] = gardens; // cost 4
    testGame->hand[0][5] = estate; // cost 2
    testGame->hand[0][6] = village; // cost 3
    testGame->handCount[0] = 7;
    int choicePos = 2; // province
    int trashCard = province;
    int choiceCost = 8;

    // Save current hand count and action count
    int handCountBefore = testGame->handCount[0];
    int buyCountBefore = testGame->numBuys;
    int coinCountBefore = testGame->coins;


    // call cardEffect
    int returnVal = cardEffect(card, choicePos, 0, 0, testGame, handPos, 0);
   
     
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase1 = "salvager effect with hand count of 7, salvager position of 0, buy count 1, coin count 0, province choice";

    int assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore - 2, returnVal, 0);
    //printf("returnVal: %i, handCount: %i, assertHandCountReturnVal: %i\n", returnVal, testGame->handCount[0], assertHandCountReturnVal);

    // Verify that salvager is in played pile, should be 1
    int playedPileResult = checkPlayedPile(testGame, salvager);
    
    // Verify that salvager is not in the hand, should be 0
    int handResult = checkHand(testGame, salvager);

    // Assert that salvager is found in discard pile and not found in hand
    int assertSalvagerLocation = assertTrue(playedPileResult, 1, handResult, 0);

    // printf("salvager played pile: %i, salvager hand: %i, assertSalvagerLocation: %i\n", playedPileResult, handResult, assertSalvagerLocation);

    // Verify that the choice ard is not in the played pile, should be 0
    int playedPileChoiceResult = checkPlayedPile(testGame, trashCard);

    // Verify that the choice card is not in the hand, should be 0
    int handChoiceResult = checkHand(testGame, trashCard);

    // Assert that trash card is not in discard pile or hand
    int assertTrashCard = assertTrue(playedPileChoiceResult, 0, handChoiceResult, 0);

   // printf("trash discard pile: %i, trash hand: %i, assertTrashCard: %i\n", playedPileChoiceResult, handChoiceResult, assertTrashCard);

    // Assert that after playing salvager, there is one more buy and choiceCost more coins
    int assertBuyCoin = assertTrue(testGame->numBuys, buyCountBefore + 1, testGame->coins, coinCountBefore + choiceCost);

   // printf("buycount: %i, coins: %i, assertBuyCoin: %i\n", testGame->numBuys, testGame->coins, assertBuyCoin);
 
    // Assert that all parts of the test pass
    int assertPart1 = assertTrue(assertHandCountReturnVal, 1, assertSalvagerLocation, 1);
    int assertPart2 = assertTrue(assertTrashCard, 1, assertBuyCoin, 1);
 
    // Assert that both halves of the test pass
    if(assertTrue(assertPart1, 1, assertPart2, 1))
    {
	printResults(testCase1, 1);
    }
    else
    {
	printResults(testCase1, 0);
    }

    /* Test Case 2: 7 cards in hand, salvager in position 0, numBuys starts at 1, coins starts at 0, choice1 is copper */
    printf("\nsalvager Test Case 2\n"); 
  
    // initialize deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numBuys = 1;
    testGame->coins = 0;

    // Set up deck for player 0
    
    j = 0;
    // Deck holds card values curse and duchy, no salvager
    for(i=curse; i <= duchy; i++)
    {
    	if(i != estate)
	{
            testGame->deck[0][j] = i;
            testGame->deckCount[0] += 1;
            j++;
        }
    }
 
    // Played pile has valid cards that aren't in hand or deck, no salvager
    j = 0;
    for(i = sea_hag; i <= treasure_map; i++)
    {
	testGame->playedCards[j] = i;
	testGame->playedCardCount++; 
        j++;
    }


    // Set up hand for player 0
    // Cards in hand include salvager and cards not in deck or discard
    handPos = 0;
    testGame->hand[0][0] = salvager;
    testGame->hand[0][1] = copper; // cost 0
    testGame->hand[0][2] = province; // cost 8
    testGame->hand[0][3] = council_room; // cost 5
    testGame->hand[0][4] = gardens; // cost 4
    testGame->hand[0][5] = estate; // cost 2
    testGame->hand[0][6] = village; // cost 3
    testGame->handCount[0] = 7;
    choicePos = 1; // copper
    trashCard = copper;
    choiceCost = 0;

    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    buyCountBefore = testGame->numBuys;
    coinCountBefore = testGame->coins;


    // call cardEffect
    returnVal = cardEffect(card, choicePos, 0, 0, testGame, handPos, 0);
   
     
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase2 = "salvager effect with hand count of 7, salvager position of 0, buy count 1, coin count 0, copper choice";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore - 2, returnVal, 0);

    // Verify that salvager is in played pile, should be 1
    playedPileResult = checkPlayedPile(testGame, salvager);
    
    // Verify that salvager is not in the hand, should be 0
    handResult = checkHand(testGame, salvager);

    // Assert that salvager is found in discard pile and not found in hand
    assertSalvagerLocation = assertTrue(playedPileResult, 1, handResult, 0);

    // Verify that the choice ard is not in the played pile, should be 0
    playedPileChoiceResult = checkPlayedPile(testGame, trashCard);

    // Verify that the choice card is not in the hand, should be 0
    handChoiceResult = checkHand(testGame, trashCard);

    // Assert that trash card is not in discard pile or hand
    assertTrashCard = assertTrue(playedPileChoiceResult, 0, handChoiceResult, 0);

    // Assert that after playing salvager, there is one more buy and choiceCost more coins
    assertBuyCoin = assertTrue(testGame->numBuys, buyCountBefore + 1, testGame->coins, coinCountBefore + choiceCost);

    // Assert that all parts of the test pass
    assertPart1 = assertTrue(assertHandCountReturnVal, 1, assertSalvagerLocation, 1);
    assertPart2 = assertTrue(assertTrashCard, 1, assertBuyCoin, 1);
 
    // Assert that both halves of the test pass
    if(assertTrue(assertPart1, 1, assertPart2, 1))
    {
	printResults(testCase2, 1);
    }
    else
    {
	printResults(testCase2, 0);
    }

    /* Test Case 3: 7 cards in hand, salvager in position 0, numBuys starts at 1, coins starts at 0, choice1 is council room */
    printf("\nsalvager Test Case 3\n"); 
  
    // initialize deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numBuys = 1;
    testGame->coins = 0;

    // Set up deck for player 0
    
    j = 0;
    // Deck holds card values curse and duchy, no salvager
    for(i=curse; i <= duchy; i++)
    {
    	if(i != estate)
	{
            testGame->deck[0][j] = i;
            testGame->deckCount[0] += 1;
            j++;
        }
    }
 
    // Played pile has valid cards that aren't in hand or deck, no salvager
    j = 0;
    for(i = sea_hag; i <= treasure_map; i++)
    {
	testGame->playedCards[j] = i;
	testGame->playedCardCount++; 
        j++;
    }


    // Set up hand for player 0
    // Cards in hand include salvager and cards not in deck or discard
    handPos = 0;
    testGame->hand[0][0] = salvager;
    testGame->hand[0][1] = copper; // cost 0
    testGame->hand[0][2] = province; // cost 8
    testGame->hand[0][3] = council_room; // cost 5
    testGame->hand[0][4] = gardens; // cost 4
    testGame->hand[0][5] = estate; // cost 2
    testGame->hand[0][6] = village; // cost 3
    testGame->handCount[0] = 7;
    choicePos = 3; // council_room
    trashCard = council_room;
    choiceCost = 5;

    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    buyCountBefore = testGame->numBuys;
    coinCountBefore = testGame->coins;


    // call cardEffect
    returnVal = cardEffect(card, choicePos, 0, 0, testGame, handPos, 0);
   
     
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase3 = "salvager effect with hand count of 7, salvager position of 0, buy count 1, coin count 0, council room choice";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore - 2, returnVal, 0);
    // printf("returnVal: %i, handCount: %i, assertHandCountReturnVal: %i\n", returnVal, testGame->handCount[0], assertHandCountReturnVal);

    // Verify that salvager is in played pile, should be 1
    playedPileResult = checkPlayedPile(testGame, salvager);
    
    // Verify that salvager is not in the hand, should be 0
    handResult = checkHand(testGame, salvager);

    // Assert that salvager is found in discard pile and not found in hand
    assertSalvagerLocation = assertTrue(playedPileResult, 1, handResult, 0);

    // printf("salvager played pile: %i, salvager hand: %i, assertSalvagerLocation: %i\n", playedPileResult, handResult, assertSalvagerLocation);

    // Verify that the choice ard is not in the played pile, should be 0
    playedPileChoiceResult = checkPlayedPile(testGame, trashCard);

    // Verify that the choice card is not in the hand, should be 0
    handChoiceResult = checkHand(testGame, trashCard);

    // Assert that trash card is not in discard pile or hand
    assertTrashCard = assertTrue(playedPileChoiceResult, 0, handChoiceResult, 0);

    // printf("trash discard pile: %i, trash hand: %i, assertTrashCard: %i\n", playedPileChoiceResult, handChoiceResult, assertTrashCard);

    // Assert that after playing salvager, there is one more buy and choiceCost more coins
    assertBuyCoin = assertTrue(testGame->numBuys, buyCountBefore + 1, testGame->coins, coinCountBefore + choiceCost);

    // printf("buycount: %i, coins: %i, assertBuyCoin: %i\n", testGame->numBuys, testGame->coins, assertBuyCoin);
 
    // Assert that all parts of the test pass
    assertPart1 = assertTrue(assertHandCountReturnVal, 1, assertSalvagerLocation, 1);
    assertPart2 = assertTrue(assertTrashCard, 1, assertBuyCoin, 1);
 
    // Assert that both halves of the test pass
    if(assertTrue(assertPart1, 1, assertPart2, 1))
    {
	printResults(testCase3, 1);
    }
    else
    {
	printResults(testCase3, 0);
    }

    /* Test Case 4: 7 cards in hand, salvager in position 0, numBuys starts at 1, coins starts at 0, choice1 is gardens*/
    printf("\nsalvager Test Case 4\n"); 
  
    // initialize deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numBuys = 1;
    testGame->coins = 0;

    // Set up deck for player 0
    
    j = 0;
    // Deck holds card values curse and duchy, no salvager
    for(i=curse; i <= duchy; i++)
    {
    	if(i != estate)
	{
            testGame->deck[0][j] = i;
            testGame->deckCount[0] += 1;
            j++;
        }
    }
 
    // Played pile has valid cards that aren't in hand or deck, no salvager
    j = 0;
    for(i = sea_hag; i <= treasure_map; i++)
    {
	testGame->playedCards[j] = i;
	testGame->playedCardCount++; 
        j++;
    }


    // Set up hand for player 0
    // Cards in hand include salvager and cards not in deck or discard
    handPos = 0;
    testGame->hand[0][0] = salvager;
    testGame->hand[0][1] = copper; // cost 0
    testGame->hand[0][2] = province; // cost 8
    testGame->hand[0][3] = council_room; // cost 5
    testGame->hand[0][4] = gardens; // cost 4
    testGame->hand[0][5] = estate; // cost 2
    testGame->hand[0][6] = village; // cost 3
    testGame->handCount[0] = 7;
    choicePos = 4; // gardens
    trashCard = gardens;
    choiceCost = 4;

    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    buyCountBefore = testGame->numBuys;
    coinCountBefore = testGame->coins;


    // call cardEffect
    returnVal = cardEffect(card, choicePos, 0, 0, testGame, handPos, 0);
   
     
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase4 = "salvager effect with hand count of 7, salvager position of 0, buy count 1, coin count 0, gardens choice";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore - 2, returnVal, 0);
    // printf("returnVal: %i, handCount: %i, assertHandCountReturnVal: %i\n", returnVal, testGame->handCount[0], assertHandCountReturnVal);

    // Verify that salvager is in played pile, should be 1
    playedPileResult = checkPlayedPile(testGame, salvager);
    
    // Verify that salvager is not in the hand, should be 0
    handResult = checkHand(testGame, salvager);

    // Assert that salvager is found in discard pile and not found in hand
    assertSalvagerLocation = assertTrue(playedPileResult, 1, handResult, 0);

    // printf("salvager played pile: %i, salvager hand: %i, assertSalvagerLocation: %i\n", playedPileResult, handResult, assertSalvagerLocation);

    // Verify that the choice ard is not in the played pile, should be 0
    playedPileChoiceResult = checkPlayedPile(testGame, trashCard);

    // Verify that the choice card is not in the hand, should be 0
    handChoiceResult = checkHand(testGame, trashCard);

    // Assert that trash card is not in discard pile or hand
    assertTrashCard = assertTrue(playedPileChoiceResult, 0, handChoiceResult, 0);

    // printf("trash discard pile: %i, trash hand: %i, assertTrashCard: %i\n", playedPileChoiceResult, handChoiceResult, assertTrashCard);

    // Assert that after playing salvager, there is one more buy and choiceCost more coins
    assertBuyCoin = assertTrue(testGame->numBuys, buyCountBefore + 1, testGame->coins, coinCountBefore + choiceCost);

    // printf("buycount: %i, coins: %i, assertBuyCoin: %i\n", testGame->numBuys, testGame->coins, assertBuyCoin);
 
    // Assert that all parts of the test pass
    assertPart1 = assertTrue(assertHandCountReturnVal, 1, assertSalvagerLocation, 1);
    assertPart2 = assertTrue(assertTrashCard, 1, assertBuyCoin, 1);
 
    // Assert that both halves of the test pass
    if(assertTrue(assertPart1, 1, assertPart2, 1))
    {
	printResults(testCase4, 1);
    }
    else
    {
	printResults(testCase4, 0);
    }


    /* Test Case 5: 7 cards in hand, salvager in position 0, numBuys starts at 1, coins starts at 0, choice1 is estate */
    printf("\nsalvager Test Case 5\n"); 
  
    // initialize deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numBuys = 1;
    testGame->coins = 0;

    // Set up deck for player 0
    
    j = 0;
    // Deck holds card values curse and duchy, no salvager
    for(i=curse; i <= duchy; i++)
    {
    	if(i != estate)
	{
            testGame->deck[0][j] = i;
            testGame->deckCount[0] += 1;
            j++;
        }
    }
 
    // Played pile has valid cards that aren't in hand or deck, no salvager
    j = 0;
    for(i = sea_hag; i <= treasure_map; i++)
    {
	testGame->playedCards[j] = i;
	testGame->playedCardCount++; 
        j++;
    }


    // Set up hand for player 0
    // Cards in hand include salvager and cards not in deck or discard
    handPos = 0;
    testGame->hand[0][0] = salvager;
    testGame->hand[0][1] = copper; // cost 0
    testGame->hand[0][2] = province; // cost 8
    testGame->hand[0][3] = council_room; // cost 5
    testGame->hand[0][4] = gardens; // cost 4
    testGame->hand[0][5] = estate; // cost 2
    testGame->hand[0][6] = village; // cost 3
    testGame->handCount[0] = 7;
    choicePos = 5; // estate
    trashCard = estate;
    choiceCost = 2;

    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    buyCountBefore = testGame->numBuys;
    coinCountBefore = testGame->coins;


    // call cardEffect
    returnVal = cardEffect(card, choicePos, 0, 0, testGame, handPos, 0);
   
     
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase5 = "salvager effect with hand count of 7, salvager position of 0, buy count 1, coin count 0, estate choice";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore - 2, returnVal, 0);
    // printf("returnVal: %i, handCount: %i, assertHandCountReturnVal: %i\n", returnVal, testGame->handCount[0], assertHandCountReturnVal);

    // Verify that salvager is in played pile, should be 1
    playedPileResult = checkPlayedPile(testGame, salvager);
    
    // Verify that salvager is not in the hand, should be 0
    handResult = checkHand(testGame, salvager);

    // Assert that salvager is found in discard pile and not found in hand
    assertSalvagerLocation = assertTrue(playedPileResult, 1, handResult, 0);

    // printf("salvager played pile: %i, salvager hand: %i, assertSalvagerLocation: %i\n", playedPileResult, handResult, assertSalvagerLocation);

    // Verify that the choice ard is not in the played pile, should be 0
    playedPileChoiceResult = checkPlayedPile(testGame, trashCard);

    // Verify that the choice card is not in the hand, should be 0
    handChoiceResult = checkHand(testGame, trashCard);

    // Assert that trash card is not in discard pile or hand
    assertTrashCard = assertTrue(playedPileChoiceResult, 0, handChoiceResult, 0);

    // printf("trash discard pile: %i, trash hand: %i, assertTrashCard: %i\n", playedPileChoiceResult, handChoiceResult, assertTrashCard);

    // Assert that after playing salvager, there is one more buy and choiceCost more coins
    assertBuyCoin = assertTrue(testGame->numBuys, buyCountBefore + 1, testGame->coins, coinCountBefore + choiceCost);

    // printf("buycount: %i, coins: %i, assertBuyCoin: %i\n", testGame->numBuys, testGame->coins, assertBuyCoin);
 
    // Assert that all parts of the test pass
    assertPart1 = assertTrue(assertHandCountReturnVal, 1, assertSalvagerLocation, 1);
    assertPart2 = assertTrue(assertTrashCard, 1, assertBuyCoin, 1);
 
    // Assert that both halves of the test pass
    if(assertTrue(assertPart1, 1, assertPart2, 1))
    {
	printResults(testCase5, 1);
    }
    else
    {
	printResults(testCase5, 0);
    }

   /* Test Case 6: 7 cards in hand, salvager in position 0, numBuys starts at 1, coins starts at 0, choice1 is village */
    printf("\nsalvager Test Case 6\n"); 
  
    // initialize deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numBuys = 1;
    testGame->coins = 0;

    // Set up deck for player 0
    
    j = 0;
    // Deck holds card values curse and duchy, no salvager
    for(i=curse; i <= duchy; i++)
    {
    	if(i != estate)
	{
            testGame->deck[0][j] = i;
            testGame->deckCount[0] += 1;
            j++;
        }
    }
 
    // Played pile has valid cards that aren't in hand or deck, no salvager
    j = 0;
    for(i = sea_hag; i <= treasure_map; i++)
    {
	testGame->playedCards[j] = i;
	testGame->playedCardCount++; 
        j++;
    }


    // Set up hand for player 0
    // Cards in hand include salvager and cards not in deck or discard
    handPos = 0;
    testGame->hand[0][0] = salvager;
    testGame->hand[0][1] = copper; // cost 0
    testGame->hand[0][2] = province; // cost 8
    testGame->hand[0][3] = council_room; // cost 5
    testGame->hand[0][4] = gardens; // cost 4
    testGame->hand[0][5] = estate; // cost 2
    testGame->hand[0][6] = village; // cost 3
    testGame->handCount[0] = 7;
    choicePos = 6; // village
    trashCard = village;
    choiceCost = 3;

    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    buyCountBefore = testGame->numBuys;
    coinCountBefore = testGame->coins;


    // call cardEffect
    returnVal = cardEffect(card, choicePos, 0, 0, testGame, handPos, 0);
   
     
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase6 = "salvager effect with hand count of 7, salvager position of 0, buy count 1, coin count 0, village choice";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore - 2, returnVal, 0);
    // printf("returnVal: %i, handCount: %i, assertHandCountReturnVal: %i\n", returnVal, testGame->handCount[0], assertHandCountReturnVal);

    // Verify that salvager is in played pile, should be 1
    playedPileResult = checkPlayedPile(testGame, salvager);
    
    // Verify that salvager is not in the hand, should be 0
    handResult = checkHand(testGame, salvager);

    // Assert that salvager is found in discard pile and not found in hand
    assertSalvagerLocation = assertTrue(playedPileResult, 1, handResult, 0);

    // printf("salvager played pile: %i, salvager hand: %i, assertSalvagerLocation: %i\n", playedPileResult, handResult, assertSalvagerLocation);

    // Verify that the choice ard is not in the played pile, should be 0
    playedPileChoiceResult = checkPlayedPile(testGame, trashCard);

    // Verify that the choice card is not in the hand, should be 0
    handChoiceResult = checkHand(testGame, trashCard);

    // Assert that trash card is not in discard pile or hand
    assertTrashCard = assertTrue(playedPileChoiceResult, 0, handChoiceResult, 0);

    // printf("trash discard pile: %i, trash hand: %i, assertTrashCard: %i\n", playedPileChoiceResult, handChoiceResult, assertTrashCard);

    // Assert that after playing salvager, there is one more buy and choiceCost more coins
    assertBuyCoin = assertTrue(testGame->numBuys, buyCountBefore + 1, testGame->coins, coinCountBefore + choiceCost);

    // printf("buycount: %i, coins: %i, assertBuyCoin: %i\n", testGame->numBuys, testGame->coins, assertBuyCoin);
 
    // Assert that all parts of the test pass
    assertPart1 = assertTrue(assertHandCountReturnVal, 1, assertSalvagerLocation, 1);
    assertPart2 = assertTrue(assertTrashCard, 1, assertBuyCoin, 1);
 
    // Assert that both halves of the test pass
    if(assertTrue(assertPart1, 1, assertPart2, 1))
    {
	printResults(testCase6, 1);
    }
    else
    {
	printResults(testCase6, 0);
    }


   /* Test Case 7: 7 cards in hand, salvager in position 0, numBuys starts at 1, coins starts at 500, choice1 is village */
    printf("\nsalvager Test Case 7\n"); 
  
    // initialize deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numBuys = 1;
    testGame->coins = 500;

    // Set up deck for player 0
    
    j = 0;
    // Deck holds card values curse and duchy, no salvager
    for(i=curse; i <= duchy; i++)
    {
    	if(i != estate)
	{
            testGame->deck[0][j] = i;
            testGame->deckCount[0] += 1;
            j++;
        }
    }
 
    // Played pile has valid cards that aren't in hand or deck, no salvager
    j = 0;
    for(i = sea_hag; i <= treasure_map; i++)
    {
	testGame->playedCards[j] = i;
	testGame->playedCardCount++; 
        j++;
    }


    // Set up hand for player 0
    // Cards in hand include salvager and cards not in deck or discard
    handPos = 0;
    testGame->hand[0][0] = salvager;
    testGame->hand[0][1] = copper; // cost 0
    testGame->hand[0][2] = province; // cost 8
    testGame->hand[0][3] = council_room; // cost 5
    testGame->hand[0][4] = gardens; // cost 4
    testGame->hand[0][5] = estate; // cost 2
    testGame->hand[0][6] = village; // cost 3
    testGame->handCount[0] = 7;
    choicePos = 6; // village
    trashCard = village;
    choiceCost = 3;

    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    buyCountBefore = testGame->numBuys;
    coinCountBefore = testGame->coins;


    // call cardEffect
    returnVal = cardEffect(card, choicePos, 0, 0, testGame, handPos, 0);
   
     
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase7 = "salvager effect with hand count of 7, salvager position of 0, buy count 1, coin count 500, village choice";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore - 2, returnVal, 0);
    // printf("returnVal: %i, handCount: %i, assertHandCountReturnVal: %i\n", returnVal, testGame->handCount[0], assertHandCountReturnVal);

    // Verify that salvager is in played pile, should be 1
    playedPileResult = checkPlayedPile(testGame, salvager);
    
    // Verify that salvager is not in the hand, should be 0
    handResult = checkHand(testGame, salvager);

    // Assert that salvager is found in discard pile and not found in hand
    assertSalvagerLocation = assertTrue(playedPileResult, 1, handResult, 0);

    // printf("salvager played pile: %i, salvager hand: %i, assertSalvagerLocation: %i\n", playedPileResult, handResult, assertSalvagerLocation);

    // Verify that the choice ard is not in the played pile, should be 0
    playedPileChoiceResult = checkPlayedPile(testGame, trashCard);

    // Verify that the choice card is not in the hand, should be 0
    handChoiceResult = checkHand(testGame, trashCard);

    // Assert that trash card is not in discard pile or hand
    assertTrashCard = assertTrue(playedPileChoiceResult, 0, handChoiceResult, 0);

    // printf("trash discard pile: %i, trash hand: %i, assertTrashCard: %i\n", playedPileChoiceResult, handChoiceResult, assertTrashCard);

    // Assert that after playing salvager, there is one more buy and choiceCost more coins
    assertBuyCoin = assertTrue(testGame->numBuys, buyCountBefore + 1, testGame->coins, coinCountBefore + choiceCost);

    // printf("buycount: %i, coins: %i, assertBuyCoin: %i\n", testGame->numBuys, testGame->coins, assertBuyCoin);
 
    // Assert that all parts of the test pass
    assertPart1 = assertTrue(assertHandCountReturnVal, 1, assertSalvagerLocation, 1);
    assertPart2 = assertTrue(assertTrashCard, 1, assertBuyCoin, 1);
 
    // Assert that both halves of the test pass
    if(assertTrue(assertPart1, 1, assertPart2, 1))
    {
	printResults(testCase7, 1);
    }
    else
    {
	printResults(testCase7, 0);
    }


   /* Test Case 8: 7 cards in hand, salvager in position 0, numBuys starts at 333, coins starts at 500, choice1 is village */
    printf("\nsalvager Test Case 8\n"); 
  
    // initialize deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numBuys = 333;
    testGame->coins = 500;

    // Set up deck for player 0
    
    j = 0;
    // Deck holds card values curse and duchy, no salvager
    for(i=curse; i <= duchy; i++)
    {
    	if(i != estate)
	{
            testGame->deck[0][j] = i;
            testGame->deckCount[0] += 1;
            j++;
        }
    }
 
    // Played pile has valid cards that aren't in hand or deck, no salvager
    j = 0;
    for(i = sea_hag; i <= treasure_map; i++)
    {
	testGame->playedCards[j] = i;
	testGame->playedCardCount++; 
        j++;
    }


    // Set up hand for player 0
    // Cards in hand include salvager and cards not in deck or discard
    handPos = 0;
    testGame->hand[0][0] = salvager;
    testGame->hand[0][1] = copper; // cost 0
    testGame->hand[0][2] = province; // cost 8
    testGame->hand[0][3] = council_room; // cost 5
    testGame->hand[0][4] = gardens; // cost 4
    testGame->hand[0][5] = estate; // cost 2
    testGame->hand[0][6] = village; // cost 3
    testGame->handCount[0] = 7;
    choicePos = 6; // village
    trashCard = village;
    choiceCost = 3;

    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    buyCountBefore = testGame->numBuys;
    coinCountBefore = testGame->coins;


    // call cardEffect
    returnVal = cardEffect(card, choicePos, 0, 0, testGame, handPos, 0);
   
     
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase8 = "salvager effect with hand count of 7, salvager position of 0, buy count 333, coin count 500, village choice";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore - 2, returnVal, 0);
    // printf("returnVal: %i, handCount: %i, assertHandCountReturnVal: %i\n", returnVal, testGame->handCount[0], assertHandCountReturnVal);

    // Verify that salvager is in played pile, should be 1
    playedPileResult = checkPlayedPile(testGame, salvager);
    
    // Verify that salvager is not in the hand, should be 0
    handResult = checkHand(testGame, salvager);

    // Assert that salvager is found in discard pile and not found in hand
    assertSalvagerLocation = assertTrue(playedPileResult, 1, handResult, 0);

    // printf("salvager played pile: %i, salvager hand: %i, assertSalvagerLocation: %i\n", playedPileResult, handResult, assertSalvagerLocation);

    // Verify that the choice ard is not in the played pile, should be 0
    playedPileChoiceResult = checkPlayedPile(testGame, trashCard);

    // Verify that the choice card is not in the hand, should be 0
    handChoiceResult = checkHand(testGame, trashCard);

    // Assert that trash card is not in discard pile or hand
    assertTrashCard = assertTrue(playedPileChoiceResult, 0, handChoiceResult, 0);

    // printf("trash discard pile: %i, trash hand: %i, assertTrashCard: %i\n", playedPileChoiceResult, handChoiceResult, assertTrashCard);

    // Assert that after playing salvager, there is one more buy and choiceCost more coins
    assertBuyCoin = assertTrue(testGame->numBuys, buyCountBefore + 1, testGame->coins, coinCountBefore + choiceCost);

    // printf("buycount: %i, coins: %i, assertBuyCoin: %i\n", testGame->numBuys, testGame->coins, assertBuyCoin);
 
    // Assert that all parts of the test pass
    assertPart1 = assertTrue(assertHandCountReturnVal, 1, assertSalvagerLocation, 1);
    assertPart2 = assertTrue(assertTrashCard, 1, assertBuyCoin, 1);
 
    // Assert that both halves of the test pass
    if(assertTrue(assertPart1, 1, assertPart2, 1))
    {
	printResults(testCase8, 1);
    }
    else
    {
	printResults(testCase8, 0);
    }


   /* Test Case 9: 7 cards in hand, salvager in position 6, numBuys starts at 333, coins starts at 500, choice1 is village */
    printf("\nsalvager Test Case 9\n"); 
  
    // initialize deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numBuys = 333;
    testGame->coins = 500;

    // Set up deck for player 0
    
    j = 0;
    // Deck holds card values curse and duchy, no salvager
    for(i=curse; i <= duchy; i++)
    {
    	if(i != estate)
	{
            testGame->deck[0][j] = i;
            testGame->deckCount[0] += 1;
            j++;
        }
    }
 
    // Played pile has valid cards that aren't in hand or deck, no salvager
    j = 0;
    for(i = sea_hag; i <= treasure_map; i++)
    {
	testGame->playedCards[j] = i;
	testGame->playedCardCount++; 
        j++;
    }


    // Set up hand for player 0
    // Cards in hand include salvager and cards not in deck or discard
    handPos = 6;
    testGame->hand[0][0] = village; // cost 3
    testGame->hand[0][1] = copper; // cost 0
    testGame->hand[0][2] = province; // cost 8
    testGame->hand[0][3] = council_room; // cost 5
    testGame->hand[0][4] = gardens; // cost 4
    testGame->hand[0][5] = estate; // cost 2
    testGame->hand[0][6] = salvager;
    testGame->handCount[0] = 7;
    choicePos = 0; // 
    trashCard = village;
    choiceCost = 3;

    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    buyCountBefore = testGame->numBuys;
    coinCountBefore = testGame->coins;

    // call cardEffect
    returnVal = cardEffect(card, choicePos, 0, 0, testGame, handPos, 0);
   
     
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase9 = "salvager effect with hand count of 7, salvager position of 6, buy count 333, coin count 500, village choice";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore - 2, returnVal, 0);
    //printf("returnVal: %i, handCount: %i, assertHandCountReturnVal: %i\n", returnVal, testGame->handCount[0], assertHandCountReturnVal);

    // Verify that salvager is in played pile, should be 1
    playedPileResult = checkPlayedPile(testGame, salvager);
    
    // Verify that salvager is not in the hand, should be 0
    handResult = checkHand(testGame, salvager);

    // Assert that salvager is found in discard pile and not found in hand
    assertSalvagerLocation = assertTrue(playedPileResult, 1, handResult, 0);

    //printf("salvager played pile: %i, salvager hand: %i, assertSalvagerLocation: %i\n", playedPileResult, handResult, assertSalvagerLocation);

    // Verify that the choice ard is not in the played pile, should be 0
    playedPileChoiceResult = checkPlayedPile(testGame, trashCard);

    // Verify that the choice card is not in the hand, should be 0
    handChoiceResult = checkHand(testGame, trashCard);

    // Assert that trash card is not in discard pile or hand
    assertTrashCard = assertTrue(playedPileChoiceResult, 0, handChoiceResult, 0);

    //printf("trash discard pile: %i, trash hand: %i, assertTrashCard: %i\n", playedPileChoiceResult, handChoiceResult, assertTrashCard);

    // Assert that after playing salvager, there is one more buy and choiceCost more coins
    assertBuyCoin = assertTrue(testGame->numBuys, buyCountBefore + 1, testGame->coins, coinCountBefore + choiceCost);

    //printf("buycount: %i, coins: %i, assertBuyCoin: %i\n", testGame->numBuys, testGame->coins, assertBuyCoin);
 
    // Assert that all parts of the test pass
    assertPart1 = assertTrue(assertHandCountReturnVal, 1, assertSalvagerLocation, 1);
    assertPart2 = assertTrue(assertTrashCard, 1, assertBuyCoin, 1);
 
    // Assert that both halves of the test pass
    if(assertTrue(assertPart1, 1, assertPart2, 1))
    {
	printResults(testCase9, 1);
    }
    else
    {
	printResults(testCase9, 0);
    }


   /* Test Case 10: 7 cards in hand, salvager in position 6, numBuys starts at 333, coins starts at 500, choice1 is province at index 2 */
    printf("\nsalvager Test Case 10\n"); 
  
    // initialize deck and card counts and actions
    testGame->deckCount[0] = 0;
    testGame->handCount[0] = 0;
    testGame->discardCount[0] = 0;
    testGame->playedCardCount = 0; 
    testGame->numBuys = 333;
    testGame->coins = 500;

    // Set up deck for player 0
    
    j = 0;
    // Deck holds card values curse and duchy, no salvager
    for(i=curse; i <= duchy; i++)
    {
    	if(i != estate)
	{
            testGame->deck[0][j] = i;
            testGame->deckCount[0] += 1;
            j++;
        }
    }
 
    // Played pile has valid cards that aren't in hand or deck, no salvager
    j = 0;
    for(i = sea_hag; i <= treasure_map; i++)
    {
	testGame->playedCards[j] = i;
	testGame->playedCardCount++; 
        j++;
    }


    // Set up hand for player 0
    // Cards in hand include salvager and cards not in deck or discard
    handPos = 6;
    testGame->hand[0][0] = village; // cost 3
    testGame->hand[0][1] = copper; // cost 0
    testGame->hand[0][2] = province; // cost 8
    testGame->hand[0][3] = council_room; // cost 5
    testGame->hand[0][4] = gardens; // cost 4
    testGame->hand[0][5] = estate; // cost 2
    testGame->hand[0][6] = salvager;
    testGame->handCount[0] = 7;
    choicePos = 2; // 
    trashCard = province;
    choiceCost = 8;

    // Save current hand count and action count
    handCountBefore = testGame->handCount[0];
    buyCountBefore = testGame->numBuys;
    coinCountBefore = testGame->coins;

   
    // call cardEffect
    returnVal = cardEffect(card, choicePos, 0, 0, testGame, handPos, 0);
   
     
    // Assert that the before handCount is the same as current handCount and that returnVal is 0
    // Check the restults of this test case
    char* testCase10 = "salvager effect with hand count of 7, salvager position of 6, buy count 333, coin count 500, village choice";

    assertHandCountReturnVal = assertTrue(testGame->handCount[0], handCountBefore - 2, returnVal, 0);
  //  printf("returnVal: %i, handCount: %i, assertHandCountReturnVal: %i\n", returnVal, testGame->handCount[0], assertHandCountReturnVal);

   
    // Verify that salvager is in played pile, should be 1
    playedPileResult = checkPlayedPile(testGame, salvager);
    
    // Verify that salvager is not in the hand, should be 0
    handResult = checkHand(testGame, salvager);

    // Assert that salvager is found in discard pile and not found in hand
    assertSalvagerLocation = assertTrue(playedPileResult, 1, handResult, 0);

    //printf("salvager played pile: %i, salvager hand: %i, assertSalvagerLocation: %i\n", playedPileResult, handResult, assertSalvagerLocation);

    // Verify that the choice ard is not in the played pile, should be 0
    playedPileChoiceResult = checkPlayedPile(testGame, trashCard);

    // Verify that the choice card is not in the hand, should be 0
    handChoiceResult = checkHand(testGame, trashCard);

    // Assert that trash card is not in discard pile or hand
    assertTrashCard = assertTrue(playedPileChoiceResult, 0, handChoiceResult, 0);

    //printf("trash discard pile: %i, trash hand: %i, assertTrashCard: %i\n", playedPileChoiceResult, handChoiceResult, assertTrashCard);

    // Assert that after playing salvager, there is one more buy and choiceCost more coins
    assertBuyCoin = assertTrue(testGame->numBuys, buyCountBefore + 1, testGame->coins, coinCountBefore + choiceCost);

    //printf("buycount: %i, coins: %i, assertBuyCoin: %i\n", testGame->numBuys, testGame->coins, assertBuyCoin);
 
    // Assert that all parts of the test pass
    assertPart1 = assertTrue(assertHandCountReturnVal, 1, assertSalvagerLocation, 1);
    assertPart2 = assertTrue(assertTrashCard, 1, assertBuyCoin, 1);
 
    // Assert that both halves of the test pass
    if(assertTrue(assertPart1, 1, assertPart2, 1))
    {
	printResults(testCase10, 1);
    }
    else
    {
	printResults(testCase10, 0);
    }





}

/******************************************************************************
 * Description: This is the main function. It calls testSalvager().
 * ***************************************************************************/

int main(int argc, char *argv[])
{
    testSalvager();
    return 0;
}
