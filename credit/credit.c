#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long num;

    do
    {
        num = get_long("Number = ");
    }
    while (num <= 0);

    int sum1 = 0;
    int sum2 = 0;
    int sum = 0;
    int first_digit = 0;
    int second_digit = 0;
    int digit = 0;
    int temp = 0;

    while (num > 0)
    {
        temp = num % 10;
        digit++;

        if (digit % 2 != 0)
        {
            sum1 += temp;
        }
        else
        {
            int i = 2 * temp;

            if (i >= 10)
            {
                sum2 += i % 10;
                i /= 10;
                sum2 += i;
            }
            else
            {
                sum2 += i;
            }
        }
        if (num >= 10 && num <= 100)
        {
            second_digit = temp;
        }
        if (num > 0 && num < 10)
        {
            first_digit = temp;
        }

        num /= 10;
    }

    sum = sum1 + sum2;

    if (sum % 10 == 0 && digit == 15 && first_digit == 3 &&
        (second_digit == 4 || second_digit == 7))
    {
        printf("AMEX\n");
    }

    else if (sum % 10 == 0 && digit == 16 && first_digit == 5 &&
             (second_digit > 0 && second_digit < 6))
    {
        printf("MASTERCARD\n");
    }

    else if (sum % 10 == 0 && (digit == 13 || digit == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }
}
