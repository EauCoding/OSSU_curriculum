#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;

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
    if (card == NULL)
    {
        printf("Could not open the file.\n");
        return 1;
    }

    // Create a buffer for a block of data
    BYTE buffer[BLOCK_SIZE];

    // Initialize image count and first image found
    int image_count = 0;
    int first_image_found = 0;

    // Initialize output file
    FILE *new_jpeg = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Create JPEGs from the data
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (first_image_found > 0)
            {
                fclose(new_jpeg);
                image_count++;
            }

            char image_name[8];
            sprintf(image_name, "%03i.jpg", image_count);

            new_jpeg = fopen(image_name, "w");
            if (new_jpeg == NULL)
            {
                printf("Could not open the new image file.\n");
                return 1;
            }

            fwrite(buffer, 1, BLOCK_SIZE, new_jpeg);

            first_image_found = 1;
        }
        else if (first_image_found == 1)
        {
            fwrite(buffer, 1, BLOCK_SIZE, new_jpeg);
        }
    }

    // Close every file that has been opened
    fclose(card);
    fclose(new_jpeg);
}