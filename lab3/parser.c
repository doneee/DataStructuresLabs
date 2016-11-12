/******************************************************************************
Name: Donald Swany
Program: parser
File: parser.c
Main file for parser program. This program takes a xml formatted file and
parses it, storing the values into an array, allows you to search it by
last name or SSN, or list all entries. Optional tag -s will simply print out 
entries by SSN.
Usage: parser [-s] <filename>
******************************************************************************/

#include "parser.h"

//Constant to hold all of the known tags.
const char *TAGS[] = {"student", "first", "last", "ssn", "mi"};
//Arbitrary max for number of entries to grab.
const int MAX_ENTRIES = 50;

//Main entry point.
int main(int argc, char *argv[])
{
  int i; //Incrimenting variable
  FILE *inf; //Input file pointer.
  //Array to hold the parsed data. Its size varies on the constant values.
  //I used a 3-dimensional array so that the program does not rely a specific
  // number of tags.(More tags could later be added.)
  char students[MAX_ENTRIES][sizeof(TAGS)][21]; //Max field size is 20.
  int dope_students[MAX_ENTRIES]; //Dope vector to hold sorting values.
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
              fprintf(stderr, "Unknown flag\n");
          }
          break;
        default:
          //Assume that any token without a flag modifier is the filename.
          filename = argv[i];
          break;
      }

    if( ! filename) //If we didn't get a filename argument, show usage.
    {
      fprintf(stderr, "Usage:\t%s [-s] <filename>\n\t-s\tSort by SSN.\n", argv[0]);
      return 0;
    }

  //Attempt to open file. Save file pointer to inf.
  if( ! (inf = fopen(filename, "r")))
  {
    fprintf(stderr, "Unable to open file '%s'!\n", filename);
    return 1;
  }
  
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

          case 2: case 4: case 6: case 8: //<first>, <last>, <ssn>, <mi>
            depth++; //Increase the depth by 1.
            //Set field based on the tag_index. Divide it
            // by 2, then subtract 1 to give it a 0 index.
            field = tag_index / 2 - 1;
            break;

          case 3: case 5: case 7: case 9: //</first>, </last>, </ssn>, </mi>
            depth--; //Decrease depth by 1.
            field = -1; //Unset current field.
            break;

          default: //Found a tag that doesn't match the known tag list.
            fprintf(stderr, "Unknown tag found!\n");
            return 1;
        }
        break;

      case '\n': case '\t': case '\r':
        //Ignore newlines and tabs.
        break;
      case ' ': //Whitespace
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
          fprintf(stderr, "Error: character '%d' not nested in a tag!\n", ch);

        break;
    }
  }

  if(flag_s) //If the flag to sort by ssn has been set, sort by ssn.
  {
    //Give the dope vector some initial values.
    i = 0; while((dope_students[i] = i++) < entries);
    
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
      
      print_key();
      for(i = 0; i < entries; i++)
        print_record(students[dope_students[i]], 1);
      
      return 0;
  }
  else //Else, display menu.
  {
    char choice[21];
    while(1)
    {
      main_menu:
      fflush(stdin);
      printf("\033[2H\033[2JSearch student database: %s.\n", filename);
      printf("%s%s%s%s", "\t1. Search for student by SSN number.\n",
                         "\t2. Search for student by last name.\n",
                         "\t3. List all students.\n",
                         "\t4. Quit.\nChoice: ");
      switch(getc(stdin))
      {
        case '1': //Search by SSN.
         fflush(stdin);
          printf("Enter SSN without dashes: ");
          fgets(choice, 21, stdin);
          *(choice + strlen(choice) - 1) = '\0';
          for (i = 0; i < entries; i++)
          {
            if( ! strcmp(choice, students[i][2]))
            {
              printf("%-20s %-20s MI %-20s\n", "SSN", "FIRST NAME", "LAST NAME");
              print_record(students[i], 2);
              pause();
              goto main_menu;
            }
          }
          printf("No matching record!\n");
          pause();
          break;
        case '2': //Search by last name.
          fflush(stdin);
          printf("Enter last name: ");
          fgets(choice, 21, stdin);
          *(choice + strlen(choice) - 1) = '\0';
          for (i = 0; i < entries; i++)
          {
            if( ! stricmp(choice, students[i][1]))
            {
              print_key();
              print_record(students[i], 1);
              pause();
              goto main_menu;
            }
          }
          printf("No Matching Record!\n");
          pause();
          break;
        case '3': //Print all.
          print_key();
          for(i = 0; i < entries; i++)
            print_record(students[i], 1);
          
          pause();
          break;
        case '4': case 'X': case 'x':
          return 0;
        default:
          continue;
      
      }
    }
  }
}

/******************************************************************************
fuction print_record()
Prints out the data in a record neatly formatted.
Input: Array of strings(fields).
Returns: Nothing.
******************************************************************************/
void print_record(char student[sizeof(TAGS)][21], int format)
{
  char ssn_string[12] = "XXX-XX-XXXX";
  //Lets format the ssn.
  strncpy(ssn_string, student[2], 3);
  strncpy(ssn_string + 4, student[2] + 3, 2);
  strncpy(ssn_string + 7, student[2] + 5, 4);
  
  //Truncate middle name in case it was more than 1 character long.
  *(student[3] + 1) = '\0';
  
  switch(format)
  {
    case 2: //List by SSN.
      printf("%-20s %-20s %-2s %-20s\n",
                                  ssn_string,
                                  student[0],
                                  student[3],
                                  student[1]);    
      break;
    default: //List by last name.
     //Print out first and last names.
      printf("%-20s %-20s %-2s %s\n", student[1],
                                      student[0],
                                      student[3],
                                      ssn_string);
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


