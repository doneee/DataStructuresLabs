/*File: part5.c
Author:Johnny Snelling
Date: 4-26-11 

The driver source code part5 which will read all 
stop words and put them into a forest of trees then
put all new non-stop words from the abstract file into the same tree. 
Then keep a count of article offsets for non stopwords. It then
implements a simple user interface to do an inorder traversal of the tree and print all words 
and offsets for nonstopwords. Also allow the user to search for a word. Display an 
appropriate message if the word is not found or if it is a stop word.

compile with: make
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

#include "part5.h"

//Main entry point.
int main(int argc, char *argv[])
{
  
  int askeyValues[36];
  struct searchWord * hashTable[36];
  int userChoice;
  FILE * inFile;//input fle pointer for stopwords.dat
  FILE *inf; //Input file pointer for abstracts.dat
  
  userChoice = 7;//default value for the user choice
 
 //Attempt to open file. Save file pointer to inf.
  if( ! (inFile = fopen("stopwords.dat", "r")))
  {
    fprintf(stderr, "Unable to open file 'stopwords.dat'!\n");
    return 1;
  }
  
  

  //Attempt to open file. Save file pointer to inf.
  if( ! (inf = fopen("abstracts.dat", "r")))
  {
    fprintf(stderr, "Unable to open file 'abstracts.dat'!\n");
    return 1;
  }
  
  
  loadDopePointers(askeyValues);
  makeHash (hashTable);
  //load all words into the binary tree
  loadStopWords(inFile, askeyValues, hashTable);
  loadSearchWords(inf, askeyValues, hashTable);
  
  
  
  
  //user interface
  printf("\n\nwelcome to part 3\n\n");
  
  //runs till the user picks a zero
  while (userChoice != 0)
  {
    //instructions
    printf("\n\nPress 1 to search for a word\n");
	printf("or 0 to quit\n\n");
	fflush(stdin);
	scanf("%d", &userChoice);//gets the user's deciscion
	switch (userChoice)
	{
	  case 1://lets the user enter a word and searches for it in the tree
		searchforWord(hashTable, askeyValues, inf);
		break;
	  case 0://will cause the whole program to terminate
	    break;
	  default://in case the user makes a mistake
	    printf("Not a valid choice please try again");
		break;
    }
  

  }

}

