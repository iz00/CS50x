// Simulate a game of scrabble, that scores words based on a mapping of letters to points

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
string get_winner(int s1, int s2);

int main(void)
{
    // Prompt words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    string winner = get_winner(score1, score2);
    printf("%s\n", winner);
}

// Compute and return score for word
int compute_score(string word)
{
    // Initialize score to 0
    int score = 0;
    // Loop through word, accessing each character, len is calculated first for efficiency
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        // Check if character is a letter, because other characters aren't worth points
        if (isalpha(word[i]))
        {
            // Convert letter to uppercase and use ASCII mapping to get right index
            // Add the corresponding index of the letter in POINTS array to scores
            score += POINTS[toupper(word[i]) - 'A'];
        }
    }
    return score;
}

// Get winner based on scores
string get_winner(int s1, int s2)
{
    if (s1 > s2)
    {
        return "Player 1 wins!";
    }
    else if (s2 > s1)
    {
        return "Player 2 wins!";
    }
    else
    {
        return "Tie!";
    }
}
