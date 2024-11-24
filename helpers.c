#include "helpers.h"
#include <math.h>   //for round() to round-off floats to nearest integers

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;

            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtRed = round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float sepiaBlue, sepiaGreen, sepiaRed;

            sepiaBlue = 0.131 * image[i][j].rgbtBlue + 0.534 * image[i][j].rgbtGreen + 0.272 * image[i][j].rgbtRed;
            sepiaGreen = 0.168 * image[i][j].rgbtBlue + 0.686 * image[i][j].rgbtGreen + 0.349 * image[i][j].rgbtRed;
            sepiaRed = 0.189 * image[i][j].rgbtBlue + 0.769 * image[i][j].rgbtGreen + 0.393 * image[i][j].rgbtRed;

            //For Blue
            if(round(sepiaBlue) > 255)
            {
                sepiaBlue = 255;    //Cap colour
                image[i][j].rgbtBlue = sepiaBlue;
            }
            else
            {
                image[i][j].rgbtBlue = round(sepiaBlue);
            }

            //For Green
            if(round(sepiaGreen) > 255)
            {
                sepiaGreen = 255;    //Cap colour
                image[i][j].rgbtGreen = sepiaGreen;
            }
            else
            {
                image[i][j].rgbtGreen = round(sepiaGreen);
            }

            //For Red
            if(round(sepiaRed) > 255)
            {
                sepiaRed = 255;    //Cap colour
                image[i][j].rgbtRed = sepiaRed;
            }
            else
            {
                image[i][j].rgbtRed = round(sepiaRed);
            }

        }
    }
    return;
}

// Reflect image horizontally: NOT WORKING
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp[3];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //perform swapping
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - 1 -i].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 -i].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 -i].rgbtRed;

            image[i][width - 1 -i].rgbtBlue = temp[0];
            image[i][width - 1 -i].rgbtGreen = temp[1];
            image[i][width - 1 -i].rgbtRed = temp[2];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Declarartion
    int Red, Green, Blue;
    int count;
    RGBTRIPLE temp[height][width];

    //reach the columns
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            Blue = 0;
            Green = 0;
            Red = 0;
            count = 0;

            for(int k = -1; k < 2; k++)
            {
                for(int l = -1; l < 2; l++)
                {
                    //stop loop from drifting in unknown territory
                    if((i + k) < 0 || (j +l) < 0)
                    {
                        continue;
                    }

                    Blue = Blue + image[i + k][j + l].rgbtBlue;
                    Green = Green + image[i + k][j + l].rgbtGreen;
                    Red = Red + image[i + k][j + l].rgbtRed;

                    count++;
                }
            }

            temp[i][j].rgbtBlue = round(Blue / count);
            temp[i][j].rgbtGreen = round(Green / count);
            temp[i][j].rgbtRed = round(Red / count);
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
