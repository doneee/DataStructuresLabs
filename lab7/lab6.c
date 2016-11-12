/******************************************************************************
Name: Donald Swany
Program: Lab6
File: lab6.c
Misc. Generates random numbers, sorts them with qsort, then displays them in
three separate columns.
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
  //default number of integers.
  int n_count = 25;
  
  //If command-line arguement is supplied, store it in n_count.
  if (argc > 1) n_count = atoi(argv[1]) > 0 ? atoi(argv[1]) : n_count;

  //Create an array based on size of n_count.
  int rand_nums[n_count];
  //Incrementer variable.
  int i;
  
  printf("Custom size usage: %s <int>\n", argv[0]);
  
  //Seed rand with current time.
  srand(time(NULL));
  
  //Fill rand_nums with random numbers.
  for(i = 0; i < n_count; i++)
    rand_nums[i] = rand();
  
  //Call qsort to sort the integers.
  qsort(rand_nums, n_count, sizeof(rand_nums[0]), compare);
  
  //Print numbers out into three columns.
  for(i = 0; i < n_count / 3; i++)
  {
    //Print first row item.
    printf("%2d: %-10d ", 1 + i, rand_nums[i]);
    //Do some math to find which item to print next.
    printf("%2d: %-10d ", 1 + i + n_count / 3 + (n_count % 3 ? 1 : 0), 
      rand_nums[i + n_count / 3 + (n_count % 3 ? 1 : 0)]);
    //Same as above.
    printf("%2d: %-10d ", 1 + i + n_count / 3  * 2 + (n_count % 3), 
      rand_nums[i + n_count / 3 * 2 + (n_count % 3)]);
    //Print newline.
    printf("\n");
    
    //Pause every 20 lines.
    if (! ((i + 1) % 20))
      pause();
      
  }
  
  //Print out final row with any remaining numbers.
  if(n_count % 3) printf("%2d: %-10d ", n_count / 3 + 1, rand_nums[n_count / 3]);
  if(n_count % 3 > 1) printf("%2d: %-10d ", n_count / 3 * 2 + 2, rand_nums[n_count / 3 * 2 + 1]);
  printf("\n");
  
  return 0;
}

/******************************************************************************
fuction compare()
Function used with qsort to sort integers
Input: Two numbers: x, y
Returns: +1 if out of order, -1 if not.
******************************************************************************/
int compare(const void *x, const void *y)
{
  return (*(int *)x > *(int *)y) ? 1 : -1;
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
