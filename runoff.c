#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // we first initialize an int with a value that can never show up organically
    int candidateplace = MAX_CANDIDATES + 1;
    // we then iterate over all the candidates, checking the given name against theirs to see if
    // it's a valid vote. we then save that candidates location in the candidates index.
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidateplace = i;
        }
    }
    // if the previous loop found that the name given belonged to a real candidate, we set the given
    // voter's candidate preference at the given rank, then return true. if the name wasn't found,
    // we don't record anything and we return false.
    if (candidateplace != MAX_CANDIDATES + 1)
    {
        preferences[voter][rank] = candidateplace;
        return true;
    }
    else
    {
        return false;
    }
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // we loop over all the voters
    for (int i = 0; i < voter_count; i++)
    {
        // we then loop over all ranks
        for (int j = 0; j < candidate_count; j++)
        {
            // if the candidate at the j'th rank hasn't been eliminated, add a vote to their .votes
            // and break out of the j-loop to move onto the next voter.
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // we loop over all the candidates
    for (int i = 0; i < MAX_CANDIDATES; i++)
    {
        // if there's a candidate with more than half the votes, we print their name and return
        // true. otherwise, we return false.
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // first, we set a tracking int to a value that could never happen, as we try to find the winner
    // before we find the minimum amount of votes.
    int minvotes = MAX_VOTERS;
    // we then loop over all the candidates.
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate hasn't been eliminated and their # of votes is less than the current
        // minimum amount of votes, we set minvotes to their # of votes.
        if (candidates[i].eliminated == false && candidates[i].votes < minvotes)
        {
            minvotes = candidates[i].votes;
        }
    }
    // finally, we return the lowest # of votes found.
    return minvotes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // first, we initialize a tracking int.
    int tugofwar = 0;
    // we then iterate over all the candidates.
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate hasn't been eliminated, we increment the tug of war counter.
        if (candidates[i].eliminated == false)
        {
            tugofwar++;
        }
        // if the candidate hasn't been eliminated and also has the same # of votes as the min, we
        // decrement the counter. the amount of candidates that fufills these conditions are
        // obviously going to be less or equal to the number of candidates that are only eliminated,
        // so no worries about signs in the int.
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            tugofwar--;
        }
    }
    // if the tug of war int is 0, that means that all of the candidates left have the same number
    // of votes, which means there's a tie. in writing this comment, i see how I could have done
    // this a bit simpler, but what can you do.
    if (tugofwar == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // we iterate over all the candidates, and then flag the candidate with the lowest number of
    // votes as eliminated. we don't need to worry about ties, as the only time this function is
    // called is if there isn't a tie.
    for (int i = 0; i < MAX_CANDIDATES; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
