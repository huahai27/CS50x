#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// void upper(string word);
// int score(string uword);

// int main(int argc, string argv[])
// {
//     string word1 = get_string("Player 1: ");
//     string word2 = get_string("Player 2: ");

//     upper(word1);
//     upper(word2);

//     int score1 = score(word1);
//     int score2 = score(word2);

//     if (score1 > score2)
//     {
//         printf("Player 1 wins!\n");
//     }

//     if (score1 < score2)
//     {
//         printf("Player 2 wins!\n");
//     }

//     if (score1 == score2)
//     {
//         printf("Tie!\n");
//     }

//     return 0;
// }

// void upper(string word)
// {
//     for (int i = 0, length = strlen(word); i < length; i++)
//     {
//         word[i] = toupper(word[i]);
//     }
// }

// int score(string uword)
// {
//     int sum = 0;

//     for (int i = 0, length = strlen(uword); i < length; i++)
//     {
//         if (uword[i] == 'A' || uword[i] == 'E' || uword[i] == 'I' || uword[i] == 'L' ||
//             uword[i] == 'N' || uword[i] == 'O' || uword[i] == 'R' || uword[i] == 'S' ||
//             uword[i] == 'T' || uword[i] == 'U')
//         {
//             sum += 1;
//         }

//         if (uword[i] == 'D' || uword[i] == 'G')
//         {
//             sum += 2;
//         }

//         if (uword[i] == 'B' || uword[i] == 'C' || uword[i] == 'M' || uword[i] == 'P')
//         {
//             sum += 3;
//         }

//         if (uword[i] == 'F' || uword[i] == 'H' || uword[i] == 'V' || uword[i] == 'W' ||
//             uword[i] == 'Y')
//         {
//             sum += 4;
//         }

//         if (uword[i] == 'K')
//         {
//             sum += 5;
//         }

//         if (uword[i] == 'J' || uword[i] == 'X')
//         {
//             sum += 8;
//         }

//         if (uword[i] == 'Q' || uword[i] == 'Z')
//         {
//             sum += 10;
//         }
//     }

//     return sum;
// }

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Prompt the user for two words
    string word1 = get_string("Player 1；");
    string word2 = get_string("Player 2: ");

    // Compute the score of each word
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Keep track of score
    int score = 0;

    // Compute score for each character
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isupper(word[i]))
        {
            score += POINTS[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += POINTS[word[i] - 'a'];
        }
    }

    return score;
}
