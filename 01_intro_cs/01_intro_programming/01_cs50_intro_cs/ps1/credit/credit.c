#include <cs50.h>
#include <stdio.h>

void checksum(long credit_card_num);
int doubled_num(int remainder);
void check_print(int checksum_result, int first_two_digit, int remainder, int length_card_num);

int main(void)
{
    // Prompt for input
    long credit_card_num = get_long("Number: ");

    // Calculate checksum
    checksum(credit_card_num);
}

void checksum(long credit_card_num)
{
    int remainder = credit_card_num % 10;
    int prev_remainder;

    long quotient = credit_card_num / 10;

    int length_card_num = 1;

    int even_num = 0;
    int odd_num = 0;

    do
    {
        if (length_card_num % 2 == 0)
        {
            even_num += doubled_num(remainder);
        }
        else
        {
            odd_num += remainder;
        }

        prev_remainder = remainder;
        remainder = quotient % 10;
        quotient = quotient / 10;
        length_card_num++;
    }
    while (quotient > 0);

    if (length_card_num % 2 == 0)
    {
        even_num += doubled_num(remainder);
    }
    else
    {
        odd_num += remainder;
    }

    int checksum_result = even_num + odd_num;
    int first_two_digit = remainder * 10 + prev_remainder;

    check_print(checksum_result, first_two_digit, remainder, length_card_num);
}

int doubled_num(int remainder)
{
    int double_num = remainder * 2;

    if (double_num >= 10)
    {
        int rem = double_num % 10;
        int quo = double_num / 10;

        double_num = rem + quo;
    }

    return double_num;
}

void check_print(int checksum_result, int first_two_digit, int remainder, int length_card_num)
{
    string result = "INVALID";

    // Check for card length and starting digits
    if (checksum_result % 10 == 0)
    {
        if ((length_card_num == 15) && ((first_two_digit == 34) || (first_two_digit == 37)))
        {
            result = "AMEX";
        }
        else if (((length_card_num == 13) || (length_card_num == 16)) && (remainder == 4))
        {
            result = "VISA";
        }
        else if ((length_card_num == 16) && ((first_two_digit >= 51) && (first_two_digit <= 55)))
        {
            result = "MASTERCARD";
        }
    }

    // Print AMEX, MASTERCARD, VISA, or INVALID
    printf("%s\n", result);
}
