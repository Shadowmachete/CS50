#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    int checksum = 0;
    int checkTwo;
    for (int i = 0; i < 16; i++)
    {
        if (number < 1000)
        {
            checkTwo = number;
        }
        // loop through the number and add
        if (i % 2 == 1)
        {
            checksum += (2 * (number % 10)) % 10 + (2 * (number % 10)) / 10;
        }
        else
        {
            checksum += number % 10;
        }
        number /= 10;
    }

    if (checksum % 10 == 0)
    {
        // getting first or first 2 digits
        printf("%i", checkTwo);
        // checking if first 2 digits satisfy condition
        if (((int) (checkTwo / 10)) == 4)
        {
            printf("VISA\n");
        }
        else if (checkTwo == 34 || checkTwo == 37)
        {
            printf("AMEX\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}