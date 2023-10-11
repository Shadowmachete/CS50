#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc < 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    if (!(argv[1][strlen(argv[1])-3] == 'w' && argv[1][strlen(argv[1])-2] == 'a' && argv[1][strlen(argv[1])-1] == 'v'))
    {
        printf("Input is not a WAV file.\n");
        return 2;
    }
    // Open input file for reading
    // TODO #2
    char *inputFile = argv[1];
    char *outputFile = argv[2];
    FILE *input = fopen(inputFile, "r");
    if (input == NULL)
    {
        printf("Could not open %s.\n", inputFile);
        return 3;
    }
    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(header), 1, input);
    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(header))
    {
        printf("Could not extract header from %s.\n", inputFile);
        return 4;
    }
    // Open output file for writing
    // TODO #5

    // Write header to file
    // TODO #6

    // Use get_block_size to calculate size of block
    // TODO #7

    // Write reversed audio to file
    // TODO #8
}

int check_format(WAVHEADER header)
{
    // TODO #4
    BYTE *format[4];
    for (int i = 0; i < 4; i++)
    {
        format[i] = &header.format[i];
    }
    printf("%s", format);
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return 0;
}