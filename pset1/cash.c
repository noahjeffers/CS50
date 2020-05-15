#include <cs50.h>
#include <stdio.h>
#include <math.h>


//finds the minimum nunmber of coins that can be used to make change
int main(void)
{
    int cent;
    //prompts the user until the enter a valid input
    do
    {
        cent = round((get_float("Change owed: ")) * 100);
    }
    while (cent <= 0);
    
    //finds out how many quarters are needed 
    int quarters = cent / 25;
    int change = cent % 25;
    
    //finds out how many dimes are needed 
    int dimes = (change) / 10;
    change = change % 10;
    
    //finds out how many nickels are needed
    int nickels = (change) / 5;
    change = change % 5;

    //finds out how many pennies are needed
    int pennies = (change) / 1;
    
    int total_change = quarters + dimes + nickels + pennies;
    printf("%i\n", total_change);
}