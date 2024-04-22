#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// score table
int table[27] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10, 0};

// eval function to find the score table index for a given letter.
int eval(int n)
{
    int temp = n;
    // take the given letter and put it into uppercase, so we have a known range to work with
    temp = toupper(n);
    // A in ASCII is 65, so by subtracting 65,
    // we translate our acceptable letter range to [0,...,25]
    temp -= 65;
    // if the letter is within that acceptable range, return its position in said range.
    // if not, return 0.
    if (temp >= 0 && temp <= 25)
    {
        return temp;
    }
    else
    {
        return 26;
    }
}

// scoring function that sums the table returns
int score(string s)
{
    int total = 0;
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        total += table[eval(s[i])];
    }
    return total;
}

int main(void)
{
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");
    int p1score = score(p1);
    int p2score = score(p2);
    // printf("p1score: %i\n", p1score);
    // printf("p2score: %i\n", p2score);
    if (p1score > p2score)
    {
        printf("Player 1 wins!\n");
    }
    else if (p1score < p2score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
