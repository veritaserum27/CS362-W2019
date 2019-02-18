/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 4
 * Description: This is a random tester for the card village in dominion.c.
 * Citations: The example given in Assignment 3: cardtest4.c
 * 	My cardtest3.c file from Assignment 3
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
	printf("   --village: FAIL %s\n", testCase);
    }
    else
    {
	printf("   --village: PASS %s\n", testCase);
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

/******************************************************************************
* Preconditions: srand() is seeded within main
* Parameters: two ints, one of which marks the low range and the other of which
* 	marks the high range of a random number (inclusive)
* Description: This helper function returns an int within the range of low ..
*	high inclusive.
* Return Value: an int within range
******************************************************************************/
int randomInt(int low, int high)
{
	// Get a random number
	int newRandom = rand();
	//printf("low: %i, high: %i\n", low, high);
	
	// While our random number is outside the range we want
	while ((newRandom > high) || (newRandom < low))
	{
		// If our random number is too big
		if (newRandom > high)
		{
			// make it smaller by modding it by our high range + 1
			newRandom = newRandom % (high + 1);
		}
		else
		{
			// It is too small, increment it
			newRandom++;
		}
	}

	// Return this number that is in range
	return newRandom;
}


/******************************************************************************
* Preconditions: An array of ints of size 10 is declared in main and passed by
*	reference to this function
* Parameters: a pointer to an array of ints, int of the card that must be 
*	included
* Description: This function fills an array of ints with 9 random numbers and 
* 	the card that must be included for a total of ten ints because the game
*	only allows 10 kingdom cards in initializeGame()
* Return Value: none
******************************************************************************/
void fillKingdom(int* kingdomArr, int thisCard)
{
	int i = 1;
	
	// include our target card
	kingdomArr[0] = thisCard;
	
	while (i < 10)
	{
		// get a new card
		int newCard = randomInt(council_room, treasure_map);
		
		// check if it's already in this array
		int j;
		int inArr = 0; // boolean for following check
		
		// check all the cards we've added until this point
		for(j = 1; j < i; j++)
		{
			if (kingdomArr[j] == newCard)
			{
				// this card is already in the array
				inArr = 1;
				break;
			}
		}
		
		// If it's not already in the array, add the new card
		if(inArr == 0)
		{
			kingdomArr[i] = newCard;
			
			// increment i
			i++;
		}
		// otherwise, don't increment i, get a new random card
	}
	
	return;
		
}

/******************************************************************************
* Parameters: gameStruct*, int specifying player
* Description: this sets up a player's deck, deckCount, hand, handCount, 
*	discard, and discardCount
* Return Value: none
******************************************************************************/
void setUpPlayer(struct gameState* state, int player)
{
	int i;
	// get size of deck for this player
	state->deckCount[player] = randomInt(2, MAX_DECK);

	// Get cards curse .. treasure_map for the deck
	for(i = 0; i < state->deckCount[player]; i++)
	{
		// fill deck with cards
		int card = randomInt(curse, treasure_map);
		state->deck[player][i] = card;
	}
	
	// get size of hand for this player (always has at least 1 card so can 
	// hold target card for test)
	state->handCount[player] = randomInt(1, MAX_HAND);
	
	// Get cards curse .. treasure_map for the hand
	for(i = 0; i < state->handCount[player]; i++)
	{
		// fill hand with cards
		state->hand[player][i] = randomInt(curse, treasure_map);
	}
	

	// get size of discard for this player
	state->discardCount[player] = randomInt(0, MAX_DECK);
		
	for(i = 0; i < state->discardCount[player]; i++)
	{
		// fill discard with cards
		state->discard[player][i] = randomInt(curse, treasure_map);
	}
		
}

/******************************************************************************
* Parameters: gameStruct*
* Desription: this function fills the played cards for this state with valid
*	cards
* Return Value: None
******************************************************************************/
void setPlayedCards(struct gameState* state)
{
	// get size of playedCardsCount
	state->playedCardCount = randomInt(0, MAX_DECK);
	
	// Get cards curse .. treasure_map for the played cards
	int i;
	for(i = 0; i < state->playedCardCount; i++)
	{
		// fill played with cards
		state->playedCards[i] = randomInt(curse, treasure_map);
	}
}

/******************************************************************************
* This is the oracle
******************************************************************************/
int main()
{
    int newCards = 1; // village should return 1 new card
	int actionIncrease = 2; // village should increase action by 2
	int handCountComparison = 0; // 1 if handcount matches expected value
	int discarded = 1; // the card played will be discarded
	int actionCountComparison = 0; // 1 if  matches expected value
	int deckCountComparison = 0; // 1 if deckCount matches expected value
	int playedCountComparison = 0; // 1 if playedCardCount matches expected value
	
	int numPlayers; // value randomly assigned
	int thisPlayer; // value randomly assigned
	int handPos; // value randomly assigned
	
	int otherPlayerHandMatch = 1; // 0 if player's hand changes 
	int otherPlayerDeckMatch = 1; // 0 if player's deck changes
	int playerHandComp = 0; // 1 if matches expected value
	int otherPlayerDeckComp = 0; // 1 if matches expected value
	
	int kingdomMatch = 1; // 0 if kingdom cards in states differ
	int victoryMatch = 1; // 0 if victory cards in states differ
	int kingdomComp = 0; // 1 if matches expected value
	int victoryComp = 0; // 1 if matches expected value
	
    int testCount = 1; // this will be incremented

	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int i;
    int seed = 1000; // needed for game initialization
	time_t thisTime;
	int keepTesting = 1; // this is a boolean to track test conditions
	int testCondition = 0; // this is a counter for which conditions we've tested
	
	double running_time = 0; // for total running time
	clock_t start = clock(); // this is the time we start
	
	// Seed random number generator for randomInt 
	srand((unsigned) time(&thisTime));
	 
	// Kingdom cards in play
	int k[10];
	
	// This the the state of the game that will be sent to village
    struct gameState testGame;
	
	// This is the state of the game that will be used to preserve the original state
	struct gameState originalGame;
	
	printf("---------- Randomly Testing Card: %s ----------\n", TESTCARD);
	
	// Run tests until these conditions are tested
	while(keepTesting)
	{
		/* set up test case */
		fillKingdom(&k[0], village);

		// initialize game state and player cards
		initializeGame(numPlayers, k, seed, &originalGame); 
	
		// number of players
		numPlayers = randomInt(2, MAX_PLAYERS);
		originalGame.numPlayers = numPlayers;
    
		// Set the current player
		thisPlayer = randomInt(0, numPlayers - 1);
		originalGame.whoseTurn = thisPlayer;
	
		// Set up decks, hands, and discard for all players
		for (i = 0; i < numPlayers; i++)
		{
			// call function to set up player
			setUpPlayer(&originalGame, i);
		}
		
		// Set played cards
		setPlayedCards(&originalGame);
		
		// Put target card in hand of this player
		if(originalGame.handCount[thisPlayer] > 1)
		{
			handPos = randomInt(0, originalGame.handCount[thisPlayer] - 1);
		}
		else
		{
			handPos = 0;
		}
		
		// replaces whatever was there
		originalGame.hand[thisPlayer][handPos] = village; 
		
		// Set a random number of actions for this player
		originalGame.numActions = randomInt(0, 10); 

		// Print test count, details about this test
		printf("\n  -----Test %i-----\n", testCount);
		
		// Number of players, which player is current
		printf("   Number of Players: %i, Whose Turn: %i\n", 
			originalGame.numPlayers, originalGame.whoseTurn);
		
		// Details about current player
		printf("   Current Player's Deck Count: %i, Starting Action Count: %i\n", 
			originalGame.deckCount[thisPlayer], originalGame.numActions);
		printf("   Current Player's Hand Count: %i, village Position: %i\n",
			originalGame.handCount[thisPlayer], handPos);
			
		// Copy game into test
		memcpy(&testGame, &originalGame, sizeof(struct gameState));
		
		
		if((testCondition == 0) && (originalGame.numPlayers == 2))
		{
			testCondition += 1;
		}
		if((testCondition == 1) && (originalGame.numPlayers == 3))
		{
			testCondition += 1;
		}
		if((testCondition == 2) && (originalGame.numPlayers == MAX_PLAYERS))
		{
			testCondition += 1;
		}
		if((testCondition == 3) && (originalGame.numActions == 1))
		{
			testCondition += 1;
		}
		if((testCondition == 4) && (originalGame.numActions == 2))
		{
			testCondition += 1;
		}
		if((testCondition == 5) && (originalGame.numActions == 5))
		{
			testCondition += 1;
		}
		if((testCondition == 4) && (originalGame.numActions == 7))
		{
			testCondition += 1;
		}
		if((testCondition == 5) && (originalGame.numActions == 8))
		{
			testCondition += 1;
		}
		if((testCondition == 6) && (originalGame.numActions == 10))
		{
			testCondition += 1;
		}
		if((testCondition == 7) && (originalGame.numActions == 0))
		{
			testCondition += 1;
			keepTesting = 0; // This is our last test
		}
		
		// Execute call to cardEffect
		cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
		
		/* Check Results */
		
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
		// played count should be 1 more than original played count
		// assert that the above is true
		playedCountComparison = assertTrue(testGame.playedCardCount, 
			originalGame.playedCardCount + 1);
	
		// print result
		printResults("+1 played card", playedCountComparison);
		if(playedCountComparison == 0)
		{
			printf("     played card count: %i, expected: %i\n", testGame.playedCardCount, 
				originalGame.playedCardCount + 1);	
		}
		
		// deck count should be <= original deck count - 1
		if(testGame.deckCount[thisPlayer] <=
			originalGame.deckCount[thisPlayer] - newCards)
		{
			// assert that the above is true
			deckCountComparison = 1;
		}
		
		// print result
		printResults("deck count reduced by 1 card", deckCountComparison);
		if(deckCountComparison == 0)
		{
			printf("        deck count: %i, expected: <=%i\n", 
				testGame.deckCount[thisPlayer], originalGame.deckCount[thisPlayer] 
				- newCards);	
		}
		
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
		
		// Check states of other players
		printf("\n     ----Other Players----\n");
		int j;
		for(j = 0; j < originalGame.numPlayers; j++)
		{
			// if this is not the current player
			if(j != thisPlayer)
			{
				// Check hand and deck of other players.
				// Check hand
				for (i=0; i < originalGame.handCount[j]; i++)
				{
					// compare hands
					if(originalGame.hand[j][i] != testGame.hand[j][i])
					{
						// this player had a change in their hand
						otherPlayerHandMatch = 0;
						break;
					}
				}
				
				// Check deck
				for (i=0; i < originalGame.deckCount[j]; i++)
				{
					// compare decks
					if(originalGame.deck[j][i] != testGame.deck[j][i])
					{
						// this player had a change in their hand
						otherPlayerDeckMatch = 0;
						break;
					}
				}
				
				printf("         -----Player %i-----\n", j);
				// check state
				playerHandComp = assertTrue(otherPlayerHandMatch, 1);
	
				// print result
				printResults("player's hand unchanged", playerHandComp);
				
				// Assert that the other player's deck did not change
				otherPlayerDeckComp = assertTrue(otherPlayerDeckMatch, 1);
				
				// print result
				printResults("player's deck unchanged", otherPlayerDeckComp);
				
			}
		}
		
		printf("\n     ----Kingdom and Victory Cards----\n");
		// kingdom and victory cards should not change
		// kingdom cards
		for(i = 0; i < 10; i++)
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
		
		printf("\n");

		// Increment test count
		testCount++;
	}
	
	printf("---------- Testing for %s complete. ----------\n", TESTCARD);
	
	// execution time
	clock_t finish = clock();
	running_time += (double)(finish - start)/ CLOCKS_PER_SEC;
	printf("Total running time for %s Random Tester: %f seconds\n\n", TESTCARD, running_time);
	
	return 0;
}

