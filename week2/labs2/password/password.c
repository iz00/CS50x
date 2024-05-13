// Check that a password has at least one lowercase letter, uppercase letter, number and symbol

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    // Prompt user for password
    string password = get_string("Enter your password: ");

    // Check if password valid, and print message accordingly
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// Return true or false for validation of password
bool valid(string password)
{
    // Bool variable for characteristics password must have, initially all false
    bool has_lower = false, has_upper = false, has_number = false, has_symbol = false;

    // Loop through password, len is calculated first for efficiency
    for (int i = 0, len = strlen(password); i < len; i++)
    {
        // Check if password character is lowercase, if true change variable
        if (islower(password[i]))
        {
            has_lower = true;
        }
        // Check if password character is uppercase, if true change variable
        if (isupper(password[i]))
        {
            has_upper = true;
        }
        // Check if password character is a number, if true change variable
        if (isdigit(password[i]))
        {
            has_number = true;
        }
        // Check if password character is a symbol, if true change variable
        if (ispunct(password[i]))
        {
            has_symbol = true;
        }
    }

    // Return true if password has all tests for validation as true
    if (has_lower && has_upper && has_number && has_symbol)
    {
        return true;
    }
    return false;
}
