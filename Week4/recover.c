#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t TYPE;

const int one_block = 512;

int main(int argc, char *argv[])
{
    TYPE buffer[one_block];
    int image_number = 0;
    char name[8] = "###.jpg";

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *output = NULL;
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("%s could not be opened.\n", argv[1]);
        return 1;
    }

    while (fread(buffer, 1, one_block, input) == one_block)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // check if the first JPEG
            if (image_number > 0)
            {
                fclose(output);
            }

            sprintf(name, "%03i.jpg", image_number);
            output = fopen(name, "w");
            fwrite(buffer, 1, one_block, output);
            image_number ++;
        }
        else
        {
            // check if already found JPEG
            if (image_number > 0)
            {
                fwrite(buffer, 1, one_block, output);
            }
        }

    }

    fclose(input);
    fclose(output);

    return 0;
}