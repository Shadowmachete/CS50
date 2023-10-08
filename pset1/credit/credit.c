#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    char checksum[256];
    sprintf(checksum, "%li", number);
    int sum = 0;
    for (int i = 15; i >= 0; i--)
    {
        printf("%i", checksum[i]);
        if (i % 2 == 0)
        {
            sum += 2 * (int) checksum[i];
        }
        else
        {
            sum += (int) checksum[i];
        }
        printf("%i\n", sum);
    }
    if (number % 10 == 0)
    {
        if (checksum[1] + checksum[2] == 34 || checksum[1] + checksum[2] == 37)
        {
            printf("AMEX\n");
        }
    }
}