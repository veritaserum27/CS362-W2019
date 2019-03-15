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
    printf("\n\nUNIT TESTS FOR GETCOST() FUNCTION\n");

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

    /* Test Case 2: estate
     * We expect getCost to return 2 */

    printf("\ngetCost() Test Case 2\n");
    returnVal = getCost(estate);

    // Check the restults of this test case
    char* testCase2 = "getting cost of estate";

    // Assert that the return value is 2
    if(assertTrue(0, 0, returnVal, 2))
    {
	printResults(testCase2, 1);
    }
    else
    {
	printResults(testCase2, 0);
    }


    /* Test Case 3: duchy
     * We expect getCost to return 5 */

    printf("\ngetCost() Test Case 3\n");
    returnVal = getCost(duchy);

    // Check the restults of this test case
    char* testCase3 = "getting cost of duchy";

    // Assert that the return value is 5 
    if(assertTrue(0, 0, returnVal, 5))
    {
	printResults(testCase3, 1);
    }
    else
    {
	printResults(testCase3, 0);
    }


    /* Test Case 4: province
     * We expect getCost to return 8 */

    printf("\ngetCost() Test Case 4\n");
    returnVal = getCost(province);

    // Check the restults of this test case
    char* testCase4 = "getting cost of province";

    // Assert that the return value is 8 
    if(assertTrue(0, 0, returnVal, 8))
    {
	printResults(testCase4, 1);
    }
    else
    {
	printResults(testCase4, 0);
    }


    /* Test Case 5: copper
     * We expect getCost to return 0 */

    printf("\ngetCost() Test Case 5\n");
    returnVal = getCost(copper);

    // Check the restults of this test case
    char* testCase5 = "getting cost of copper";

    // Assert that the return value is 0 
    if(assertTrue(0, 0, returnVal, 0))
    {
	printResults(testCase5, 1);
    }
    else
    {
	printResults(testCase5, 0);
    }


    /* Test Case 6: silver
     * We expect getCost to return 3 */

    printf("\ngetCost() Test Case 6\n");
    returnVal = getCost(silver);

    // Check the restults of this test case
    char* testCase6 = "getting cost of silver";

    // Assert that the return value is 3 
    if(assertTrue(0, 0, returnVal, 3))
    {
	printResults(testCase6, 1);
    }
    else
    {
	printResults(testCase6, 0);
    }

  /* Test Case 7: gold
     * We expect getCost to return 6 */

    printf("\ngetCost() Test Case 7\n");
    returnVal = getCost(gold);

    // Check the restults of this test case
    char* testCase7 = "getting cost of gold";

    // Assert that the return value is 6 
    if(assertTrue(0, 0, returnVal, 6))
    {
	printResults(testCase7, 1);
    }
    else
    {
	printResults(testCase7, 0);
    }


  /* Test Case 8: adventurer
     * We expect getCost to return 6 */

    printf("\ngetCost() Test Case 8\n");
    returnVal = getCost(adventurer);

    // Check the restults of this test case
    char* testCase8 = "getting cost of adventurer";

    // Assert that the return value is 6 
    if(assertTrue(0, 0, returnVal, 6))
    {
	printResults(testCase8, 1);
    }
    else
    {
	printResults(testCase8, 0);
    }


  /* Test Case 9: council_room
     * We expect getCost to return 5 */

    printf("\ngetCost() Test Case 9\n");
    returnVal = getCost(council_room);

    // Check the restults of this test case
    char* testCase9 = "getting cost of council_room";

    // Assert that the return value is 5 
    if(assertTrue(0, 0, returnVal, 5))
    {
	printResults(testCase9, 1);
    }
    else
    {
	printResults(testCase9, 0);
    }

  /* Test Case 10: feast
     * We expect getCost to return 4 */

    printf("\ngetCost() Test Case 10\n");
    returnVal = getCost(feast);

    // Check the restults of this test case
    char* testCase10 = "getting cost of feast";

    // Assert that the return value is 4 
    if(assertTrue(0, 0, returnVal, 4))
    {
	printResults(testCase10, 1);
    }
    else
    {
	printResults(testCase10, 0);
    }

  /* Test Case 11: gardens
     * We expect getCost to return 4 */

    printf("\ngetCost() Test Case 11\n");
    returnVal = getCost(gardens);

    // Check the restults of this test case
    char* testCase11 = "getting cost of gardens";

    // Assert that the return value is 4 
    if(assertTrue(0, 0, returnVal, 4))
    {
	printResults(testCase11, 1);
    }
    else
    {
	printResults(testCase11, 0);
    }

  /* Test Case 12: mine
     * We expect getCost to return 5 */

    printf("\ngetCost() Test Case 12\n");
    returnVal = getCost(mine);

    // Check the restults of this test case
    char* testCase12 = "getting cost of mine";

    // Assert that the return value is 5 
    if(assertTrue(0, 0, returnVal, 5))
    {
	printResults(testCase12, 1);
    }
    else
    {
	printResults(testCase12, 0);
    }

  /* Test Case 13: remodel
     * We expect getCost to return 4 */

    printf("\ngetCost() Test Case 13\n");
    returnVal = getCost(remodel);

    // Check the restults of this test case
    char* testCase13 = "getting cost of remodel";

    // Assert that the return value is 4 
    if(assertTrue(0, 0, returnVal, 4))
    {
	printResults(testCase13, 1);
    }
    else
    {
	printResults(testCase13, 0);
    }

  /* Test Case 14: smithy
     * We expect getCost to return 4 */

    printf("\ngetCost() Test Case 14\n");
    returnVal = getCost(smithy);

    // Check the restults of this test case
    char* testCase14 = "getting cost of smithy";

    // Assert that the return value is 4 
    if(assertTrue(0, 0, returnVal, 4))
    {
	printResults(testCase14, 1);
    }
    else
    {
	printResults(testCase14, 0);
    }

  /* Test Case 15: village
     * We expect getCost to return 3 */

    printf("\ngetCost() Test Case 15\n");
    returnVal = getCost(village);

    // Check the restults of this test case
    char* testCase15 = "getting cost of village";

    // Assert that the return value is 3 
    if(assertTrue(0, 0, returnVal, 3))
    {
	printResults(testCase15, 1);
    }
    else
    {
	printResults(testCase15, 0);
    }


  /* Test Case 16: baron
     * We expect getCost to return 4 */

    printf("\ngetCost() Test Case 16\n");
    returnVal = getCost(baron);

    // Check the restults of this test case
    char* testCase16 = "getting cost of baron";

    // Assert that the return value is 4 
    if(assertTrue(0, 0, returnVal, 4))
    {
	printResults(testCase16, 1);
    }
    else
    {
	printResults(testCase16, 0);
    }

  /* Test Case 17: great_hall
     * We expect getCost to return 3 */

    printf("\ngetCost() Test Case 17\n");
    returnVal = getCost(great_hall);

    // Check the restults of this test case
    char* testCase17 = "getting cost of great_hall";

    // Assert that the return value is 3 
    if(assertTrue(0, 0, returnVal, 3))
    {
	printResults(testCase17, 1);
    }
    else
    {
	printResults(testCase17, 0);
    }


    /* Test Case 18: minion
     * We expect getCost to return 5 */

    printf("\ngetCost() Test Case 18\n");
    returnVal = getCost(minion);

    // Check the restults of this test case
    char* testCase18 = "getting cost of minion";

    // Assert that the return value is 5 
    if(assertTrue(0, 0, returnVal, 5))
    {
	printResults(testCase18, 1);
    }
    else
    {
	printResults(testCase18, 0);
    }


  /* Test Case 19: steward
     * We expect getCost to return 3 */

    printf("\ngetCost() Test Case 19\n");
    returnVal = getCost(steward);

    // Check the restults of this test case
    char* testCase19 = "getting cost of steward";

    // Assert that the return value is 3 
    if(assertTrue(0, 0, returnVal, 3))
    {
	printResults(testCase19, 1);
    }
    else
    {
	printResults(testCase19, 0);
    }


    /* Test Case 20: tribute
     * We expect getCost to return 5 */

    printf("\ngetCost() Test Case 20\n");
    returnVal = getCost(tribute);

    // Check the restults of this test case
    char* testCase20 = "getting cost of tribute";

    // Assert that the return value is 5 
    if(assertTrue(0, 0, returnVal, 5))
    {
	printResults(testCase20, 1);
    }
    else
    {
	printResults(testCase20, 0);
    }


  /* Test Case 21: ambassador
     * We expect getCost to return 3 */

    printf("\ngetCost() Test Case 21\n");
    returnVal = getCost(ambassador);

    // Check the restults of this test case
    char* testCase21 = "getting cost of ambassador";

    // Assert that the return value is 3 
    if(assertTrue(0, 0, returnVal, 3))
    {
	printResults(testCase21, 1);
    }
    else
    {
	printResults(testCase21, 0);
    }


  /* Test Case 22: cutpurse
     * We expect getCost to return 4 */

    printf("\ngetCost() Test Case 22\n");
    returnVal = getCost(cutpurse);

    // Check the restults of this test case
    char* testCase22 = "getting cost of cutpurse";

    // Assert that the return value is 4 
    if(assertTrue(0, 0, returnVal, 4))
    {
	printResults(testCase22, 1);
    }
    else
    {
	printResults(testCase22, 0);
    }


  /* Test Case 23: embargo
     * We expect getCost to return 2 */

    printf("\ngetCost() Test Case 23\n");
    returnVal = getCost(embargo);

    // Check the restults of this test case
    char* testCase23 = "getting cost of embargo";

    // Assert that the return value is 2 
    if(assertTrue(0, 0, returnVal, 2))
    {
	printResults(testCase23, 1);
    }
    else
    {
	printResults(testCase23, 0);
    }


    /* Test Case 24: outpost
     * We expect getCost to return 5 */

    printf("\ngetCost() Test Case 24\n");
    returnVal = getCost(outpost);

    // Check the restults of this test case
    char* testCase24 = "getting cost of outpost";

    // Assert that the return value is 5 
    if(assertTrue(0, 0, returnVal, 5))
    {
	printResults(testCase24, 1);
    }
    else
    {
	printResults(testCase24, 0);
    }


    /* Test Case 25: salvager
     * We expect getCost to return 4 */

    printf("\ngetCost() Test Case 25\n");
    returnVal = getCost(salvager);

    // Check the restults of this test case
    char* testCase25 = "getting cost of salvager";

    // Assert that the return value is 4 
    if(assertTrue(0, 0, returnVal, 4))
    {
	printResults(testCase25, 1);
    }
    else
    {
	printResults(testCase25, 0);
    }


    /* Test Case 26: sea_hag
     * We expect getCost to return 4 */

    printf("\ngetCost() Test Case 26\n");
    returnVal = getCost(sea_hag);

    // Check the restults of this test case
    char* testCase26 = "getting cost of sea_hag";

    // Assert that the return value is 4 
    if(assertTrue(0, 0, returnVal, 4))
    {
	printResults(testCase26, 1);
    }
    else
    {
	printResults(testCase26, 0);
    }


    /* Test Case 27: treasure_map
     * We expect getCost to return 4 */

    printf("\ngetCost() Test Case 27\n");
    returnVal = getCost(treasure_map);

    // Check the restults of this test case
    char* testCase27 = "getting cost of treasure_map";

    // Assert that the return value is 4 
    if(assertTrue(0, 0, returnVal, 4))
    {
	printResults(testCase27, 1);
    }
    else
    {
	printResults(testCase27, 0);
    }


    /* Test Case 28: invalid int value 497
     * We expect getCost to return -1 */

    printf("\ngetCost() Test Case 28\n");
    returnVal = getCost(497);

    // Check the restults of this test case
    char* testCase28 = "getting cost of invalid value 497";

    // Assert that the return value is -1 
    if(assertTrue(0, 0, returnVal, -1))
    {
	printResults(testCase28, 1);
    }
    else
    {
	printResults(testCase28, 0);
    }


    /* Test Case 29: invalid int value -8
     * We expect getCost to return -1 */

    printf("\ngetCost() Test Case 29\n");
    returnVal = getCost(-8);

    // Check the restults of this test case
    char* testCase29 = "getting cost of invalid value -8";

    // Assert that the return value is -1 
    if(assertTrue(0, 0, returnVal, -1))
    {
	printResults(testCase29, 1);
    }
    else
    {
	printResults(testCase29, 0);
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
