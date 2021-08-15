#include <math.h>

#include "helpers.h"

// Convert image to grayscale
// It took me some time to remember to compile 'filter'
// so bits and pieces may not be needed in this code
// they were written when I couldn't figure out what was wrong
// once I compiled filter, it all worked so I don't want to fuck with it
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // change the array as they are mutable within functions without any extra pointer magic
    // you are given the image
    // let's loop through each pixel
    // loop through each row
    for (int i = 0; i < height; i++)
    {
        // loop through each pixel of the given row i
        for (int j = 0; j < width; j++)
        {
            // get the rgb values of the pixel from RGBTRIPLE
            // using byte without #include because it stand to reason that it should already
            // be here. helpers.c <-- helpers.h <-- hmp.h
            BYTE red = image[i][j].rgbtRed;
            BYTE green = image[i][j].rgbtGreen;
            BYTE blue = image[i][j].rgbtBlue;

            // Do the grayscale math now
            // What data types should I even use
            // I'll try casting I guess
            float avgf = (red + green + blue) / 3.0;
            int avg = round(avgf);
            // assign the new values
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // double loop to go pixel by pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE r = image[i][j].rgbtRed;
            BYTE g = image[i][j].rgbtGreen;
            BYTE b = image[i][j].rgbtBlue;

            // sepia math provided by cs50 website

            int sr = round((.393 * r) + (.769 * g) + (.189 * b));
            int sg = round((.349 * r) + (.686 * g) + (.168 * b));
            int sb = round((.272 * r) + (.534 * g) + (.131 * b));
            // the math goes over 255 sometimes so
            if (sr > 255)
            {
                sr = 255;
            }
            if (sg > 255)
            {
                sg = 255;
            }
            if (sb > 255)
            {
                sb = 255;
            }
            image[i][j].rgbtRed = sr;
            image[i][j].rgbtGreen = sg;
            image[i][j].rgbtBlue = sb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // the idea is as follows
        // get current pixel and swap it with its counterpart on the other side
        // so you only want to make it half way across the picture
        // otherwise you would undo all of the work
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];

            int index = (width - 1) - j;
            image[i][j] = image[i][index];
            image[i][index] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // in order to not include the already blurred pixels
    // make a copy of image
    RGBTRIPLE ic[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ic[i][j] = image[i][j];
        }
    }
    // ic is now a copy of image
    // loop through each ic pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // set up totals for averaging
            int rt = 0;  // red total
            int gt = 0;  // green total
            int bt = 0;  // blue total
            int at = 0;  // total adjacent pixels 
            
            // for each pixel look at its hypothetical adjacents + itself
            // so that's the parent coord (i, j) and then the others
            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    int i_edit = i - a;
                    int j_edit = j - b;
                    // check if the coords are within the border 0...height and 0...width
                    if (i_edit >= 0 && i_edit < height && j_edit >= 0 && j_edit < width)
                    {
                        // if yes add its pixel values to the totals and up the adj count
                        rt += ic[i_edit][j_edit].rgbtRed;
                        gt += ic[i_edit][j_edit].rgbtGreen;
                        bt += ic[i_edit][j_edit].rgbtBlue;
                        at++;
                    }
                }
            }
            // set the focused primary pixel color values to the average of the totals
            // set it to image and not the copy
            image[i][j].rgbtRed = round(rt / (float) at);
            image[i][j].rgbtGreen = round(gt / (float) at);
            image[i][j].rgbtBlue = round(bt / (float) at);
        }
    }

    return;
}
