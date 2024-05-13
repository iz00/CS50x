# Validate a card number with Luhn's algorithm and check card brand

from sys import exit


def main():
    # Prompt user for card number, ignoring non-numeric common characters
    card_number = input("Number: ").replace(" ", "").replace("-", "").replace(".", "")
    if not card_number.isdecimal():
        exit("INVALID")

    card_number_sum = calculate_luhn_sum(card_number)

    print(validate_card_check_type(card_number, card_number_sum))


# Calculate Luhn's algorithm sum of card number
def calculate_luhn_sum(number):
    s = 0

    # Slice number starting from second to last digit, getting every other digit
    for digit in number[-2::-2]:
        # Double the digit and add its digits to s
        digit = int(digit) * 2
        s += digit // 10 + digit % 10

    # Slice number starting from last digit, getting every other digit
    for digit in number[::-2]:
        # Add the digit to s
        s += int(digit)

    return s


# Return validation (invalid if it is) and type (if valid) of card
def validate_card_check_type(number, s):
    # Card invalid if last digit of sum is not 0
    if s % 10 != 0:
        return "INVALID"

    card_digits = len(number)

    # It's an American Express card
    if card_digits == 15 and number[:2] in ["34", "37"]:
        return "AMEX"
    # It's a MasterCard card
    elif card_digits == 16 and number[:2] in ["51", "52", "53", "54", "55"]:
        return "MASTERCARD"
    # It's a Visa card
    elif (card_digits == 13 or card_digits == 16) and number[0] == "4":
        return "VISA"
    # If didn't check validation for brands, it is invalid
    else:
        return "INVALID"


main()
