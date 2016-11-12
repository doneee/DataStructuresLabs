/******************************************************************************
Name: Team5
Program: term
File: term.h
Prototypes and other includes for the term program.
******************************************************************************/

//Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct word {
  char *value;
  int stop;
  struct wordloc *offsets;
  struct word *prev;
  struct word *next;
};

struct wordloc {
  long offset;
  struct wordloc *next;
};


//Prototypes
void ucase(char *); //Converts a string to all lower case letters.
int match_tag(char *); //Returns index of matching tags.
int in_order(char *, char *); //Function to help sort strings.
int stricmp(char *, char *); //Incase sensitive compare.

