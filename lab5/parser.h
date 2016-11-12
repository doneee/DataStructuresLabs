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
#define print_key() printf("%-20s %-20s MI %-20s\n", "SSN", "FIRST NAME", "LAST NAME")

struct student {
  char first[21];
  char mi[2];
  char last[21];
  long ssn;
  struct student *prev;
  struct student *next;
};

//Prototypes
void lcase(char *); //Converts a string to all lower case letters.
int match_tag(char *); //Returns index of matching tags.
int in_order(char *, char *); //Function to help sort strings.
void print_record(struct student *, int);
void print_records(struct student *, int);
void print_records_pre(struct student *, int);
void print_records_post(struct student *, int);
int stricmp(char *, char *);
struct student *file_student(struct student *, struct student *);
struct student *search_records(struct student *, int);

