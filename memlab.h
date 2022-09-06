// Assignment 5
// Hands on experience for creating better memory management systems
// Operating Systems Laboratory (CS39002)
// Group 34
// Amartya Mandal 19CS10009
// Divyansh Bhatia 19CS10027

#ifndef MEMLAB_H
#define MEMLAB_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<pthread.h>

#define INTEGER 1
#define CHARACTER 2
#define MEDIUM_INT 3
#define BOOLEAN 4
#define MAX_SIZE 1000
#define MAX_CHAR 10
#define MAX_VAR 2000000

void createMem(int);   					// size
void freeMem();
void createVar(char *, int);  			// name, type
void assignVar(char *, int, int); 		// name, type, val
void createArr(char *, int, int); 		// name, type, size
void assignArr(char *, int, int, int); 	// name, type, val, which array element
void freeElem(char *);  				// name
int getVar(char *);
int getArrElem(char *, int);
void newFunc();
void endFunc();

#endif
