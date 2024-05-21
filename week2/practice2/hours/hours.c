// Calculate total or average number of hours spent on course's homeworks every week

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    // Prompt user for weeks taking cs50, defines array hours with size weeks
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    // Loops through hours and fills each element with user input of hours spent per week
    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    // Prompt user for output T or A for total or average hours
    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    // Print hours based on output, and the array hours
    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// Calculate total or average of hours in array
float calc_hours(int hours[], int weeks, char output)
{
    // Initialize sum to 0 and loops through array, adding to sum every element
    float sum = 0;
    for (int i = 0; i < weeks; i++)
    {
        sum += hours[i];
    }

    // If average, divide sum of hours by the number of weeks, sum is float so works
    if (output == 'A')
    {
        return sum / weeks;
    }
    return sum;
}
