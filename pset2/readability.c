#include <string.h>
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    string input = get_string("Text: ");
    string output;
    int n = strlen(input);

    // l will be the nummber of letters in the text input
    float l = 0;
    // w will be the number of words in the text input.
    // it will be determined by counting the spaces in the input.
    //
    // its initial value is 1 because the last word will be followed by a . not a space
    float w = 1;
    // s will be the number of sentences in the text input
    // this will be determined by counting . ! ?
    float s = 0;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(input[i]))
        {
            l++;
        }

        if (isspace(input[i]))
        {
            w++;
        }

        if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            s++;
        }
    }

    // L is the average number of letters per 100 words in the text
    // S is the average number of sentences per 100 words in the text
    float L = 100 * (l / w);
    float S = 100 * (s / w);

    //uses the formula provided to determine the Grade Level of the input text.
    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index >= 1 && index < 16)
    {
        printf("Grade %.0f", index);
    }
    else if (index > 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Before Grade 1");
    }

    printf("\n");
}
