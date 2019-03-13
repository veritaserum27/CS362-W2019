/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 4
 * Description: This is a random tester for the card salvager in dominion.c.
 * Citations: The example given in Assignment 3: cardtest4.c
 * 	My cardtest4.c file from Assignment 3
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
	printf("   --salvager: FAIL %s\n", testCase);
    }
    else
    {
	printf("   --salvager: PASS %s\n", testCase);
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
	
	// get size of hand for this player (always has at least 2 cards so can 
	// hold target card for test and have one to trash)
	state->handCount[player] = randomInt(2, MAX_HAND);
	
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
    int newCards = 0; // salvager should return 1 new card
	int handCountComparison = 0; // 1 if handcount matches expected value
	int discarded = 2; // the card played will be discarded, choice will be trashed
	int buyIncrease = 1; // salvager should increase the buys by 1
    int playedCountComparison = 0; // 1 if played count matches expected value
	int coinCountComp = 0; // 1 if coin count matches expected value
	int buyComp = 0; // 1 if buy count matches expected value
	int deckCountComparison = 0; // 1 if deckcount matches expected value
	
	
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
	int choiceVal = 0;
	
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
	
	// This the the state of the game that will be sent to salvager
    struct gameState testGame;
	
	// This is the state of the game that will be used to preserve the original state
	struct gameState originalGame;
	
	printf("---------- Randomly Testing Card: %s ----------\n", TESTCARD);
	
	// Run tests until these conditions are tested
	while(keepTesting)
	{
		/* set up test case */
		fillKingdom(&k[0], salvager);

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
		originalGame.hand[thisPlayer][handPos] = salvager; 
		
		// Select a card from the hand as the "choice" card
		choice1 = randomInt(0, originalGame.handCount[thisPlayer] - 1);
		
		// can't choose salvager card
		while (choice1 == handPos)
		{
			// get a new position for choice card to trash
			choice1 = randomInt(0, originalGame.handCount[thisPlayer] - 1);
		}
		
		// Get the value of this card
		choiceVal = getCost(originalGame.hand[thisPlayer][choice1]);
		
		// get random coin amount
		originalGame.coins = randomInt(0, 50);
		
		// Print test count, details about this test
		printf("\n  -----Test %i-----\n", testCount);
		
		// Number of players, which player is current
		printf("   Number of Players: %i, Whose Turn: %i\n", 
			originalGame.numPlayers, originalGame.whoseTurn);
		
		// Details about current player
		printf("   Current Player's Deck Count: %i, Choice Position: %i\n", 
			originalGame.deckCount[thisPlayer], choice1);
		printf("   Current Player's Hand Count: %i, salvager Position: %i\n",
			originalGame.handCount[thisPlayer], handPos);
		printf("   Current Coin Count: %i, choice card's value: %i\n",
			originalGame.coins, originalGame.hand[thisPlayer][choice1]);

			
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
		if((testCondition == 3) && (choiceVal == 0))
		{
			testCondition += 1;
		}
		if((testCondition == 4) && (choiceVal == 2))
		{
			testCondition += 1;
		}
		if((testCondition == 5) && (choiceVal == 5))
		{
			testCondition += 1;
		}
		if((testCondition == 4) && (choiceVal == 6))
		{
			testCondition += 1;
		}
		if((testCondition == 5) && (choiceVal == 3))
		{
			testCondition += 1;
		}
		if((testCondition == 6) && (choiceVal == 4))
		{
			testCondition += 1;
		}
		if((testCondition == 7) && (choiceVal == 8))
		{
			testCondition += 1;
		}
		if((testCondition == 8) && (choice1 == 0))
		{
			testCondition += 1;
			keepTesting = 0; // This is our last test
		}
		
		// Execute call to cardEffect
		cardEffect(salvager, choice1, choice2, choice3, &testGame, handPos, &bonus);
		
		/* Check Results */		
		
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
		
		// salvager should no longer be in this player's hand at handPos
		if(testGame.hand[thisPlayer][handPos] == salvager)
		{
			// print result
			printResults("salvager not in hand", 0);
		}
		else
		{
			// print result
			printResults("salvager not in hand", 1);
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

