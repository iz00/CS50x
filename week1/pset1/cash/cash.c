// Greedy algorithm to calculate minimum amount of coins for owed cents user inputs

#include <cs50.h>
#include <stdio.h>

// Definitions of values of coins
#define QUARTER_VALUE 25
#define DIME_VALUE 10
#define NICKEL_VALUE 5
#define PENNY_VALUE 1

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Prompt for how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * QUARTER_VALUE;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * DIME_VALUE;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * NICKEL_VALUE;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * PENNY_VALUE;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

// Prompt user for cents, check if 0 or positive
int get_cents(void)
{
    int n;
    do
    {
        n = get_int("Change owed: ");
    }
    while (n < 0);
    return n;
}

// Calculate the amount of quarters
int calculate_quarters(int cents)
{
    // Division of two ints will truncate the decimal part, the cents that can't be even one coin of this value
    return cents / QUARTER_VALUE;
}

// Calculate the amount of dimes
int calculate_dimes(int cents)
{
    return cents / DIME_VALUE;
}

// Calculate the amount of nickels
int calculate_nickels(int cents)
{
    return cents / NICKEL_VALUE;
}

// Calculate the amount of pennies
int calculate_pennies(int cents)
{
    return cents / PENNY_VALUE;
}
