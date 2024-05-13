// Calculate approximate grade level needed to comprehend some text, based in Coleman-Liau index

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);
int calculate_index(int letters, int words, int sentences);
void check_print_grade(int n);

int main(void)
{
    // Prompt user for text
    string text = get_string("Text: ");

    // Define and calculate three variables, letters count, words count, and sentences count
    int letters_count = count_letters(text);
    int words_count = count_words(text);
    int sentences_count = count_sentences(text);

    // Calculate index in Coleman-Liau formula using the values discovered before
    int index = calculate_index(letters_count, words_count, sentences_count);

    // Print corresponding grade
    check_print_grade(index);
}

// Calculate how many letters string s has
int count_letters(string s)
{
    int n = 0;
    // Loop through s to get each character through i, len is calculated first for efficiency
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        // If character is alphabetic, increase n
        if (isalpha(s[i]))
        {
            n++;
        }
    }
    return n;
}

// Calculate how many words string s has
int count_words(string s)
{
    int n = 0;
    // Loop through s to get each character through i, len is calculated first for efficiency
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        // If character is a space, isn't the first or last character
        // And the char before it isn't a space, increase n
        if ((s[i] == ' ') && (i != 0) && (i != len - 1) && (s[i - 1] != ' '))
        {
            n++;
        }
    }
    // Return ++n because the spaces are between words, so n would return one less word than should
    return ++n;
}

// Calculate how many sentences string s has
int count_sentences(string s)
{
    int n = 0;
    // Loop through s to get each character through i, len is calculated first for efficiency
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        // If character is ., !, or ? increase n
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            n++;
        }
    }
    return n;
}

// Calculate index of Coleman-Liau formula
int calculate_index(int letters, int words, int sentences)
{
    // Calculate amount of letters L and sentences S in 100 words
    float L = letters / (float) words * 100;
    float S = sentences / (float) words * 100;

    // Round the result of formula applied
    return round(0.0588 * L - 0.296 * S - 15.8);
}

// Check grade through index and print accordingly
void check_print_grade(int n)
{
    if (n < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (n > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", n);
    }
}
