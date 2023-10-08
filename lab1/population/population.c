#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startSize = 0;
    do
    {
        printf("Start size: ");
        scanf("%d", &startSize);
    }
    while (startSize < 9);
    // TODO: Prompt for end size
    int endSize = 0;
    do
    {
        printf("End size: ");
        scanf("%d", &endSize);
    }
    while (endSize < startSize);
    // TODO: Calculate number of years until we reach threshold
    int numYears;
    int numBirths;
    int numDeaths;
    while (startSize < endSize) {
        numBirths = (int) startSize / 3;
        numDeaths = (int) startSize / 4;
        startSize += numBirths;
        startSize -= numDeaths;
        numYears++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", numYears);
}
