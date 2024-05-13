// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    // Prompt for bill_amount, tax_percent and tip_percent
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    // Print the half of the bill, with 2 digits after the point
    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// Calculate half of the bill, apllying tax before tip
float half(float bill, float tax, int tip)
{
    // In a division, at least one of the two must be a float for the result to be float
    bill += bill * (tax / 100);

    // As tip was int, the number 100 is float with the .0 at the end
    bill += bill * (tip / 100.0);

    return bill / 2;
}
