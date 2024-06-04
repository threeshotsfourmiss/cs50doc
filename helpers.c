#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // this is our buffer, creatively named mixingpot
    float mixingpot = 0.0;
    // iterate over all the pixels.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // make sure the buffer is 0
            mixingpot = 0.0;
            // add all the channels and then divide by the number of channels. it's finding a mean.
            // not rocket science.
            mixingpot = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            mixingpot = mixingpot / 3.0;
            // round it to make sure it's an integer value, otherwise we run into issues
            mixingpot = round(mixingpot);
            // finally assign the pixel its new colors
            image[i][j].rgbtRed = mixingpot;
            image[i][j].rgbtGreen = mixingpot;
            image[i][j].rgbtBlue = mixingpot;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // declare our intermediary variables
    float sepiaRed = 0.0;
    float sepiaGreen = 0.0;
    float sepiaBlue = 0.0;
    // iterate over all the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // set our values for the new sepia pixel
            sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                       .189 * image[i][j].rgbtBlue;
            sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                         .168 * image[i][j].rgbtBlue;
            sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                        .131 * image[i][j].rgbtBlue;
            // round them so we don't run into fun times
            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);
            // cap all the values at 255 (there's probably a better way to do this, but I couldn't
            // quickly find the function so if()'s it is)
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
            // write out the new pixel
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // declare our  buffers
    float bufferRed = 0.0;
    float bufferGreen = 0.0;
    float bufferBlue = 0.0;
    // I had it in my mind that the errors I was getting in check50 were due to improper bounds
    // checking, so I wrote out this little intermediate step to make sure I was looping over the
    // correct number of pixels horizontally. totally unhelpful, but was helpful to check against.
    int span = 0;
    if (width % 2 == 0)
    {
        span = width / 2;
    }
    if (width % 2 != 0)
    {
        span = (width - 1) / 2;
    }
    // iterate over all the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < span; j++)
        {
            // set our buffers to be the value of the pixel on the left side
            bufferRed = image[i][j].rgbtRed;
            bufferGreen = image[i][j].rgbtGreen;
            bufferBlue = image[i][j].rgbtBlue;
            // set the left side pixel to the right pixel
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            // set the right pixel to our buffer values, so the original left pixel
            image[i][width - j - 1].rgbtRed = bufferRed;
            image[i][width - j - 1].rgbtGreen = bufferGreen;
            image[i][width - j - 1].rgbtBlue = bufferBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // declare our divising factor
    float numavg = 0.0;
    // declare our buffers
    float redbuf = 0.0;
    float greenbuf = 0.0;
    float bluebuf = 0.0;
    // declare our reference image
    RGBTRIPLE ref[height][width];
    // iterate over the entire image and copy it to the reference
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ref[i][j] = image[i][j];
        }
    }
    // iterate over all the pixels
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // set buffers and factor to 0
            numavg = 0.0;
            redbuf = 0.0;
            greenbuf = 0.0;
            bluebuf = 0.0;
            // iterate on the neighbors of the current pixel. if the current pixel is (0,0), we want
            // to iterate over
            // [(-1,-1), (0,-1), (1,-1)
            //  (-1, 0), (0, 0), (1, 0)
            //  (-1, 1), (0, 1), (1, 1)]
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    // this godawful if statement basically asks "for the pixel (x,y), is y between
                    // 0 and the height of the image, inclusive" and does the same for x. I think I
                    // remember having issues with chaining operators, e.g. (0 <= y+i < height), so
                    // this is what you get. sorry!
                    if (y + i >= 0 && y + i < height && x + j >= 0 && x + j < width)
                    {
                        // add up all of the valid pixels (the ones actually in the image) to the
                        // buffer, and increment the factor. note that we are adding from the
                        // reference image we created earlier, so that we don't use already blurred
                        // pixels in the next pixel
                        redbuf = redbuf + ref[y + i][x + j].rgbtRed;
                        greenbuf = greenbuf + ref[y + i][x + j].rgbtGreen;
                        bluebuf = bluebuf + ref[y + i][x + j].rgbtBlue;
                        numavg = numavg + 1.0;
                    }
                }
            }
            // round all the buffers to get an integer value -- had some issues with validation
            // because of this, very important step. also, because we only incremented the divising
            // factor when we added a valid pixel to the buffer, we know for a fact that the factor
            // is equal to the number of valid pixels we added, so this finds the mean (not counting
            // weird floating point error, but it's so close to exactly equal that it doesn't
            // matter).
            redbuf = round(redbuf / numavg);
            greenbuf = round(greenbuf / numavg);
            bluebuf = round(bluebuf / numavg);
            // finally, write out the buffers to the image
            image[y][x].rgbtRed = redbuf;
            image[y][x].rgbtGreen = greenbuf;
            image[y][x].rgbtBlue = bluebuf;
        }
    }
    return;
}
