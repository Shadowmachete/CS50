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
    if (check_format(header) == 1)
    {
        printf("Could not extract header from %s.\n", inputFile);
        return 4;
    }
    // Open output file for writing
    // TODO #5
    FILE *output = fopen(outputFile, "w");
    if (output == NULL)
    {
        printf("Could not open output file.\n");
        return 5;
    }
    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(header), 1, output);
    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);
    // Write reversed audio to file
    // TODO #8
    WORD buffer;
    printf("%li\n", ftell(input));
    while (fread(&buffer, block_size, 1, input))
    {
        fseek(input, -2 * block_size, SEEK_CUR);
        printf("%li\n", ftell(input));
        fwrite(&buffer, block_size, 1, output);
    }

    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    BYTE format[4] = {'W', 'A', 'V', 'E'};
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != format[i])
        {
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return (int) header.numChannels * header.bitsPerSample / 8;
}