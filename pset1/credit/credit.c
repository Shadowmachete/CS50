#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    int checksum = 0;
    for (int i = 15; i >= 0; i--)
    {
        // loop through the number and add
    }
    if (checksum % 10 == 0)
    {
        // check first 1/2 digits and print the correct thing
    }
    else
    {
        printf("INVALID");
    }
}