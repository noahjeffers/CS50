#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //takes user input and outputs it with a greeting
    string name = get_string("What is your name? ");
    printf("hello, %s\n", name);
}