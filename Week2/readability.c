#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int index = (int)round(5.88 * letters / words - 29.6 * sentences / words - 15.8);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int num = 0;

    for (int i = 0, n = strlen(text); i < n; i ++)
    {
        if (islower(text[i]))
        {
            text[i] = toupper(text[i]);
        }

        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            num ++;
        }
    }

    return num;
}

int count_words(string text)
{
    int num = 0;

    for (int i = 0, n = strlen(text); i < n; i ++)
    {
        if (text[i] == ' ' && text[i + 1] != ' ')
        {
            num ++;
        }
    }

    num ++;

    return num;
}

int count_sentences(string text)
{
    int num = 0;

    for (int i = 0, n = strlen(text); i < n; i ++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            num ++;
        }
    }

    return num;
}