/******************************************************************************
Name: Donald Swany
Program: parser
File: parser.h
Prototypes and other includes for the parser program.
******************************************************************************/

//Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//This function call was a too simple to need an entire function
#define print_key() printf("%-20s %-20s MI %-20s\n", "LAST NAME", "FIRST NAME", "SSN")

//Prototypes
void lcase(char *); //Converts a string to all lower case letters.
int match_tag(char *); //Returns index of matching tags.
int in_order(char *, char *); //Function to help sort strings.
void print_record(char [][]);
int stricmp(char *, char *);
