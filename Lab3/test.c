#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void readFile(FILE *ptr)
{
    char ch;

    int newline = 0;
    int countchar = 0;
    int words = 0;
    int vowels = 0;
    int consonants = 0;
    int digits = 0;
    int specialChar = 0;
    int in_word = 0; // flag to track word boundaries

    while ((ch = fgetc(ptr)) != EOF)
    {
        countchar++;
        
        // Count lines
        if (ch == '\n')
        {
            newline++;
        }

        // Count vowels
        if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' ||
            ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
        {
            vowels++;
        }

        // Count digits
        if (isdigit(ch))
        {
            digits++;
        }


        // Count words (transition from non-alphabetic to alphabetic)
        if (isalpha(ch))
        {
            if (!in_word)
            {
                in_word = 1; // starting a new word
                words++;
            }
        }
        else
        {
            in_word = 0; // ending the current word
        }

        // Count consonants (isalpha but not a vowel)
        if (isalpha(ch) && !(ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' ||
                             ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'))
        {
            consonants++;
        }
    }

    fclose(ptr);

    specialChar = countchar - (vowels+consonants+digits+specialChar);

    printf("# of characters: %d\n", countchar);
    printf("# of lines: %d\n", newline);
    printf("# of vowels: %d\n", vowels);
    printf("# of consonants: %d\n", consonants);
    printf("# of digits: %d\n", digits);
    printf("# of special characters: %d\n", specialChar);
    printf("# of words: %d\n", words);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *ptr = fopen(argv[1], "r");
    if (ptr == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    readFile(ptr);

    return 0;
}
