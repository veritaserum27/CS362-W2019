/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Assignment 3
 * Description: This is a unit test for the getCost() function in dominion.c.
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
	printf("getCost(): FAIL %s\n", testCase);
    }
    else
    {
	printf("getCost(): PASS %s\n", testCase);
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
 * Name: testGetCost()
 * Parameters: none
 * Description: This unit test proves that a call to getCost returns the 
 * 	expected cost value for each Dominion card in the game.
 * Return Value: none
 * ***************************************************************************/

void testGetCost()
{
    /* Test Case 1: curse
     * We expect getCost to return 0 */

    printf("\ngetCost() Test Case 1\n");
    int returnVal = getCost(curse);

    // Check the restults of this test case
    char* testCase1 = "getting cost of curse";

    // Assert that the return value is 0
    if(assertTrue(0, 0, returnVal, 0))
    {
	printResults(testCase1, 1);
    }
    else
    {
	printResults(testCase1, 0);
    }
}

/******************************************************************************
 * Description: This is the main function. It calls testGetCost().
 * ***************************************************************************/

int main(int argc, char *argv[])
{
    testGetCost();
    return 0;
}
