#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

char start;

int check(char prod[10][10] ,char * str ,int n)
{
    
}

void main()
{
    char productions[10][10]; 
    int flag=1;
    int n;
    
    char string[10] = {0};

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter the Start symbol:");
    scanf(" %c" ,&start);

    printf("Enter the productions: \n");
    for(int i=0;i<n;i++){
        printf("Production %d: ", i+1);
        scanf("%s", productions[i]);
    }

    printf("Given productions are\n");

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < strlen(productions[i]); j++)
        {
            printf("%c" ,productions[i][j]);
        }

        printf("\n");
        
    }

    printf("Enter the string:");
    scanf("%s" ,string);

    flag = check(productions ,string ,n);

    if(!flag)
    {
        printf("String can be derived\n");
    }
    else
    {
        printf("String can't be derived from the production");
    }
    
}