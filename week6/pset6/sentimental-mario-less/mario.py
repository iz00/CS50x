# Build a right alligned pyramid from mario with the height as user input

# Definition of limits of height
TOO_LOW_HEIGHT, TOO_HIGH_HEIGHT = 0, 9


def main():
    # Prompt for height of pyramid
    height = get_height()

    # Print pyramid with height
    print_pyramid(height)


# Prompt user for height, check if input is int and if it is within the limits
def get_height():
    while True:
        try:
            n = int(input("Height: "))
        except ValueError:
            pass
        else:
            if n > TOO_LOW_HEIGHT and n < TOO_HIGH_HEIGHT:
                return n


# Print pyramid with height n
def print_pyramid(n):
    # Loop height times, i starts at 1 because it is the number of # printed each line
    for i in range(1, n + 1):
        # Get strings of empty spaces and of bricks on each line
        empty_spaces = " " * (n - i)
        bricks = "#" * i

        # Print each level of pyramid
        print(f"{empty_spaces}{bricks}")


main()
