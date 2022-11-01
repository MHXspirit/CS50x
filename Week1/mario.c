#include <cs50.h>
#include <stdio.h>

void mario(int height);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

    mario(height);
}

void mario(int height)
{
    for (int i = 0; i < height; i ++)
    {
        // print the left pyramids
        for (int j = 0; j < height; j ++)
        {
            if (j < height - i - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }

        // print the middle gap
        printf("  ");

        // print the right pyramids
        for (int j = 0; j <= i; j ++)
        {
            printf("#");
        }

        //move to next row
        printf("\n");
    }
}