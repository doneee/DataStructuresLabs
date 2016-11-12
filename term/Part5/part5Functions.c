/*File: part5Functions.c
Author:Johnny Snelling
Date: 4-26-11 

The source code for functions used in  part5 which will read all 
stop words and put them into a forest of trees then
put all new non-stop words from the abstract file into the same tree. 
Then keep a count of article offsets for non stopwords. It then
implements a simple user interface to do an inorder traversal of the tree and print all words 
and offsets for nonstopwords. Also allow the user to search for a word. Display an 
appropriate message if the word is not found or if it is a stop word.

compile with: make
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

#include "part5.h"

const char *TAGS[] = {"ARTICLE", "TITLE", "AUTHOR", "ABSTRACT"};



/*//////////////////////////////////////////////////////////
loads all stopwords into the binary tree
Parameters:
  hashTable - root nodes of binary trees
  inFile - file pointer for the stopwords.dat file
  int askeyValues - a list of askeyValues
Returns:
  Nothing
*//////////////////////////////////////////////
void loadStopWords(FILE * inFile, int askeyValues[36], struct searchWord * hashTable[36])
{
  char tempWord[20];//holds the word grabbed from the stopword file
  int word_len;// used to dertimen the length of the word to allocate in memmory
  int i;
  char * word_tmp;//used to tmp hold the word in memory befo9re the tree can point ot it
  struct searchWord * locn;//the local node that is being used
  
  //keep going till at the end of the file
  while(!feof(inFile))
  {
    
    fscanf(inFile, "%s", tempWord);//grab word from the file
    word_len = strlen(tempWord);//
    word_tmp = (char *)malloc(sizeof(char) * word_len + 1);
    strcpy(word_tmp, tempWord);
	
	i = findRootNode(tempWord[0], askeyValues);
	locn = hashTable[i];
	
	
	//create root node and fill it
    if (locn->rightWing == NULL)
    {
      locn->rightWing = makeNode();
	  locn->rightWing->stopWord = 1;
      locn->rightWing->word = word_tmp;
      continue;
    }
	
	else
	locn = locn->rightWing;
	

  
	 
	 //loops through until a break is met in the loop
     while (1)
     {
	   
	   //if the words are the same it does not add it to the tree
	   if (strcmp(locn->word, word_tmp) == 0)
		 break;
	  
       //comapares the value of the local SSN with the temporary SSN	 
       if (strcmp(locn->word, word_tmp) > 0)
	   {
	   
        //if new word is less it goes to the left, and if there is no left it will
		//create a left node and then copy the data from the temp variables
		//into the the new left node and then breaks out of this loop
	     if (locn->leftWing == NULL)
		 {
		    locn->leftWing = makeNode();
			locn->leftWing->stopWord = 1;
            locn->leftWing->word = word_tmp;
		    break;
		 }
		

 
		 //if the there is a node to the left the local node moves to the left
		 //and then loops through again
              locn = locn->leftWing;
		 
	   }
	

           else
	   {
	    
		   //if new word is less it goes to the left, and if there is no left it will
		  //create a left node and then copy the data from the temp variables
		  //into the the new left node and then breaks out of this loop
           if (locn->rightWing == NULL)
		   {
		     locn->rightWing = makeNode();
			 locn->rightWing->stopWord = 1;
             locn->rightWing->word = word_tmp;
			 
			 break;
		   }
	     
	       locn = locn->rightWing;
	   }
	 }
  }

}



