#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int pyramidHeight = 0;
    while ((pyramidHeight < 1) || (pyramidHeight > 8)) {
        printf("Input a height for the pyramid (between 1 and 8 inclusive): ");
        scanf("%d", &pyramidHeight);
    }
    for (int layer = 1; layer < pyramidHeight + 1; layer++) {
        // spaces until the start of the brick
        for (int i = 1; i < pyramidHeight - layer + 1; i++) {
            printf(" ");
        }
        // left half of the wall
        for (int i = 1; i < layer + 1; i++) {
            printf("#");
        }
        // space in the middle
        printf("  ");

        // right half of the wall
        for (int i = 1; i < layer + 1; i++) {
            printf("#");
        }
        printf("\n");
    }
}