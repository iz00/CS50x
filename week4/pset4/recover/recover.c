// Recover JPEGs from a forensic image

#include <stdint.h>
#include <stdio.h>

// Images filenames length
#define FILENAME_LENGTH 8

// Type definition for BYTE
typedef uint8_t BYTE;

// There are 512 bytes in a block
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Ensure proper usage (1 command-line argument)
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open input file in read mode
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Buffer can hold 512 bytes in stack
    BYTE buffer[BLOCK_SIZE];

    // Declaration of output file
    FILE *output = NULL;

    // Memory in stack for filename
    char filename[FILENAME_LENGTH];

    int files_counter = 0;

    // Read from input into buffer until there is bytes to read
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, input))
    {
        // If found signature for beggining of JPEG in buffer
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If there was previous file found, close it
            if (files_counter)
            {
                fclose(output);
            }

            // Creation of filename, sequence of numbers with 3 digits starting from 0
            sprintf(filename, "%03i.jpg", files_counter);

            // Open output file in write mode, given a filename
            output = fopen(filename, "wb");
            if (output == NULL)
            {
                fclose(input);
                printf("Could not open file.\n");
                return 1;
            }

            files_counter++;
        }

        // If there is a file open, write the buffer to it
        if (files_counter)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output);
        }
    }

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}
