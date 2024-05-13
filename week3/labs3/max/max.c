// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int get_number_elements(void);
int max(int array[], int n);

int main(void)
{
    // Prompt for number of elements
    int n = get_number_elements();

    // Declaration of array of size n
    int arr[n];

    // Prompt user for value of every element of array
    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i + 1);
    }

    // Print max value found
    printf("The max value is %i.\n", max(arr, n));
}

// Prompt user for number of elements, check if greater than 0
int get_number_elements(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    return n;
}

// Calculate and return max value in array
int max(int array[], int n)
{
    // Initially, first element is the max
    int max = array[0];

    // Loop through array beggining after first element
    for (int i = 1; i < n; i++)
    {
        // If element greater than previous max, becomes current max
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}
