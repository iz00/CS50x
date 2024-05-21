// List all prime numbers in a range specified by the user

#include <cs50.h>
#include <stdio.h>

int get_min(void);
int get_max(int m);
void tests_numbers(int mi, int ma);
bool prime(int number);

int main(void)
{
    // Prompt for min and max of the range
    int min = get_min();
    int max = get_max(min);

    // Test each number in the range if prime, print number if true
    tests_numbers(min, max);
}

// Prompt user for min of the range, check if positive
int get_min(void)
{
    int n;
    do
    {
        n = get_int("Minimum: ");
    }
    while (n < 1);
    return n;
}

// Prompt user for max of the range, check if greater than min
int get_max(int m)
{
    int n;
    do
    {
        n = get_int("Maximum: ");
    }
    while (n <= m);
    return n;
}

// Loop through all numbers between mi and ma, return is void, only print number if prime
void tests_numbers(int mi, int ma)
{
    for (int i = mi; i <= ma; i++)
    {
        // The number is passed to the function prime as an argument, to check if prime
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

// Return true if number is prime, false otherwise
bool prime(int number)
{
    // 1 isn't prime, as well as even numbers, except for 2
    if ((number == 1) || ((number % 2 == 0) && (number != 2)))
    {
        return false;
    }

    // Get the max number necessary for testing in the loop
    int max_test = number / 2;

    // Starting from 3 until the half of the number + 2
    // i gets incremented by 2, so it is always odd
    for (int i = 3; i < max_test; i += 2)
    {
        // Test if the number is divisible by i, if true return false
        if (number % i == 0)
        {
            return false;
        }
    }

    // If function reach here, the loop couldn't find a divisor, return true
    return true;
}
