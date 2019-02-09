/******************************************************************************
 * Author: Laura Lund, lundl@oregonstate.edu
 * Assignment: CS 362 Winter 2019, Random Tester Quiz
 * Description: This file contains a function testme() that is tested via the
 * 		random tester functions inputChar() and inputString().
 * ***************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
	int randIndex = rand();
	
	// Create a pool of valid characters + a few invalid characters
	char static characterPool[] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']', 
		'a', 'r', 'e', 's', 't'};
	
	// Randomly select a character from the valid pool by modding the random number
	randIndex = randIndex % 14;	// random index
	
	// Return the character at this random index
    return characterPool[randIndex];
}

char *inputString()
{
    // TODO: rewrite this function
	int i;
	
	// Randomly choose whether or not to return "reset\0" or a new string
	int randomChoice = rand();
	randomChoice = randomChoice % 2; // 50% chance of either string

	// if randomChoice == 0
	if(randomChoice == 0)
	{
		// return "reset"
		char static resetString[] = {'r', 'e', 's', 'e', 't', '\0'};
		return resetString;
	}
	// Otherwise
	// Build strings of length 6 using random characters.
	char static returnString[6];
    // Return the random string
	for(i = 0; i < sizeof(returnString); i++)
	{
		// call inputChar to get another character
		returnString[i] = inputChar();
	}
	// return new string
    return returnString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
