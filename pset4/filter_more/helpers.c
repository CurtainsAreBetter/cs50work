#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // double loop to go pixel by pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // color values
            BYTE r = image[i][j].rgbtRed;
            BYTE g = image[i][j].rgbtGreen;
            BYTE b = image[i][j].rgbtBlue;
            // grayscale via averaging
            int avg = round((r + g + b) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // double for loop to go through the image pixel by pixel (but only half across becase swap)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // swap pixels
            RGBTRIPLE tmp = image[i][j];
            int index = (width - 1) - j;
            image[i][j] = image[i][index];
            image[i][index] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy image to reference
    RGBTRIPLE ic[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ic[i][j] = image[i][j];
        }
    }
    // using ic as reference, loop through its pixels and use them to update
    // image's pixels into a blurred image
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

// function for combing Gx Gy values
int combine(int x, int y)
{
    // square the values
    x *= x;
    y *= y;
    float rt = sqrt(x + y);
    int output = round(rt);
    return output;
}



// rember that the inputs will still need some set up from the edges function

// input should be set up so that
// 1,1 is the pixel in question
RGBTRIPLE g_of(RGBTRIPLE subset[3][3])
{
    // really just is the sum. make an rgbtriple that has them values
    // set up rgb totals
    
    // set Gx and rgb totals
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int xrt = 0;
    int xgt = 0;
    int xbt = 0;
    
    // set Yx and rgb totals
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int yrt = 0;
    int ygt = 0;
    int ybt = 0;
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // do math with coresponding coord
            // Gx
            xrt += (Gx[i][j] * subset[i][j].rgbtRed);
            xgt += (Gx[i][j] * subset[i][j].rgbtGreen);
            xbt += (Gx[i][j] * subset[i][j].rgbtBlue);
            
            // Gy
            yrt += (Gy[i][j] * subset[i][j].rgbtRed);
            ygt += (Gy[i][j] * subset[i][j].rgbtGreen);
            ybt += (Gy[i][j] * subset[i][j].rgbtBlue);
        }
    }
    
    // combine using the function
    int cr = combine(xrt, yrt);  // combined red
    int cg = combine(xgt, ygt);  // combined green
    int cb = combine(xbt, ybt);  // combined blue
    
    // make sure they're not over 255
    if (cr > 255)
    {
        cr = 255;
    }
    if (cg > 255)
    {
        cg = 255;
    }
    if (cb > 255)
    {
        cb = 255;
    }
    
    
    RGBTRIPLE output;
    output.rgbtRed = cr;
    output.rgbtGreen = cg;
    output.rgbtBlue = cb;
    return output;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // make copy of image
    RGBTRIPLE ic[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ic[i][j] = image[i][j];
        }
    }
    
    // go through each pixel of ic
    // for each pixel, gather its adjacents into a 3x3 array
    // if the adjacent is outside of the image range set its color values to zero
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // make temp array
            RGBTRIPLE ta[3][3];
            // now do the look around
            // adding each adjacent to the proper index
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    // get coords
                    int i_edit = i - (a - 1);
                    int j_edit = j - (b - 1);
                    // check if the coords are out of range
                    if ((i_edit < 0 || i_edit >= height) || (j_edit < 0 || j_edit >= width))
                    {
                        // set values to zero
                        RGBTRIPLE temptriple;
                        temptriple.rgbtRed = 0;
                        temptriple.rgbtGreen = 0;
                        temptriple.rgbtBlue = 0;
                        // add to the temp array
                        ta[a][b] = temptriple;
                    }
                    else
                    {
                        // add the pixel to the temp array
                        ta[a][b] = ic[i_edit][j_edit];
                    }
                    
                }
            }
            // using the completed temp array
            // get the pixel's new values and set the pixel of image as such
            image[i][j] = g_of(ta);
        }
    }
    return;
}
