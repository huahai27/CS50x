#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string key = argv[1];
    int exist[26] = {0};

    for (int i = 0; i < 26; i++)
    {
        exist[toupper(key[i]) - 'A']++;
    }

    for (int i = 0; i < 26; i++)
    {
        if (exist[i] != 1)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        key[i] = toupper(key[i]);
    }

    string plaintext = get_string("plaintext: ");

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                plaintext[i] = key[plaintext[i] - 'A'];
            }
            else
            {
                plaintext[i] = tolower(key[plaintext[i] - 'a']);
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);

    return 0;
}
