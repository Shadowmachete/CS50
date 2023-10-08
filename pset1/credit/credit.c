#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    int checksum = 0;
    for (int i = 0; i < 16; i++)
    {
        // loop through the number and add
        checksum += number % 10;
        number /= 10;
    }
    printf("%i\n", checksum);
    if (checksum % 10 == 0)
    {
        // check first 1/2 digits and print the correct thing
    }
    else
    {
        printf("INVALID\n");
    }
}