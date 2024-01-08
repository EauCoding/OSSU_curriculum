#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int calculate_index(int letter_num, int word_num, int sentence_num);
int count_letters(string text);
int count_sentences(string text);
int count_words(string text);
void print_grade(int index);

int main(void)
{
    // Prompt the user for a text
    string text = get_string("Text: ");

    // Count letters in text
    int letter_num = count_letters(text);

    // Count words in text
    int word_num = count_words(text);

    // Count sentences in text
    int sentence_num = count_sentences(text);

    // Calculate Coleman-Liau index
    int index = calculate_index(letter_num, word_num, sentence_num);

    // Print output
    print_grade(index);
}

int count_letters(string text)
{
    int count_letter = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int letter = toupper(text[i]);

        if ((letter >= 65) && (letter <= 90))
        {
            count_letter++;
        }
    }

    return count_letter;
}

int count_words(string text)
{
    int count_word = 1;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((int)text[i] == 32)
        {
            count_word++;
        }
    }

    return count_word;
}

int count_sentences(string text)
{
    int count_sentence = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (((int)text[i] == 46) || ((int)text[i] == 33) || ((int)text[i] == 63))
        {
            count_sentence++;
        }
    }

    return count_sentence;
}

int calculate_index(int letter_num, int word_num, int sentence_num)
{
    float L = letter_num / (float)word_num * 100;
    float S = sentence_num / (float)word_num * 100;

    return (int)round(0.0588 * L - 0.296 * S - 15.8);
}

void print_grade(int index)
{
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
        printf("Grade %i\n", index);
    }
}
