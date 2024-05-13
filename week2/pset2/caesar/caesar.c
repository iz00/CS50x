// Encode a message using Caesar's cipher, given a key and plaintext input by user

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_LENGTH 26

bool validate_argc(int c);
bool validate_argument(string v);
void print_ciphertext(string text, int key);

int main(int argc, string argv[])
{

    // Variable command_argument_valid is true if command line argument is valid, false otherwise
    bool command_argument_valid = validate_argc(argc);

    if (command_argument_valid)
    {
        command_argument_valid = validate_argument(argv[1]);
    }

    // If command line argument not valid, print a usage message and return 1 for error
    if (!command_argument_valid)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Prompt user for plaintext
    string plaintext = get_string("plaintext:  ");

    // Encode plaintext with the key, converted from string to int, and print ciphertext
    print_ciphertext(plaintext, atoi(argv[1]));

    return 0;
}

// Validate amount of arguments, if not 2, return false
bool validate_argc(int c)
{
    if (c != 2)
    {
        return false;
    }
    return true;
}

// Validate argument, if passed validation of argc
bool validate_argument(string v)
{
    // All characters of argument have to be digits
    for (int i = 0, len = strlen(v); i < len; i++)
    {
        if (!isdigit(v[i]))
        {
            return false;
        }
    }

    // If is digit, the number has to be 0 or positive
    if (atoi(v) < 0)
    {
        printf("Usage: ./caesar key\n");
        return false;
    }

    return true;
}

// Encode the text with the key and print it
void print_ciphertext(string text, int key)
{
    printf("ciphertext: ");

    // Loop through text to get each character through i, len is calculated first for efficiency
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Get alphabetical index of letter, then rotate it by key positions, using modulo
        // Then return the index to ASCII, and print the letter, respecting the case
        if (isupper(text[i]))
        {
            printf("%c", (text[i] - 'A' + key) % ALPHABET_LENGTH + 'A');
        }
        else if (islower(text[i]))
        {
            printf("%c", (text[i] - 'a' + key) % ALPHABET_LENGTH + 'a');
        }
        // If character not a letter, just print it
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}
