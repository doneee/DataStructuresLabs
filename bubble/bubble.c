/****************************************************************************/
/* File: bubble.c                                                           */
/* Author: Donald Swany                                                     */
/* Date: January 19, 2011                                                   */
/*                                                                          */
/* Bubble.c demonstrates the bubble sort algorithm. The algorithm           */
/* sorts elements of an array into ascending order making continuous        */
/* passes through the array from left to right comparing adjacent           */
/* elements. If the contents of the elements are out of order, they         */
/* are swapped. WHen a complete pass yields no more swaps, the array        */
/* is sorted.                                                               */
/*                                                                          */
/* The array is a randomly generated list of integers. The program          */
/* displays the unsorted list and pauses until the user presses             */
/* the RETURN key. It then sorts the array and displays it. All input       */
/* and output is through the standard devices.                              */
/*                                                                          */
/* Compile with:                                                            */
/*   gcc -Wall bubble.c -o bubble                                           */
/*                                                                          */
/****************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define ARRAYSIZE 25

///// funciton prototypes /////
void bubblesort ( int [ ] );
void swap ( int [ ], int, int );
void load_array ( int [ ] );
void display_array ( int [ ], int );
void pause ( void );

int main ( )
{
	int list [ ARRAYSIZE ]; // storage for list to be sorted
	
	load_array ( list );
	display_array ( list, ARRAYSIZE );
	pause ( );
	bubblesort ( list );
	display_array ( list, ARRAYSIZE );
	
	return 0;
}

///////////////////////////////////////////////////////////////////
// Sorts elements of an array into ascending order using         //
// bubble sort algorithm                                         //
// Parameters:                                                   //
//   array - list of integers to be sorted                       //
// Returns:                                                      //
//   nothing                                                     //
///////////////////////////////////////////////////////////////////
void bubblesort ( int array [ ] )
{
	int swaps; // swap counter
	int i;     // loop counter
	
	// make continuous passes through array comparing adjacent
	// elements, when a pass yeilds no more swaps, array is
	// sorted
	do {
		swaps = 0; // make sure counter is reset for each pass
		for ( i = 0; i < ARRAYSIZE - 1; i ++) {
			// compare elements, swap if out of order
			if ( array [ i ] > array [ i + 1 ] ) {
				swap ( array, i, i + 1 );
				swaps ++;
			}	
		}		
	} while ( swaps > 0 );
}

///////////////////////////////////////////////////////////////////
// Swaps the contents of two array elements                      //
// Parameters:                                                   //
//   x - first element                                           //
//   y - element immediate right if x                            //
// Returns:                                                      //
//   nothing                                                     //
///////////////////////////////////////////////////////////////////
void swap ( int a [ ], int x, int y )
{
	int temp; // temporarily holds first value while swapping
	
	temp = a [ x ];
	a [ x ] = a [ y ];
	a [ y ] = temp;
	return;
}
///////////////////////////////////////////////////////////////////
// Loads an array with randomly selected numbers between         //
// 0 and 99                                                      //
// Parameters:                                                   //
//   array - list of integers to be sorted                       //
// Returns:                                                      //
//   nothing                                                     //
///////////////////////////////////////////////////////////////////

void load_array ( int list[ ] )
{
	int c; // loop counter
	
	// seed random number generator using system clock
	srand ( ( unsigned int ) time ( NULL ) );
	// generate the proper number of values
	for ( c = 0; c < ARRAYSIZE; c ++ )
		// get a random inteer and scale to 2 digits
		list [ c ] = rand ( ) % 100;
	return;
}

///////////////////////////////////////////////////////////////////
// Displays array elements on the same line with a space between //
// Parameters:                                                   //
//   array - list of integers to be sorted                       //
//   size - number of elements in the array                      //
// Returns:                                                      //
//  nothing                                                      //
///////////////////////////////////////////////////////////////////
void display_array ( int array [ ], int size )
{
	int i; //loop counter
	
	printf ( "\n" );
	for ( i = 0; i < size; i ++ )
		printf ( "%d ", array [ i ] );
	printf ( "\n\n" );
	return;
}

///////////////////////////////////////////////////////////////////
// Pause the program until the user hits RETURN                  //
// Parameters:                                                   //
//   none                                                        //
// Returns:                                                      //
//  nothing                                                      //
///////////////////////////////////////////////////////////////////
void pause ( void )
{
	printf ( "Press ENTER to continue ..." );
	getchar ( );
	return;
}
