/******************************************************************************
Name: Donald Swany
Program: Lab1/program2.c

This program creates some intitialized variables, then prints out the variable
names, values, byte size, and memory location.
******************************************************************************/

//Includes
#include <stdio.h>

//prototype function called print_var_info.
void print_var_info(char cname[6], char cvar, 
                    char sname[6], short svar,
                    char iname[6], int ivar, 
                    char lname[6], long lvar, 
                    char fname[6], float fvar, 
                    char dname[6], double dvar);

                    
//Main entry point.
int main()
{
    char   var_c = 'D';            //char with arbitrary value.
    short  var_s = 10;             //short with arbitrary value.
    int    var_i = 1337;           //int with arbitrary value.
    long   var_l = -573;           //long with arbitrary value.
    float  var_f = 3.23432;        //float with arbitrary value.
    double var_d = 2342.764574643; //double with arbitrary value.
    
    //State the purpose of the program.
    printf("This program will declare and initialize some ");
    printf("variables, then pass them \nto a function that ");
	printf("will print them to the screen.\n\n");
    
    //Pass the variable names as literals and the variables, themselves,
    //    to the function print_var_info.
    print_var_info( "var_c", var_c,
                    "var_s", var_s,
                    "var_i", var_i,
                    "var_l", var_l,
                    "var_f", var_f,
                    "var_d", var_d);
    
    return 0; //DONE!
}

/******************************************************************************
Function: print_var_info(...)
This function takes takes a variable and a char array at a max of 5 characters 
and prints them out with the byte size and address of said variable.

Input: Alternating char array for variable name, then the variable, itself. 
6 variables total.
Returns: Nothing.
*******************************************************************************/
void print_var_info(char cname[6], char cvar, 
                    char sname[6], short svar,
                    char iname[6], int ivar, 
                    char lname[6], long lvar, 
                    char fname[6], float fvar, 
                    char dname[6], double dvar)
{
    //Print char var_c name, contents, size, and memory location.
    printf("Variable '%s' = '%c', and it's size is %d bytes @ 0x%p.\n", 
        cname, cvar, sizeof(cvar), &cvar);
    
    //Print short var_s name, contents, size, and memory location.
    printf("Variable '%s' = '%hd', and it's size is %d bytes @ 0x%p.\n", 
        sname, svar, sizeof(svar), &svar);
    
    //Print int var_i name, contents, size, and memory location.
    printf("Variable '%s' = '%d', and it's size is %d bytes @ 0x%p.\n", 
        iname, ivar, sizeof(ivar), &ivar);
    
    //Print long var_l name, contents, size, and memory location.
    printf("Variable '%s' = '%ld', and it's size is %d bytes @ 0x%p.\n", 
        lname, lvar, sizeof(lvar), &lvar);
    
    //Print float var_f name, contents, size, and memory location.
    printf("Variable '%s' = '%f', and it's size is %d bytes @ 0x%p.\n", 
        fname, fvar, sizeof(fvar), &fvar);
    
    //Print double var_d name, contents, size, and memory location.
    printf("Variable '%s' = '%lf', and it's size is %d bytes @ 0x%p.\n", 
        dname, dvar, sizeof(dvar), &dvar);
    
    return;
}
