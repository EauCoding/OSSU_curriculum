#include <math.h>
#include <stdlib.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Find average pixel color value
            int avgValue = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float)3);

            // Update pixel color values
            image[i][j].rgbtBlue = avgValue;
            image[i][j].rgbtGreen = avgValue;
            image[i][j].rgbtRed = avgValue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE reverse_pxl[width];

        for (int j = 0; j < width; j++)
        {
            reverse_pxl[width - j - 1] = image[i][j];
        }

        for (int k = 0; k < width; k++)
        {
            image[i][k] = reverse_pxl[k];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // New image to hold the blurred image
    RGBTRIPLE imageOut[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top left corner
            if (i == 0 && j == 0)
            {
                int avgRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / (float)4);
                int avgGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / (float)4);
                int avgBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / (float)4);

                imageOut[i][j].rgbtRed = avgRed;
                imageOut[i][j].rgbtGreen = avgGreen;
                imageOut[i][j].rgbtBlue = avgBlue;
            }
            else if (i == 0 && j == width - 1)
            {
                int avgRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / (float)4);
                int avgGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / (float)4);
                int avgBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / (float)4);

                imageOut[i][j].rgbtRed = avgRed;
                imageOut[i][j].rgbtGreen = avgGreen;
                imageOut[i][j].rgbtBlue = avgBlue;
            }
            else if (i == height - 1 && j == 0)
            {
                int avgRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / (float)4);
                int avgGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / (float)4);
                int avgBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / (float)4);

                imageOut[i][j].rgbtRed = avgRed;
                imageOut[i][j].rgbtGreen = avgGreen;
                imageOut[i][j].rgbtBlue = avgBlue;
            }
            else if (i == height - 1 && j == width - 1)
            {
                int avgRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / (float)4);
                int avgGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / (float)4);
                int avgBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / (float)4);

                imageOut[i][j].rgbtRed = avgRed;
                imageOut[i][j].rgbtGreen = avgGreen;
                imageOut[i][j].rgbtBlue = avgBlue;
            }
            else if (i == 0 && (j != 0 || j != width - 1))
            {
                int avgRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / (float)6);
                int avgGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / (float)6);
                int avgBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / (float)6);

                imageOut[i][j].rgbtRed = avgRed;
                imageOut[i][j].rgbtGreen = avgGreen;
                imageOut[i][j].rgbtBlue = avgBlue;
            }
            else if (i == height - 1 && (j != 0 || j != width - 1))
            {
                int avgRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / (float)6);
                int avgGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / (float)6);
                int avgBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / (float)6);

                imageOut[i][j].rgbtRed = avgRed;
                imageOut[i][j].rgbtGreen = avgGreen;
                imageOut[i][j].rgbtBlue = avgBlue;
            }
            else if ((i != 0 || i != height - 1) && j == 0)
            {
                int avgRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / (float)6);
                int avgGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / (float)6);
                int avgBlue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / (float)6);

                imageOut[i][j].rgbtRed = avgRed;
                imageOut[i][j].rgbtGreen = avgGreen;
                imageOut[i][j].rgbtBlue = avgBlue;
            }
            else if ((i != 0 || i != height - 1) && j == width - 1)
            {
                int avgRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / (float)6);
                int avgGreen = round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / (float)6);
                int avgBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / (float)6);

                imageOut[i][j].rgbtRed = avgRed;
                imageOut[i][j].rgbtGreen = avgGreen;
                imageOut[i][j].rgbtBlue = avgBlue;
            }
            else
            {
                int avgRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / (float)9);
                int avgGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / (float)9);
                int avgBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / (float)9);

                imageOut[i][j].rgbtRed = avgRed;
                imageOut[i][j].rgbtGreen = avgGreen;
                imageOut[i][j].rgbtBlue = avgBlue;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageOut[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // New image to hold the blurred image
    RGBTRIPLE imageOut[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top left corner
            if (i == 0 && j == 0)
            {
                int redX = image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int redY = image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int red = round(sqrt(redX ^ 2 + redY ^ 2));

                int greenX = image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int greenY = image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int green = round(sqrt(greenX ^ 2 + greenY ^ 2));

                int blueX = image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;
                int blueY = image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;
                int blue = round(sqrt(blueX ^ 2 + blueY ^ 2));

                imageOut[i][j].rgbtRed = red;
                imageOut[i][j].rgbtGreen = green;
                imageOut[i][j].rgbtBlue = blue;
            }
            else if (i == 0 && j == width - 1)
            {
                int redX = image[i][j - 1].rgbtRed * -2 + image[i + 1][j - 1].rgbtRed * -1;
                int redY = image[i + 1][j].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed * 1;
                int red = round(sqrt(redX ^ 2 + redY ^ 2));

                int greenX = image[i][j - 1].rgbtGreen * -2 + image[i + 1][j - 1].rgbtGreen * -1;
                int greenY = image[i + 1][j].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen * 1;
                int green = round(sqrt(greenX ^ 2 + greenY ^ 2));

                int blueX = image[i][j - 1].rgbtBlue * -2 + image[i + 1][j - 1].rgbtBlue * -1;
                int blueY = image[i + 1][j].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue * 1;
                int blue = round(sqrt(blueX ^ 2 + blueY ^ 2));

                imageOut[i][j].rgbtRed = red;
                imageOut[i][j].rgbtGreen = green;
                imageOut[i][j].rgbtBlue = blue;
            }
            else if (i == height - 1 && j == 0)
            {
                int redX = image[i][j + 1].rgbtRed * 2 + image[i - 1][j + 1].rgbtRed * 1;
                int redY = image[i - 1][j].rgbtRed * -2 + image[i - 1][j + 1].rgbtRed * -1;
                int red = round(sqrt(redX ^ 2 + redY ^ 2));

                int greenX = image[i][j + 1].rgbtGreen * 2 + image[i - 1][j + 1].rgbtGreen * 1;
                int greenY = image[i - 1][j].rgbtGreen * -2 + image[i - 1][j + 1].rgbtGreen * -1;
                int green = round(sqrt(greenX ^ 2 + greenY ^ 2));

                int blueX = image[i][j + 1].rgbtBlue * 2 + image[i - 1][j + 1].rgbtBlue * 1;
                int blueY = image[i - 1][j].rgbtBlue * -2 + image[i - 1][j + 1].rgbtBlue * -1;
                int blue = round(sqrt(blueX ^ 2 + blueY ^ 2));

                imageOut[i][j].rgbtRed = red;
                imageOut[i][j].rgbtGreen = green;
                imageOut[i][j].rgbtBlue = blue;
            }
            else if (i == height - 1 && j == width - 1)
            {
                int redX = image[i][j - 1].rgbtRed * -2 + image[i - 1][j - 1].rgbtRed * -1;
                int redY = image[i - 1][j].rgbtRed * -2 + image[i - 1][j - 1].rgbtRed * -1;
                int red = round(sqrt(redX ^ 2 + redY ^ 2));

                int greenX = image[i][j - 1].rgbtGreen * -2 + image[i - 1][j - 1].rgbtGreen * -1;
                int greenY = image[i - 1][j].rgbtGreen * -2 + image[i - 1][j - 1].rgbtGreen * -1;
                int green = round(sqrt(greenX ^ 2 + greenY ^ 2));

                int blueX = image[i][j - 1].rgbtBlue * -2 + image[i - 1][j - 1].rgbtBlue * -1;
                int blueY = image[i - 1][j].rgbtBlue * -2 + image[i - 1][j - 1].rgbtBlue * -1;
                int blue = round(sqrt(blueX ^ 2 + blueY ^ 2));

                imageOut[i][j].rgbtRed = red;
                imageOut[i][j].rgbtGreen = green;
                imageOut[i][j].rgbtBlue = blue;
            }
            else if (i == 0 && (j != 0 || j != width - 1))
            {
                int redX = image[i][j - 1].rgbtRed * -2 + image[i + 1][j - 1].rgbtRed * -1 + image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int redY = image[i + 1][j - 1].rgbtRed * 1 + image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int red = round(sqrt(redX ^ 2 + redY ^ 2));

                int greenX = image[i][j - 1].rgbtGreen * -2 + image[i + 1][j - 1].rgbtGreen * -1 + image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int greenY = image[i + 1][j - 1].rgbtGreen * 1 + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int green = round(sqrt(greenX ^ 2 + greenY ^ 2));

                int blueX = image[i][j - 1].rgbtBlue * -2 + image[i + 1][j - 1].rgbtBlue * -1 + image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;
                int blueY = image[i + 1][j - 1].rgbtBlue * 1 + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;
                int blue = round(sqrt(blueX ^ 2 + blueY ^ 2));

                imageOut[i][j].rgbtRed = red;
                imageOut[i][j].rgbtGreen = green;
                imageOut[i][j].rgbtBlue = blue;
            }
            else if (i == height - 1 && (j != 0 || j != width - 1))
            {
                int redX = image[i][j - 1].rgbtRed * -2 + image[i - 1][j - 1].rgbtRed * -1 + image[i][j + 1].rgbtRed * 2 + image[i - 1][j + 1].rgbtRed * 1;
                int redY = image[i - 1][j - 1].rgbtRed * -1 + image[i - 1][j].rgbtRed * -2 + image[i - 1][j + 1].rgbtRed * -1;
                int red = round(sqrt(redX ^ 2 + redY ^ 2));

                int greenX = image[i][j - 1].rgbtGreen * -2 + image[i - 1][j - 1].rgbtGreen * -1 + image[i][j + 1].rgbtGreen * 2 + image[i - 1][j + 1].rgbtGreen * 1;
                int greenY = image[i - 1][j - 1].rgbtGreen * -1 + image[i - 1][j].rgbtGreen * -2 + image[i - 1][j + 1].rgbtGreen * -1;
                int green = round(sqrt(greenX ^ 2 + greenY ^ 2));

                int blueX = image[i][j - 1].rgbtBlue * -2 + image[i - 1][j - 1].rgbtBlue * -1 + image[i][j + 1].rgbtBlue * 2 + image[i - 1][j + 1].rgbtBlue * 1;
                int blueY = image[i - 1][j - 1].rgbtBlue * -1 + image[i - 1][j].rgbtBlue * -2 + image[i - 1][j + 1].rgbtBlue * -1;
                int blue = round(sqrt(blueX ^ 2 + blueY ^ 2));

                imageOut[i][j].rgbtRed = red;
                imageOut[i][j].rgbtGreen = green;
                imageOut[i][j].rgbtBlue = blue;
            }
            else if ((i != 0 || i != height - 1) && j == 0)
            {
                int redY = image[i - 1][j].rgbtRed * -2 + image[i - 1][j + 1].rgbtRed * -1 + image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int redX = image[i - 1][j + 1].rgbtRed * 1 + image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int red = round(sqrt(redX ^ 2 + redY ^ 2));

                int greenY = image[i - 1][j].rgbtGreen * -2 + image[i - 1][j + 1].rgbtGreen * -1 + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int greenX = image[i - 1][j + 1].rgbtGreen * 1 + image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int green = round(sqrt(greenX ^ 2 + greenY ^ 2));

                int blueY = image[i - 1][j].rgbtBlue * -2 + image[i - 1][j + 1].rgbtBlue * -1 + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;
                int blueX = image[i - 1][j + 1].rgbtBlue * 1 + image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;
                int blue = round(sqrt(blueX ^ 2 + blueY ^ 2));

                imageOut[i][j].rgbtRed = red;
                imageOut[i][j].rgbtGreen = green;
                imageOut[i][j].rgbtBlue = blue;
            }
            else if ((i != 0 || i != height - 1) && j == width - 1)
            {
                int redY = image[i - 1][j].rgbtRed * -2 + image[i - 1][j - 1].rgbtRed * -1 + image[i + 1][j].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed * 1;
                int redX = image[i - 1][j - 1].rgbtRed * -1 + image[i][j - 1].rgbtRed * -2 + image[i + 1][j - 1].rgbtRed * -1;
                int red = round(sqrt(redX ^ 2 + redY ^ 2));

                int greenY = image[i - 1][j].rgbtGreen * -2 + image[i - 1][j - 1].rgbtGreen * -1 + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen * 1;
                int greenX = image[i - 1][j - 1].rgbtGreen * -1 + image[i][j - 1].rgbtGreen * -2 + image[i + 1][j - 1].rgbtGreen * -1;
                int green = round(sqrt(greenX ^ 2 + greenY ^ 2));

                int blueY = image[i - 1][j].rgbtBlue * -2 + image[i - 1][j - 1].rgbtBlue * -1 + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue * 1;
                int blueX = image[i - 1][j - 1].rgbtBlue * -1 + image[i][j - 1].rgbtBlue * -2 + image[i + 1][j - 1].rgbtBlue * -1;
                int blue = round(sqrt(blueX ^ 2 + blueY ^ 2));

                imageOut[i][j].rgbtRed = red;
                imageOut[i][j].rgbtGreen = green;
                imageOut[i][j].rgbtBlue = blue;
            }
            else
            {
                int redX = image[i - 1][j - 1].rgbtRed * -1 + image[i][j - 1].rgbtRed * -2 + image[i + 1][j - 1].rgbtRed * -1 + image[i - 1][j + 1].rgbtRed * 1 + image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int redY = image[i - 1][j - 1].rgbtRed * -1 + image[i - 1][j].rgbtRed * -2 + image[i - 1][j + 1].rgbtRed * -1 + image[i + 1][j - 1].rgbtRed * 1 + image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int red = round(sqrt(redX ^ 2 + redY ^ 2));

                int greenX = image[i - 1][j - 1].rgbtGreen * -1 + image[i][j - 1].rgbtGreen * -2 + image[i + 1][j - 1].rgbtGreen * -1 + image[i - 1][j + 1].rgbtGreen * 1 + image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int greenY = image[i - 1][j - 1].rgbtGreen * -1 + image[i - 1][j].rgbtGreen * -2 + image[i - 1][j + 1].rgbtGreen * -1 + image[i + 1][j - 1].rgbtGreen * 1 + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int green = round(sqrt(greenX ^ 2 + greenY ^ 2));

                int blueX = image[i - 1][j - 1].rgbtBlue * -1 + image[i][j - 1].rgbtBlue * -2 + image[i + 1][j - 1].rgbtBlue * -1 + image[i - 1][j + 1].rgbtBlue * 1 + image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;
                int blueY = image[i - 1][j - 1].rgbtBlue * -1 + image[i - 1][j].rgbtBlue * -2 + image[i - 1][j + 1].rgbtBlue * -1 + image[i + 1][j - 1].rgbtBlue * 1 + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;
                int blue = round(sqrt(blueX ^ 2 + blueY ^ 2));

                imageOut[i][j].rgbtRed = red;
                imageOut[i][j].rgbtGreen = green;
                imageOut[i][j].rgbtBlue = blue;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (imageOut[i][j].rgbtRed > 255 || imageOut[i][j].rgbtGreen > 255 || imageOut[i][j].rgbtBlue > 255)
            {
                image[i][j].rgbtRed = 255;
                image[i][j].rgbtGreen = 255;
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j] = imageOut[i][j];
            }
        }
    }
}
