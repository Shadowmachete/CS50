#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    long checksum = 0;
    for (int i = 1; i < 16; i++)
    {
        if (i % 2 == 0)
        {
            checksum += 2 * number % 10;
        }
        else
        {
            checksum += number % 10;
        }
        checksum /= 10;
    }
    printf("%li\n", checksum);
}