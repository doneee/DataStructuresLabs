/******************************************************************************
Name: Donald Swany
Program: Lab1/program3.c

This program does conversions between degrees in Fahrenheit and Celsius. It
handles them as floats to get an accurate conversion. It has a menu that
allows you to choose which conversion they want to do.
******************************************************************************/

//Includes
#include <stdio.h>

//Prototypes
float to_celsius(float f);
float to_fahrenheit(float c);
void pause();

//Main entry point.
int main()
{
    int choice; //An int to hold the choice that is made at the menu.
    float temp; //A float variable to store the original temperature.

    //Display the purpose and usage of this program.
    printf("\nThis program will convert between \xBA \bF and \xBA \bC.\n");
    //I use \xBA \bF because I want the degrees symbol and F/C to be next
    //  to eachother. I hope there is a more elegant way of doing that.
    
    while(1) //Infinite loop until exit is chosen. (while 1 = 1)
    {
        //Display the menu.
        printf("\nOptions are:\n1 - Fahrenheit to Celsius\n2 - Celsius to ");
        printf("Fahrenheit\n3 - Exit\n\n");
         
        //Flush buffer to get rid of any bogus data. 
        fflush(stdin);
        
        printf("Choice: "); //Prompt for desired option.
        
        //Continue to next loop if scanf gets an error.
        if (scanf("%d", &choice) < 1) { continue; }
        
        //Switch to various cases depending on the option chosen.
        switch(choice)
        {
            case 1: //Option 1 was chosen. Do F>C conversion.
                printf("Please enter a F temperature to be converted: ");
                
                //Wait for input of a float. If value is bogus, go back to menu.
                if (scanf("%f", &temp) < 1) { break; } 
                
                //Call to_celsius, passing it the temp variable, and print out
                //  results, all in one statement.
                printf("%g\xBA \bF is %.3f\xBA \bC\n", temp, to_celsius(temp));
                pause(); //Not really needed, but its part of the assignment.
                break;
                
            case 2: //Option 2 was chosen. Do C>F conversion.
                printf("Please enter a C temperature to be converted: ");
                
                //Wait for input of a float. If value is bogus, go back to menu.
                if (scanf("%f", &temp) < 1) { break; } 
                
                //Call to_fahrenheit, passing it the temp variable, and print 
                //  out results, all in one statement.
                printf("%g\xBA \bC is %.3f\xBA \bF\n", temp, to_fahrenheit(temp));
                pause(); //Not really needed, but its part of the assignment.
                break;
                
            case 3: //Option 3 was chosen. Exit program.
                return 0; //DONE!
        }
    }
}

/******************************************************************************
fuction to_celsius(temperature)
Converts a float value from Fahrenheit to Celsius.
Input: float - Some value in Fahrenheit
Returns: A float with the converted value.
******************************************************************************/
float to_celsius(float f)
{
    //Do some math. Make sure its dealing with floats!
    return (5.0/9) * (f - 32);
}

/******************************************************************************
fuction to_fahrenheit(temperature)
Converts a float value from Celsius to Fahrenheit.
Input: float - Some value in Celsius
Returns: A float with the converted value.
******************************************************************************/
float to_fahrenheit(float c)
{
    //Do some math. Make sure its dealing with floats!
    return (9.0/5) * c + 32;
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
