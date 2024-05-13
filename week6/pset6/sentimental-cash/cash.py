# Greedy algorithm to calculate minimum amount of coins for owed change user inputs

from cs50 import get_float

# Definitions of values of coins
QUARTER, DIME, NICKEL, PENNY = 25, 10, 5, 1
coins_list = [QUARTER, DIME, NICKEL, PENNY]


def main():
    # Prompt for how much change the customer is owed
    change = get_change()

    # Print total number of coins to give the customer
    print(calculate_coins(change))


# Prompt user for change, check if 0 or positive
def get_change():
    while True:
        n = get_float("Change owed: ")
        if n >= 0:
            return n


# Calculate total number of coins to give the user
def calculate_coins(change):
    # Get only the integer part of change, each unit is equivalent to 4 quarters
    coins = int(change) * 4

    # Update change to be its cents part
    change = int((change - int(change)) * 100)

    for coin in coins_list:
        # Divide and truncate change by every coin value to get the amount of that coin
        coins += change // coin
        # Update change to be the value that can't fit in that coin's value
        change %= coin

    return coins


main()
