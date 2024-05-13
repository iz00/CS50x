// Implement atoi (convert string to int) using recursion

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    // Prompt user for string that represents a positive integer
    string input = get_string("Enter a positive integer: ");

    // Check for any non-numeric character, and finish program
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

// Receive string as input, returns int of string converted
int convert(string input)
{
    // Base case of recursion, all digits were considered and the string is all NUL
    if (input[0] == '\0')
    {
        return 0;
    }

    // Get current last index with a digit in string
    int last_index = strlen(input) - 1;

    // Get current last digit of string
    int last_digit = input[last_index];

    // Update string, last digit is substituted by NUL so next recursion runs on digit before it
    input[last_index] = '\0';

    // Recursive case, returns current last digit converted to int + function call to itself multiplied by 10
    return (last_digit - '0') + (10 * convert(input));
}
