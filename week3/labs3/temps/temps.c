// Practice working with structs and applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

// Struct of average temp
typedef struct
{
    string city;
    int temp;
} avg_temp;

// Global array of type average temp
avg_temp temps[NUM_CITIES];

void sort_cities(void);

int main(void)
{
    // Filling of array temps

    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    // Print temps array, with both fields of struct avg_temp
    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// Sort cities by temperature in descending order

// Bubble sort
void sort_cities(void)
{
    // Counter of swaps in each iteration
    int swap_counter;

    do
    {
        swap_counter = 0;

        // Loop through temps
        for (int i = 0; i < NUM_CITIES - 1; i++)
        {
            // If two sequencial elements are in wrong order (first smaller than second)
            if (temps[i].temp < temps[i + 1].temp)
            {
                // Swap elements
                avg_temp aux = temps[i];
                temps[i] = temps[i + 1];
                temps[i + 1] = aux;

                swap_counter++;
            }
        }
    }
    // If no swaps, temps is sorted
    while (swap_counter != 0);
}

/*
// Selection sort
void sort_cities(void)
{
    // Loop through temps
    for (int i = 0; i < NUM_CITIES - 1; i++)
    {
        // Index of biggest element of unsorted part
        int biggest_index = i;

        // Loop through unsorted part
        for (int j = i + 1; j < NUM_CITIES; j++)
        {
            // If temp is bigger than previous biggest found, or equal, but city name comes first
            if ((temps[j].temp > temps[biggest_index].temp) ||
                ((temps[j].temp == temps[biggest_index].temp) && (temps[j].city[0] < temps[biggest_index].city[0])))
            {
                biggest_index = j;
            }
        }
        // Swap biggest found in unsorted part with first element in unsorted part
        avg_temp aux = temps[i];
        temps[i] = temps[biggest_index];
        temps[biggest_index] = aux;
    }
}
*/
