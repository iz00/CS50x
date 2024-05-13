// Encode a message per a mapping of the alphabet letters to letters in a key input by the user

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ALPHABET_LENGTH 26

string validate_argc(int c);
string validate_argument(string v);
void print_ciphertext(string text, string key);

int main(int argc, string argv[])
{
    // Variable command_argument_validation is valid if command line argument is valid, else is custom message
    string command_argument_validation = validate_argc(argc);

    if (!strcmp(command_argument_validation, "valid"))
    {
        command_argument_validation = validate_argument(argv[1]);
    }

    // If command line argument not valid, print the corresponding message and return 1 for error
    if (strcmp(command_argument_validation, "valid"))
    {
        printf("%s\n", command_argument_validation);
        return 1;
    }

    // Prompt user for plaintext
    string plaintext = get_string("plaintext:  ");

    // Encode plaintext with the key, and print ciphertext
    print_ciphertext(plaintext, argv[1]);

    return 0;
}

// Validate amount of arguments, if not 2, return usage message
string validate_argc(int c)
{
    if (c != 2)
    {
        return "Usage: ./substitution key";
    }
    return "valid";
}

// Validate argument, if passed validation of argc
string validate_argument(string v)
{
    int len = strlen(v);
    // The length of argument has to be the same as the alphabet, for correct mapping
    if (len != ALPHABET_LENGTH)
    {
        return "Key must contain 26 characters.";
    }

    // Loop through argument to get each character through i
    for (int i = 0; i < len; i++)
    {
        // All characters of argument have to be letters
        if (!isalpha(v[i]))
        {
            return "Key must only contain alphabetic characters.";
        }

        // Check if there are two equal letters in argument, which can't happen for correct mapping
        for (int j = i + 1; j < len; j++)
        {
            if (tolower(v[i]) == tolower(v[j]))
            {
                return "Key must not contain repeated characters.";
            }
        }
    }
    return "valid";
}

// Encode the text with the key and print it
void print_ciphertext(string text, string key)
{
    printf("ciphertext: ");

    // Loop through text to get each character through i, len is calculated first for efficiency
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Get alphabetical index of letter, then map it to corresponding position in the key
        // Then print the letter uppercase or lowercase depending on how it was before encoding
        if (isupper(text[i]))
        {
            printf("%c", toupper(key[text[i] - 'A']));
        }
        else if (islower(text[i]))
        {
            printf("%c", tolower(key[text[i] - 'a']));
        }
        // If character not a letter, just print it
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}
