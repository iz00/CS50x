// Function to change black pixels of image to another color

#include "helpers.h"

// Change all black pixels to a color of choosing
void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through image's pixels, in the matrix of height(i) and width(j)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];

            // If pixel is black (red, green and blue values of pixel zero), change color
            if (pixel.rgbtRed == 0x00 && pixel.rgbtGreen == 0x00 && pixel.rgbtBlue == 0x00)
            {
                // 0x2191FB is a blue tone color
                image[i][j].rgbtRed = 0x21;
                image[i][j].rgbtGreen = 0x91;
                image[i][j].rgbtBlue = 0xFB;
            }
        }
    }
}
