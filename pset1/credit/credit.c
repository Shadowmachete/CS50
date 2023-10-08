#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    int checksum = 0;
    long checkTwo = number + 0;
    for (int i = 0; i < 16; i++)
    {
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
    if ((checksum % 10 == 0) && (checkTwo > pow(10, 13)) && (checkTwo < pow(10, 15)))
    {
        // getting first or first 2 digits
        while (checkTwo > 100)
        {
            checkTwo /= 10;
        }
        // checking if first 2 digits satisfy condition
        if (((int) (checkTwo / 10)) == 4)
        {
            printf("VISA\n");
        }
        else if (checkTwo == 34 || checkTwo == 37)
        {
            printf("AMEX\n");
        }
        else if (checkTwo == 51 || checkTwo == 52 || checkTwo == 53 || checkTwo == 54 || checkTwo == 55)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}