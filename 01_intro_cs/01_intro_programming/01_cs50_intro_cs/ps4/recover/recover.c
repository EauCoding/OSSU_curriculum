#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

const int BUFFER_SIZE = 512;

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

    FILE *output = NULL;

    // Create a buffer for a block of data
    BYTE buffer[BUFFER_SIZE];

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BUFFER_SIZE, card) == BUFFER_SIZE)
    {
        // Create JPEGs from the data
        return 0;
    }
}