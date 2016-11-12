/**********************************************************************
Name: Donald Swany
Program: Lab1/program1.c

This program creates some variables, initializing some of the 
variables, and assigning values to the others after declaration. It 
then prints out the values using multiple printf statements.
**********************************************************************/

//Includes
#include <stdio.h>

//Main entry point.
int main()
{
    //Declare variables and initialize some of them with arbitrary values.
    char   cu, ci = 'A';         //Empty char; char with arbitrary value.
    short  su, si = 10;          //Empty short; short with arbitrary value.
    int    iu, ii = 9;           //Empty int; int with arbitrary value.
    long   Lu, Li = 0xFF7000;    //Empty long; long with arbitrary value.
    float  fu, fi = 98.6f;       //Empty float; float with arbitrary value.
    double du, di = 30.6435235f; //Empty double; double with arbitrary value.
    
    //Describe what the program is doing.
    printf("This program creates various 'initialized' and 'assigned' "); 
    printf("variables, and prints them to the screen.\n\n");
    
    
    //Print the variable name and values of each of the initialized
    //  variables on new lines with separate printfs.
    printf("Variables that have been 'intialized': \n");
    printf("char 'ci' = %c\n", ci);
    printf("short 'si' = %hi\n", si);
    printf("int 'ii' = %i\n", ii);
    printf("long 'Li' = %li\n", Li);
    printf("float 'fi' = %f\n", fi);
    printf("double 'du' = %lf\n", di);    
    printf("\n");
    
    //Assign arbitrary values to Empty variables.
    cu = 'B';
    su = 49;
    iu = 573;
    Lu = 0xABCDEF;
    fu = 26.2f;
    du = 2334.33252352f;
    
    //Print the float and double names and values on a single line, 
    //  single printf.
    printf("'Assigned' float variable values: \n");
    printf("float 'fu' = %f, double 'du' = %lf.\n", fu, du);
    printf("\n");
    
    //Print out decimal names and values on a single line.
    printf("'Assigned' number variable values: \n");
    printf("short 'su' = %hi, ", su);
    printf("int 'iu' = %i, ", iu);
    printf("long 'Lu' = %li\n", Lu);
    printf("\n");
    
    //Print out the assigned char name and value
    printf("'Assigned' char variable value: \n");
    printf("char 'cu' = %c\n", cu);    
    
    return 0; //DONE!
}
