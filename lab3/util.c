/******************************************************************************
Name: Donald Swany
Program: parser
File: util.c
Misc. Utilties for the parser application.
******************************************************************************/
#include "parser.h"

/******************************************************************************
fuction lcase()
Converts a string to all lower case characters. Changes the original string.
Input: Pointer to a string.
Returns: Nothing.
******************************************************************************/
void lcase(char *str)
{
  int i; //Incrimenting variable
  for(i = 0; i < strlen(str); i++)
  {
    //If current character is uppercase, add 32 to it to make
    // it lowercase.
    if((91 > *(str + i)) && (64 < *(str + i))) *(str + i) += 32;
  }
}

/******************************************************************************
fuction pause()
Waits for a RETURN, then allows the program to continue.
Input: None.
Returns: Nothing.
******************************************************************************/
void pause()
{
  fflush(stdin); //Otherwise, it will grab the return from the last input.

  //Tell the user to press RETURN, then wait...
  printf("Press RETURN to continue...");
  getchar();
  return;
}

/******************************************************************************
fuction in_order(char *str1, char *str2)
Compares two strings, and returns 1 if they are in descending order.
Input: Two pointers to two strings in memory.
Returns: int; 1, if in order. 0, if not in order. (TRUE/FALSE)
******************************************************************************/
int in_order(char *str1, char *str2)
{
  int p; //Incrimenter.
  //Loop through each character in the strings.
  for(p = 0; (p < strlen(str1)) && (p < strlen(str2)); p++)
  {
    //printf("Compare: %s, %s\n", (str1 + p),(str2 + p));
    if(*(str1 + p) == '\0') return 1;
    //If the characters at this position are the same, move onto the next one.
    if(*(str1 + p) == *(str2 + p)) continue;
      //Return whether they are in order or not.
      return (*(str1 + p) < *(str2 + p));
  }
  //The strings are the same, so assume they must be in order!
  return 1;
}

/******************************************************************************
fuction stricmp(char *str1, char *str2)
Same as strcmp, except it case insensitive.
Input: Two strings to compare.
Returns: int; 0, if matching. Non-zero depending on the difference(strcmp).
******************************************************************************/
int stricmp(char *str1, char *str2)
{
  char t1[strlen(str1)];
  char t2[strlen(str2)];
  strcpy(t1, str1);
  strcpy(t2, str2);
  lcase(t1);
  lcase(t2);
  return strcmp(t1, t2);
}
