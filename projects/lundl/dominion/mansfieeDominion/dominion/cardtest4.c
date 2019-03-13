/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 3
 * Description: This is a unit test for the card salvager in dominion.c.
 * Citation: The example given in the assignment: cardtest4.c
 * ***************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h" 
#include "rngs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TESTCARD "salvager"
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
	printf("    salvager: FAIL %s\n", testCase);
    }
    else
    {
	printf("    salvager: PASS %s\n", testCase);
    }
}

/******************************************************************************
 * Name: assertTrue()
 * Parameters: four ints: one holding the actual value of the test result, 
 * 	one holding the expected value of the test result
 * Description: This helper function compares actual value to expected value.
 * 	If the actual value matches the expected value, return 1. Otherwise, 
 * 	return 0.
 * Return Value: Returns 1 if the input values match "true." Returns 0 otherwise.
 * ***************************************************************************/
int assertTrue(int actualVal, int expectedVal)
{
    if(actualVal == expectedVal)
    {
	return 1;
    }
    return 0;
}

int main()
{
    int newCards = 0; // salvager should return 0 new cards
	int handCountComparison = 0; // 1 if handcount matches expected value
	int discarded = 2; // the card played will be discarded, choice will be trashed
	int buyIncrease = 1; // salvager should increase the buys by 1
    int playedCardComp = 0; // 1 if played count matches expected value
	int coinCountComp = 0; // 1 if coin count matches expected value
	int buyComp = 0; // 1 if buy count matches expected value
	int cardFound = 0; // 1 if card found in hand
	
	int numPlayers = 2;
	int thisPlayer = 0;
	int player1HandMatch = 1; // 0 if player 1's hand changes 
	int player1DeckMatch = 1; // 0 if player 1's deck changes
	int player1HandComp = 0; // 1 if matches expected value
	int player1DeckComp = 0; // 1 if matches expected value
	
	int player2HandMatch = 1; // 0 if player 2's hand changes 
	int player2DeckMatch = 1; // 0 if player 2's deck changes
	int player2HandComp = 0; // 1 if matches expected value
	int player2DeckComp = 0; // 1 if matches expected value
	
	int player3HandMatch = 1; // 0 if player 3's hand changes 
	int player3DeckMatch = 1; // 0 if player 3's deck changes
	int player3HandComp = 0; // 1 if matches expected value
	int player3DeckComp = 0; // 1 if matches expected value
	
	int kingdomMatch = 1; // 0 if kingdom cards in states differ
	int victoryMatch = 1; // 0 if victory cards in states differ
	int kingdomComp = 0; // 1 if matches expected value
	int victoryComp = 0; // 1 if matches expected value
	
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int choiceVal = 0;
	int i;
    int seed = 1000; // needed for game initialization

    // This the the state of the game that will be sent to salvager
    struct gameState testGame;
	
	// This is the state of the game that will be used to preserve the original state
	struct gameState originalGame;
	
	// Kingdom cards in play
	int k[10] = {adventurer, embargo, smithy, minion, mine, cutpurse, sea_hag,
		tribute, baron, council_room};
	
	// initialize game state and player cards
	initializeGame(numPlayers, k, seed, &originalGame); 
    
	// Put salvager in the last hand position for this player
	// Set player's hand
	originalGame.hand[thisPlayer][0] = province; // cost 8
	originalGame.hand[thisPlayer][1] = estate; // cost 2
	originalGame.hand[thisPlayer][2] = copper; // cost 0
	originalGame.hand[thisPlayer][3] = council_room; // cost 5
	originalGame.hand[thisPlayer][4] = gardens; // cost 4
	originalGame.hand[thisPlayer][5] = village; // cost 3
	originalGame.hand[thisPlayer][6] = salvager; 
	originalGame.handCount[0] = 7;
	handPos = 6;
	choice1 = 5;
	choiceVal = 3;
	
	printf("---------- Testing Card: %s ----------\n", TESTCARD);
	
	// ----- Test 1: hand count of 7, salvager in pos 6, 2 players -----
	printf("-----Test 1: hand count of 7, salvager in pos 6, 2 players-----\n");
	printf("-----choice card: village, cost: 3, position: 5-----\n");	
	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(salvager, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// hand count should be -2 of original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("-2 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// played cards should increase by 1
	// assert that the above is true
	playedCardComp = assertTrue(testGame.playedCardCount, 
		originalGame.playedCardCount + 1);
	
	// print result
	printResults("+1 played cards", playedCardComp);
	if(playedCardComp == 0)
	{
		printf("     played count: %i, expected: %i\n", testGame.playedCardCount, 
			originalGame.playedCardCount + 1);	
	}
	
	// coin count should increase by cost of choice card
	// assert that the above is true
	coinCountComp = assertTrue(testGame.coins, originalGame.coins + choiceVal);
	
	printResults("+cost of choice card added to coin count", coinCountComp);
	if(coinCountComp == 0)
	{
		printf("        coin count: %i, expected: %i\n", testGame.coins, 
			originalGame.coins + choiceVal);
	}
	
	// buys should increase by 1
	buyComp = assertTrue(testGame.numBuys, originalGame.numBuys + buyIncrease);
	
	// print results
	printResults("+1 buy count", buyComp);
	if(buyComp == 0)
	{
		printf("     buy count: %i, expected: %i\n", testGame.numBuys, 
			originalGame.numBuys + buyIncrease);    
	}
	
	

	
	// The states of other players should not change. 
	// Check hand and deck of other players.
	// Check hand
	for (i=0; i < originalGame.handCount[1]; i++)
	{
		// compare hands
		if(originalGame.hand[1][i] != testGame.hand[1][i])
		{
			// this player had a change in their hand
			player1HandMatch = 0;
			break;
		}
	}
	
	// Check deck
	for (i=0; i < originalGame.deckCount[1]; i++)
	{
		// compare decks
		if(originalGame.deck[1][i] != testGame.deck[1][i])
		{
			// this player had a change in their hand
			player1DeckMatch = 0;
			break;
		}
	}
	
	// Assert that the other player's hand did not change
	player1HandComp = assertTrue(player1HandMatch, 1);
	
	// print result
	printResults("player 1's hand unchanged", player1HandComp);
	
	// Assert that the other player's deck did not change
	player1DeckComp = assertTrue(player1DeckMatch, 1);
	
	// print result
	printResults("player 1's deck unchanged", player1DeckComp);
	

	// Salvager should not be in hand
	for(i = 0; i < testGame.handCount[thisPlayer]; i++)
	{
		if(testGame.hand[thisPlayer][i] == salvager)
		{
			cardFound = 1;
			handPos = i;
		}
	}
	
	if(cardFound)
	{
		printResults("salvager not in hand", 0);
	}
	else
	{
		printResults("salvager not in hand", 1);
	}
	
	// kingdom and victory cards should not change
	// kingdom cards
	for(i = 0; i < sizeof(k); i++)
	{
		// if the kingdom cards in the test are different from 
		//those in the original
		if(originalGame.supplyCount[k[i]] != testGame.supplyCount[k[i]])
		{
			printf("kingdom card %i is different at %i\n", k[i], i);
			kingdomMatch = 0;
			
			break;
		}
	}
	
	// assert no change in kingdom cards
	kingdomComp = assertTrue(kingdomMatch, 1);
	
	printResults("kingdom cards unchanged", kingdomComp);
	
	// victory cards
	for(i = estate; i <= province; i++)
	{
		// if the victory cards in the test are different from 
		//those in the original
		if(originalGame.supplyCount[i] != testGame.supplyCount[i])
		{
			printf("victory card %i is different\n", i);
			victoryMatch = 0;
			
			break;
		}
	}
	
	// assert no change in victory cards
	victoryComp = assertTrue(victoryMatch, 1);
	
	printResults("victory cards unchanged", victoryComp);

	
	// ----- Test 2: hand count of 7, salvager in pos 6, 2 players -----
	printf("\n-----Test 2: hand count of 7, salvager in pos 6, 2 players-----\n");
	printf("-----choice card: province, cost: 8, position: 0-----\n");	
	
	// Put salvager in the last hand position for this player
	// Set player's hand
	originalGame.hand[thisPlayer][0] = province; // cost 8
	originalGame.hand[thisPlayer][1] = estate; // cost 2
	originalGame.hand[thisPlayer][2] = copper; // cost 0
	originalGame.hand[thisPlayer][3] = council_room; // cost 5
	originalGame.hand[thisPlayer][4] = gardens; // cost 4
	originalGame.hand[thisPlayer][5] = village; // cost 3
	originalGame.hand[thisPlayer][6] = salvager; 
	originalGame.handCount[0] = 7;
	handPos = 6;
	choice1 = 0;
	choiceVal = 8;
	
	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(salvager, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// hand count should be -2 of original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("-2 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// played cards should increase by 1
	// assert that the above is true
	playedCardComp = assertTrue(testGame.playedCardCount, 
		originalGame.playedCardCount + 1);
	
	// print result
	printResults("+1 played cards", playedCardComp);
	if(playedCardComp == 0)
	{
		printf("     played count: %i, expected: %i\n", testGame.playedCardCount, 
			originalGame.playedCardCount + 1);	
	}
	
	// coin count should increase by cost of choice card
	// assert that the above is true
	coinCountComp = assertTrue(testGame.coins, originalGame.coins + choiceVal);
	
	printResults("+cost of choice card added to coin count", coinCountComp);
	if(coinCountComp == 0)
	{
		printf("        coin count: %i, expected: %i\n", testGame.coins, 
			originalGame.coins + choiceVal);
	}
	
	// buys should increase by 1
	buyComp = assertTrue(testGame.numBuys, originalGame.numBuys + buyIncrease);
	
	// print results
	printResults("+1 buy count", buyComp);
	if(buyComp == 0)
	{
		printf("     buy count: %i, expected: %i\n", testGame.numBuys, 
			originalGame.numBuys + buyIncrease);    
	}
	
	// The states of other players should not change. 
	// Check hand and deck of other players.
	// Check hand
	for (i=0; i < originalGame.handCount[1]; i++)
	{
		// compare hands
		if(originalGame.hand[1][i] != testGame.hand[1][i])
		{
			// this player had a change in their hand
			player1HandMatch = 0;
			break;
		}
	}
	
	// Check deck
	for (i=0; i < originalGame.deckCount[1]; i++)
	{
		// compare decks
		if(originalGame.deck[1][i] != testGame.deck[1][i])
		{
			// this player had a change in their hand
			player1DeckMatch = 0;
			break;
		}
	}
	
	// Assert that the other player's hand did not change
	player1HandComp = assertTrue(player1HandMatch, 1);
	
	// print result
	printResults("player 1's hand unchanged", player1HandComp);
	
	// Assert that the other player's deck did not change
	player1DeckComp = assertTrue(player1DeckMatch, 1);
	
	// print result
	printResults("player 1's deck unchanged", player1DeckComp);
	
	// Salvager should not be in hand
	for(i = 0; i < testGame.handCount[thisPlayer]; i++)
	{
		if(testGame.hand[thisPlayer][i] == salvager)
		{
			cardFound = 1;
			handPos = i;
		}
	}
	
	if(cardFound)
	{
		printResults("salvager not in hand", 0);
	}
	else
	{
		printResults("salvager not in hand", 1);
	}
	

	// kingdom and victory cards should not change
	// kingdom cards
	for(i = 0; i < sizeof(k); i++)
	{
		// if the kingdom cards in the test are different from 
		//those in the original
		if(originalGame.supplyCount[k[i]] != testGame.supplyCount[k[i]])
		{
			printf("kingdom card %i is different at %i\n", k[i], i);
			kingdomMatch = 0;
			
			break;
		}
	}
	
	// assert no change in kingdom cards
	kingdomComp = assertTrue(kingdomMatch, 1);
	
	printResults("kingdom cards unchanged", kingdomComp);
	
	// victory cards
	for(i = estate; i <= province; i++)
	{
		// if the victory cards in the test are different from 
		//those in the original
		if(originalGame.supplyCount[i] != testGame.supplyCount[i])
		{
			printf("victory card %i is different\n", i);
			victoryMatch = 0;
			
			break;
		}
	}
	
	// assert no change in victory cards
	victoryComp = assertTrue(victoryMatch, 1);
	
	printResults("victory cards unchanged", victoryComp);
	
	// ----- Test 3: hand count of 7, salvager in pos 0, 2 players -----
	printf("\n-----Test 3: hand count of 7, salvager in pos 0, 2 players-----\n");
	printf("-----choice card: estate, cost: 2, position: 1-----\n");	
	
	// Put salvager in the first hand position for this player
	// Set player's hand
	originalGame.hand[thisPlayer][6] = province; // cost 8
	originalGame.hand[thisPlayer][1] = estate; // cost 2
	originalGame.hand[thisPlayer][2] = copper; // cost 0
	originalGame.hand[thisPlayer][3] = council_room; // cost 5
	originalGame.hand[thisPlayer][4] = gardens; // cost 4
	originalGame.hand[thisPlayer][5] = village; // cost 3
	originalGame.hand[thisPlayer][0] = salvager; 
	originalGame.handCount[0] = 7;
	handPos = 0;
	choice1 = 1;
	choiceVal = 2;
	
	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(salvager, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// hand count should be -2 of original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("-2 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// played cards should increase by 1
	// assert that the above is true
	playedCardComp = assertTrue(testGame.playedCardCount, 
		originalGame.playedCardCount + 1);
	
	// print result
	printResults("+1 played cards", playedCardComp);
	if(playedCardComp == 0)
	{
		printf("     played count: %i, expected: %i\n", testGame.playedCardCount, 
			originalGame.playedCardCount + 1);	
	}
	
	// coin count should increase by cost of choice card
	// assert that the above is true
	coinCountComp = assertTrue(testGame.coins, originalGame.coins + choiceVal);
	
	printResults("+cost of choice card added to coin count", coinCountComp);
	if(coinCountComp == 0)
	{
		printf("        coin count: %i, expected: %i\n", testGame.coins, 
			originalGame.coins + choiceVal);
	}
	
	// buys should increase by 1
	buyComp = assertTrue(testGame.numBuys, originalGame.numBuys + buyIncrease);
	
	// print results
	printResults("+1 buy count", buyComp);
	if(buyComp == 0)
	{
		printf("     buy count: %i, expected: %i\n", testGame.numBuys, 
			originalGame.numBuys + buyIncrease);    
	}
	
	// The states of other players should not change. 
	// Check hand and deck of other players.
	// Check hand
	for (i=0; i < originalGame.handCount[1]; i++)
	{
		// compare hands
		if(originalGame.hand[1][i] != testGame.hand[1][i])
		{
			// this player had a change in their hand
			player1HandMatch = 0;
			break;
		}
	}
	
	// Check deck
	for (i=0; i < originalGame.deckCount[1]; i++)
	{
		// compare decks
		if(originalGame.deck[1][i] != testGame.deck[1][i])
		{
			// this player had a change in their hand
			player1DeckMatch = 0;
			break;
		}
	}
	
	// Assert that the other player's hand did not change
	player1HandComp = assertTrue(player1HandMatch, 1);
	
	// print result
	printResults("player 1's hand unchanged", player1HandComp);
	
	// Assert that the other player's deck did not change
	player1DeckComp = assertTrue(player1DeckMatch, 1);
	
	// print result
	printResults("player 1's deck unchanged", player1DeckComp);
	
	// Salvager should not be in hand
	for(i = 0; i < testGame.handCount[thisPlayer]; i++)
	{
		if(testGame.hand[thisPlayer][i] == salvager)
		{
			cardFound = 1;
			handPos = i;
		}
	}
	
	if(cardFound)
	{
		printResults("salvager not in hand", 0);
	}
	else
	{
		printResults("salvager not in hand", 1);
	}
	

	// kingdom and victory cards should not change
	// kingdom cards
	for(i = 0; i < sizeof(k); i++)
	{
		// if the kingdom cards in the test are different from 
		//those in the original
		if(originalGame.supplyCount[k[i]] != testGame.supplyCount[k[i]])
		{
			printf("kingdom card %i is different at %i\n", k[i], i);
			kingdomMatch = 0;
			
			break;
		}
	}
	
	// assert no change in kingdom cards
	kingdomComp = assertTrue(kingdomMatch, 1);
	
	printResults("kingdom cards unchanged", kingdomComp);
	
	// victory cards
	for(i = estate; i <= province; i++)
	{
		// if the victory cards in the test are different from 
		//those in the original
		if(originalGame.supplyCount[i] != testGame.supplyCount[i])
		{
			printf("victory card %i is different\n", i);
			victoryMatch = 0;
			
			break;
		}
	}
	
	// assert no change in victory cards
	victoryComp = assertTrue(victoryMatch, 1);
	
	printResults("victory cards unchanged", victoryComp);
	
	// ----- Test 4: hand count of 7, salvager in pos 0, 3 players -----
	printf("\n-----Test 4: hand count of 7, salvager in pos 0, 3 players-----\n");
	printf("-----choice card: estate, cost: 2, position: 1-----\n");	
	
	// reinitialize game for 3 players
	numPlayers = 3;
	initializeGame(numPlayers, k, seed, &originalGame); 
	
	// Put salvager in the first hand position for this player
	// Set player's hand
	originalGame.hand[thisPlayer][6] = province; // cost 8
	originalGame.hand[thisPlayer][1] = estate; // cost 2
	originalGame.hand[thisPlayer][2] = copper; // cost 0
	originalGame.hand[thisPlayer][3] = council_room; // cost 5
	originalGame.hand[thisPlayer][4] = gardens; // cost 4
	originalGame.hand[thisPlayer][5] = village; // cost 3
	originalGame.hand[thisPlayer][0] = salvager; 
	originalGame.handCount[0] = 7;
	handPos = 0;
	choice1 = 1;
	choiceVal = 2;
	
	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(salvager, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// hand count should be -2 of original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("-2 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// played cards should increase by 1
	// assert that the above is true
	playedCardComp = assertTrue(testGame.playedCardCount, 
		originalGame.playedCardCount + 1);
	
	// print result
	printResults("+1 played cards", playedCardComp);
	if(playedCardComp == 0)
	{
		printf("     played count: %i, expected: %i\n", testGame.playedCardCount, 
			originalGame.playedCardCount + 1);	
	}
	
	// coin count should increase by cost of choice card
	// assert that the above is true
	coinCountComp = assertTrue(testGame.coins, originalGame.coins + choiceVal);
	
	printResults("+cost of choice card added to coin count", coinCountComp);
	if(coinCountComp == 0)
	{
		printf("        coin count: %i, expected: %i\n", testGame.coins, 
			originalGame.coins + choiceVal);
	}
	
	// buys should increase by 1
	buyComp = assertTrue(testGame.numBuys, originalGame.numBuys + buyIncrease);
	
	// print results
	printResults("+1 buy count", buyComp);
	if(buyComp == 0)
	{
		printf("     buy count: %i, expected: %i\n", testGame.numBuys, 
			originalGame.numBuys + buyIncrease);    
	}
	
	// The states of other players should not change. 
	// Check hand, deck of other players
	// Check hand
	for (i=0; i < originalGame.handCount[1]; i++)
	{
		// compare hands
		if(originalGame.hand[1][i] != testGame.hand[1][i])
		{
			// this player had a change in their hand
			player1HandMatch = 0;
			break;
		}
	}
	
	// check deck
	for (i=0; i < originalGame.deckCount[1]; i++)
	{
		// compare decks
		if(originalGame.deck[1][i] != testGame.deck[1][i])
		{
			// this player had a change in their hand
			player1DeckMatch = 0;
			break;
		}
	}
	

	
	// Assert that the other player's hand did not change
	player1HandComp = assertTrue(player1HandMatch, 1);
	
	// print result
	printResults("player 1's hand unchanged", player1HandComp);
	
	// Assert that the other player's deck did not change
	player1DeckComp = assertTrue(player1DeckMatch, 1);
	
	// print result
	printResults("player 1's deck unchanged", player1DeckComp);
	
	// Player 2
	// Check hand
	for (i=0; i < originalGame.handCount[2]; i++)
	{
		// compare hands
		if(originalGame.hand[2][i] != testGame.hand[2][i])
		{
			// this player had a change in their hand
			player2HandMatch = 0;
			break;
		}
	}
	
	// Check deck
	for (i=0; i < originalGame.deckCount[2]; i++)
	{
		// compare decks
		if(originalGame.deck[2][i] != testGame.deck[2][i])
		{
			// this player had a change in their hand
			player2DeckMatch = 0;
			break;
		}
	}
	
	// Assert that the other player's hand did not change
	player2HandComp = assertTrue(player2HandMatch, 1);
	
	// print result
	printResults("player 2's hand unchanged", player2HandComp);
	
	// Assert that the other player's deck did not change
	player2DeckComp = assertTrue(player2DeckMatch, 1);
	
	// print result
	printResults("player 2's deck unchanged", player2DeckComp);
	
	
	
	// Salvager should not be in hand
	for(i = 0; i < testGame.handCount[thisPlayer]; i++)
	{
		if(testGame.hand[thisPlayer][i] == salvager)
		{
			cardFound = 1;
			handPos = i;
		}
	}
	
	if(cardFound)
	{
		printResults("salvager not in hand", 0);
	}
	else
	{
		printResults("salvager not in hand", 1);
	}
	

	// kingdom and victory cards should not change
	// kingdom cards
	for(i = 0; i < sizeof(k); i++)
	{
		// if the kingdom cards in the test are different from 
		//those in the original
		if(originalGame.supplyCount[k[i]] != testGame.supplyCount[k[i]])
		{
			printf("kingdom card %i is different at %i\n", k[i], i);
			kingdomMatch = 0;
			
			break;
		}
	}
	
	// assert no change in kingdom cards
	kingdomComp = assertTrue(kingdomMatch, 1);
	
	printResults("kingdom cards unchanged", kingdomComp);
	
	// victory cards
	for(i = estate; i <= province; i++)
	{
		// if the victory cards in the test are different from 
		//those in the original
		if(originalGame.supplyCount[i] != testGame.supplyCount[i])
		{
			printf("victory card %i is different\n", i);
			victoryMatch = 0;
			
			break;
		}
	}
	
	// assert no change in victory cards
	victoryComp = assertTrue(victoryMatch, 1);
	
	printResults("victory cards unchanged", victoryComp);
	
	// ----- Test 5: hand count of 7, salvager in pos 0, 4 players -----
	printf("\n-----Test 5: hand count of 7, salvager in pos 0, 4 players-----\n");
	printf("-----choice card: estate, cost: 2, position: 1-----\n");	
	
	// reinitialize game for 4 players
	numPlayers = 4;
	initializeGame(numPlayers, k, seed, &originalGame); 
	
	// Put salvager in the first hand position for this player
	// Set player's hand
	originalGame.hand[thisPlayer][6] = province; // cost 8
	originalGame.hand[thisPlayer][1] = estate; // cost 2
	originalGame.hand[thisPlayer][2] = copper; // cost 0
	originalGame.hand[thisPlayer][3] = council_room; // cost 5
	originalGame.hand[thisPlayer][4] = gardens; // cost 4
	originalGame.hand[thisPlayer][5] = village; // cost 3
	originalGame.hand[thisPlayer][0] = salvager; 
	originalGame.handCount[0] = 7;
	handPos = 0;
	choice1 = 1;
	choiceVal = 2;
	
	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(salvager, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// hand count should be -2 of original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("-2 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// played cards should increase by 1
	// assert that the above is true
	playedCardComp = assertTrue(testGame.playedCardCount, 
		originalGame.playedCardCount + 1);
	
	// print result
	printResults("+1 played cards", playedCardComp);
	if(playedCardComp == 0)
	{
		printf("     played count: %i, expected: %i\n", testGame.playedCardCount, 
			originalGame.playedCardCount + 1);	
	}
	
	// coin count should increase by cost of choice card
	// assert that the above is true
	coinCountComp = assertTrue(testGame.coins, originalGame.coins + choiceVal);
	
	printResults("+cost of choice card added to coin count", coinCountComp);
	if(coinCountComp == 0)
	{
		printf("        coin count: %i, expected: %i\n", testGame.coins, 
			originalGame.coins + choiceVal);
	}
	
	// buys should increase by 1
	buyComp = assertTrue(testGame.numBuys, originalGame.numBuys + buyIncrease);
	
	// print results
	printResults("+1 buy count", buyComp);
	if(buyComp == 0)
	{
		printf("     buy count: %i, expected: %i\n", testGame.numBuys, 
			originalGame.numBuys + buyIncrease);    
	}
	
	// The states of other players should not change. 
	// Check hand, deck of other players
	// Check hand
	for (i=0; i < originalGame.handCount[1]; i++)
	{
		// compare hands
		if(originalGame.hand[1][i] != testGame.hand[1][i])
		{
			// this player had a change in their hand
			player1HandMatch = 0;
			break;
		}
	}
	
	// check deck
	for (i=0; i < originalGame.deckCount[1]; i++)
	{
		// compare decks
		if(originalGame.deck[1][i] != testGame.deck[1][i])
		{
			// this player had a change in their hand
			player1DeckMatch = 0;
			break;
		}
	}
	

	
	// Assert that the other player's hand did not change
	player1HandComp = assertTrue(player1HandMatch, 1);
	
	// print result
	printResults("player 1's hand unchanged", player1HandComp);
	
	// Assert that the other player's deck did not change
	player1DeckComp = assertTrue(player1DeckMatch, 1);
	
	// print result
	printResults("player 1's deck unchanged", player1DeckComp);
	
	// Player 2
	// Check hand
	for (i=0; i < originalGame.handCount[2]; i++)
	{
		// compare hands
		if(originalGame.hand[2][i] != testGame.hand[2][i])
		{
			// this player had a change in their hand
			player2HandMatch = 0;
			break;
		}
	}
	
	// Check deck
	for (i=0; i < originalGame.deckCount[2]; i++)
	{
		// compare decks
		if(originalGame.deck[2][i] != testGame.deck[2][i])
		{
			// this player had a change in their hand
			player2DeckMatch = 0;
			break;
		}
	}
	
	// Assert that the other player's hand did not change
	player2HandComp = assertTrue(player2HandMatch, 1);
	
	// print result
	printResults("player 2's hand unchanged", player2HandComp);
	
	// Assert that the other player's deck did not change
	player2DeckComp = assertTrue(player2DeckMatch, 1);
	
	// print result
	printResults("player 2's deck unchanged", player2DeckComp);
	
	// Player 3
	// Check hand
	for (i=0; i < originalGame.handCount[3]; i++)
	{
		// compare hands
		if(originalGame.hand[3][i] != testGame.hand[3][i])
		{
			// this player had a change in their hand
			player3HandMatch = 0;
			break;
		}
	}
	
	// Check deck
	for (i=0; i < originalGame.deckCount[3]; i++)
	{
		// compare decks
		if(originalGame.deck[3][i] != testGame.deck[3][i])
		{
			// this player had a change in their hand
			player3DeckMatch = 0;
			break;
		}
	}
	
	// Assert that the other player's hand did not change
	player3HandComp = assertTrue(player3HandMatch, 1);
	
	// print result
	printResults("player 3's hand unchanged", player3HandComp);
	
	// Assert that the other player's deck did not change
	player3DeckComp = assertTrue(player3DeckMatch, 1);
	
	// print result
	printResults("player 3's deck unchanged", player3DeckComp);
	
	
	// Salvager should not be in hand
	for(i = 0; i < testGame.handCount[thisPlayer]; i++)
	{
		if(testGame.hand[thisPlayer][i] == salvager)
		{
			cardFound = 1;
			handPos = i;
		}
	}
	
	if(cardFound)
	{
		printResults("salvager not in hand", 0);
	}
	else
	{
		printResults("salvager not in hand", 1);
	}
	

	// kingdom and victory cards should not change
	// kingdom cards
	for(i = 0; i < sizeof(k); i++)
	{
		// if the kingdom cards in the test are different from 
		//those in the original
		if(originalGame.supplyCount[k[i]] != testGame.supplyCount[k[i]])
		{
			printf("kingdom card %i is different at %i\n", k[i], i);
			kingdomMatch = 0;
			
			break;
		}
	}
	
	// assert no change in kingdom cards
	kingdomComp = assertTrue(kingdomMatch, 1);
	
	printResults("kingdom cards unchanged", kingdomComp);
	
	// victory cards
	for(i = estate; i <= province; i++)
	{
		// if the victory cards in the test are different from 
		//those in the original
		if(originalGame.supplyCount[i] != testGame.supplyCount[i])
		{
			printf("victory card %i is different\n", i);
			victoryMatch = 0;
			
			break;
		}
	}
	
	// assert no change in victory cards
	victoryComp = assertTrue(victoryMatch, 1);
	
	printResults("victory cards unchanged", victoryComp);
	
	printf("---------- Testing for %s complete. ----------\n", TESTCARD);
	
	return 0;
}

