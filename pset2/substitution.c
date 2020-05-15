#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int returnValue = 0;
    // Checks that the user has provided a value at runtime AND that the length of the value is long enough
    if (argc != 2)
    {
        returnValue = 1;
        printf("Usage: ./substitution key");
    }
    else if (strlen(argv[1]) != 26)
    {
        returnValue = 1;
        printf("Key must contain 26 characters.");
    }
    else
    {
        //this for loop checks to make sure that there are no duplicates in the Key
        for (int i = 0; i < 26; i++)
        {
            //makes sure that the key is made up of letters
            if (isalpha(argv[1][i]))
            {
                for (int j = i + 1; j < 26; j++)
                {
                    //compares the letter at the index of the first loop with the letter
                    //   at the index of the second loop to make sure that the are unique
                    if (argv[1][i] == argv[1][j])
                    {
                        printf("No duplicates allowed in key");
                        return 1;
                    }
                }
            }
            //prints an error message if a number is found in the key.
            else
            {
                printf("No numbers allowed in the key.");
                return 1;
            }
        }

        //gets a string to be encrypted
        string input = get_string("plaintext: ");
        int n = strlen(input);
        printf("ciphertext: ");
        //loops through the input encrypting each letter with the equivalent in the key
        for (int i = 0; i < n; i++)
        {
            char output = ' ';
            //using tolower on the input to make comparison easier
            //
            //using a switch to sort the input, and give it the correct value from the key
            switch (tolower(input[i]))
            {
                case 'a':
                    output = argv[1][0];
                    break;
                case 'b':
                    output = argv[1][1];
                    break;
                case 'c':
                    output = argv[1][2];
                    break;
                case 'd':
                    output = argv[1][3];
                    break;
                case 'e':
                    output = argv[1][4];
                    break;
                case 'f':
                    output = argv[1][5];
                    break;
                case 'g':
                    output = argv[1][6];
                    break;
                case 'h':
                    output = argv[1][7];
                    break;
                case 'i':
                    output = argv[1][8];
                    break;
                case 'j':
                    output = argv[1][9];
                    break;
                case 'k':
                    output = argv[1][10];
                    break;
                case 'l':
                    output = argv[1][11];
                    break;
                case 'm':
                    output = argv[1][12];
                    break;
                case 'n':
                    output = argv[1][13];
                    break;
                case 'o':
                    output = argv[1][14];
                    break;
                case 'p':
                    output = argv[1][15];
                    break;
                case 'q':
                    output = argv[1][16];
                    break;
                case 'r':
                    output = argv[1][17];
                    break;
                case 's':
                    output = argv[1][18];
                    break;
                case 't':
                    output = argv[1][19];
                    break;
                case 'u':
                    output = argv[1][20];
                    break;
                case 'v':
                    output = argv[1][21];
                    break;
                case 'w':
                    output = argv[1][22];
                    break;
                case 'x':
                    output = argv[1][23];
                    break;
                case 'y':
                    output = argv[1][24];
                    break;
                case 'z':
                    output = argv[1][25];
                    break;
                default:
                    output = input[i];
                    break;
            }
            //using an if else to deal with capitalization of the input
            //
            //as the capitalization of the key provided doesn't matter
            //it is the capitalization of the input that is relevant
            if (isupper(input[i]))
            {
                //if the input character at current index is uppercase,
                //we use toupper to make the output uppercase as well
                output = toupper(output);
            }
            else
            {
                //if the input character at current index is lowercase,
                //we use to tolower to make the output lowercase as well
                output = tolower(output);
            }
            printf("%c", output);
        }
    }
    printf("\n");
    return returnValue;
}
