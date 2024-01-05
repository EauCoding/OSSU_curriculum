#include <cs50.h>
#include <stdio.h>

int get_height(void);
void build_pyramid(int height);

int main(void)
{
    // Prompt the user to enter a positive number between 1 and 8
    int height = get_height();

    // Build the pyramid
    build_pyramid(height);
}

int get_height(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    return height;
}

void build_pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (j >= (height - 1 - i))
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        printf("  ");

        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
