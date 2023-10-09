#include <cs50.h>
#include <stdio.h>

int count_letters(string text);

int main(void)
{
    string text = get_string("Text: ");
    int numLetters = count_letters(text);
    int grade;
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

}