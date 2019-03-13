/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 3
 * Description: This is a unit test for the card village in dominion.c.
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

#define TESTCARD "village"
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
	printf("    village: FAIL %s\n", testCase);
    }
    else
    {
	printf("    village: PASS %s\n", testCase);
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
    int newCards = 1; // village should return 1 new card
	int actionIncrease = 2; // village should increase action by 2
	int handCountComparison = 0; // 1 if handcount matches expected value
	int discarded = 1; // the card played will be discarded
	int actionCountComparison = 0; // 1 if deckCount matches expected value
    
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
	int i;
    int seed = 1000; // needed for game initialization

    // This the the state of the game that will be sent to village
    struct gameState testGame;
	
	// This is the state of the game that will be used to preserve the original state
	struct gameState originalGame;
	
	// Kingdom cards in play
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag,
		tribute, baron, council_room};
	
	// initialize game state and player cards
	initializeGame(numPlayers, k, seed, &originalGame); 
    
	// Put village in the last hand position for this player
	int originalCard = originalGame.hand[thisPlayer]
		[originalGame.handCount[thisPlayer]-1]; // save original card
	originalGame.hand[thisPlayer][originalGame.handCount[thisPlayer] - 1] = village;
	handPos = originalGame.handCount[thisPlayer] - 1;
	
	// What is in current player's hand?
	/*for(i = 0; i < originalGame.handCount[thisPlayer]; i++)
	{
		printf("card at %i: %i\n", i, originalGame.hand[thisPlayer][i]);
	}
	
	// What is in the current player's deck?
	for(j = 0; j < originalGame.deckCount[thisPlayer]; j++)
	{
		printf("card at %i in deck: %i\n", j, originalGame.deck[thisPlayer][j]);
	}*/
	
	printf("---------- Testing Card: %s ----------\n", TESTCARD);
	
	// ----- Test 1: hand count of 5, village in pos 4, 2 players -----
	printf("-----Test 1: hand count of 5, village in pos 4, 2 players-----\n");
	
	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// hand count should be same as original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("+/-0 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// action count should be 2 more than original action count
	// assert that the above is true
	actionCountComparison = assertTrue(testGame.numActions, 
		originalGame.numActions + actionIncrease);
	
	// print result
	printResults("+2 actions", actionCountComparison);
	if(actionCountComparison == 0)
	{
		printf("     action count: %i, expected: %i\n", testGame.numActions, 
			originalGame.numActions + actionIncrease);	
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
	
	// village should no longer be in this player's hand at handPos
	if(testGame.hand[thisPlayer][handPos] == village)
	{
		// print result
		printResults("village not in hand", 0);
	}
	else
	{
		// print result
		printResults("village not in hand", 1);
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
	
	
	// ----- Test 2: hand count of 5, village in pos 0, 2 players -----
	printf("\n-----Test 2: hand count of 5, village in pos 0, 2 players-----\n");
	
	// Put village in the first hand position for this player
	// save what's there now
	int tempCard = originalGame.hand[thisPlayer][0];
	
	// restore original card for this index
	originalGame.hand[thisPlayer][originalGame.handCount[thisPlayer]-1] = originalCard;
	
	// put village at new index
	originalGame.hand[thisPlayer][0] = village;
	handPos = 0;
	
	// save value that was at that index
	originalCard = tempCard;
	
	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// hand count should be same as original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("+/- 0 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// action count should be 2 more than original action count
	// assert that the above is true
	actionCountComparison = assertTrue(testGame.numActions, 
		originalGame.numActions + actionIncrease);
	
	// print result
	printResults("+2 actions", actionCountComparison);
	if(actionCountComparison == 0)
	{
		printf("     action count: %i, expected: %i\n", testGame.numActions, 
			originalGame.numActions + actionIncrease);	
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
	
	// village should no longer be in this player's hand at handPos
	if(testGame.hand[thisPlayer][handPos] == village)
	{
		// print result
		printResults("village not in hand", 0);
	}
	else
	{
		// print result
		printResults("village not in hand", 1);
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
	
	// ----- Test 3: hand count of 5, village in pos 4, 3 players -----
	printf("\n-----Test 3: hand count of 5, village in pos 4, 3 players-----\n");
	
	numPlayers = 3;
	
	// reinitialize game for 3 players
	initializeGame(numPlayers, k, seed, &originalGame); 
	
	// Put village in the last hand position for this player
	originalCard = originalGame.hand[thisPlayer]
		[originalGame.handCount[thisPlayer]-1]; // save original card
	originalGame.hand[thisPlayer][originalGame.handCount[thisPlayer] - 1] = village;
	handPos = originalGame.handCount[thisPlayer] - 1;
	
	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// hand count should be same as original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("+/- 0 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// action count should be 2 more than original action count
	// assert that the above is true
	actionCountComparison = assertTrue(testGame.numActions, 
		originalGame.numActions + actionIncrease);
	
	// print result
	printResults("+2 actions", actionCountComparison);
	if(actionCountComparison == 0)
	{
		printf("     action count: %i, expected: %i\n", testGame.numActions, 
			originalGame.numActions + actionIncrease);	
	}
	
	// The states of other players should not change. 
	// Check hand and deck of other players.
	
	// Player 1
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
	
	
	
	// village should no longer be in this player's hand at handPos
	if(testGame.hand[thisPlayer][handPos] == village)
	{
		// print result
		printResults("village not in hand", 0);
	}
	else
	{
		// print result
		printResults("village not in hand", 1);
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
	
	// ----- Test 4: hand count of 5, village in pos 4, 4 players -----
	printf("\n-----Test 4: hand count of 5, village in pos 4, 4 players-----\n");
	
	numPlayers = 4;
	
	// reinitialize game for 4 players
	initializeGame(numPlayers, k, seed, &originalGame); 
	
	// Put village in the last hand position for this player
	originalCard = originalGame.hand[thisPlayer]
		[originalGame.handCount[thisPlayer]-1]; // save original card
	originalGame.hand[thisPlayer][originalGame.handCount[thisPlayer] - 1] = village;
	handPos = originalGame.handCount[thisPlayer] - 1;
	
	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// hand count should be same as original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("+/- 0 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// action count should be 2 more than original action count
	// assert that the above is true
	actionCountComparison = assertTrue(testGame.numActions, 
		originalGame.numActions + actionIncrease);
	
	// print result
	printResults("+2 actions", actionCountComparison);
	if(actionCountComparison == 0)
	{
		printf("     action count: %i, expected: %i\n", testGame.numActions, 
			originalGame.numActions + actionIncrease);	
	}
	
	// The states of other players should not change. 
	// Check hand and deck of other players.
	
	// Player 1
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
	
	
	
	// village should no longer be in this player's hand at handPos
	if(testGame.hand[thisPlayer][handPos] == village)
	{
		// print result
		printResults("village not in hand", 0);
	}
	else
	{
		// print result
		printResults("village not in hand", 1);
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

