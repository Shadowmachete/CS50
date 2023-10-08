#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Input your credit card number: ");
    char checksum[256];
    sprintf(checksum, "%li", number);
    for (int i = 0; i < 16; i++)
    {
        printf("%c\n", checksum[i]);
    }
    if (true)
    {
        printf("asdyfyaudyda\n");
    }
}