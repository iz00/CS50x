// Encode a message converting each character to the binary form of its decimal ASCII value

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Global const variable of bits in a byte
const int BITS_IN_BYTE = 8;

void convert_character_binary(int character_binary[], int character_decimal);
void print_bulb(int bit);
void print_character_bulbs(int character_binary[]);

int main(void)
{
    // Prompt user for message to be encoded
    string message = get_string("Message: ");

    // Array in which each element is a digit of the binary form of character, has length of a byte
    int character_binary_digits[BITS_IN_BYTE];

    // Loop through message to get each character through i
    for (int i = 0, len = strlen(message); i < len; i++)
    {
        // Convert the decimal ASCII value of character (message[i] of type int) to binary
        convert_character_binary(character_binary_digits, message[i]);

        // Print the binary form of the character as light bulbs
        print_character_bulbs(character_binary_digits);
    }
}

// Convert the character to binary, filling the array that will receive the binary digits
void convert_character_binary(int character_binary[], int character_decimal)
{
    // Loop the size of the array, and, starting from its end, fills it with binary digits
    for (int i = 0; i < BITS_IN_BYTE; i++)
    {
        // Converts decimal character to binary through divisions of 2
        character_binary[BITS_IN_BYTE - 1 - i] = character_decimal % 2;
        character_decimal /= 2;
    }
}

// Print bulb equivalent to binary digit as input
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

// Print all bulbs in a line, referent to a character
void print_character_bulbs(int character_binary[])
{
    // Loop through binary array, print as bulb each digit
    for (int i = 0; i < BITS_IN_BYTE; i++)
    {
        print_bulb(character_binary[i]);
    }
    printf("\n");
}
