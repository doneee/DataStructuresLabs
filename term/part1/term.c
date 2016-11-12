/******************************************************************************
Name: Team5
Program: term
File: term.c
Part 1
******************************************************************************/

#include "term.h"

const char *TAGS[] = {"ARTICLE", "TITLE", "AUTHOR", "ABSTRACT"};

//Main entry point.
int main(int argc, char *argv[])
{
  int i; //Incrimenting variable
  FILE *inf; //Input file pointer.
  long loc; //Stores the file 
  char *word_tmp;
  char buffer[21] = ""; //Buffer to hold the tag name.
  char ch; //Holds each character as we move through the file.
  int tag_index;
  int word_len;


  //Attempt to open file. Save file pointer to inf.
  if( ! (inf = fopen("abstracts.dat", "r")))
  {
    fprintf(stderr, "Unable to open file 'abstracts.dat'!\n");
    return 1;
  }
  
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
            return 1;
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
          case 0: case 1: //<ARTICLE>, </ARTICLE>
          case 2: case 3: //<TITLE>, </TITLE>
          case 4: case 5: //<AUTHOR>, </AUTHOR>
          case 6: case 7: //<ABSTRACT>, </ABSTRACT>
          word_len = 0;
          break;

          default: //Found a tag that doesn't match the known tag list.
            fprintf(stderr, "Unknown tag found!\n");
            return 1;
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
          
          //Print word to screen.
          printf("Word: '%s'\n", word_tmp);
          
          //Reset word_len to zero and free the memory that was created.
          word_len = 0;
          free(word_tmp);
        }
        break;
      default:
        //If its non-whitespace, then incriment the word length counter.
        word_len++;
        break;
    }
  }
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
