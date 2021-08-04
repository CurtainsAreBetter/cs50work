#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Get index of a candidate
// returns -1 if name is not found
int candex(string name)
{
    //loop through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            return i;
        }
    }
    return -1;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    // check if name exists in candidates[]
    // check if name has already been voted for
    // yep
    // I think I could use candex() here but i don't want to think more than I have to
    // and I've already written this loop
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i], name))
        {
            // name was found within candidates
            for (int j = 0; j < rank; j++)
            {
                // if name == candidate that has the index found at rank's index of j
                if (!strcmp(name, candidates[ranks[j]]))
                {
                    // name is a repeat
                    return false;
                }
            }
            // update rank by setting name as it's index and putting that int into the proper
            // location
            ranks[rank] = candex(name);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // preferences[i][j] is number of voters who prefer i over j

    // look at pref[r[i]], look through what comes after r[i]
    // do this until the 2nd to last index of ranks so you don't go past your array
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // idk if this is worth doing but just to make sure nothing weird happens
        preferences[ranks[i]][ranks[i]] = 0;  // You can't win or lose against yourself
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            // ties can be ignored
            int check = preferences[i][j] - preferences[j][i];
            // ij > ji
            if (check > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // if ij < ji
            else if (check < 0)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// meant to be used for sort_pairs this function saves my brain from having to think
// gets the strength of a pair
int strength(pair p)
{
    int num = preferences[p.winner][p.loser] - preferences[p.loser][p.winner];
    return num;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int check;
    do
    {
        check = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (strength(pairs[i]) < strength(pairs[ i + 1]))
            {
                pair tmp_pair = pairs[i + 1];
                pairs[i + 1] = pairs[i];
                pairs[i] = tmp_pair;
                check++;
            }
        }
    }
    while (check > 0);
    return;
}

// Recursive function to traverse the graph looking for cycles
// Returns true if a cycle is made from the given pair
// Returns false if no cycle is made
bool check_cycle(int base, int search)
{
    // go through elements of locked[search]
    for (int i = 0; i < candidate_count; i++)
    {
        // if one is true (locked in)
        if (locked[search][i])
        {
            // check and see if the current index is equal to pair.winner
            if (i == base)
            {
                // if so, that means a cycle would be formed
                return true;
            }
            else
            {
                // look to find if a cycle is formed further down the path
                if (check_cycle(base, i))
                {
                    return true;
                }
            }
        }
    }
    // no cycles were found so it is safe to add
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // loop through the sorted pairs
    for (int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;

        // check if a cycle would not be created by the given pair
        if (!check_cycle(w, l))
        {
            // if false, then there are no cycles to worry about.
            // lock in the pairing
            locked[w][l] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // set up exists
    int exists[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        exists[i] = 0;
    }

    // find the candidate with no edges towards them
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                exists[j]++;
            }
        }
    }
    // print found candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (!exists[i])
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
