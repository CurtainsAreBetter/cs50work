#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9
int preferences[MAX][MAX];
bool locked[MAX][MAX];
typedef struct
{
    int winner;
    int loser;
}
pair;
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
int pair_count;
int candidate_count;
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }
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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }
    pair_count = 0;
    int voter_count = get_int("Number of voters: ");
    for (int i = 0; i < voter_count; i++)
    {
        int ranks[candidate_count];
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
int candex(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            return i;
        }
    }
    return -1;
}
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i], name))
        {
            for (int j = 0; j < rank; j++)
            {
                if (!strcmp(name, candidates[ranks[j]]))
                {
                    return false;
                }
            }
            ranks[rank] = candex(name);
            return true;
        }
    }
    return false;
}
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        preferences[ranks[i]][ranks[i]] = 0;  // You can't win or lose against yourself
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}
void add_pairs(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            int check = preferences[i][j] - preferences[j][i];
            if (check > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
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
int strength(pair p)
{
    int num = preferences[p.winner][p.loser] - preferences[p.loser][p.winner];
    return num;
}
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
bool check_cycle(int base, int search)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[search][i])
        {
            if (i == base)
            {
                return true;
            }
            else
            {
                if (check_cycle(base, i))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
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
void print_winner(void)
{
    int exists[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        exists[i] = 0;
    }
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
    for (int i = 0; i < candidate_count; i++)
    {
        if (!exists[i])
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
