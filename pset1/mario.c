#include <cs50.h>
#include <stdio.h>

int get_valid_input(void);
int find_spaces(int n);

int main(void)
{
    //gets a valid input for the height of the pyramid
    int input = get_valid_input();
    for (int i = 1; i <= input; i++)
    {
        //prints out the spaces to format the left pyramid
        for (int j = input; j > i; j--)
        {
            printf(" ");
        }
        
        // prints out the pound symbol to create the left pyarmid
        for (int h = 0; h < i; h++)
        {
            printf("#");
        }
        // creates the gap between the pyramids
        printf("  ");
        //prints the right pyramid
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");

    }
}

//returns a valid int between 1-8(inclusive)
int get_valid_input(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}
