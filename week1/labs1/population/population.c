// Calculate number of years to get from start to end size of population

#include <cs50.h>
#include <stdio.h>

// If population is less than 9, it will stagnate
#define MIN_SIZE 9

int get_start_size(void);
int get_end_size(int s);
int calculate_years(int s, int e);

int main(void)
{
    // Prompt for start and end sizes
    int start = get_start_size();
    int end = get_end_size(start);

    // Calculate number of years until we reach threshold
    int years = calculate_years(start, end);

    // Print number of years
    printf("Years: %i\n", years);
}

// Prompt user for start size, check if greater than or equal to MIN_SIZE
int get_start_size(void)
{
    int n;
    do
    {
        n = get_int("Start size: ");
    }
    while (n < MIN_SIZE);
    return n;
}

// Prompt user for end size, check if greater than or equal to start size
int get_end_size(int s)
{
    int n;
    do
    {
        n = get_int("End size: ");
    }
    while (n < s);
    return n;
}

// Calculate number of years from start size to end size in a loop
int calculate_years(int s, int e)
{
    int y = 0;
    while (e > s)
    {
        // In a year, n / 3 llamas are born and n / 4 llamas pass away
        s += s / 3 - s / 4;
        y++;
    }
    return y;
}
