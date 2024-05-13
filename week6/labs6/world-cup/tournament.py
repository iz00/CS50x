# Simulate a sports tournament

import csv
import sys
import random

# Number of simulations to run
N = 1000


def main():
    # Ensure correct usage (1 command-line argument)
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # Read teams into memory from file

    try:
        file = open(sys.argv[1])
    except FileNotFoundError:
        sys.exit("File not found")
    else:
        file_reader = csv.DictReader(file)

        for team in file_reader:
            # Convert rating to int for it to be used in coming calculations
            team["rating"] = int(team["rating"])
            teams.append(team)

        file.close()

    counts = {}
    # Simulate N tournaments and keep track of win counts
    for i in range(N):
        winner = simulate_tournament(teams)

        # Check if winner already found previously, else initializes the winner key in count
        if winner in counts:
            counts[winner] += 1
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


# Simulate a game: Return True if team1 wins, False otherwise
def simulate_game(team1, team2):
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


# Simulate a round: Return a list of winning teams
def simulate_round(teams):
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


# Simulate a tournament: Return name of winning team
def simulate_tournament(teams):
    while True:
        if len(teams) == 1:
            return teams[0]["team"]

        # simulate_round returns a list with half length of list it was given
        teams = simulate_round(teams)


if __name__ == "__main__":
    main()
