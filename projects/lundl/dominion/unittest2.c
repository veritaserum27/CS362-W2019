/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 3
 * Description: This is a unit test the whoseTurn() function in dominion.c.
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
 * Parameters: a char* holding a string to be printed, an int holding the test
 * 	case number, an int holding a test result.
 * Description: This helper function prints to the console a message indicating
 * 	PASS or FAIL for a given test case. If the assertResult is 0, the test
 * 	failed. Otherwise, it passed.
 * Return Value: none
 * ***************************************************************************/

void printResults(char* testCase, int num, int assertResult)
{
    if(assertResult == 0)
    {
	printf("whoseTurn(): FAIL %s %i\n", testCase, num);
    }
    else
    {
	printf("whoseTurn(): PASS %s %i\n", testCase, num);
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
 * Name: testWhoseTurn()
 * Parameters: none
 * Description: This unit test proves that when a value is assigned to a  
 *	gameStruct object.whoseTurn, that same value is return by a
 *	call to whoseTurn() in dominion.c.
 * Return Value: none
 * ***************************************************************************/

void testWhoseTurn()
{
    // Initialize a gameState struct with values we need for this test
    struct gameState* testGame = newGame();

    /* Test Cases 1 - Max number of players
     * These test cases prove that whoseTurn() returns the player whose
     * turn it is. */ 
    
    // Max number of players, test each player's turn 
    testGame->numPlayers = MAX_PLAYERS;
    
    // message for test result 
    char* testMessage = "whose turn out of MAX_PLAYERS and player";
    int i;

    // track which test case we are on
    int testCaseNum = 1;

    // for each player 0 .. MAX_PLAYERS
    for(i = 0; i < MAX_PLAYERS; i++)
    {
	// print this test case
        printf("\nwhoseTurn() Test Case %i\n", testCaseNum);
 	testCaseNum++;

        // assign i to whoseTurn in the struct   
       	testGame->whoseTurn = i;


        // Call whoseTurn() and assert results match the value we just assigned
	int returnVal = whoseTurn(testGame);
	if(assertTrue(0, 0, returnVal, i))
	{
	    printResults(testMessage, i, 1);
	}
	else
	{
	    printResults(testMessage, i, 0);
	}
    }

    /* Next Batch of test Cases */
    char* testMessage2 = "whose turn out of min players (2) and player";

    testGame->numPlayers = 2;
    for(i = 0; i < 2; i++)
    {
        // Print label for this test case
        printf("\nwhoseTurn() Test Case %i\n", testCaseNum);
 	testCaseNum++;

        // Min number of players, test each player's turn 
    	testGame->whoseTurn = i;

	// Call whoseTurn() and assert results
	int returnVal = whoseTurn(testGame);
	if(assertTrue(0, 0, returnVal, i))
	{
	    printResults(testMessage2, i, 1);
	}
	else
	{
	    printResults(testMessage2, i, 0);
	}
    }

}

/******************************************************************************
 * This it the main function. It calls testWhoseTurn().
 * ***************************************************************************/

int main(int argc, char *argv[])
{
    testWhoseTurn();
    return 0;
}
