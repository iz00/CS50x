// Says hello to the name the user types

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for name, and print the name after hello with format in printf
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}
