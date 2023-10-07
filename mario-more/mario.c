#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int pyramidHeight = 0;
    while ((pyramidHeight < 1) || (pyramidHeight > 8)) {
        printf("Input a height for the pyramid (between 1 and 8 inclusive): ");
        scanf("%d", &pyramidHeight);
    }
    for (layer = 1; layer < pyramidHeight + 1; layer++) {
        printf(" "*)
    }
    printf("%i", pyramidHeight);
}