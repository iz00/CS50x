# Output some value depending on a given greeting

# Get input from user and deletes leading whitespaces
greeting = input("Greeting: ").lstrip()

# Get just first five characters of greeting and lower them
first_five_chars = greeting[:5].lower()

# Test the first_five_characters and output accordingly
if first_five_chars == "hello":
    print("$0")
elif first_five_chars[0] == "h":
    print("$20")
else:
    print("$100")
