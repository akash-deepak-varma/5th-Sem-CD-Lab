#include<stdio.h>
#include<string.h>

void main()
{
    char presentState = '0';
    char string[100];
    int lenght;

    printf("Enter the string:");
    scanf("%[^\n]" ,string);
    printf("Entered string is:%s\n" ,string);

    lenght = strlen(string);

    for(int i=0;i<lenght;i++)
    {
        if(presentState =='0')
        {
            if(string[i] == 'a' || string[i] == 'b')
            {
                presentState = '1';
            }
            
        }
        else if (presentState =='1')
        {
            if (string[i] == 'a' || string[i] == 'b')
            {
                presentState = '2';
            }
        }
        else if (presentState =='2')
        {
            if (string[i] == 'a' || string[i] == 'b')
            {
                presentState = '0';
            }
        }
        
    }

    if(presentState == '0')
    {
        printf("DFA Accepts\n");
    }
    else 
    {
        printf("DFA Rejects\n");
    }
}