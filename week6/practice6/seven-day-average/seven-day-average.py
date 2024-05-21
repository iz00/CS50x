# Calculate 7-day average of Covid cases in US states input by user

import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    # Get input from user of states to calculate 7-day average on
    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# Return dictionary that stores 14 most recent days of new cases by state
def calculate(reader):
    previous_cases, new_cases = {}, {}

    # Read every line of reader csv file as a dictionary, called day
    for day in reader:
        new_cases_day = int(day["cases"])

        # Try to acess the cases of previous_cases of current state
        try:
            # Calculate the new_cases_day, by subtracting the previous_cases from current day cases
            new_cases_day -= previous_cases[day["state"]]

        # If KeyError, that state was not yet included, thus create a list for 14 days of current state
        except KeyError:
            new_cases.update({day["state"]: [new_cases_day]})

        # With new_cases_day calculated, include it in list for 14 days of current state
        else:
            # If list already has 14 states, delete the first one (oldest)
            if len(new_cases[day["state"]]) == 14:
                new_cases[day["state"]].pop(0)
            new_cases[day["state"]].append(new_cases_day)

        # Update cases of previous_cases of current state to be current day cases
        previous_cases.update({day["state"]: int(day["cases"])})

    return new_cases


# Calculate and print 7-day average for given states
def comparative_averages(new_cases, states):
    for state in states:
        # Get average for current and previous week, by splicing the list of cases of state
        average_current_week = sum(new_cases[state][7:]) / 7
        average_previous_week = sum(new_cases[state][:7]) / 7

        difference = average_current_week - average_previous_week

        print(f"{state} had a 7-day average of {round(average_current_week)}", end=" ")

        # Catch division by zero, else calculate the percentage increase or decrease of cases
        try:
            percent = difference / average_previous_week
        except ZeroDivisionError:
            raise ZeroDivisionError
        else:
            percent *= 100

        if difference < 0:
            print(f"and a decrease of {abs(percent):.2f}%.")
        else:
            print(f"and an increase of {percent:.2f}%.")


main()
