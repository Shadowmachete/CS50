#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    int checksum = 0;
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

    if (checksum % 10 == 0)
    {
        // getting first or first 2 digits
        long checkFirstTwo = number;
        printf("%li, %li\n", checkFirstTwo, (checkFirstTwo / 10));
        while (checkFirstTwo >= 100)
        {
            checkFirstTwo /= 10;
        }
        printf("%li, %li\n", checkFirstTwo, (checkFirstTwo / 10));
        // checking if first 2 digits satisfy condition
        if (((int) (checkFirstTwo / 10)) == 4)
        {
            printf("VISA\n");
        }
        else if (checkFirstTwo == 34 || checkFirstTwo == 37)
        {
            printf("AMEX\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}