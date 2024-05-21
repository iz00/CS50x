# Outputs given text in a figlet font

from sys import argv, exit
from pyfiglet import Figlet
from random import choice

figlet = Figlet()

# Get a list of fonts available to use
fonts = figlet.getFonts()

# If no command-line arguments, choose randomly a font
if len(argv) == 1:
    figlet.setFont(font=choice(fonts))

# If two command-line arguments, one to set the font, and other a valid font, set the font
elif len(argv) == 3 and argv[1] in ["-f", "--font"] and argv[2] in fonts:
    figlet.setFont(font=argv[2])

else:
    print("Invalid usage")
    exit(1)

# Get input of string to output and output it in set font
s = input("Input: ")

print("Output:")

print(figlet.renderText(s))

exit(0)
