#include <cs50.h>
#include <stdio.h>

int start_number(long number, int length);
void check(int length, int start_number);

int main(void)
{
    long number = get_long("Number: ");
    long another = number;
    int length = 0;
    int checksum = 0;

    // checksum
    while (another != 0)
    {
        int tmp = another % 10;
        if (length % 2 == 1)
        {
            tmp *= 2;
            if (tmp > 9)
            {
                checksum += tmp / 10 + tmp % 10;
            }
            else
            {
                checksum += tmp;
            }
        }
        else
        {
            checksum += tmp;
        }

        another /= 10;
        length ++;
    }

    // judgement
    if (checksum % 10 == 0)
    {
        int start = start_number(number, length);
        check(length, start);
    }
    else
    {
        printf("INVALID\n");
    }
}

int start_number(long number, int length)
{
    for (int i = 0; i < length - 2; i ++)
    {
        number /= 10;
    }

    return (int)number;
}

void check(int length, int start_number)
{
    if (length == 15)
    {
        if (start_number == 34 || start_number == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (length == 16)
    {
        if (start_number <= 55 && start_number >= 51)
        {
            printf("MASTERCARD\n");
        }
        else if (start_number >= 40 && start_number <= 49)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (length == 13)
    {
        if (start_number >= 40 && start_number <= 49)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}