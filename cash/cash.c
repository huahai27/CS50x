#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);
    int num = 0;

    while (change / 25 > 0)
    {
        change -= 25;
        num++;
    }

    while (change / 10 > 0)
    {
        change -= 10;
        num++;
    }

    while (change / 5 > 0)
    {
        change -= 5;
        num++;
    }

    num += change;

    printf("%d\n", num);

    return 0;
}
