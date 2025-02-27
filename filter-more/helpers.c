#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int val_gra = (int) round(
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = val_gra;
            image[i][j].rgbtGreen = val_gra;
            image[i][j].rgbtBlue = val_gra;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width) / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double val_red = 0.0;
            double val_green = 0.0;
            double val_blue = 0.0;
            double cnt = 0.0;

            for (int row = -1; row < 2; row++)
            {
                for (int col = -1; col < 2; col++)
                {
                    if (i + row < height && i + row > -1 && j + col < width && j + col > -1)
                    {
                        val_red += image[i + row][j + col].rgbtRed;
                        val_green += image[i + row][j + col].rgbtGreen;
                        val_blue += image[i + row][j + col].rgbtBlue;
                        cnt++;
                    }
                    else
                    {
                        continue;
                    }
                }
            }

            tmp[i][j].rgbtRed = (int) round(val_red / cnt);
            tmp[i][j].rgbtGreen = (int) round(val_green / cnt);
            tmp[i][j].rgbtBlue = (int) round(val_blue / cnt);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int val_Gx_red = 0;
            int val_Gy_red = 0;
            int val_Gx_green = 0;
            int val_Gy_green = 0;
            int val_Gx_blue = 0;
            int val_Gy_blue = 0;
            int val_red = 0;
            int val_green = 0;
            int val_blue = 0;

            for (int row = -1; row < 2; row++)
            {
                for (int col = -1; col < 2; col++)
                {
                    if (i + row < height && i + row > -1 && j + col < width && j + col > -1)
                    {
                        int r = row + 1;
                        int c = col + 1;

                        val_Gx_red += (image[i + row][j + col].rgbtRed * Gx[r][c]);
                        val_Gy_red += (image[i + row][j + col].rgbtRed * Gy[r][c]);
                        val_Gx_green += (image[i + row][j + col].rgbtGreen * Gx[r][c]);
                        val_Gy_green += (image[i + row][j + col].rgbtGreen * Gy[r][c]);
                        val_Gx_blue += (image[i + row][j + col].rgbtBlue * Gx[r][c]);
                        val_Gy_blue += (image[i + row][j + col].rgbtBlue * Gy[r][c]);
                    }
                }
            }

            val_red = (int) round(sqrt(val_Gx_red * val_Gx_red + val_Gy_red * val_Gy_red));
            val_green =
                (int) round(sqrt(val_Gx_green * val_Gx_green + val_Gy_green * val_Gy_green));
            val_blue = (int) round(sqrt(val_Gx_blue * val_Gx_blue + val_Gy_blue * val_Gy_blue));

            tmp[i][j].rgbtRed = val_red > 255 ? 255 : val_red;
            tmp[i][j].rgbtGreen = val_green > 255 ? 255 : val_green;
            tmp[i][j].rgbtBlue = val_blue > 255 ? 255 : val_blue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }

    return;
}
