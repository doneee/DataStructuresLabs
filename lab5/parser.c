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
  struct student *students;
  struct student *current;
  char buffer[21] = ""; //Buffer to hold the tag name.
  char ch; //Holds each character as we move through the file.
  //Some variables to track where we are.
  int tag_index, cursor = 0;
  char *field, ssn_tmp[10];
  int tmp_size;
  char choice[21];
  //Stores our command-line parameters.
  int flag_s = 0; char *filename;
  

  students = current = (struct student *)malloc(sizeof(struct student));

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
            current = (struct student *)malloc(sizeof(struct student));
            break;
          case 1: // </student>
            //printf("<%s>\n", current->first);
            file_student(students, current);
            cursor = 0;
            field = NULL;
            current = NULL;
          case 2: //<first>
            field = current->first;
            tmp_size = sizeof(current->first);
            break;
          case 4: //<last>
            field = current->last;
            tmp_size = sizeof(current->last);
            break;
          case 6: //<ssn>
            field = ssn_tmp;
            tmp_size = sizeof(ssn_tmp);
            break;
          case 8: //<mi>
            field = current->mi;
            tmp_size = sizeof(current->mi);
            break;
          case 7: //</ssn>
            current->ssn = atoi(ssn_tmp);
            //Continue on to the next case.
          case 3: case 5:  case 9: //</first>, </last>, </mi> 
            cursor = 0;
            field = NULL;
            break;

          default: //Found a tag that doesn't match the known tag list.
            fprintf(stderr, "Unknown tag found!\n");
            return 1;
        }
        break;

      case '\n': case '\t': case '\r':
        //Ignore newlines and tabs.
        break;
      case ' ':
        //Ignore spaces unless they are part of a field.
        if((cursor < 1) || ( ! field) || ( ! current))
          break;
      default:
        //If a field is currently open, and within the strings size,
        // append the current character.
        if((current) && (field) && (cursor < (tmp_size - 1)))
        {
          //Append the character to current field, then terminate it.
          field[cursor++] = ch;
          field[cursor + 1] = '\0';
        }
        else
          fprintf(stderr, "Error: character (%c) will not fit in memory!\n", ch);

        break;
    }
  }

 

 while(1)
  {
    main_menu:
    fflush(stdin);
    printf("\033[2H\033[2JSearch student database: %s.\n", filename);
    printf("%s%s%s%s%s", "\t1. Search for student by SSN number.\n",
                         "\t2. List all students in order.\n",
                         "\t3. List all students in pre order traversal.\n",
                         "\t4. List all students in post order traversal.\n",
                         "\t5. Quit.\nChoice: ");
    switch(getc(stdin))
    {
      case '1': //Search by SSN.
        fflush(stdin);
        printf("Enter SSN: ");
        
        //Grab up to 11 characters from the input buffer. Ignore dashes.
        for(i = 0; i < 12; i++)
        {
          //Save each character to choice variable.
          *(choice + i) = getc(stdin);
          //If character is a dash, ignore it.
          if (*(choice + i) == '-') i--;
          //If character is a newline, ignore it and break loop.
          if (*(choice + i) == '\n')
          {
            *(choice + i) = '\0';
            break;
          }
        }

        //If a matching record was found, print it out to the screen.
        if (current = search_records(students, atoi(choice)))
        {
          print_key();
          print_record(current, 2);
        }
        else 
        {
          //If not, show message.
          fprintf(stderr, "No matching record found!\n");
        }
        pause();
        break;
      case '2': //Print all.
        print_key();
        print_records(students->next, 2);
        pause();
        break;
      case '3': //Pre order traversal.
        print_key();
        print_records_pre(students->next, 2);
        pause();
        break;
      case '4': //Post order traversal.
        print_key();
        print_records_post(students->next, 2);
        pause();
        break;
      case '5': case 'X': case 'x':
        return 0;
      default:
        continue;
    
    }
  }
 }

