// Simulate the game Wordle similarly

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Each of the text files contains 1000 words
#define LISTSIZE 1000

// Values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET "\e[0;39m"

// User-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    // Ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
    int wordsize = atoi(argv[1]);

    if (wordsize != 5 && wordsize != 6 && wordsize != 7 && wordsize != 8)
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }

    // Open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // Load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // Pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // Allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // Print greeting, using ANSI color codes
    printf(GREEN "This is WORDLE50" RESET "\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // Main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // Obtain user's guess
        string guess = get_guess(wordsize);

        // Array to hold guess status, initially set to zero
        int status[wordsize];

        // Set all elements of status array initially to 0, aka WRONG
        for (int j = 0; j < wordsize; j++)
        {
            status[j] = WRONG;
        }

        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);

        // If user guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result
    if (won)
    {
        printf("You won!\n");
    }
    else
    {
        printf("The word was: %s\n", choice);
    }

    return 0;
}

// Prompt user for their guess on word
string get_guess(int wordsize)
{
    string guess;

    // Ensure user actually provide a guess that is the correct length
    do
    {
        guess = get_string("Input a %i-letter word: ", wordsize);
    }
    while (strlen(guess) != wordsize);

    // Ensure the guess has all letters lowercase
    for (int i = 0, len = strlen(guess); i < len; i++)
    {
        guess[i] = tolower(guess[i]);
    }

    return guess;
}

// Compare guess to choice and score points as appropriate, storing points in status
int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;

    // Iterate over each letter of the guess
    for (int i = 0; i < wordsize; i++)
    {
        // Iterate over each letter of the choice
        for (int j = 0; j < wordsize; j++)
        {
            if (guess[i] == choice[j])
            {
                // If the letter is in the same position in both words
                if (i == j)
                {
                    status[i] = EXACT;
                    break;
                }
                else
                {
                    status[i] = CLOSE;
                }
            }
        }
        score += status[i];
    }

    return score;
}

// Print word character-for-character with correct color coding, then reset terminal font to normal
void print_word(string guess, int wordsize, int status[])
{
    // Loop through status
    for (int i = 0; i < wordsize; i++)
    {
        // Switch the status and set the corresponding color
        switch (status[i])
        {
            case EXACT:
                printf(GREEN "");
                break;

            case CLOSE:
                printf(YELLOW "");
                break;

            case WRONG:
                printf(RED "");
                break;
        }

        printf("%c", guess[i]);
    }

    printf(RESET "\n");
    return;
}
