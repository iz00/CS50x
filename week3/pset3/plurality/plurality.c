// Simulate a plurality election

#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

bool vote(string name);
int get_max_votes(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for no candidates, invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Check for too many candidates, invalid usage
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Populate array of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote or returns false if candidate not valid
bool vote(string name)
{
    // Loop through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Case insensitive, update votes for candidate found
        if (strcasecmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Get the max number of votes received by a candidate
int get_max_votes(void)
{
    // Initially, first candidate has the max votes
    int max = candidates[0].votes;

    // Loop through candidates beggining after first element
    for (int i = 1; i < candidate_count; i++)
    {
        // If candidate has more votes than previous max, becomes current max
        if (candidates[i].votes > max)
        {
            max = candidates[i].votes;
        }
    }
    return max;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_votes = get_max_votes();

    // Loop through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate has max number of votes
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
