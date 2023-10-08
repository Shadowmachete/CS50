#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    int checksum = 0;
    printf("%li\n", number % 10);
    for (int i = 0; i < 16; i++)
    {
        checksum += 2 * (number % 10**(i*2) - number % 10**(i*2-1));
        printf("%i", checksum);
    }
}