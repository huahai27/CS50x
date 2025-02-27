#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int compute_letters(string text);
int compute_words(string text);
int compute_sentences(string text);

int main(void)
{
    float index = 0.0;
    double L = 0;
    double S = 0;
    int W = 0;

    string text = get_string("Text: ");

    W = compute_words(text);
    L = compute_letters(text) * 100.0 / W;
    S = compute_sentences(text) * 100.0 / W;

    index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        int temp = (int) round(index);
        printf("Grade %d\n", temp);
    }
}

int compute_letters(string text)
{
    int ret = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalnum(text[i]))
        {
            ret++;
        }
    }
    return ret;
}

int compute_words(string text)
{
    int ret = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isspace(text[i]))
        {
            ret++;
        }
    }

    ret++;

    return ret;
}

int compute_sentences(string text)
{
    int ret = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            ret++;
        }
    }

    return ret;
}
