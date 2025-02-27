#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // Create a buffer for a block of data
    uint8_t buffer[512];
    char filename[8];
    int fileNumber = 0;
    int flag = 1;

    fread(buffer, 512, 1, card);
    FILE *img;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Create JPEGs from the data
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            flag = 0;
            if (fileNumber == 0)
            {
                sprintf(filename, "%03i.jpg", fileNumber);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
                fileNumber++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", fileNumber);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
                fileNumber++;
            }
        }
        else
        {
            if (flag == 0)
            {
                fwrite(buffer, 1, 512, img);
            }
            else
            {
                flag = 1;
                continue;
            }
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);
}
