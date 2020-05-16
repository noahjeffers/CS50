#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            //stores the original RGB values 
            float oRed =  image[i][j].rgbtRed;
            float oGreen = image[i][j].rgbtGreen;
            float oBlue = image[i][j].rgbtBlue;
            //adds up the original RGB values and divides them by 3 to find the average
            int avgValue = (int)roundf((oRed + oGreen + oBlue) / 3);
            
            //sets each of the RGB values for the indexed pixel to the average RGB value 
            image[i][j].rgbtRed = (avgValue);
            image[i][j].rgbtGreen = (avgValue);
            image[i][j].rgbtBlue = (avgValue);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            //stores the original RGB values 
            float oRed =  image[i][j].rgbtRed;
            float oGreen = image[i][j].rgbtGreen;
            float oBlue = image[i][j].rgbtBlue;

            //adjusts each of the RGB values with the given formula to acheive a sepia tone
            int sepiaRed = roundf(.393 * oRed + .769 * oGreen + .189 * oBlue);
            int sepiaGreen = roundf(.349 * oRed + .686 * oGreen + .168 * oBlue);
            int sepiaBlue = roundf(.272 * oRed + .534 * oGreen + .131 * oBlue);

            //if any of the values are over 255 they are capped at 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }  
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            // sets the indexed RGB values to the new sepia tones
            image[i][j].rgbtRed = (int)sepiaRed;
            image[i][j].rgbtGreen = (int)sepiaGreen;
            image[i][j].rgbtBlue = (int)sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //takes in the width and then creates a variable with half of the width
    int varWidth = width;
    int halfwidth = width / 2;
    //temporary variable to store the pixel that is being swapped with
    RGBTRIPLE rgbTemp = {0, 0, 0};
    //loops through the rows of the picture
    for (int i = 0; i < height; i++)
    {
        //resets the width each row
        varWidth = width;
        //loops through the individual pixels in each row
        for (int j = 0; j < halfwidth; j++)
        {
            //tmp variables that store the two pixels that are being swapped
            RGBTRIPLE rgbInitial = image[i][j];
            rgbTemp = image[i][varWidth - 1];
            //sets the indexs at opposite ends of the row to the opposite values
            image[i][varWidth - 1] = rgbInitial;
            image[i][j] = rgbTemp;
            varWidth--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    
    // creates default variables to hold the colour values of the index 
    float avgRed = 0;
    float avgGreen = 0;
    float avgBlue = 0;
    //counts how many tiles have been added

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {           
            //1
            avgRed = (float)image[i][j].rgbtRed;
            avgGreen = (float)image[i][j].rgbtGreen;
            avgBlue = (float)image[i][j].rgbtBlue;
            //counts how many tiles have been added
            int tileCount = 1;
            
            if (i < height - 1)
            {       
                //2
                avgRed += (float)image[i + 1][j].rgbtRed;
                avgGreen += (float)image[i + 1][j].rgbtGreen;
                avgBlue += (float)image[i + 1][j].rgbtBlue;
                
                tileCount++;
            }
            if (i > 0)
            {       
                //3
                avgRed += (float)image[i - 1][j].rgbtRed;
                avgGreen += (float)image[i - 1][j].rgbtGreen;
                avgBlue += (float)image[i - 1][j].rgbtBlue;
                
                tileCount++;
            }
            if (j < width - 1)
            {       
                //4
                avgRed += (float)image[i][j + 1].rgbtRed;
                avgGreen += (float)image[i][j + 1].rgbtGreen;
                avgBlue += (float)image[i][j + 1].rgbtBlue;
                
                tileCount++;
            }
            if (j > 0)
            {       
                //5
                avgRed += (float)image[i][j - 1].rgbtRed;
                avgGreen += (float)image[i][j - 1].rgbtGreen;
                avgBlue += (float)image[i][j - 1].rgbtBlue;
                
                tileCount++;
            }
            // CORNERS /////////////////////////////////
            
            if (i > 0 && j > 0)
            {       
                //6
                avgRed += (float)image[i - 1][j - 1].rgbtRed;
                avgGreen += (float)image[i - 1][j - 1].rgbtGreen;
                avgBlue += (float)image[i - 1][j - 1].rgbtBlue;
                
                tileCount++;
            }
            if (i < height - 1 && j > 0)
            {       
                //7
                avgRed += (float)image[i + 1][j - 1].rgbtRed;
                avgGreen += (float)image[i + 1][j - 1].rgbtGreen;
                avgBlue += (float)image[i + 1][j - 1].rgbtBlue;
                
                tileCount++;
            }
            if (i > 0 && j < width - 1)
            {       
                //8
                avgRed += (float)image[i - 1][j + 1].rgbtRed;
                avgGreen += (float)image[i - 1][j + 1].rgbtGreen;
                avgBlue += (float)image[i - 1][j + 1].rgbtBlue;
                
                tileCount++;
            }
            if (i < height - 1 && j < width - 1)
            {      
                //9
                avgRed += (float)image[i + 1][j + 1].rgbtRed;
                avgGreen += (float)image[i + 1][j + 1].rgbtGreen;
                avgBlue += (float)image[i + 1][j + 1].rgbtBlue;
                
                tileCount++;
            }
            
            float Red = roundf(avgRed / tileCount);
            float Green = roundf(avgGreen / tileCount);
            float Blue = roundf(avgBlue / tileCount);
            
            copy[i][j].rgbtRed = (int)Red;
            copy[i][j].rgbtGreen = (int)Green;
            copy[i][j].rgbtBlue = (int)Blue;
        }
    }
    //copies the new blurred values over to the original file.
    //  preventing skewing the results with already blurred Data
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    } 
    return;
}