/*//////////////////////////////////////////////////////////
loads all stopwords into the binary tree
Parameters:
  hashTable - root nodes of binary trees
  inf - file pointer for the abstracts.dat file
  int askeyValues - a list of askeyValues
Returns:
  Nothing
*//////////////////////////////////////////////
void loadSearchWords (FILE * inf, int askeyValues[36], struct searchWord * hashTable[36])
{
  int i; //Incrimenting variable
  long loc; //Stores the file 
  char *word_tmp;
  char tempWord[20] = "";
  char buffer[21] = ""; //Buffer to hold the tag name.
  char ch; //Holds each character as we move through the file.
  int tag_index;
  int word_len;
  struct searchWord * locn;
  struct wordLoc * locLink;
  long tempOffset;
  //Loop through each character of the file.
  while(((ch = fgetc(inf)) != EOF))
  {
    switch(ch)
    {
      case '<': //Opening tag character.
        i = word_len = 0;
        //Fill buffer with the name of the tag. Stop at closing tag
        // character, EOF, or max size of tag name.
        while(((ch = fgetc(inf)) != EOF) && (ch != '>') && (i < 20))
        {
          //If it finds another opening tag before current tag ends,
          // give a parsing error.
          if(ch == '<')
          {
            fprintf(stderr, "Parsing Error!\n");
            
          }
            
          //Append the current character to buffer.
          *(buffer + i++) = ch;
        }
        //Terminate the buffer string after we get the whole tag.
        *(buffer + i) = '\0';
        ucase(buffer); //Convert the buffer to lower case.

        //Use match_tag to find the index of the current tag.
        tag_index = match_tag(buffer);

        //Basically, any known tag will be accepted, since we're going to save
        // words from all fields. I'll leave this switch in here in case we
        // want to do different things based on the 
        switch(tag_index)
        {
          case 0: tempOffset = (ftell(inf) - 9 );//<ARTICLE>
			word_len = 0;
			break;
		  case 1: // </ARTICLE>
          case 2: case 3: //<TITLE>, </TITLE>
          case 4: case 5: //<AUTHOR>, </AUTHOR>
          case 6: case 7: //<ABSTRACT>, </ABSTRACT>
            word_len = 0;
			break;
          default: //Found a tag that doesn't match the known tag list.
            fprintf(stderr, "Unknown tag found!\n");
            
        }
        break;

      case ' ': case '\n': case '\t': case '\r':
        //Found whitespace/end of word.
        if((word_len > 0) && (tag_index > 1))
        {
          //Save current location.
          loc = ftell(inf);
          //Move file pointer back to beginning of the word.
          fseek(inf, (loc - word_len - 1), SEEK_SET);
          //Create a new char array that is the size of the word and \0.
          word_tmp = (char *)malloc(sizeof(char) * word_len + 1);
          //Store word into the char array.
          fgets(word_tmp, word_len + 1, inf);
          //Set file pointer back to after the word, just in case.
          fseek(inf, loc, SEEK_SET);
          
          //Convert word to UPPERCASE.
          ucase(word_tmp);
		  
		  
	i = findRootNode(*(word_tmp + (word_len - 1)), askeyValues);
	
	//if word starts with something besides a number or letter
	//it skims off the first character of the word
	if ( i == 36 )
	{
	  *(word_tmp + (word_len - 1)) = NULL;	  
	}
	
    //find the root node for new word
	i = findRootNode(*word_tmp, askeyValues);
	
	//if word starts with something besides a number or letter
	//it skims off the first character of the word
	if ( i == 36 )
	{
	  word_tmp ++;
      i = findRootNode(*word_tmp, askeyValues);	  
	}
	
	locn = hashTable[i];
	
	//create root node and fill it
    if (locn->rightWing == NULL)
    {
      locn->rightWing = makeNode();
	  locn->rightWing->next = makeLinkNode();
	  locn->rightWing->next->offset = tempOffset;
	  locn->rightWing->stopWord = 0;
      locn->rightWing->word = word_tmp;
	  word_len = 0;
      break;
    }
	
	else
	locn = locn->rightWing;
	
	while(1)
	{
	    //if the words are the same
	   if (strcmp(locn->word, word_tmp) == 0)
	   {
	   
	     if (locn->stopWord)
		   break;
		 
		   //if in the same article dont mind saving the offset
		   if (locn->next->offset == tempOffset)
		   {
		     break;
		   }
		 
		   else
		   {
			   locLink = locn->next;
			   //go through until till at the end of the list
			   
		       while(locLink->next != NULL)
		      {
		        locLink = locLink->next;
		      }
		       locLink->next = makeLinkNode();
		       locLink->next->offset = tempOffset;//load the new offset
		       break;
			 
		   }
		 
		 break;
	   }
       //comapares the value of the local word with the temporary word	 
       if (strcmp(locn->word, word_tmp) > 0)
	   {
	   
        //if word is less it goes to the left, and if there is no left it will
		//create a left node and then copy the data from the temp node
		//into the the new left node and then breaks out of this loop
	     if (locn->leftWing == NULL)
		 {
		  locn->leftWing = makeNode();
		  locn->leftWing->next = makeLinkNode();
		  locn->leftWing->next->offset = tempOffset;
		  locn->leftWing->stopWord = 0;
          locn->leftWing->word = word_tmp;
		   break;
		 }
		 
		 //if the there is a node to the left the local node moves to the left
		 //and then loops through again
         locn = locn->leftWing;
		 
	   }
	   else
	   {
	    
		   //if new word is less it goes to the left, and if there is no left it will
		  //create a left node and then copy the data from the temp variables
		  //into the the new left node and then breaks out of this loop
           if (locn->rightWing == NULL)
		   {
		     locn->rightWing = makeNode();
			 locn->rightWing->next = makeLinkNode();
			 locn->rightWing->next->offset = tempOffset;
			 locn->rightWing->stopWord = 0;
             locn->rightWing->word = word_tmp;
			 
			 break;
		   }
	     
	       locn = locn->rightWing;
	    }
	  }
	 }
     
  
          
          
          //Reset word_len to zero and free the memory that was created.
          word_len = 0;
          //free(word_tmp);
		
        
        break;
      default:
        //If its non-whitespace, then incriment the word length counter.
        word_len++;
        break;
    }
  }
  
 
  
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
  ucase(t1);
  ucase(t2);
  return strcmp(t1, t2);
}





