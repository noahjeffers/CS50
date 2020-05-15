#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string output = " ";
    long input; 
    int total = 0;
    
    //Makes sure that the Credit Card entered is greater than 0
    do
    {
        input = get_long("Number: ");
    
    }
    while (input < 1);
    
    int length = 0;
    long validCreditCardNumber = input;
    
    //determines how many digits are in the credit card number
    while (validCreditCardNumber > 0)
    {
        validCreditCardNumber = validCreditCardNumber / 10;
        length++;
    }
    
    //if the length of the input is one of the accepted values it proceeds through to determine the checksum
    //otherwise it is declared Invalid
    if (length == 13 || length == 15 || length == 16)
    {
        //counting from the end of the Credit Card Number
        int second     = ((input % 100) / 10) * 2;
        int fourth     = ((input % 10000) / 1000) * 2;
        int sixth      = ((input % 1000000) / 100000) * 2;
        int eigth      = ((input % 100000000) / 10000000) * 2;
        int tenth      = ((input % 10000000000) / 1000000000) * 2;
        int twelfth    = ((input % 1000000000000) / 100000000000) * 2;
        int fourteenth = ((input % 100000000000000) / 10000000000000) * 2;
        int sixteenth  = ((input % 10000000000000000) / 1000000000000000) * 2;
        
        //finds the first and second digits of the checksum values
        total += (second / 10) + (second % 10);
        total += (fourth / 10) + (fourth % 10);
        total += (sixth / 10) + (sixth % 10);
        total += (eigth / 10) + (eigth % 10);
        total += (tenth / 10) + (tenth % 10);
        total += (twelfth / 10) + (twelfth % 10);
        total += (fourteenth / 10) + (fourteenth % 10);
        total += (sixteenth / 10) + (sixteenth % 10);
        
        //finds the checksum values that don't get multiplied by 2
        total += (input % 10);                            //last digit
        total += (input % 1000) / 100;                      //third last digit
        total += (input % 100000) / 10000;                  //fifth last digit
        total += (input % 10000000) / 1000000;              //seventh last digit
        total += (input % 1000000000) / 100000000;          //ninth last digit
        total += (input % 100000000000) / 10000000000;      //eleventh last digit
        total += (input % 10000000000000) / 1000000000000;  //thirteenth last digit
        total += (input % 1000000000000000) / 100000000000000;//fifteenth last digit
        
        //if the checksum total ends in 0 it is a valid card number
        if ((total % 10) == 0)
        {
            if ((input / 10000000000000) == 34 || (input / 10000000000000) == 37)
            {
                output = "AMEX";
            }
            else if ((input / 100000000000000) > 50 && (input / 100000000000000) < 56)
            {
                output = "MASTERCARD";
            }
            else if ((input / 1000000000000) == 4 || (input / 1000000000000000) == 4)
            {
                output = "VISA";
            }
            else
            {
                output = "INVALID";
            }
        }
        else
        {
            output = "INVALID";
        }
    }
    else
    {
        output = "INVALID";
    }
    printf("%s\n", output);
}



