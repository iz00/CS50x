# Calculate approximate grade level needed to comprehend some text, based in Coleman-Liau index


def main():
    text = input("Text: ")

    words = text.split()
    # Join the words, separated by spaces, to get rid of unnecessary spaces from user input
    text = " ".join(words)

    letters_count = count_letters(text)

    # If there are no letters, there are also no words or sentences
    if letters_count == 0:
        words_count = sentences_count = 0
    else:
        # Get amount of words and of sentences, defined by ., ! or ?
        words_count = len(words)
        sentences_count = text.count(".") + text.count("!") + text.count("?")

    index = calculate_index(letters_count, words_count, sentences_count)

    print(define_grade(index))


# Calculate amount of letters in t
def count_letters(t):
    letters = 0

    # Check each character if is alphabetical, if it is, increment counter
    for c in t:
        if c.isalpha():
            letters += 1

    return letters


# Calculate index of Coleman-Liau formula
def calculate_index(letters, words, sentences):
    # Calculate amount of letters L and sentences S in 100 words
    L = letters / words * 100
    S = sentences / words * 100

    # Round the result of formula applied
    return round(0.0588 * L - 0.296 * S - 15.8)


# Check grade through index
def define_grade(n):
    if n < 1:
        return "Before Grade 1"

    if n > 16:
        return "Grade 16+"

    return f"Grade {n}"


main()
