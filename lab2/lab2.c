/******************************************************************************
Name: Donald Swany
Program: Lab2/lab2.c
This program loads an array of "strings" containing information about the
presidents of the United States. It makes use of an external object file,
called potus.o, that is linked separately. When loaded, the data will be
parsed, then a menu will be displayed allowing you to display the data using
various sorting methods.

Note: I have a habit of using only the absolute necessary about of variables
and as few function calls as I can manage. Sometimes, this makes the code a
little more difficult to read for others. Sorry, if this is the case!
******************************************************************************/

//Includes
#include <stdio.h>
#include <string.h>

//Prototypes
int load_potus (char myarray [] [81], char filename[]);
void pause();
int in_order(char *, char *); //Function to help sort strings.

//Create a struct to hold the various values needed for each president.
typedef struct
{
  char *fm_name; //First and middle names
  char *last_name; //Last name
  char *term; //Term, stored a string
  char *state; //Home state
} president;

//Main entry point.
int main()
{
  int MAX = 50; //Predefined MAX of presidents to load.
  int choice; //Stores response from menu.
  int dope_vector[MAX]; //Stores my sorting arrangement.
  int i; //Incrimenting variable.
  char potus[MAX][81]; //Holds the data that function potus returns.
  president pres[MAX]; //An array of the struct president.
  
  //Load presidents into potus array, and change MAX to reflect the
  // actual number of entries.
  MAX = load_potus(potus, "presidents.dat");

  //Do a for-loop based on the number of lines that are returned
  // and load data into struct.
  for(i = 0; i < MAX; i++)
  {
    //Set some intial values for the dope vector. Could be done
    // at the beginning, but I decided to do it during this loop.
    dope_vector[i] = i;

    //Save the token addresses to the struct. Temporarily save the
    // entire name as in fm_name. We'll come back and fix it.
    pres[i].fm_name = strtok(potus[i], ",");
    pres[i].term = strtok(NULL, ",");
    pres[i].state = strtok(NULL, ",");

    //I run these through the tokenizer to trim any white space.
    pres[i].term = strtok(pres[i].term, " ");
    pres[i].state = strtok(pres[i].state, " ");

    //Find the position of the last name, then store it.
    pres[i].last_name = strrchr(pres[i].fm_name, ' ') + 1;

    //Make sure to add any prepended 'Van' to the last name.
    //Sneaky Van Buren. I almost didn't catch that.
    if (strstr((pres[i].last_name - 5), " Van "))
      pres[i].last_name = (pres[i].last_name - 4);

    //Terminates the fm_name string just before the last name.
    *(pres[i].last_name - 1) = '\0';
    
    //Originally, I parsed the first and middle names, but since there
    // wasn't any need for them to be separated, I just removed the step.
  }

  //Sort the data by first and middle names. This is useful if the sort chosen
  // has duplicate values. This way, it can fall back on sorting by name.
  for(i = 0; i < (MAX - 1); i++)
  {
      //If current and next president are not in order, swap them.
      if( ! in_order(pres[dope_vector[i]].fm_name, 
                     pres[dope_vector[i + 1]].fm_name))
      {
          //XOR swap so I don't have to use a temp variable.
          dope_vector[i] ^= dope_vector[i + 1] ^= 
            dope_vector[i] ^= dope_vector[i + 1];
          //Reset the counter. Set to -1 because the for-loop will +1.
          i = -1;

      }
  }

  //Same as above. This just sorts by last name.
  for(i = 0; i < (MAX - 1); i++)
  {
      //If current and next president are not in order, swap them.
      if( ! in_order(pres[dope_vector[i]].last_name, 
                     pres[dope_vector[i + 1]].last_name))
      {
          //XOR swap so I don't have to use a temp variable.
          dope_vector[i] ^= dope_vector[i + 1] ^= 
            dope_vector[i] ^= dope_vector[i + 1];
          //Reset the counter. Set to -1 because the for-loop will +1.
          i = -1;

      }
  }

  while (1) //Infinite loop
  {
    //Clear the screen and display the menu.
    printf("\033[2H\033[2JSort presidents of the United States by:\n");
    printf("\t1. Last Name\n\t2. Inaguration Year\n\t3. Home State\n");
    printf("\t4. Exit\n\n");
    //Flush input buffer to get rid of bogus data.
    fflush(stdin);

    //Get menu choice.
    printf("Choice: ");
    if (scanf("%d", &choice) < 1) continue; //Continue if data is bogus.

    //Switch, based on choice.
    switch (choice)
    {
      case 1: //Sort by last name.
        //Don't do anything. It was already sorted by last name above.
        break;
      case 2: //Sort by term.
        for(i = 0; i < (MAX - 1); i++)
        {
            //If current and next president are not in order, swap them.
            if( ! in_order(pres[dope_vector[i]].term, 
                           pres[dope_vector[i + 1]].term))
            {
                //XOR swap so I don't have to use a temp variable.
                dope_vector[i] ^= dope_vector[i + 1] ^= 
                  dope_vector[i] ^= dope_vector[i + 1];
                //Reset the counter. Set to -1 because the for-loop will +1.
                i = -1;
            }
        }
        break;
        
      case 3: //Sort by state.
        for(i = 0; i < (MAX - 1); i++)
        {
            //If current and next president are not in order, swap them.
            if( ! in_order(pres[dope_vector[i]].state, 
                           pres[dope_vector[i + 1]].state))
            {
                //XOR swap so I don't have to use a temp variable.
                dope_vector[i] ^= dope_vector[i + 1] ^= 
                  dope_vector[i] ^= dope_vector[i + 1];
                //Reset the counter. Set to -1 because the for-loop will +1.
                i = -1;
            }
        }
        break;
        
      case 4: case 'x': //Allow users to enter 'x' to exit, as well.
      //Exit chosen.
        return 0; //Thank you for playing.
        
      default: //If no valid option was chosen.
        //Start the next loop.
        continue;
    }
    
    //Print out results.
    for(i = 0; i < MAX ; i++)
    {
      //Print line number.
      printf("%2d. ", i + 1);

      //Print full name.
      printf("%s %s, ", pres[dope_vector[i]].fm_name, 
                        pres[dope_vector[i]].last_name);
      //Print term.
      printf("%s, ", pres[dope_vector[i]].term);
      //Print state.
      printf("%s\n", pres[dope_vector[i]].state);

      //Pauses every 20 entries.
      if (((i + 1) / 20 * 20) == (i + 1))
      {
        //Make a nice little pause prompt.
        printf("(More...) ");
        pause();
        printf("\n");
      }
    }
    pause();
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
    //If the characters at this position are the same, move onto the next one.
    if(*(str1 + p) == *(str2 + p)) continue;
      //Return whether they are in order or not.
      return (*(str1 + p) < *(str2 + p));
  }
  //The strings are the same, so assume they must be in order!
  return 1;
}
