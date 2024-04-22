#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string lowercase(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isupper(s[i]))
        {
            s[i] = tolower(s[i]);
        }
    }
    return s;
}

string substitution(string text, string key)
{
    int length = strlen(text);
    string encrypted = text;

    // encode cases
    int status[length];
    for (int i = 0, n = length; i < n; i++)
    {
        status[i] = 0;
    }
    for (int i = 0, n = length; i < n; i++)
    {
        if (isupper(text[i]))
        {
            status[i] = 1;
        }
        else
        {
            status[i] = 0;
        }
    }

    // transform into all lowercase
    string lowertext = lowercase(text);
    key = lowercase(key);

    for (int i = 0, n = length; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            encrypted[i] = key[lowertext[i] - 97];
        }
        else
        {
            encrypted[i] = lowertext[i];
        }
    }

    // restore case
    for (int i = 0, n = length; i < n; i++)
    {
        if (status[i] == 1)
        {
            encrypted[i] = toupper(encrypted[i]);
        }
        else
        {
            encrypted[i] = encrypted[i];
        }
    }

    // debug cases print
    // printf("    Cases: ");
    // for (int i = 0, n = length; i < n; i++){printf("%i", status[i]);}
    // printf("\n");

    return encrypted;
}

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Missing command-line argument\n");
        return 1;
    }

    // now we begin doing key checks to make sure it's sane
    string key = lowercase(argv[1]);
    int length = strlen(key);
    // printf("%s, %i\n", key, length);

    if (length != 26)
    {
        printf("Key not proper length!\n");
        return 1;
    }
    // check if the key has any nonalphabetical characters
    for (int i = 0, n = length; i < n; i++)
    {
        if (isalpha(key[i]) == false)
        {
            // printf("Nonalphabetical characters!\n");
            return 1;
        }
    }
    // printf("nonalpha: %i\n", nonalpha);

    // see if there are any duplicates by checking against an array
    int dupe[26];
    int dupecheck = 0;
    for (int i = 0, n = length; i < n; i++)
    {
        dupe[i] = 0;
    }
    for (int i = 0, n = length; i < n; i++)
    {
        dupe[key[i] - 97] += 1;
    }
    for (int i = 0, n = length; i < n; i++)
    {
        if (dupe[i] != 1)
        {
            dupecheck++;
        }
    }
    if (dupecheck != 0)
    {
        return 1;
    }
    string text = get_string("plaintext: ");
    printf("ciphertext: %s\n", substitution(text, key));
    return 0;
}
