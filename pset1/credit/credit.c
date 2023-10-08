#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    int checksum = 0;
    printf("%li\n", number % 10);
    for (int i = 1; i < 16; i++)
    {
        long higherPower = pow(10, i);
        long lowerPower = pow(10, i-1);
        if (i % 2 == 0) {
            checksum += 2 * (number % higherPower - number % lowerPower);
        }
        else
        {
            checksum += number % higherPower - number % lowerPower;
        }
        printf("%i\n", checksum);
    }
}