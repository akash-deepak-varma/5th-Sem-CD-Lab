/*Question:  

Implement a recursive descent parser for the given context-free grammar (CFG), do the needful and show whether the string is accepted/rejected:



1. S → E  

2. E → E + T | E - T | T  
{
    E->TE'
    E' -> +TE' | -TE' | # 
}

3. T → T * F | T / F | F  

{
    T -> FT'
    T' -> *FT' | /FT' | # 
}

4. F → ( E ) | - F | + F | N | V  

5. V → x | y | z  

6. N → D | D N  

{
    N -> DN'
    N' -> N | #
}

7. D → 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

==================================================*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char string[24];
char lookAhead;
int ptr = 0;

int N();
void E();

void error()
{
    printf("String not accepted\n");
    exit(0);
}

int D()
{
    if(lookAhead == '1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'|'9'|'0')
    {
        ptr++;
        lookAhead = string[ptr];
        return 1;
    }

    return 0;
}

int N2()
{
    if(!N())
    {
        return 2;
    }
}

int N()
{
    if(!D())
    {
        error();
    }
    return N2();
}

int V()
{
    if(lookAhead == 'x'|'y'|'z')
    {
        ptr++;
        lookAhead = string[ptr];
        return 1;
    }
    else 
    {
        return 0;
    }
}

void F()
{
    if(lookAhead == '(')
    {
        ptr++;
        lookAhead = string[ptr];
        E();
        if(lookAhead == ')')
        {
            ptr++;
            lookAhead = string[ptr];
        }
        else
        {
            error();
        }
    }
    else if(lookAhead == '+')
    {
        ptr++;
        lookAhead = string[ptr];
        F();
    }
    else if(lookAhead == '-')
    {
        ptr++;
        lookAhead = string[ptr];
        F();
    }

    int flag = V();
    int flag2;

    if(!flag)
    {
        flag2 = N();
    }

    if(flag == 0 && flag2 == 0)
    {
        error();
    }

}

void T2()
{
    if(lookAhead == '*')
    {
        ptr++;
        lookAhead = string[ptr];
        F();
        T2();
    }
    else if(lookAhead == '/')
    {
        ptr++;
        lookAhead = string[ptr];
        F();
        T2();
    }
    else
    {
        return;
    }
}

void T()
{
    F();
    T2();
}

void E2()
{
    if(lookAhead == '+')
    {
        ptr++;
        lookAhead = string[ptr];
        T();
        E2();
    }
    else if(lookAhead == '-')
    {
        ptr++;
        lookAhead = string[ptr];
        T();
        E2();
    }
    else 
    {
        return;
    }
}

void E()
{
    T();
    E2();
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

    if(lookAhead == '$')
    {
        printf("String Accepected\n");
    }
    else
    {
        printf("String not accepted\n");
    }

    return 0;
}