#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

char start;


void main()
{
    char productions[10][10]; 
    int flag=1;
    int n;

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


    
}