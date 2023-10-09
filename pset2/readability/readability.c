#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);

int main(void)
{
    string text = get_string("Text: ");
    int numLetters = count_letters(text);
    printf("%i\n", numLetters);
    int grade = 0;
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
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    int count = 0;
    for (i = 0; i < strlen(text); i++)
    {
        if (text[i] >= 65 && text[i] <= 122)
        {
            count += 1;
        }
    }
    return count;
}