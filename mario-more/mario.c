#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Height = ");
    }
    while (height > 8 || height < 1);

    for (int i = 1; i <= height; i++)
    {
        int j = height - i;

        while (j > 0)
        {
            printf(" ");
            j--;
        }

        int k = i;

        while (k > 0)
        {
            printf("#");
            k--;
        }

        printf("  ");

        int m = i;

        while (m > 0)
        {
            printf("#");
            m--;
        }

        if (i != height)
        {
            printf("\n");
        }
    }

    printf("\n");
}
