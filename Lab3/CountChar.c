//lines words char vowel consonets digits spec char

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

void readFile(FILE *ptr)
{
    char ch;

    int newline = 0; //
    int countchar = 0; // 
    int words = 0;
    int vowels = 0; //
    int nonvowels = 0;
    int digits = 0; //
    int specialChar = 0;
    int flag = 0;
    while((ch = fgetc(ptr)) != EOF)
    {
        countchar++;
        if(ch == '\n')
        {
            newline++;
        }

        if(ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O'  || ch == 'U' || ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
        {
            vowels++;
        }

        if(isdigit(ch))
        {
            digits++;
        }

        if(ispunct(ch))
        {
            specialChar++;
        }

        if(flag == 0 && !isalpha(ch))
        {
            flag = 1;
        }
        else if (flag == 1 && !isalpha(ch))
        {
            flag = 0;
        }
        
        else if(flag == 1 && isalpha(ch))
        {
            flag = 2;
        }
        else if(flag == 2 && !isalpha(ch))
        {
            flag = 0;
            words++;
        }


        //printf("%c" ,ch);
    }
    fclose(ptr);



    nonvowels = countchar - (vowels+digits+specialChar);

    printf("# of char are %d\n" ,countchar);
    printf("# of lines are %d\n" ,newline);
    printf("# of vowels are %d\n" ,vowels);
    printf("# of digits are %d\n" ,digits);
    printf("# of special are %d\n" ,specialChar);
    printf("# of consonets are %d\n" ,nonvowels);
    printf("# of words are %d\n" ,words);
}

int main(int argc, char *argv[])
{
    FILE *ptr;
    char ch;

    ptr = fopen(argv[1] ,"r");



    readFile(ptr);
}