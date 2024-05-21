// Write a function to replace vowels with numbers, like l33tsp36k

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string sentence);

int main(int argc, string argv[])
{
    // If more or less than 1 command-line argument besides the execute name of program
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }

    // Variable sentence_converted receives command-line argument after replace function
    string sentence_converted = replace(argv[1]);

    printf("%s\n", sentence_converted);

    return 0;
}

// Replace vowels with numbers in sentence
string replace(string sentence)
{
    // Loop through string, len is calculated first for efficiency
    for (int i = 0, len = strlen(sentence); i < len; i++)
    {
        // Switch check if current char is a vowel, if is change it to corresponding number
        switch (sentence[i])
        {
            case 'a':
                sentence[i] = '6';
                break;
            case 'e':
                sentence[i] = '3';
                break;
            case 'i':
                sentence[i] = '1';
                break;
            case 'o':
                sentence[i] = '0';
                break;
        }
    }
    return sentence;
}
