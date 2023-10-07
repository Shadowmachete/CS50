#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startSize = 0;
    do {
        printf("Start size: \n");
        scanf("%d", &startSize);
    }
    while (startSize < 9);
    // TODO: Prompt for end size
    int endSize = 0;
    do {
        printf("Start size: \n");
        scanf("%d", &endSize);
    }
    while (endSize < startSize);
    // TODO: Calculate number of years until we reach threshold
    int numYears;
    numYears ++;
    // TODO: Print number of years
    printf("Years: %i\n", numYears);
}
