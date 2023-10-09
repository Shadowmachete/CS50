#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int numLetters = count_letters(text);
    int numWords = count_words(text);
    int numSentences = count_sentences(text);
    printf("%i Letters, %i Words, %i Sentences.\n", numLetters, numWords, numSentences);
    float grade = 0.0588 * (numLetters * 100 / numWords ) - 0.296 * (numSentences * 100 / numWords ) - 15.8;
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(grade));
    }
}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] >= 65 && text[i] <= 122)
        {
            count += 1;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i+1] == ' ' || text[i+1] == '.' || text[i+1] == ',') && (text[i] != ' ' && text[i] != '.' && text[i] != ','))
        {
            count += 1;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count += 1;
        }
    }
    return count;
}