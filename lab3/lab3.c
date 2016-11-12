/******************************************************************************
Name: Donald Swany
Program: Lab3
File: parser.c
******************************************************************************/

#include "parser.h"

//Constants to hold all of the known tags.
const char *TAGS[] = {"student", "first", "last", "ssn"};
const int MAX_ENTRIES = 50;

//Main entry point.
int main(int argc, char *argv[])
{
  int i; //Incrimenting variable
  FILE *inf; //Input file pointer.
  //Array to hold the parsed data. Its size varies on the constant values.
  char students[MAX_ENTRIES][sizeof(*TAGS)][21];
  int dope_students[MAX_ENTRIES];
  char buffer[21] = ""; //Buffer to hold the tag name.
  char ch; //Holds each character as we move through the file.
  //Some variables to track where we are.
  int tag_index, depth = 0, field = 0, cursor = 0, entries = 0;
  //Stores our command-line parameters.
  int flag_s = 0; char *filename;

  //Check if we have any command line arguments.
  if(argc > 1)
    for(i = 1; i < argc; i++) //Loop through arguments.
      switch(*argv[i])
      {
        case '-': //Flag modifier
          switch(*(argv[i] + 1)) //Look up flag and process it.
          {
            case 's': //Sort by SSN flag.
              flag_s = 1;
              break;
            default:
              printf("Unknown flag\n");
          }
          break;
        default:
          filename = argv[i];
          break;
      }

    if( ! filename) //If we didn't get a filename argument, show usage.
    {
      printf("Usage:\t%s [-s] <filename>\n\t-s\tSort by SSN.\n", argv[0]);
      return 0;
    }

  //Attempt to open file. Save file pointer to inf.
  if( ! (inf = fopen(filename, "r")))
    exit_msg("Unable to open file!\n");

  //Loop through each character of the file.
  while(((ch = fgetc(inf)) != EOF))
  {
    switch(ch)
    {
      case '<': //Opening tag character.
        i = cursor = 0;
        //Fill buffer with the name of the tag. Stop at closing tag
        // character, EOF, or max size of tag name.
        while(((ch = fgetc(inf)) != EOF) && (ch != '>') && (i < 20))
        {
          //If it finds another opening tag before current tag ends,
          // give a parsing error.
          if(ch == '<') exit_msg("Parsing Error!\n");

          //Append the current character to buffer.
          *(buffer + i++) = ch;
        }
        //Terminate the buffer string after we get the whole tag.
        *(buffer + i) = '\0';
        lcase(buffer); //Convert the buffer to lower case.

        //Use match_tag to find the index of the current tag.
        tag_index = match_tag(buffer);

        switch(tag_index)
        {
          case 0: // <student>
            depth++; //Increase the depth by 1.
            break;

          case 1: // </student>
            depth--;  //Decrease depth by 1.
            field = -1; //Unset current field.
            entries++; //Move on to next entry.
            break;

          case 2: case 4: case 6: //<first>, <last>, <ssn>
            depth++; //Increase the depth by 1.
            //Set field based on the tag_index. Divide it
            // by 2, then subtract 1 to give it a 0 index.
            field = tag_index / 2 - 1;
            break;

          case 3: case 5: case 7: //</first>, </last>, </ssn>
            depth--; //Decrease depth by 1.
            field = -1; //Unset current field.
            break;

          default: //Found a tag that doesn't match the known tag list.
            exit_msg("Unknown tag found!\n");
            break;
        }
        break;

      case ' ': case '\n': case '\t': case '\r': //Whitespace
        //If not currently in a field, ignore whitespace.
        if(depth < 2) break;
      default:
        //If a field is currently open, and within the strings size,
        // append the current character.
        if((depth > 1) && (cursor < (sizeof(**students) - 1)))
        {
          //Append the character to current field, then terminate it.
          students[entries][field][cursor++] = ch;
          students[entries][field][cursor + 1] = '\0';
        }
        else
          printf("Error: character '%d' not nested in a tag!\n", ch);

        break;
    }
  }

  //Give the dope vector some initial values.
  i = 0; while((dope_students[i] = i++) < entries);

  if(flag_s) //If the flag to sort by ssn has been set, sort by ssn.
  {
    for (i = 0; i < entries - 1; i++)
      if( ! in_order(students[dope_students[i]][2],
                     students[dope_students[i + 1]][2]))
      {
        //Swap dope vector numbers.
        dope_students[i] ^= dope_students[i + 1] ^=
          dope_students[i] ^= dope_students[i + 1];
        i = -1; //Restart sorting.
      }
  }
  else //Else, sort by last and first names.
  {
    for (i = 0; i < entries - 1; i++)
      if( ! in_order(students[dope_students[i]][0],
                     students[dope_students[i + 1]][0]))
      {
        //Swap dope vector numbers.
        dope_students[i] ^= dope_students[i + 1] ^=
          dope_students[i] ^= dope_students[i + 1];
        i = -1; //Restart sorting
      }

    for (i = 0; i < entries - 1; i++)
      if( ! in_order(students[dope_students[i]][1],
                     students[dope_students[i + 1]][1]))
      {
        //Swap dope vector numbers.
        dope_students[i] ^= dope_students[i + 1] ^=
          dope_students[i] ^= dope_students[i + 1];
        i = -1; //Restart sorting.
      }
  }

  printf("%-20s %-20s %-20s\n", "LAST NAME", "FIRST NAME",
    "SSN");
    char tmp[5];
  for(i = 0; i < entries; i++)
  {
    //Print out first and last names.
    printf("%-20s %-20s ", students[dope_students[i]][1],
                           students[dope_students[i]][0]);

    //Print out SSN with dashes. 
    strncpy(tmp, students[dope_students[i]][2], 3); *(tmp+3) = '\0';
    printf("%s-", tmp);
    strncpy(tmp, students[dope_students[i]][2] + 3, 2); *(tmp+2) = '\0';
    printf("%s-", tmp);
    strncpy(tmp, students[dope_students[i]][2] + 5, 4); *(tmp+4) = '\0';
    printf("%s\n", tmp);
  }
  return 0;
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
  for(i = 0; i < (sizeof(TAGS) / sizeof(*TAGS)); i++)
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


