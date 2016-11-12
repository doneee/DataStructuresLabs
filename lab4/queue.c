/******************************************************************************
Name: Donald Swany
Program: queue
File: queue.c
This program presents a menu that allows the user to store words in a queue.
The program then allows them to delete, search, or list words in the queue.
******************************************************************************/

#include "queue.h"

//Main entry point.
int main(int argc, char *argv[])
{
  //struct item pointers to hold position addresses.
  struct item *start, *current;
  //A char array to temporarily hold the word.
  char word_buf[11];
  
  //Create an empty struct item to start with.
  start = current = (struct item *)malloc(sizeof(struct item));
  
  //Clear the screen.
  printf("\033[2H\033[2J");
  //Show Menu.
  printf("%s%s", "Word Queue\n\t1.\tInsert Word\n\t2.\tDelete Word\n\t3.", 
                 "\tList Words\n\t4.\tFind Word\n\t5.\tQuit\n\n");
    
  while(1) //Infinite loop
  {
    printf("Choice: ");
    //Flush, then wait for a menu choice.
    fflush(stdin); 
    switch(getc(stdin))
    {
      case '1': //New word
        //Prompt for word input, then store it in word_buf.
        fflush(stdin);
        printf("Enter a word: ");
        fgets(word_buf, 11, stdin);
        //Trim trailing new-line.
        if(*(word_buf + strlen(word_buf) - 1) == '\n') 
          *(word_buf + strlen(word_buf) - 1) = '\0';
        
        //Insert word, then update current pointer with the latest word
        // address.
        current = insert_word(current, word_buf);
        
        //Print confirmation.
        printf("Word '%s' was added to the list!\n", current->word);
        break;
      case '2': // Delete word
        //Prompt for word.
        fflush(stdin);
        printf("Delete word: ");  
        fgets(word_buf, 11, stdin);
        //Trim trailing new-line.
        if(*(word_buf + strlen(word_buf) - 1) == '\n')
          *(word_buf + strlen(word_buf) - 1) = '\0';
        
        //Print out whether it was successfully found/deleted.
        printf("%s", ! delete_word(start, word_buf) ? "Successfully deleted!\n" : 
                                                      "Word not found!\n");
        break;
      case '3': //List words
        //Call function to display word list, passing it the pointer to the first
        // item.
        display_words(start);
        break;
      case '4': //Search for word
        //Prompt for word.
        fflush(stdin);
        printf("Search for word: ");  
        fgets(word_buf, 11, stdin);
        //Trim trailing new-line.
        if(*(word_buf + strlen(word_buf) - 1) == '\n')
          *(word_buf + strlen(word_buf) - 1) = '\0';
        
        //Print whether or not the word was found.
        printf("Word '%s' was %sfound!\n", word_buf, 
          find_word(start, word_buf) ? "" : "not ");
        break;
        
      case 'h': case 'H': // Show menu
        //Redisplay the menu if needed.
        printf("%s%s", "Word Queue\n\t1.\tInsert Word\n\t2.\tDelete Word\n\t3.",
                       "\tList Words\n\t4.\tFind Word\n\t5.\tQuit\n\n");
        break;
      case '5': case 'Q': case 'q': //Quit
        return 0;
    }
  }
}
