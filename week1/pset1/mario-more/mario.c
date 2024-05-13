// Build two pyramids (right and left alligned) from mario with the height as user input

#include <cs50.h>
#include <stdio.h>

// Definitions of min and max height of pyramids
#define MIN_HEIGHT 1
#define MAX_HEIGHT 8

int get_height(void);
void print_char_times(char c, int n);
void print_pyramids(int n);

int main(void)
{
    // Prompt for height of pyramids
    int height = get_height();

    // Print pyramids with height
    print_pyramids(height);
}

// Prompt user for height, check if greater than MIN and less than MAX
int get_height(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while ((n < MIN_HEIGHT) || (n > MAX_HEIGHT));

    return n;
}

// Prints determined character c, n times
void print_char_times(char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}

// Print pyramids with height n
void print_pyramids(int n)
{
    // Loop height times, i starts at 1 because it is the number of # printed each line in each pyramid
    for (int i = 1; i <= n; i++)
    {
        // The number of empty spaces printed in every line of left pyramid is the height - i
        int num_empty_spaces = n - i;

        // Print the left pyramid line
        print_char_times(' ', num_empty_spaces);
        print_char_times('#', i);

        // Print the two empty spaces between the pyramids
        printf("  ");

        // Print the right pyramid line
        print_char_times('#', i);

        // Create a new line
        printf("\n");
    }
}
