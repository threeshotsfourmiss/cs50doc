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
} candidate;

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
    // iterates over all the candidates and if the name given matches a name in the list, we
    // increment their votes and then return. otherwise, we return false (not actually, no idea why)
    for (int i = 0; i < MAX; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // we define an array of winners with enough space to fit every candidate if needed. we also
    // define a 'winnervotes' number.
    string winner[MAX];
    int winnervotes = 0;
    // we iterate over all the candidates, and if we find a candidate with a higher number of votes
    // than our current 'winnervotes', we update 'winnervotes' to the current leading candidate.
    for (int i = 0; i < MAX; i++)
    {
        if (candidates[i].votes > winnervotes)
        {
            winnervotes = candidates[i].votes;
        }
    }
    // we iterate over all the candidates and print all candidates who have a number of votes equal
    // to the winner's number of votes, which is another way of saying they won. this handily takes
    // away all need to handle arrays of strings or handle special cases, as this will always print
    // the winner.
    for (int i = 0; i < MAX; i++)
    {
        if (candidates[i].votes == winnervotes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
