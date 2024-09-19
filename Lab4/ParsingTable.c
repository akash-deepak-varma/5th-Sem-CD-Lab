#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct production
{
    char left[10];
    char right[10][10];
} prod;

struct table
{
    char nonter[10];
    char term[10];
    int tersize;
    char values[10][10];
} parseTable;

int n;

int isAppended(char *term, char c, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (term[i] == c)
        {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char** argv)
{
    printf("Enter the # of Productions:");
    scanf("%d", &n);
    parseTable.tersize=0;

    for (int i = 0; i < n; i++)
    {
        char string[10];

        printf("Enter the production-%d", i + 1);
        scanf("%s", string);

        prod.left[i] = string[0];

        for (int j = 2; j < strlen(string); j++)
        {
            prod.right[i][j - 2] = string[j];
        }
    }

    // for (int i = 0; i < n; i++)
    // {
    //     printf("%c\n", prod.left[i]);
    // }

    // for (int i = 0; i < n; i++)
    // {
    //     printf("%s\n", prod.right[i]);
    // }

    for(int i=0; i<n ;i++)
    {
        for(int j=0; j<strlen(prod.right[i]); j++)
        {
            if(prod.right[i][j] == '|')
            {
                continue;
            }
            else if(prod.right[i][j] == '#')
            {
                continue;
            }

            if(!isupper(prod.right[i][j]) && !isAppended(parseTable.nonter ,prod.right[i][j] ,parseTable.tersize))
            {
                parseTable.nonter[parseTable.tersize] = prod.right[i][j];
                parseTable.tersize++;
            } 
        }
    }

    parseTable.nonter[parseTable.tersize] = '$';
    parseTable.tersize++;

    printf("Terminals in parse table:\n");
    for (int i = 0; i < parseTable.tersize; i++)
    {
        printf("%c\n",parseTable.nonter[i]);
    }

    strcpy(parseTable.term ,prod.left);

    printf("Nonterminals\n");
    for (size_t i = 0; i < n; i++)
    {
        printf("%c\n" ,parseTable.term[i]);
    }
    

    return 0;
}