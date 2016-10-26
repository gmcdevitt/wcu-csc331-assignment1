#include <sys/types.h>
#include <stdlib.h>
#include "stdio.h"

/**
 * Gerard McDevitt - 0860485
 * Assignment 1 - Fibonacci Sequence with Forking
 *
 *
 * !!!PLEASE NOTE!!!
 * This program cannot go very deep into the Fibonacci Sequence,
 * it quickly reaches numbers too large to be stored in a basic int, specifically at the 47th Fibonacci Number.
 */
 
/* Prototypes */
int promptForInput(void);
char* getFibonacciSequence(int limit);
char* fibonacciAux(int limit, int a, int b, char *sequence);

/*
 * Prompts the user for the depth to go into Fibonacci Sequence.
 * Then traverses the Fibonacci Sequence to that depth, printing out the sequence up to that point
 */
void main(void) {
	pid_t pid;
	char* sequence;
	int input;

	pid = fork();
	if (0 > pid) { 
		fprintf(stderr, "Forking a process for the Fibonacci Program failed!");
	} else if (0 == pid) {
		input = promptForInput();
		sequence = getFibonacciSequence(input);
		
		if (1 == input) {
			printf("The first number in the Fibonacci Sequence is '%s'.\n", sequence);
		} else if (1 < input) {
			printf("The first %d numbers in the Fibonacci Sequence are '%s'.\n", input, sequence);
		}	
	} else {
		wait();
		exit(0);
	}
}

/*
 * Prompts the user for a non negative integer.
 */
int promptForInput(void) {
	int input;
		
	printf("Please input an integer value, this is how far into the Fibbonaci Sequence to go:\n");
	scanf("%d", &input);
	
	if (0 > input) {
	   printf("'%d' is less than 0! Try again!", input);
	   exit(-1);
    } else if (0 == input) {
	   printf("You either entered 0 or something other than a number! Try again!\n");
	   exit(-1);   
    }
    
    return input;
}

/*
 * Call fibonacciAux with the initial state for the Fibonacci Sequence and how deep to go into it (number of steps).
 */
char* getFibonacciSequence(int steps) {
	char *start = "0";
	return fibonacciAux(steps, 0, 1, start);
} 

/* 
 * Compute the next value of the Fibonacci Sequence.
 * Write that value to the end of the sequence.
 */
char* fibonacciAux(int remainingSteps, int a, int b, char *sequence) {
	/* Check if we are where we need to be in the sequence... */
	if (remainingSteps == 1) {
		return sequence;
	} 
	
	/* Get the next value of the Fibonacci Sequence... */
	int sum = a + b;
	
	/*
	 * Needed a way to dynamically allocate memory for when the sequence would get very long (with input like 100),
	 * Borrowed the solution here http://stackoverflow.com/a/3923207
	 */
	int size = snprintf(NULL, 0, "%s %d", sequence, sum); /* Figure out how many characters to allocate to the string... */
	char *next = malloc(size + 1); /* Allocate them, compensating for the exit character. */
	sprintf(next, "%s %d", sequence, sum); /* Actually write to the newly created buffered char array */

	fibonacciAux((remainingSteps - 1), b, (a + b), next);
}

