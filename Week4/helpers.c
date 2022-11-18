#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            BYTE tmp = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = tmp;
            image[i][j].rgbtRed = tmp;
            image[i][j].rgbtGreen = tmp;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width / 2; j ++)
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
    RGBTRIPLE tmp_image[height][width];
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            int tmpb = 0;
            int tmpg = 0;
            int tmpr = 0;
            double count = 0;

            for (int k = -1; k < 2; k ++)
            {
                for (int t = -1; t < 2; t ++)
                {
                    if ((i + k >= 0 && i + k <= height - 1) && (j + t >= 0 && j + t <= width - 1))
                    {
                        tmpb += image[i + k][j + t].rgbtBlue;
                        tmpg += image[i + k][j + t].rgbtGreen;
                        tmpr += image[i + k][j + t].rgbtRed;
                        count ++;
                    }
                }
            }

            tmp_image[i][j].rgbtBlue = round(tmpb / count);
            tmp_image[i][j].rgbtGreen = round(tmpg / count);
            tmp_image[i][j].rgbtRed = round(tmpr / count);
        }
    }

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            int tmp_blue_x = 0;
            int tmp_green_x = 0;
            int tmp_red_x = 0;

            int tmp_blue_y = 0;
            int tmp_green_y = 0;
            int tmp_red_y = 0;

            for (int k = -1; k < 2; k ++)
            {
                for (int t = -1; t < 2; t ++)
                {
                    if ((i + k >= 0 && i + k <= height - 1) && (j + t >= 0 && j + t <= width - 1))
                    {
                        tmp_blue_x += Gx[k + 1][t + 1] * image[i + k][j + t].rgbtBlue;
                        tmp_blue_y += Gy[k + 1][t + 1] * image[i + k][j + t].rgbtBlue;
                        tmp_green_x += Gx[k + 1][t + 1] * image[i + k][j + t].rgbtGreen;
                        tmp_green_y += Gy[k + 1][t + 1] * image[i + k][j + t].rgbtGreen;
                        tmp_red_x += Gx[k + 1][t + 1] * image[i + k][j + t].rgbtRed;
                        tmp_red_y += Gy[k + 1][t + 1] * image[i + k][j + t].rgbtRed;
                    }
                }
            }

            if (round(sqrt(tmp_blue_x * tmp_blue_x + tmp_blue_y * tmp_blue_y)) <= 255)
            {
                tmp_image[i][j].rgbtBlue = round(sqrt(tmp_blue_x * tmp_blue_x + tmp_blue_y * tmp_blue_y));
            }
            else
            {
                tmp_image[i][j].rgbtBlue = 255;
            }

            if (round(sqrt(tmp_green_x * tmp_green_x + tmp_green_y * tmp_green_y)) <= 255)
            {
                tmp_image[i][j].rgbtGreen = round(sqrt(tmp_green_x * tmp_green_x + tmp_green_y * tmp_green_y));
            }
            else
            {
                tmp_image[i][j].rgbtGreen = 255;
            }

            if (round(sqrt(tmp_red_x * tmp_red_x + tmp_red_y * tmp_red_y)) <= 255)
            {
                tmp_image[i][j].rgbtRed = round(sqrt(tmp_red_x * tmp_red_x + tmp_red_y * tmp_red_y));
            }
            else
            {
                tmp_image[i][j].rgbtRed = 255;
            }
        }
    }

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }

    return;
}
