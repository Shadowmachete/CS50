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
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBlue = 0, sumGreen = 0, sumRed = 0, total = 0;
            for (int vertical_shift = -1; vertical_shift <= 1; vertical_shift++)
            {
                for (int horizontal_shift = -1; horizontal_shift <= 1; horizontal_shift++)
                {
                    if (i + vertical_shift < 0 || i + vertical_shift > height || j + horizontal_shift < 0 || j + horizontal_shift > width)
                    {
                        continue;
                    }
                    else
                    {
                        sumBlue += image[i+vertical_shift][j+horizontal_shift].rgbtBlue;
                        sumGreen += image[i+vertical_shift][j+horizontal_shift].rgbtGreen;
                        sumRed += image[i+vertical_shift][j+horizontal_shift].rgbtRed;
                        total += 1;
                    }
                }
            }
            new_image[i][j].rgbtBlue = (int) round(sumBlue / (total * 1.0));
            new_image[i][j].rgbtGreen = (int) round(sumGreen / (total * 1.0));
            new_image[i][j].rgbtRed = (int) round(sumRed / (total * 1.0));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][i].rgbtBlue = new_image[i][j].rgbtBlue;
            image[i][i].rgbtGreen = new_image[i][j].rgbtGreen;
            image[i][i].rgbtRed = new_image[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3];
    Gx[0][0] = -1;
    Gx[0][1] = 0;
    Gx[0][2] = 1;
    Gx[1][0] = -2;
    Gx[1][1] = 0;
    Gx[1][2] = 2;
    Gx[2][0] = -1;
    Gx[2][1] = 0;
    Gx[2][2] = 1;

    int Gy[3][3];
    Gy[0][0] = -1;
    Gy[0][1] = -2;
    Gy[0][2] = -1;
    Gy[1][0] = 0;
    Gy[1][1] = 0;
    Gy[1][2] = 0;
    Gy[2][0] = 1;
    Gy[2][1] = 2;
    Gy[2][2] = 1;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gx_blue = 0, Gy_blue = 0, Gx_green = 0, Gy_green = 0, Gx_red = 0, Gy_red = 0;
            for (int vertical_shift = -1; vertical_shift <= 1; vertical_shift++)
            {
                for (int horizontal_shift = -1; horizontal_shift <= 1; horizontal_shift++)
                {
                    if (i + vertical_shift < 0 || i + vertical_shift > height || j + horizontal_shift < 0 || j + horizontal_shift > width)
                    {
                        continue;
                    }
                    else
                    {
                        Gx_blue += image[i+vertical_shift][j+horizontal_shift].rgbtBlue * Gx[1+vertical_shift][1+horizontal_shift];
                        Gx_green += image[i+vertical_shift][j+horizontal_shift].rgbtGreen * Gx[1+vertical_shift][1+horizontal_shift];
                        Gx_red += image[i+vertical_shift][j+horizontal_shift].rgbtRed * Gx[1+vertical_shift][1+horizontal_shift];

                        Gy_blue += image[i+vertical_shift][j+horizontal_shift].rgbtBlue * Gy[1+vertical_shift][1+horizontal_shift];
                        Gy_green += image[i+vertical_shift][j+horizontal_shift].rgbtGreen * Gy[1+vertical_shift][1+horizontal_shift];
                        Gy_red += image[i+vertical_shift][j+horizontal_shift].rgbtRed * Gy[1+vertical_shift][1+horizontal_shift];
                    }
                }
            }
            image[i][j].rgbtBlue = (int) round(sqrt(pow(Gx_blue, 2) + pow(Gy_blue, 2))) < 255 ? (int) round(sqrt(pow(Gx_blue, 2) + pow(Gy_blue, 2))) : 255;
            image[i][j].rgbtGreen = (int) round(sqrt(pow(Gx_green, 2) + pow(Gy_green, 2))) < 255 ? (int) round(sqrt(pow(Gx_green, 2) + pow(Gy_green, 2))) : 255;
            image[i][j].rgbtRed = (int) round(sqrt(pow(Gx_red, 2) + pow(Gy_red, 2))) < 255 ? (int) round(sqrt(pow(Gx_red, 2) + pow(Gy_red, 2))) : 255;
        }
    }
    return;
}
