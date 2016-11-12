/*File: makeNodeFunction.c
Author:Johnny Snelling
Date: 4-26-11 

The source code for the makeNodeFunction used in  part5 which will read all 
stop words and put them into a forest of trees then
put all new non-stop words from the abstract file into the same tree. 
Then keep a count of article offsets for non stopwords. It then
implements a simple user interface to do an inorder traversal of the tree and print all words 
and offsets for nonstopwords. Also allow the user to search for a word. Display an 
appropriate message if the word is not found or if it is a stop word.

compile with: make
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/




#include "part5.h"


/*//////////////////////////////////////////////////////////
makes a new node in the queue by allocatting storge for a structure and then
having a pointer point to the structure in memory
Parameters:
  nothing
Returns:
  a structure the is type Words
*//////////////////////////////////////////////////////////
struct searchWord * makeNode ( void )
{
  struct searchWord * new; //a local pointer
  
  //dynamically allocate storage and maybe 'initialize'
  new = (struct searchWord *) calloc (1, sizeof (struct searchWord) );
  new->leftWing = NULL;//makes sure the left and right wings are Null since it
  new->rightWing = NULL;//is a new node
  return new; //send adress of new node back
}

struct wordLoc * makeLinkNode ( void )
{
  struct wordLoc * new; //a local pointer
  
  //dynamically allocate storage and maybe 'initialize'
  new = (struct wordLoc *) calloc (1, sizeof (struct wordLoc) );
  new->offset = NULL;
  new->next = NULL;
  return new; //send adress of new node back
}

