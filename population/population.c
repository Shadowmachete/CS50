#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startSize = 0;
    while (startSize < 9) {
        printf("Start size: \n");
        scanf("%d", &startSize);
    }
    // TODO: Prompt for end size
    int endSize = 0;
    while (endSize < startSize) {
        printf("Start size: \n");
        scanf("%d", &endSize);
    }
    // TODO: Calculate number of years until we reach threshold
    int numYears;
    numYears ++;
    // TODO: Print number of years
    printf("Years: %i\n", numYears);
}
