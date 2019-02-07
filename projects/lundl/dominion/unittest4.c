/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 3
 * Description: This is a unit test for the getWinners() function in dominion.c.
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
	printf("isGameOver(): FAIL %s\n", testCase);
    }
    else
    {
	printf("isGameOver(): PASS %s\n", testCase);
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
 * Name: testIsGameOver()
 * Parameters: none
 * Description: This unit test proves that after calling isGameOver with a
 * 	various game-ending supply counts, the game is over.
 * Return Value: none
 * ***************************************************************************/

void testIsGameOver()
{
    printf("\n\nUNIT TESTS FOR ISGAMEOVER() FUNCTION\n");

    // Initialize a gameState struct with values we need for this test
    struct gameState* testGame = newGame();

    // loop through cards to set number counts
    int i;
    for(i = curse; i <= treasure_map; i++)
    {
	testGame->supplyCount[i] = 25;
    }

    /* Test Case 1: all cards have count of 25 
     * We expect isGameOver to return 0. */

    printf("\nisGameOver() Test Case 1\n");

   // Pass this gameState struct to isGameOver()
    int returnVal = isGameOver(testGame);

    // Check the restults of this test case
    char* testCase1 = "isGameOver with all cards at count 25";

    // Assert that the returnval is 0
    if(assertTrue(0, 0, returnVal, 0))
    {
	printResults(testCase1, 1);
    }
    else
    {
	printResults(testCase1, 0);
    }


    /* Test Case 2: province count is 0, all other cards 25 
     * We expect isGameOver to return 1. */

    testGame->supplyCount[province] = 0;
    printf("\nisGameOver() Test Case 2\n");

    // Pass this gameState struct to isGameOver()
    returnVal = isGameOver(testGame);

    // Check the restults of this test case
    char* testCase2 = "isGameOver with province count 0 and other cards 25";

    // Assert that the returnval is 1
    if(assertTrue(0, 0, returnVal, 1))
    {
	printResults(testCase2, 1);
    }
    else
    {
	printResults(testCase2, 0);
    }

    /* Test Case 3: three cards have count of 0 
     * We expect isGameOver to return 1. */

    testGame->supplyCount[province] = 25;
    testGame->supplyCount[baron] = 0;
    testGame->supplyCount[gardens] = 0;
    testGame->supplyCount[adventurer] = 0;
 
    printf("\nisGameOver() Test Case 3\n");

    // Pass this gameState struct to isGameOver()
    returnVal = isGameOver(testGame);

    // Check the restults of this test case
    char* testCase3 = "isGameOver with three card counts of 0, all others 25";

    // Assert that the returnval is 1
    if(assertTrue(0, 0, returnVal, 1))
    {
	printResults(testCase3, 1);
    }
    else
    {
	printResults(testCase3, 0);
    }


    /* Test Case 4: two cards have count of 0 
     * We expect isGameOver to return 0. */

    testGame->supplyCount[baron] = 25;
    testGame->supplyCount[gardens] = 25;
    testGame->supplyCount[adventurer] = 0;
 
    printf("\nisGameOver() Test Case 4\n");

    // Pass this gameState struct to isGameOver()
    returnVal = isGameOver(testGame);

    // Check the restults of this test case
    char* testCase4 = "isGameOver with two card counts of 0, all others 25";

    // Assert that the returnval is 0
    if(assertTrue(0, 0, returnVal, 0))
    {
	printResults(testCase4, 1);
    }
    else
    {
	printResults(testCase4, 0);
    }

    /* Test Case 5: province has a count of 1, other cards have count of 25 
     * We expect isGameOver to return 0. */

    testGame->supplyCount[province] = 1;
    testGame->supplyCount[adventurer] = 25;
 
    printf("\nisGameOver() Test Case 5\n");

    // Pass this gameState struct to isGameOver()
    returnVal = isGameOver(testGame);

    // Check the restults of this test case
    char* testCase5 = "isGameOver with province count of 1, all others 25";

    // Assert that the returnval is 0
    if(assertTrue(0, 0, returnVal, 0))
    {
	printResults(testCase5, 1);
    }
    else
    {
	printResults(testCase5, 0);
    }

    /* Test Case 6: province has a count of 0, three others have a count of 0, all other cards have count of 25 
     * We expect isGameOver to return 1. */

    testGame->supplyCount[province] = 0;
    testGame->supplyCount[smithy] = 0;
    testGame->supplyCount[mine] = 0;
    testGame->supplyCount[council_room] = 0;

    printf("\nisGameOver() Test Case 6\n");

    // Pass this gameState struct to isGameOver()
    returnVal = isGameOver(testGame);

    // Check the restults of this test case
    char* testCase6 = "isGameOver with province count of 0, three others count 0, all others 25";

    // Assert that the returnval is 1
    if(assertTrue(0, 0, returnVal, 1))
    {
	printResults(testCase6, 1);
    }
    else
    {
	printResults(testCase6, 0);
    }

 
    /* Test Case 7: all cards have count of 0 
     * We expect isGameOver to return 1. */

    // loop through cards to set number counts
    for(i = curse; i <= treasure_map; i++)
    {
	testGame->supplyCount[i] = 0;
    }


    printf("\nisGameOver() Test Case 7\n");

    // Pass this gameState struct to isGameOver()
    returnVal = isGameOver(testGame);

    // Check the restults of this test case
    char* testCase7 = "all cards have count 0";

    // Assert that the returnval is 1
    if(assertTrue(0, 0, returnVal, 1))
    {
	printResults(testCase7, 1);
    }
    else
    {
	printResults(testCase7, 0);
    }
 
    /* Test Case 8: province has count of -1, all other cards have count of 25 
     * We expect isGameOver to return 1. */

    // loop through cards to set number counts
    for(i = curse; i <= treasure_map; i++)
    {
	testGame->supplyCount[i] = 25;
    }

    testGame->supplyCount[province] = -1;

    printf("\nisGameOver() Test Case 8\n");

    // Pass this gameState struct to isGameOver()
    returnVal = isGameOver(testGame);

    // Check the restults of this test case
    char* testCase8 = "provice count -1, all other cards have count 25";

    // Assert that the returnval is 1
    if(assertTrue(0, 0, returnVal, 1))
    {
	printResults(testCase8, 1);
    }
    else
    {
	printResults(testCase8, 0);
    }
 
    /* Test Case 9: three cards have count of -1, all other cards have count of 25 
     * We expect isGameOver to return 1. */

    // loop through cards to set number counts
    for(i = curse; i <= treasure_map; i++)
    {
	testGame->supplyCount[i] = 25;
    }

    testGame->supplyCount[village] = -1;
    testGame->supplyCount[treasure_map] = -1;
    testGame->supplyCount[mine] = -1;


    printf("\nisGameOver() Test Case 9\n");

    // Pass this gameState struct to isGameOver()
    returnVal = isGameOver(testGame);

    // Check the restults of this test case
    char* testCase9 = "three cards have count -1, all other cards have count 25";

    // Assert that the returnval is 1
    if(assertTrue(0, 0, returnVal, 1))
    {
	printResults(testCase9, 1);
    }
    else
    {
	printResults(testCase9, 0);
    }



}

/******************************************************************************
 * Description: This is the main function. It calls testShuffle().
 * ***************************************************************************/

int main(int argc, char *argv[])
{
    testIsGameOver();
    return 0;
}
