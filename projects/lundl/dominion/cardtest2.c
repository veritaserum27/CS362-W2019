/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 3
 * Description: This is a unit test for the card adventurer in dominion.c.
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

#define TESTCARD "adventurer"
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
	printf("    adventurer: FAIL %s\n", testCase);
    }
    else
    {
	printf("    adventurer: PASS %s\n", testCase);
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
    int newCards = 2; // adventurer should return 2 new treasure cards
	int treasureCardsHand = 0; // update with actual treasure cards in hand
	int handCountComparison = 0; // 1 if handcount matches expected value
	int discarded = 1; // the card played will be discarded
	int deckCountComparision = 0; // 1 if deckCount matches expected value
    
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

    // This the the state of the game that will be sent to adventurer
    struct gameState testGame;
	
	// This is the state of the game that will be used to preserve the original state
	struct gameState originalGame;
	
	// Kingdom cards in play
	int k[10] = {smithy, embargo, village, minion, mine, cutpurse, sea_hag,
		tribute, baron, council_room};
	
	// initialize game state and player cards
	initializeGame(numPlayers, k, seed, &originalGame); 
    
	// Put adventurer in the last hand position for this player
	//int originalCard = originalGame.hand[thisPlayer]
		//[originalGame.handCount[thisPlayer]-1]; // save original card
	originalGame.hand[thisPlayer][originalGame.handCount[thisPlayer] - 1] = adventurer;
	handPos = originalGame.handCount[thisPlayer] - 1;
	
	printf("---------- Testing Card: %s ----------\n", TESTCARD);
	
	// ----- Test 1: hand count of 5, adventurer in pos 4, 2 players -----
	printf("-----Test 1: hand count of 5, adventurer in pos 4, 2 players-----\n");
	printf("-----Deck holds 2 estates and 3 coppers-----\n");

	
	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// hand count should be 2 - 1 more than original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("+1 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// deck count should be <= original deck count - 2
	if(testGame.deckCount[thisPlayer] <=
		originalGame.deckCount[thisPlayer] - newCards)
	{
		// assert that the above is true
		deckCountComparision = 1;
	}
	
	// print result
	printResults("deck count reduced by 2 or more cards", deckCountComparision);
	if(deckCountComparision == 0)
	{
		printf("        deck count: %i, expected: <=%i\n", 
			testGame.deckCount[thisPlayer], originalGame.deckCount[thisPlayer] 
			- newCards);	
	}
	
	// Count the new treasure cards in this player's handfor (i=0; i < originalGame.handCount[1]; i++)
	for(i=0; i < testGame.handCount[0]; i++)
	{
		// compare hands
		if(originalGame.hand[thisPlayer][i] != testGame.hand[0][i])
		{
			// this is a new card
			// if it is a treasure card
			if((testGame.hand[thisPlayer][i] == copper) ||
			(testGame.hand[thisPlayer][i] == silver) ||
			(testGame.hand[thisPlayer][i] == gold))
			{
				// increment the count
				treasureCardsHand++;
			}
		}
	}
	
	// New cards that are treasure cards should be exactly 2
	printResults("+2 treasure cards", assertTrue(treasureCardsHand, 2));
	
	if(!assertTrue(treasureCardsHand, 2))
	{
		printf("        new treasure card count: %i, expected: 2\n", treasureCardsHand);
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
	
	// adventurer should no longer be in this player's hand at handPos
	if(testGame.hand[thisPlayer][handPos] == adventurer)
	{
		// print result
		printResults("adventurer not in hand", 0);
	}
	else
	{
		// print result
		printResults("adventurer not in hand", 1);
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
	
	// ----- Test 2: hand count of 5, adventurer in pos 4, 2 players -----
	printf("\n-----Test 2: hand count of 5, adventurer in pos 4, 2 players-----\n");
	printf("-----Deck holds 2 silvers and 3 coppers-----\n");

    // Set deck to hold silvers where the estate cards are now
	for(i = 0; i < originalGame.deckCount[thisPlayer]; i++)
	{
		if(originalGame.deck[thisPlayer][i] == estate)
		{
			originalGame.deck[thisPlayer][i] = silver;
		}
	}


	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	
	// hand count should be 2 - 1 more than original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("+1 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// deck count should be <= original deck count - 2
	if(testGame.deckCount[thisPlayer] <=
		originalGame.deckCount[thisPlayer] - newCards)
	{
		// assert that the above is true
		deckCountComparision = 1;
	}
	
	// print result
	printResults("deck count reduced by 2 or more cards", deckCountComparision);
	if(deckCountComparision == 0)
	{
		printf("        deck count: %i, expected: <=%i\n", 
			testGame.deckCount[thisPlayer], originalGame.deckCount[thisPlayer] 
			- newCards);	
	}
	
	// Count the new treasure cards in this player's handfor (i=0; i < originalGame.handCount[1]; i++)
	treasureCardsHand = 0;
    for(i=0; i < testGame.handCount[0]; i++)
	{
		// compare hands
		if(originalGame.hand[thisPlayer][i] != testGame.hand[0][i])
		{
			// this is a new card
			// if it is a treasure card
			if((testGame.hand[thisPlayer][i] == copper) ||
			(testGame.hand[thisPlayer][i] == silver) ||
			(testGame.hand[thisPlayer][i] == gold))
			{
				// increment the count
				treasureCardsHand++;
			}
		}
	}
	
	// New cards that are treasure cards should be exactly 2
	printResults("+2 treasure cards", assertTrue(treasureCardsHand, 2));
	
	if(!assertTrue(treasureCardsHand, 2))
	{
		printf("        new treasure card count: %i, expected: 2\n", treasureCardsHand);
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
	
	// adventurer should no longer be in this player's hand at handPos
	if(testGame.hand[thisPlayer][handPos] == adventurer)
	{
		// print result
		printResults("adventurer not in hand", 0);
	}
	else
	{
		// print result
		printResults("adventurer not in hand", 1);
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
	
	// ----- Test 3: hand count of 5, adventurer in pos 4, 2 players -----
	printf("\n-----Test 3: hand count of 5, adventurer in pos 4, 2 players-----\n");
	printf("-----Deck holds 2 silvers and 3 estates-----\n");

    // Set deck to hold 2 silvers and 3 estates
	originalGame.deck[thisPlayer][0] = silver;
	originalGame.deck[thisPlayer][1] = silver;
	originalGame.deck[thisPlayer][2] = estate;
	originalGame.deck[thisPlayer][3] = estate;
	originalGame.deck[thisPlayer][4] = estate;
	

	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	
	// hand count should be 2 - 1 more than original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("+1 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// deck count should be <= original deck count - 2
	if(testGame.deckCount[thisPlayer] <=
		originalGame.deckCount[thisPlayer] - newCards)
	{
		// assert that the above is true
		deckCountComparision = 1;
	}
	
	// print result
	printResults("deck count reduced by 2 or more cards", deckCountComparision);
	if(deckCountComparision == 0)
	{
		printf("        deck count: %i, expected: <=%i\n", 
			testGame.deckCount[thisPlayer], originalGame.deckCount[thisPlayer] 
			- newCards);	
	}
	
	// Count the new treasure cards in this player's handfor (i=0; i < originalGame.handCount[1]; i++)
	treasureCardsHand = 0;
    for(i=0; i < testGame.handCount[0]; i++)
	{
		// compare hands
		if(originalGame.hand[thisPlayer][i] != testGame.hand[0][i])
		{
			// this is a new card
			// if it is a treasure card
			if((testGame.hand[thisPlayer][i] == copper) ||
			(testGame.hand[thisPlayer][i] == silver) ||
			(testGame.hand[thisPlayer][i] == gold))
			{
				// increment the count
				treasureCardsHand++;
			}
		}
	}
	
	// New cards that are treasure cards should be exactly 2
	printResults("+2 treasure cards", assertTrue(treasureCardsHand, 2));
	
	if(!assertTrue(treasureCardsHand, 2))
	{
		printf("        new treasure card count: %i, expected: 2\n", treasureCardsHand);
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
	
	// adventurer should no longer be in this player's hand at handPos
	if(testGame.hand[thisPlayer][handPos] == adventurer)
	{
		// print result
		printResults("adventurer not in hand", 0);
	}
	else
	{
		// print result
		printResults("adventurer not in hand", 1);
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
	
	// ----- Test 4: hand count of 5, adventurer in pos 4, 2 players -----
	printf("\n-----Test 4: hand count of 5, adventurer in pos 4, 2 players-----\n");
	printf("-----Deck holds 2 silvers-----\n");

    // Set deck to hold 2 silvers
	originalGame.deckCount[thisPlayer] = 2;
	
	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	
	// hand count should be 2 - 1 more than original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("+1 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// deck count should be <= original deck count - 2
	if(testGame.deckCount[thisPlayer] <=
		originalGame.deckCount[thisPlayer] - newCards)
	{
		// assert that the above is true
		deckCountComparision = 1;
	}
	
	// print result
	printResults("deck count reduced by 2 or more cards", deckCountComparision);
	if(deckCountComparision == 0)
	{
		printf("        deck count: %i, expected: <=%i\n", 
			testGame.deckCount[thisPlayer], originalGame.deckCount[thisPlayer] 
			- newCards);	
	}
	
	// Count the new treasure cards in this player's handfor (i=0; i < originalGame.handCount[1]; i++)
	treasureCardsHand = 0;
    for(i=0; i < testGame.handCount[0]; i++)
	{
		// compare hands
		if(originalGame.hand[thisPlayer][i] != testGame.hand[0][i])
		{
			// this is a new card
			// if it is a treasure card
			if((testGame.hand[thisPlayer][i] == copper) ||
			(testGame.hand[thisPlayer][i] == silver) ||
			(testGame.hand[thisPlayer][i] == gold))
			{
				// increment the count
				treasureCardsHand++;
			}
		}
	}
	
	// New cards that are treasure cards should be exactly 2
	printResults("+2 treasure cards", assertTrue(treasureCardsHand, 2));
	
	if(!assertTrue(treasureCardsHand, 2))
	{
		printf("        new treasure card count: %i, expected: 2\n", treasureCardsHand);
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
	
	// adventurer should no longer be in this player's hand at handPos
	if(testGame.hand[thisPlayer][handPos] == adventurer)
	{
		// print result
		printResults("adventurer not in hand", 0);
	}
	else
	{
		// print result
		printResults("adventurer not in hand", 1);
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
	
	// ----- Test 5: hand count of 5, adventurer in pos 4, 2 players -----
	printf("\n-----Test 5: hand count of 5, adventurer in pos 4, 2 players-----\n");
	printf("-----Deck holds 2 coppers-----\n");

    // Set deck to hold 2 coppers
	originalGame.deck[thisPlayer][0] = copper;
	originalGame.deck[thisPlayer][1] = copper;
	originalGame.deckCount[thisPlayer] = 2;
	
	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	
	// hand count should be 2 - 1 more than original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("+1 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// deck count should be <= original deck count - 2
	if(testGame.deckCount[thisPlayer] <=
		originalGame.deckCount[thisPlayer] - newCards)
	{
		// assert that the above is true
		deckCountComparision = 1;
	}
	
	// print result
	printResults("deck count reduced by 2 or more cards", deckCountComparision);
	if(deckCountComparision == 0)
	{
		printf("        deck count: %i, expected: <=%i\n", 
			testGame.deckCount[thisPlayer], originalGame.deckCount[thisPlayer] 
			- newCards);	
	}
	
	// Count the new treasure cards in this player's handfor (i=0; i < originalGame.handCount[1]; i++)
	treasureCardsHand = 0;
    for(i=0; i < testGame.handCount[0]; i++)
	{
		// compare hands
		if(originalGame.hand[thisPlayer][i] != testGame.hand[0][i])
		{
			// this is a new card
			// if it is a treasure card
			if((testGame.hand[thisPlayer][i] == copper) ||
			(testGame.hand[thisPlayer][i] == silver) ||
			(testGame.hand[thisPlayer][i] == gold))
			{
				// increment the count
				treasureCardsHand++;
			}
		}
	}
	
	// New cards that are treasure cards should be exactly 2
	printResults("+2 treasure cards", assertTrue(treasureCardsHand, 2));
	
	if(!assertTrue(treasureCardsHand, 2))
	{
		printf("        new treasure card count: %i, expected: 2\n", treasureCardsHand);
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
	
	// adventurer should no longer be in this player's hand at handPos
	if(testGame.hand[thisPlayer][handPos] == adventurer)
	{
		// print result
		printResults("adventurer not in hand", 0);
	}
	else
	{
		// print result
		printResults("adventurer not in hand", 1);
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
	
	// ----- Test 6: hand count of 5, adventurer in pos 4, 2 players -----
	printf("\n-----Test 6: hand count of 5, adventurer in pos 4, 2 players-----\n");
	printf("-----Deck holds 2 gold-----\n");

    // Set deck to hold 2 gold
	originalGame.deck[thisPlayer][0] = gold;
	originalGame.deck[thisPlayer][1] = gold;
	originalGame.deckCount[thisPlayer] = 2;
	

	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	
	// hand count should be 2 - 1 more than original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("+1 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// deck count should be <= original deck count - 2
	if(testGame.deckCount[thisPlayer] <=
		originalGame.deckCount[thisPlayer] - newCards)
	{
		// assert that the above is true
		deckCountComparision = 1;
	}
	
	// print result
	printResults("deck count reduced by 2 or more cards", deckCountComparision);
	if(deckCountComparision == 0)
	{
		printf("        deck count: %i, expected: <=%i\n", 
			testGame.deckCount[thisPlayer], originalGame.deckCount[thisPlayer] 
			- newCards);	
	}
	
	// Count the new treasure cards in this player's handfor (i=0; i < originalGame.handCount[1]; i++)
	treasureCardsHand = 0;
    for(i=0; i < testGame.handCount[0]; i++)
	{
		// compare hands
		if(originalGame.hand[thisPlayer][i] != testGame.hand[0][i])
		{
			// this is a new card
			// if it is a treasure card
			if((testGame.hand[thisPlayer][i] == copper) ||
			(testGame.hand[thisPlayer][i] == silver) ||
			(testGame.hand[thisPlayer][i] == gold))
			{
				// increment the count
				treasureCardsHand++;
			}
		}
	}
	
	// New cards that are treasure cards should be exactly 2
	printResults("+2 treasure cards", assertTrue(treasureCardsHand, 2));
	
	if(!assertTrue(treasureCardsHand, 2))
	{
		printf("        new treasure card count: %i, expected: 2\n", treasureCardsHand);
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

	
	// adventurer should no longer be in this player's hand at handPos
	if(testGame.hand[thisPlayer][handPos] == adventurer)
	{
		// print result
		printResults("adventurer not in hand", 0);
	}
	else
	{
		// print result
		printResults("adventurer not in hand", 1);
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
	
	// ----- Test 7: hand count of 5, adventurer in pos 4, 2 players -----
	printf("\n-----Test 7: hand count of 5, adventurer in pos 4, 3 players-----\n");
	printf("-----Deck holds 2 gold-----\n");
	
	// reinitialize game for 3 players
	numPlayers = 3;
	initializeGame(numPlayers, k, seed, &originalGame); 
	
    // Set deck to hold 2 gold
	originalGame.deck[thisPlayer][0] = gold;
	originalGame.deck[thisPlayer][1] = gold;
	originalGame.deckCount[thisPlayer] = 2;
	

	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	
	// hand count should be 2 - 1 more than original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("+1 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// deck count should be <= original deck count - 2
	if(testGame.deckCount[thisPlayer] <=
		originalGame.deckCount[thisPlayer] - newCards)
	{
		// assert that the above is true
		deckCountComparision = 1;
	}
	
	// print result
	printResults("deck count reduced by 2 or more cards", deckCountComparision);
	if(deckCountComparision == 0)
	{
		printf("        deck count: %i, expected: <=%i\n", 
			testGame.deckCount[thisPlayer], originalGame.deckCount[thisPlayer] 
			- newCards);	
	}
	
	// Count the new treasure cards in this player's handfor (i=0; i < originalGame.handCount[1]; i++)
	treasureCardsHand = 0;
    for(i=0; i < testGame.handCount[0]; i++)
	{
		// compare hands
		if(originalGame.hand[thisPlayer][i] != testGame.hand[0][i])
		{
			// this is a new card
			// if it is a treasure card
			if((testGame.hand[thisPlayer][i] == copper) ||
			(testGame.hand[thisPlayer][i] == silver) ||
			(testGame.hand[thisPlayer][i] == gold))
			{
				// increment the count
				treasureCardsHand++;
			}
		}
	}
	
	// New cards that are treasure cards should be exactly 2
	printResults("+2 treasure cards", assertTrue(treasureCardsHand, 2));
	
	if(!assertTrue(treasureCardsHand, 2))
	{
		printf("        new treasure card count: %i, expected: 2\n", treasureCardsHand);
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
	
	
	
	// adventurer should no longer be in this player's hand at handPos
	if(testGame.hand[thisPlayer][handPos] == adventurer)
	{
		// print result
		printResults("adventurer not in hand", 0);
	}
	else
	{
		// print result
		printResults("adventurer not in hand", 1);
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
	
	
	// ----- Test 8: hand count of 5, adventurer in pos 4, 2 players -----
	printf("\n-----Test 8: hand count of 5, adventurer in pos 4, 4 players-----\n");
	printf("-----Deck holds 2 gold-----\n");
	
	// reinitialize game for 3 players
	numPlayers = 4;
	initializeGame(numPlayers, k, seed, &originalGame); 
	
    // Set deck to hold 2 gold
	originalGame.deck[thisPlayer][0] = gold;
	originalGame.deck[thisPlayer][1] = gold;
	originalGame.deckCount[thisPlayer] = 2;
	

	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	
	// hand count should be 2 - 1 more than original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("+1 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// deck count should be <= original deck count - 2
	if(testGame.deckCount[thisPlayer] <=
		originalGame.deckCount[thisPlayer] - newCards)
	{
		// assert that the above is true
		deckCountComparision = 1;
	}
	
	// print result
	printResults("deck count reduced by 2 or more cards", deckCountComparision);
	if(deckCountComparision == 0)
	{
		printf("        deck count: %i, expected: <=%i\n", 
			testGame.deckCount[thisPlayer], originalGame.deckCount[thisPlayer] 
			- newCards);	
	}
	
	// Count the new treasure cards in this player's handfor (i=0; i < originalGame.handCount[1]; i++)
	treasureCardsHand = 0;
    for(i=0; i < testGame.handCount[0]; i++)
	{
		// compare hands
		if(originalGame.hand[thisPlayer][i] != testGame.hand[0][i])
		{
			// this is a new card
			// if it is a treasure card
			if((testGame.hand[thisPlayer][i] == copper) ||
			(testGame.hand[thisPlayer][i] == silver) ||
			(testGame.hand[thisPlayer][i] == gold))
			{
				// increment the count
				treasureCardsHand++;
			}
		}
	}
	
	// New cards that are treasure cards should be exactly 2
	printResults("+2 treasure cards", assertTrue(treasureCardsHand, 2));
	
	if(!assertTrue(treasureCardsHand, 2))
	{
		printf("        new treasure card count: %i, expected: 2\n", treasureCardsHand);
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
	
	
	// adventurer should no longer be in this player's hand at handPos
	if(testGame.hand[thisPlayer][handPos] == adventurer)
	{
		// print result
		printResults("adventurer not in hand", 0);
	}
	else
	{
		// print result
		printResults("adventurer not in hand", 1);
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
	
	// ----- Test 9: hand count of 5, adventurer in pos 4, 2 players -----
	printf("\n-----Test 9: hand count of 5, adventurer in pos 4, 4 players-----\n");
	printf("-----Deck holds 2 estate (no treasure)-----\n");
	
	// reinitialize game for 3 players
	numPlayers = 4;
	initializeGame(numPlayers, k, seed, &originalGame); 
	
    // Set deck to hold 2 estate
	originalGame.deck[thisPlayer][0] = estate;
	originalGame.deck[thisPlayer][1] = estate;
	originalGame.deckCount[thisPlayer] = 2;
	
	// Copy game into test
	memcpy(&testGame, &originalGame, sizeof(struct gameState));
	
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	
	// hand count should be 2 - 1 more than original hand count
	// assert that the above is true
	handCountComparison = assertTrue(testGame.handCount[thisPlayer], 
		originalGame.handCount[thisPlayer] + newCards - discarded);
		
	// Print result
	printResults("+1 cards in hand count", handCountComparison);
	if(handCountComparison == 0)
	{
		printf("        hand count: %i, expected: %i\n", 
			testGame.handCount[thisPlayer], originalGame.handCount[thisPlayer] 
			+ newCards - discarded);	
	}
	
	// deck count should be <= original deck count - 2
	if(testGame.deckCount[thisPlayer] <=
		originalGame.deckCount[thisPlayer] - newCards)
	{
		// assert that the above is true
		deckCountComparision = 1;
	}
	
	// print result
	printResults("deck count reduced by 2 or more cards", deckCountComparision);
	if(deckCountComparision == 0)
	{
		printf("        deck count: %i, expected: <=%i\n", 
			testGame.deckCount[thisPlayer], originalGame.deckCount[thisPlayer] 
			- newCards);	
	}
	
	// Count the new treasure cards in this player's handfor (i=0; i < originalGame.handCount[1]; i++)
	treasureCardsHand = 0;
    for(i=0; i < testGame.handCount[0]; i++)
	{
		// compare hands
		if(originalGame.hand[thisPlayer][i] != testGame.hand[0][i])
		{
			// this is a new card
			// if it is a treasure card
			if((testGame.hand[thisPlayer][i] == copper) ||
			(testGame.hand[thisPlayer][i] == silver) ||
			(testGame.hand[thisPlayer][i] == gold))
			{
				// increment the count
				treasureCardsHand++;
			}
		}
	}
	
	// New cards that are treasure cards should be exactly 2
	printResults("+2 treasure cards", assertTrue(treasureCardsHand, 2));
	
	if(!assertTrue(treasureCardsHand, 2))
	{
		printf("        new treasure card count: %i, expected: 2\n", treasureCardsHand);
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
	
	
	// adventurer should no longer be in this player's hand at handPos
	if(testGame.hand[thisPlayer][handPos] == adventurer)
	{
		// print result
		printResults("adventurer not in hand", 0);
	}
	else
	{
		// print result
		printResults("adventurer not in hand", 1);
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

