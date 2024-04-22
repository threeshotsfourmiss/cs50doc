#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    // get the height from the user
    do
    {
        h = get_int("Height: ");
    }
    // keep prompting if the answer is bigger than 8 or smaller than 1 (not vice versa!!)
    while (h > 8 || h < 1);

    for (int i = 0; i < h; i++)
    {
        // for every iteration, we want to print one less space than the one before,
        // until the final layer where we print nothing. the final iteration will
        // have i = h - 1, so by setting our condition to be c < h - i - 1, we ensure
        // that the final layer has no spaces.
        for (int c = 0; c < h - i - 1; c++)
        {
            printf(" ");
        }
        // since the first iteration will have i = 0 and the final iteration will have
        // i = h - 1, having the conditional be a < i + 1 means that we will print one
        // hash on the first iteration and h hashes on the final iteration.
        for (int a = 0; a < i + 1; a++)
        {
            printf("#");
        }
        // print the gap
        printf("  ");
        // identical to the previous loop
        for (int b = 0; b < i + 1; b++)
        {
            printf("#");
        }
        // move to a new line
        printf("\n");
    }
}
