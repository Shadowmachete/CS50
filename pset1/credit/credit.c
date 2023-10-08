#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    int checksum = 0;
    for (int i = 0; i < 16; i++)
    {
        // loop through the number and add
        if (i % 10 == 1)
        {
            checksum += 2 * number % 10;
        }
        else
        {
            checksum += number % 10;
        }
        number /= 10;
        printf("%li %i\n", number, checksum);
    }
    if (checksum % 10 == 0)
    {
        // check first 1/2 digits and print the correct thing
    }
    else
    {
        printf("INVALID\n");
    }
}