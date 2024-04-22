#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int i = 0;
int n = 0;

int wordcount(string s)
{
    int words = 1;

    for (i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == 32)
        {
            words++;
        }
    }
    return words;
}

// length is the amount of characters in the text,
// wc is the amount of words in the text, and f is
// our scaling factor.
float avgletter(int len, int wc)
{
    float words = wc;
    float length = len;
    return (length / words) * 100;
}

float avgsent(string s, int wc)
{
    int sentcount = 0;
    for (i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == 46 || s[i] == 33 || s[i] == 63)
        {
            sentcount++;
        }
    }
    float totalsentcount = sentcount;
    float words = wc;
    return (totalsentcount / words) * 100;
}

int main(void)
{
    string text = get_string("Text: ");
    int words = wordcount(text);
    int textlength = strlen(text);
    float fudge = 6.35;
    float index =
        0.0588 * avgletter(textlength, words) - 0.296 * avgsent(text, words) - 15.8 - fudge;
    int grade = round(index);

    // Debug prints
    // printf("words: %i\n", words);
    // printf("length: %i\n", textlength);
    // printf("avgletter: %f\n", avgletter(textlength, words));
    // printf("avgsent: %f\n", avgsent(text, words));
    // printf("index: %f\n", index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}
