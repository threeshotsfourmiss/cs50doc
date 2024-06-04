#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // check if there's only one argument
    if (argc != 2)
    {
        printf("proper usage: ./recover ***.raw\n");
        return 1;
    }
    // give the file an easy name
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not open the file.\n");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];

    int count = 0;
    char *filename = malloc(8);
    sprintf(filename, "%03i.jpg", count);
    while (fread(buffer, 1, 512, infile) == 512)
    {

        FILE *img = fopen(filename, "w");
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (count > 0)
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count);
            }
            count++;
        }
        else
        {
            fwrite(&buffer, 512, 1, img);
        }
    }
    free(filename);
}
