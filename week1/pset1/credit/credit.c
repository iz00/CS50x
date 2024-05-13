// Validate a card number with Luhn's algorithm and check card brand

#include <cs50.h>
#include <stdio.h>

int card_digits_amount(long n);
long power_base_ten(int times);
int calculate_luhn_sum(long n, int digits);
string validate_card_check_type(long n, int s, int digits);

int main(void)
{
    // Prompt user for card number, long because can't fit in int
    long number = get_long("Number: ");

    // Calculate amount of digits in card number
    int digits_amount = card_digits_amount(number);

    // Calculate Luhn's algorithm sum of card number
    int sum = calculate_luhn_sum(number, digits_amount);

    // Get string of validation or type of card
    string card_type = validate_card_check_type(number, sum, digits_amount);

    // Print card type, or invalid
    printf("%s\n", card_type);
}

// Calcute amount of digits in card number, because it's used in other functions
int card_digits_amount(long n)
{
    int digits = 0;

    // Current last digit of card number is removed in every iteration, and digits increased
    while (n > 0)
    {
        digits++;
        n /= 10;
    }
    return digits;
}

// Calculate 10 to the power of times, result is digit 1 followed by times digits 0
long power_base_ten(int times)
{
    long n = 1;
    for (int i = 0; i < times; i++)
    {
        n *= 10;
    }
    return n;
}

// Calculate Luhn's algorithm
int calculate_luhn_sum(long n, int digits)
{
    int s = 0;
    int digit;

    for (int i = 0; i < digits; i++)
    {
        // Variable digit is digit of card number relative to iteration, starting from right
        digit = n % power_base_ten(i + 1) / power_base_ten(i);

        // If iteration pair, s receives the digit
        if (i % 2 == 0)
        {
            s += digit;
        }
        // Else, receives the digits of the digit * 2
        else
        {
            digit *= 2;
            s += digit / 10 + digit % 10;
        }
    }
    return s;
}

// Return validation (invalid if it is) and type (if valid) of card
string validate_card_check_type(long n, int s, int digits)
{
    // Card invalid if last digit of sum is not 0
    if (s % 10 != 0)
    {
        return "INVALID";
    }

    // Get first and second digit of card number
    int first_digit = n / power_base_ten(digits - 1);
    int second_digit = n / power_base_ten(digits - 2) % 10;

    switch (first_digit)
    {
        // Return American Express if all following conditions are valid
        case 3:
            if (second_digit == 4 || second_digit == 7)
            {
                if (digits == 15)
                {
                    return "AMEX";
                }
            }
            break;

        // Return MasterCard if all following conditions are valid
        case 5:
            if (second_digit > 0 && second_digit < 6)
            {
                if (digits == 16)
                {
                    return "MASTERCARD";
                }
            }
            break;

        // Return Visa if all following conditions are valid
        case 4:
            if (digits == 13 || digits == 16)
            {
                return "VISA";
            }
            break;
    }
    // If not check validation for brands, is invalid
    return "INVALID";
}
