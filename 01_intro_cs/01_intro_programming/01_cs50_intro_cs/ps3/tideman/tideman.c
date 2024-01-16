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
} pair;

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

    // Clear graph of locked in pairs and initialize preference matrix
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
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

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Look for candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate found, update rank and return true
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[i] = rank;
            return true;
        }
    }

    // If no candidate found, don't update any ranks and return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Update the preferences array based on the current voter's ranks
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if ((strcmp(candidates[i], candidates[j]) != 0) && (ranks[i] < ranks[j]))
            {
                preferences[i][j]++;
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Add each pair of candidates to pairs array if one candidate is preferred over the other
    // Update global variable pair_count to be the total number of pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int largest_ind = i;
        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[largest_ind].winner][pairs[largest_ind].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                largest_ind = j;
            }
        }

        pair tmp_pair = pairs[i];
        pairs[i] = pairs[largest_ind];
        pairs[largest_ind] = tmp_pair;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Update locked to create the locked graph by adding all edges in decreasing order of victory strength, as long as there is no
    // cycle
    int start_candidate = pairs[0].winner;
    int end_candidate = pairs[0].loser;
    locked[start_candidate][end_candidate] = true;

    for (int i = 1; i < pair_count; i++)
    {
        if (pairs[i].loser == start_candidate && pairs[i].winner != end_candidate)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            start_candidate = pairs[i].winner;
        }
        else if (pairs[i].winner == end_candidate && pairs[i].loser != start_candidate)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            end_candidate = pairs[i].loser;
        }
        else if (pairs[i].winner != start_candidate && pairs[i].loser == end_candidate)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // Print out the winner of the election, who will be the source of the graph
    for (int i = 0; i < pair_count; i++)
    {
        int no_arrow = 0;

        for (int j = 0; j < pair_count; j++)
        {
            if (!locked[j][i])
            {
                no_arrow++;
            }
        }

        if (no_arrow == pair_count)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
