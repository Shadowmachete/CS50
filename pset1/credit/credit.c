#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    long checksum[14];
    printf("%li\n", number % 10);
    for (int i = 1; i < 16; i++)
    {
        if (i % 2 == 0)
        {
            checksum[i] = 2 * number % 10;
        }
        else
        {
            checksum[i] = number % 10;
        }
        printf("%li", checksum);
    }
}