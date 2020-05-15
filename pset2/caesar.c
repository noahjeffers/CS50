#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //sets the return value to 0
    int returnValue = 0;

    //checks to see if there are the correct number of arguments passed at runtime
    if (argc != 2)
    {
        printf("error");
        return 1;
    }

    for (int i =0, n = strlen(argv[1]); i < n; i++)
    {
        if(!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //converts the value inputted at runtime into an int
    int k = atoi(argv[1]);
    if (k > 0 && argc == 2)
    {

        //prompts the user for the plaintext
        string input = get_string("plaintext: ");
        int output = 0;
        printf("ciphertext: ");

        //retrieves the length of the string
        int stringLength = strlen(input);

        //loops through the input string encrypting the value with the arguement passed at runtime
        for (int i = 0; i < stringLength; i++)
        {
            if(isalpha(input[i]))
            {
                output = input[i] + k;

                //if the Character at the current index is uppercase it processes it here
                if (isupper(input[i]) && output > 90)
                {
                    do
                    {
                        output = output - 26;
                    }
                    while (output > 90);
                }
                //if the charachter at the current index is lowercase it is processed here
                else if (output > 122)
                {
                    do
                    {
                        output = output - 26;
                    }
                    while (output > 122);
                }
            }
            else
            {
                output =input[i];
                returnValue = 0;
            }
            printf("%c", output);
        }


        returnValue = 0;
    }
    else
    {
        printf("Usage: ./caesar key");
        returnValue = 1;
    }
    printf("\n");
    return returnValue;
}
