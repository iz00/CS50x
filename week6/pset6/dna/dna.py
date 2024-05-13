# Check a DNA database and a DNA sequence to determine to whom it belongs

import csv
import sys


def main():
    # Ensure correct usage (2 command-line arguments)
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read database file into a variable
    people = read_people_database(sys.argv[1])

    # Read DNA sequence file into a variable
    dna_sequence = read_dna_sequence(sys.argv[2])

    # Get a list with all the STRs each person in the database has
    # Get a person's keys, but slice out the first, because that's the "name" key
    STRs = list(people[0].keys())[1:]

    # Find longest match of each STR in DNA sequence
    STRs_count = get_dna_STRs(people, dna_sequence, STRs)

    # Check database for matching profiles
    print(check_match(people, STRs_count, STRs))


# Read database of DNAs to a list, each element is a dict of a person's DNA
def read_people_database(filename):
    people = []
    try:
        file = open(filename)
    except FileNotFoundError:
        sys.exit("File not found")
    else:
        file_reader = csv.DictReader(file)

        for person in file_reader:
            people.append(person)

        file.close()

    return people


# Read given person DNA sequence file into a string
def read_dna_sequence(filename):
    try:
        file = open(filename)
    except FileNotFoundError:
        sys.exit("File not found")
    else:
        dna_sequence = file.read()
        file.close()

    return dna_sequence


# Return length of longest run of subsequence in sequence
def longest_match(sequence, subsequence):
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


# Get a dict with the STRs count the given DNA has
def get_dna_STRs(people, dna_sequence, STRs):
    STRs_count = {}
    # For each STR, check for longest match in given DNA sequence
    for STR in STRs:
        STRs_count[STR] = str(longest_match(dna_sequence, STR))

    return STRs_count


# Check database for matching profiles with STRs count of DNA sequence
def check_match(people, STRs_count, STRs):
    for person in people:
        match = True
        for STR in STRs:
            # If even one STR is different, no match, update match flag and go to next person
            if STRs_count[STR] != person[STR]:
                match = False
                break
        # If no STRs are different, match flag will still be True
        if match:
            return person["name"]

    # If all people were analysed, and none resulted in a match
    return "No match"


main()
