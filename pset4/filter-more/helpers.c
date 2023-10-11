#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int grayed_value = (int) round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = grayed_value;
            image[i][j].rgbtGreen = grayed_value;
            image[i][j].rgbtRed = grayed_value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < (width / 2); i++)
    {
        for (int j = 0; j < height; j++)
        {
            int tempBlue, tempGreen, tempRed;
            // flip blue
            tempBlue = image[j][i].rgbtBlue;
            image[j][i].rgbtBlue = image[j][width-i-1].rgbtBlue;
            image[j][width-i-1].rgbtBlue = tempBlue;

            // flip green
            tempGreen = image[j][i].rgbtGreen;
            image[j][i].rgbtGreen = image[j][width-i-1].rgbtGreen;
            image[j][width-i-1].rgbtGreen = tempGreen;

            // flip red
            tempRed = image[j][i].rgbtRed;
            image[j][i].rgbtRed = image[j][width-i-1].rgbtRed;
            image[j][width-i-1].rgbtRed = tempRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int vertical_shift = -1; vertical_shift <= 1; vertical_shift++)
            {
                for (int horizontal_shift = -1; horizontal_shift <= 1; horizontal_shift++)
                {
                    if (i + vertical_shift < 0 || i + vertical_shift > height || j + horizontal_shift < 0 || j + horizontal_shift > width)
                    {
                        printf("Wall edge, i = %i, j = %i, vertical = %i, horizontal = %i\n", i, j, vertical_shift, horizontal_shift);
                    }
                }
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
