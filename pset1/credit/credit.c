#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    char checksum[256];
    sprintf(checksum, "%li", number);
    for (int i = 15; i >= 0; i--)
    {
        if (i % 2 == 0)
        {
            printf("%c\n", checksum[i]);
        }
        else
        {
            
        }
    }
    if (true)
    {
        printf("asdyfyaudyda\n");
    }
}