/******************************************************************************
fuction print_record()
Prints out the data in a record neatly formatted.
Input: Array of strings(fields).
Returns: Nothing.
******************************************************************************/
void print_record(struct student *list, int format)
{
  char ssn_string[10]; //To store the actual ssn string.
  char ssn_format[12] = "XXX-XX-XXXX"; //Format we want the ssn in.
  
  //Convert ssn from integer to string.
  sprintf(ssn_string, "%d", list->ssn);
  
  //Lets format the ssn.
  strncpy(ssn_format, ssn_string, 3);
  strncpy(ssn_format + 4, ssn_string + 3, 2);
  strncpy(ssn_format + 7, ssn_string + 5, 4);
  
  switch(format)
  {
    case 2: //List by SSN.
      printf("%-20s %-20s %-2s %-20s\n",
                                  ssn_format,
                                  list->first,
                                  list->mi,
                                  list->last);    
      break;
    default: //List by last name.
     //Print out first and last names.
      printf("%-20s %-20s %-2s %s\n", list->last,
                                      list->first,
                                      list->mi,
                                      ssn_format);
  }
}

/******************************************************************************
fuction print_records()
Traverses the binary tree and prints out all records in order.
Input: Array of strings(fields).
Returns: Nothing.
******************************************************************************/
void print_records(struct student *list, int format)
{
  //If current record has a link to a previous record, process it first.
  if(list->prev) print_records(list->prev, format);
  
  //Print current record.
  print_record(list, format);
  
  //If current record has a link to the next record, process it.
  if (list->next) print_records(list->next, format);
}

/******************************************************************************
fuction print_records_pre()
Traverses the binary tree and prints out all records in pre order.
Input: Array of strings(fields).
Returns: Nothing.
******************************************************************************/
void print_records_pre(struct student *list, int format)
{
  //Print current record.
  print_record(list, format);

  //If current record has a link to a previous record, process it.
  if(list->prev) print_records(list->prev, format);
  
  //If current record has a link to the next record, process it.
  if (list->next) print_records(list->next, format);
}

/******************************************************************************
fuction print_records_post()
Traverses the binary tree and prints out all records in post order.
Input: Array of strings(fields).
Returns: Nothing.
******************************************************************************/
void print_records_post(struct student *list, int format)
{
  //If current record has a link to a previous record, process it.
  if(list->prev) print_records(list->prev, format);
  
  //If current record has a link to the next record, process it.
  if (list->next) print_records(list->next, format);
  
  //Print current record.
  print_record(list, format);  
}

/******************************************************************************
fuction search_records()
Traverses the binary tree and prints out all records in order.
Input: Array of strings(fields).
Returns: Nothing.
******************************************************************************/
struct student *search_records(struct student *list, int ssn)
{
  //If current record matches, return it.
  if (list->ssn == ssn) return list;
  
  //If current record has a link to a previous record, process it.
  if(list->prev) return search_records(list->prev, ssn);

  //If current record has a link to the next record, process it.
  if (list->next) return search_records(list->next, ssn);
  
  return NULL;

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

/******************************************************************************
fuction file_student()
Stores the new student in the current binary tree.
Input: Pointer to a student struct in memory.
Returns: A pointer to the new entry.
******************************************************************************/
struct student *file_student(struct student *list, struct student *s)
{
  //If current student is less than new student...
  if(list->ssn < s->ssn) 
  {
    //..and the next value isn't empty...
    if(list->next != NULL)
    {
      //...pass the new student down one level.
      return file_student(list->next, s);
    }
    else
    {
      //Otherwise, set the next value to equal the new student address.
      return list->next = s;
    }
  }
  
  //If current student is greater than new student...
  if(list->ssn > s->ssn) 
  {
    //..and the prev value isn't empty...
    if(list->prev != NULL)
    {
      //...pass the new student down one level.
      return file_student(list->prev, s);
    }
    else
    {
      //Otherwise, set the next value to equal the new student address.
      return list->prev = s;
    }
  }
}


