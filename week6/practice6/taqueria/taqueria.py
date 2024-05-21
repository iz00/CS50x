# Simulate an order on a taqueria

# Dict with items as keys and values as corresponding prices
menu = {
    "Baja Taco": 4.25,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00,
}

total = 0

while True:
    # Try to get the input item
    try:
        item = input("Item: ").strip().title()
    # If user input control-d, catch and finish program
    except EOFError:
        print()
        break

    # Try to acess the input item on menu dict and add its price to total
    try:
        total += menu[item]
    # If item not in menu, try again
    except KeyError:
        continue

    print(f"Total: ${total:.2f}")