/******************************************************************************
fuction ucase()
Converts a string to all lower case characters. Changes the original string.
Input: Pointer to a string.
Returns: Nothing.
******************************************************************************/
void ucase(char *str)
{
  int i; //Incrimenting variable
  for(i = 0; i < strlen(str); i++)
  {
    //If current character is uppercase, subtract 32 to it to make
    // it uppercase.
    if((123 > *(str + i)) && (96 < *(str + i))) *(str + i) -= 32;
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
fuction match_tag()
This function looks up a tag in the known tag array and returns it's index.
Input: Pointer to a string of the tag to look up
Returns: Tag index as integer. Even are opening tags; odd are closing tags.
******************************************************************************/
int match_tag(char *tag)
{
  int i; //Incrimenting variable

  
  //Loop through all of the tags and compare them.
  for(i = 0; i < (sizeof(TAGS) / sizeof(TAGS[0])); i++)
  {
    //Test if it is a closing tag or not.
    if (*tag != '/')
    {
      //If it is a known tag, return its value. Multipy by 2, so we can
      // use alternates as returns for closing tags. Even = Opening.
      if ( ! strcmp(tag, TAGS[i])) return i * 2;
    }
    else
    {
      //If it is the closing of a known tag, return its location. Add
      // one to it so we know its a closing tag. Odd = Closing.
      if ( ! strcmp((tag + 1), TAGS[i])) return i * 2 + 1;
    }
  }
  //Not a known tag, so return -1.
  return -1;
  
}



/*//////////////////////////////////////////////////////////
Searches for a word in the forest of trees
Parameters:
  hashTable - root nodes of binary trees
  inf - file pointer for the abstracts.dat file
  int askeyValues - a list of askeyValues
Returns:
  Nothing
*//////////////////////////////////////////////
void searchforWord ( struct searchWord * hashTable[36], int askeyValues[36], FILE * inf)
{
  
  struct searchWord * locn;// a local node potiner
  struct wordLoc * locLink;
  char  userWord[20];//used to hold the word that the user enters in to be searched for
  int i;
  
  locLink = NULL;
  //user instructions
  printf ("\nPlease enter the word you would like to search for.\n\n");//asks the user for input
  
  fflush ( stdin );//clears out the input
  
  scanf ("%s", userWord);//gets the word from the user to be searched for
  
  ucase(&userWord[0]);
  
  i = findRootNode(userWord[0], askeyValues);
  
  while (i == 36)
  {
    printf ("\nNot a valid entry please try again\n");
    fflush ( stdin );//clears out the input
  
    scanf ("%s", userWord);//gets the word from the user to be searched for
  
    ucase(&userWord[0]);
  
    i = findRootNode(userWord[0], askeyValues);
  }

  locn = hashTable[i];
  locn = locn->rightWing;
  
  
  
  while (locn != NULL)
  {
    //if the users word equals a students word then it prints out the student's information
    if ( (strcmp(userWord, locn->word)) == 0)
	{
	  if (locn->stopWord)
	  {
	    printf("\nYour word is a stopword\n\n");
		break;
	  }
	  
	  else
	  {
	    printArticles(locn->next, inf);
		
		printf("\n\n");
		break;
	  }
	}
	
	//if the choice when comapred to the local nodes is less than
	//the local node is moved to the left
	//otherwise it moved to the right
	if ( strcmp(userWord, locn->word) < 0)
	locn = locn->leftWing;
	else
	locn = locn->rightWing;
	
  }
  
  if (locn == NULL)
  {
  //if there are no matches then an error message is sent to the user
  printf("Your word is not on file.\n\n\n");
  }
}

/*//////////////////////////////////////////////////////////
loads askeyValues for all numbers and upper case letters
Parameters:
  askeyValues - the blank array of integers to be loaded
  Returns:
  Nothing
*////////////////////////////////////////////
void loadDopePointers(int askeyValues[36])
{
  int e, i;

  for (e=0, i=48; i < 58; e++, i++)
  {
    askeyValues[e] = i;
  }
  
  for (i=65; i < 91; e++, i++)
  {
    askeyValues[e] = i;
  }

}


/*//////////////////////////////////////////////////////////
finds certain askey values for a character
Parameters:
  newWord - the first character of a new word
  askeyValues - a list of askeyvalues for all numbers and capital letters
Returns:
  i - the interger value that tells what askey value the letter is
*////////////////////////////////////////////////
int findRootNode(char newWord, int askeyValues[36])
{
  int i;
  
  if (newWord == '\\')
  return 1;
  for (i = 0; i < 36 ; i++)
  {
    if ( (int) newWord == askeyValues[i])
	break;
	
  }
    
  return i;
}


/*//////////////////////////////////////////////////////////
makes all the root nodes for the forest of trees
Parameters:
  hashTable - the forest of trees to be created
Returns:
  Nothing
*////////////////////////////////////////////////
void makeHash(struct searchWord * hashTable[36])
{
  int i;//used to move through elements of hash table
  
  for ( i = 0; i < 36; i++)
  {
    hashTable[i] = makeNode();
  }
}


/*//////////////////////////////////////////////////////////
loads all stopwords into the binary tree
Parameters:
  locn - a starting node for the linked list that holds article
  offsets.
  inf - file pointer for the abstracts.dat file
Returns:
  Nothing
*//////////////////////////////////////////////////
void printArticles(struct wordLoc * locn, FILE * inf)
{
  struct wordLoc * locLink;
  int i; //Incrimenting variable
  char c;
  long loc; //Stores the file 
  char *word_tmp;
  char buffer[21] = ""; //Buffer to hold the tag name.
  char ch; //Holds each character as we move through the file.
  int tag_index;
  int word_len;

  
  fseek(inf, locn->offset, SEEK_SET);

  //Loop through each character of the file.
  while(((ch = fgetc(inf)) != EOF) && (strcmp(buffer, "/ARTICLE")))
  {
    switch(ch)
    {
      case '<': //Opening tag character.
        i = word_len = 0;
        //Fill buffer with the name of the tag. Stop at closing tag
        // character, EOF, or max size of tag name.
        while(((ch = fgetc(inf)) != EOF) && (ch != '>') && (i < 20))
        {
          //If it finds another opening tag before current tag ends,
          // give a parsing error.
          if(ch == '<')
          {
            fprintf(stderr, "Parsing Error!\n");
          }
            
          //Append the current character to buffer.
          *(buffer + i++) = ch;
        }
        //Terminate the buffer string after we get the whole tag.
        *(buffer + i) = '\0';
        ucase(buffer); //Convert the buffer to lower case.

        //Use match_tag to find the index of the current tag.
        tag_index = match_tag(buffer);

        
        //Basically, any known tag will be accepted, since we're going to save
        // words from all fields. I'll leave this switch in here in case we
        // want to do different things based on the 
        switch(tag_index)
        {
          case 0: case 1://<ARTICLE>, </ARTICLE>
			word_len = 0;
			break;
          case 2: //<TITLE>, 
		    while (strcmp(buffer, "/TITLE>"))
            {
              fscanf (inf, "%c", &c);
	          
	
              if (c == '<')
	          {
	            fscanf (inf, "%s", buffer);
				if (strcmp(buffer, "/TITLE>"))
				break;
	          }
			  else
              printf ("%c", c);
            }
            printf("\n");

		    word_len = 0;
			break;
		  case 3: //</TITLE>
			word_len = 0;
			break;
          case 4: //<AUTHOR> 
		    while (strcmp(buffer, "/AUTHOR>"))
            {
              fscanf (inf, "%c", &c);
	         
	
              if (c == '<')
	          {
	            fscanf (inf, "%s", buffer);
				if (strcmp(buffer, "/AUTHOR>"))
				break;
	           }
			   
			   else
			    printf ("%c", c);
  
            }
            printf("\n");

          
		    word_len = 0;
			break;
		  case 5: // </AUTHOR>
			word_len = 0;
			break;
          case 6: //<ABSTRACT>,
		     
		    while (strcmp(buffer, "/ABSTRACT>"))
            {
              fscanf (inf, "%c", &c);
	         
	
              if (c == '<')
	          {
	            fscanf (inf, "%s", buffer);
				if (strcmp(buffer, "/ABSTRACT>"))
				break;
	           }
			   
			   else
			    printf ("%c", c);
  
            }
            printf("\n");
            pause();
           
		    word_len = 0;
			break;
		  case 7:  //</ABSTRACT>
          word_len = 0;
          break;

          default: //Found a tag that doesn't match the known tag list.
            fprintf(stderr, "Unknown tag found!\n");
        }
        break;

      default:
        //If its non-whitespace, then incriment the word length counter.
        word_len++;
        break;
    }
  }
 

    if  (locn->next != NULL)
    {
      printArticles(locn->next, inf);
    }

  
  
}




