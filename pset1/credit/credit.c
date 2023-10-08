#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    int checksum = 0;
    printf("%li\n", number % 10);
    for (int i = 1; i < 16; i++)
    {

    }
}