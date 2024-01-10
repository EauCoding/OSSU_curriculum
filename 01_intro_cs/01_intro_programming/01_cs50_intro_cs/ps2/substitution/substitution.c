#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void cipher_substitution(string cmd_arg);
int get_within_alpha(string s, int i);

int main(int argc, string argv[])
{
    // Error message when executed without/with more than one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string cmd_arg = argv[1];
    int n = strlen(cmd_arg);

    // Error message when key is invalid by not containing 26 characters
    if (n != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    int count_letter[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < n; i++)
    {
        int c = get_within_alpha(cmd_arg, i);
        count_letter[c]++;

        // Error message when key is invalid by containing any character that is not an alphabetic character
        if (!isalpha(cmd_arg[i]))
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
        // Error message when key is invalid by not containing each letter exactly once
        else if (count_letter[c] > 1)
        {
            printf("Key must contain each character only once.\n");
            return 1;
        }
    }

    cipher_substitution(cmd_arg);

    return 0;
}

int get_within_alpha(string s, int i)
{
    int upper_c = toupper(s[i]);
    int c = upper_c - 65;

    return c;
}

void cipher_substitution(string cmd_arg)
{
    string plain_text = get_string("plaintext: ");
    string cipher_text = plain_text;

    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        int c = get_within_alpha(plain_text, i);

        // Key should be case-insensitive
        if (islower(plain_text[i]))
        {
            cipher_text[i] = tolower(cmd_arg[c]);
        }
        else if (isupper(plain_text[i]))
        {
            cipher_text[i] = toupper(cmd_arg[c]);
        }
    }

    printf("ciphertext: %s\n", cipher_text);
}
