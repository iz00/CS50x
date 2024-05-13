// Functions to apply filters to images

#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through image's pixels, in the matrix of height(i) and width(j)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get average pixel value and apply it to all channels
            RGBTRIPLE pixel = image[i][j];
            int average = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Swap pixels
void swap_pixels(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    RGBTRIPLE aux = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = aux;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through image's pixels, in the matrix of height(i) and width(j)
    for (int i = 0; i < height; i++)
    {
        // Only get to half of row
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixel in first half with pixel in second half of pixels in row
            swap_pixels(&image[i][j], &image[i][width - 1 - j]);
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize a copy of image, because blurred pixels would interfere in formula for blurring
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    // Iterate through image's pixels, in the matrix of height(i) and width(j)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average_red = 0.0, average_green = 0.0, average_blue = 0.0;
            int pixels_formula = 0;

            // Iterate through coordinates around middle pixel, h (up and down) and w (left and right)
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    // Calculate pixel coordinate adding coordinates around middle pixel
                    int pixel_height = i + h, pixel_width = j + w;

                    // If coordinate (or pixel) exists in image
                    if (pixel_height >= 0 && pixel_height <= height - 1 && pixel_width >= 0 && pixel_width <= width - 1)
                    {
                        // Add channels (using the image copy to use the original pixels) to corresponding averages
                        average_red += image_copy[pixel_height][pixel_width].rgbtRed;
                        average_green += image_copy[pixel_height][pixel_width].rgbtGreen;
                        average_blue += image_copy[pixel_height][pixel_width].rgbtBlue;
                        pixels_formula++;
                    }
                }
            }

            // Apply average colors to image's pixels
            image[i][j].rgbtRed = round(average_red / pixels_formula);
            image[i][j].rgbtGreen = round(average_green / pixels_formula);
            image[i][j].rgbtBlue = round(average_blue / pixels_formula);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize a copy of image, because edge detected pixels would interfere in formula for edges
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    // Iterate through image's pixels, in the matrix of height(i) and width(j)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Kernels gx (for horizontal edges) and gy (for vertical edges)
            int gx_red = 0, gx_green = 0, gx_blue = 0;
            int gy_red = 0, gy_green = 0, gy_blue = 0;

            // Iterate through coordinates around middle pixel, h (up and down) and w (left and right)
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    // Calculate pixel coordinate adding coordinates around middle pixel
                    int pixel_height = i + h, pixel_width = j + w;

                    // If coordinate (or pixel) exists in image
                    if (pixel_height >= 0 && pixel_height <= height - 1 && pixel_width >= 0 && pixel_width <= width - 1)
                    {
                        // Initialize multipliers to h and w for formula, and double them if any of them 0
                        int gx_multiplier = w, gy_multiplier = h;

                        if (h == 0 || w == 0)
                        {
                            gx_multiplier *= 2;
                            gy_multiplier *= 2;
                        }

                        // Calculate kernels (using the image copy to use the original pixels) for each channel
                        gx_red += image_copy[pixel_height][pixel_width].rgbtRed * gx_multiplier;
                        gx_green += image_copy[pixel_height][pixel_width].rgbtGreen * gx_multiplier;
                        gx_blue += image_copy[pixel_height][pixel_width].rgbtBlue * gx_multiplier;

                        gy_red += image_copy[pixel_height][pixel_width].rgbtRed * gy_multiplier;
                        gy_green += image_copy[pixel_height][pixel_width].rgbtGreen * gy_multiplier;
                        gy_blue += image_copy[pixel_height][pixel_width].rgbtBlue * gy_multiplier;
                    }
                }
            }

            // Calculate channels using kernels
            int red = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            int green = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            int blue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));

            // Apply colors to image's pixels, capping value at 255
            image[i][j].rgbtRed = (red > 255) ? 255 : red;
            image[i][j].rgbtGreen = (green > 255) ? 255 : green;
            image[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }
}
