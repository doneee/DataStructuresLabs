/******************************************************************************
Name: Donald Swany
Program: Lab7
File: lab7.c
Misc. Loads fortunes from file and displays a random fortune.
******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Prototypes
int compare(const void *, const void *);
void pause();

//Main function
int main(int argc, char *argv[])
{
  //default number of fortunes.
  int n_count = 50;
  
  //Create an arrays based on size of n_count.
  long f_offsets[n_count];
  int f_used[n_count];
  int total = 1; //Holds total number of fortunes.
  
  int f_count = 0; //Holds current number of used fortunes.
  int i; //Incrementer variable.
  int tmp = 0; //Temp variable.
  char ch; //To hold current character as it scans file.
  char buffer[81];
  
  //Set f_used array to all zero.
  for(i = 0; i < (n_count - 1); i++)
    f_used[i] = 0;
  
  FILE *fort; //Fortune file pointer.
  
  //Open file, if error then exit.
  if( ! (fort = fopen("fortune.dat", "r")))
  {
    printf("Error loading file!\n");
    return 1;
  }
  
  f_offsets[0] = 0;
  while(((ch = fgetc(fort)) != EOF) && (total < n_count))
    if(ch == '\n' && fgetc(fort) == '\n')
      f_offsets[total++] = ftell(fort);  
  //Seed rand with current time.
  srand(time(NULL));
  
  while(1)
  {
    //Loop until it finds an unused number.
    while(f_used[(tmp = rand() % total)]);
    //Flag as used.
    f_used[tmp] = 1;
    //Add to used count.
    f_count++;
    
    //Keep printing out lines until it runs into a blank line.
    fseek(fort, f_offsets[tmp], SEEK_SET);    
    do
    {
      //If it reaches EOF before it finds two consecutive newlines, print a
      //  newline out and break the loop.
      if( ! fgets(buffer, 81, fort))
      {
        printf("\n"); 
        break;
      }
      printf("%s", buffer);
    }
    while(*buffer != '\n');
    
    
    //If all fortunes are used, reset everthing back to zero.
    if(f_count >= total)
    {
      for(i = 0; i < total; i++)
        f_used[i] = 0;
      f_count = 0;
    }
    
    fflush(stdin);
    printf("Press ENTER for another, or anything else to exit.\n");
    switch(fgetc(stdin))
    {
      case '\n': //Continue to give fortunes.
        continue;
      default: //Anything else: close the file and quit.
        fclose(fort);
        return 0;
    }
  }
}
