# Author: Laura Lund, lundl@oregonstate.edu
# Assignment: CS 362 Winter 2019, Random Tester Quiz
# Citation: this Makefile is based on the Makefile for dominion.

CFLAGS= -Wall -fpic -coverage -lm -std=c99 -ftest-coverage -fprofile-arcs

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS)
	./testme

all: testme

clean:
	rm -f *.o testme.exe testme *.gcov *.gcda *.gcno *.so *.out
