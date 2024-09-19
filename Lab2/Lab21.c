#include<stdio.h>
#include<string.h>

    char left[50];
    char right[50][50];
    int numberOfProductions;
    char teriminals[50];
    int teri;
    char face[50][50];
    int noface[10]={0,0,0,0,0,0,0,0,0,0};

void takeNumberofProductions()
{
    printf("Enter the number of productions in the grammer:");
    scanf("%d" ,&numberOfProductions);

}

int isTerminal(char var)
{
    for(int i=0;i<teri;i++)
    {
        if(var == teriminals[i])
        {
            return 1;
        }
    }

    return 0;
}


void calface(char var)
{
    int n;
    for(int i=0;i<numberOfProductions;i++)
    {
        if(var == left[i])
        {
            n=i;
        }
    }

    char test=right[n][0];

    printf("Test is:%c and var is %c\n",test ,var);

    if(test == '$')
    {
        face[n][noface[n]] = '$';
        noface[n]++;
    }
    else if(isTerminal(test) == 1)
    {
        face[n][noface[n]] = test;
        noface[n]++;
    }
    else
    {
        

    }
}



void main()
{
    takeNumberofProductions();

    

    printf("Number of productions are:%d\n" ,numberOfProductions);

    

    for(int i=0;i<numberOfProductions;i++)
    {
        printf("Enter the production:\n");

        scanf(" %c" ,&left[i]);
        printf("->");
        scanf("%s" ,right[i]);
    }

    

    

   printf("Enter the number of terminals:");
    scanf("%d" ,&teri);

    for(int k=0;k<teri;k++)
    {
        scanf(" %c" ,&teriminals[k]);
        //printf("%d" ,k);
    }

    char varible;

    printf("Enter the state to find the face:");
    scanf(" %c",&varible);

    for(int i=0;i<numberOfProductions;i++)
    {
        calface(left[i]);
    }

    face[2][0]='g';
    face[2][1]='$';

    noface[2]=2;

    for(int i=0;i<numberOfProductions;i++)
    {
        printf("first of %c is:" ,left[i]);

        for(int j=0;j<strlen(face[i]);j++)
        {
            printf("%c" ,face[i][j]);
        }

        printf("\n");
    }
    
}