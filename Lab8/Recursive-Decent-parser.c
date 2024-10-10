/*Question:  

Implement a recursive descent parser for the given context-free grammar (CFG), do the needful and show whether the string is accepted/rejected:



1. S → E  

2. E → E + T | E - T | T  

3. T → T * F | T / F | F  

4. F → ( E ) | - F | + F | N | V  

5. V → x | y | z  

6. N → D | D N  

7. D → 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

==================================================*/


#include<stdio.h>
#include<string.h>

char string[24];
char lookAhead;

void E()
{

}

void S()
{
    E();
}

int main()
{   
    printf("Enter the String:");
    scanf("%s" ,string);

    int len = strlen(string);
    string[len] = '$';
    string[len+1] = '\0';

    printf("Given String is %s\n" ,string);

    lookAhead = string[0];

    S();

    return 0;
}