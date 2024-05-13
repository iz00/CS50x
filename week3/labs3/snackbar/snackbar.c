// Practice using structs and writing a linear search function

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
#define NUM_ITEMS 10

// Menu items have item name and price
typedef struct
{
    string item;
    float price;
} menu_item;

// Global array of menu items
menu_item menu[NUM_ITEMS];

void add_items(void);
float get_cost(string item);

int main(void)
{
    // Add items to menu
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    // Print items and prices of menu
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    // Calculate total price of all items chosen
    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        // Loop will stop asking for items when user just hits enter
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        // Get cost of corresponding item and add to total price
        total += get_cost(item);
    }

    // Print total cost of items chosen
    printf("Your total cost is: $%.2f\n", total);
}

// Add items to menu array
void add_items(void)
{
    menu[0].item = "Burger";
    menu[1].item = "Vegan Burger";
    menu[2].item = "Hot Dog";
    menu[3].item = "Cheese Dog";
    menu[4].item = "Fries";
    menu[5].item = "Cheese Fries";
    menu[6].item = "Cold Pressed Juice";
    menu[7].item = "Cold Brew";
    menu[8].item = "Water";
    menu[9].item = "Soda";

    menu[0].price = 9.5;
    menu[1].price = 11;
    menu[2].price = 5;
    menu[3].price = 7;
    menu[4].price = 5;
    menu[5].price = 6;
    menu[6].price = 7;
    menu[7].price = 3;
    menu[8].price = 2;
    menu[9].price = 2;
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        // Case insensitive
        if (strcasecmp(menu[i].item, item) == 0)
        {
            return menu[i].price;
        }
    }
    // If item not found in menu
    printf("Invalid Item!\n");
    return 0.0;
}
