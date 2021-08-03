#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
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

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    // returns false if name isn't in the canidates array
    for (int i = 0; i < candidate_count; i++)
    {
        string dbug = candidates[i].name;
        if (!strcmp(name, candidates[i].name))
        {
            // update the canidate vote
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO

    // sort them
    // let's attempt a bubble sort
    int swapcount = 0;
    do
    {
        swapcount = 0;
        for (int i = 0; i < candidate_count - 1; i++)
        {
            // ordered from largest to smallest
            if (candidates[i].votes < candidates[i + 1].votes)
            {
                candidate tempc = candidates[i + 1];
                candidates[i + 1] = candidates[i];
                candidates[i] = tempc;
                swapcount++;
                // swampcount shows that a swap was made. If 0 at end of loop then the array is in the correct order
            }
        }
    }
    while (swapcount > 0);

    // print the winner(s)
    int top = candidates[0].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == top)
        {
            printf("%s\n", candidates[i].name);
        }

    }

    return;
}

