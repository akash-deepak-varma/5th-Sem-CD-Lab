/**
 * This the code for the DFA construction that will take l={a,b}, 
 * string from l and DFA accepects if string starts with "a" else rejects.
 */

#include<stdio.h>
#include<string.h>

void main()
{
    printf("C Program for the DFA Starting with a(e={a,b})\n");

    char state[3],string[100];
    char presentState;
    int lenght;

    presentState = '0';

    state[0] = '0';
    state[1] = '1';
    state[2] = '2';

    printf("Enter the String:");
    scanf("%[^\n]s" ,string);
    printf("entred string is:%s\n" ,string);
    //printf("%c\n" ,presentState);
    
    lenght=strlen(string);

    for(int i=0;i<=lenght;i++)
    {
        //printf("char-%c|| starte-%c\n" ,string[i] ,presentState);
        if(string[i] == '\0' && presentState == '1')
        {
            printf("DFA Accepets\n");
            return;
        }
        else if (string[i] == 'a' && presentState == '0')
        {
            presentState ='1';
        }
        else if (string[i] == 'b' && presentState == '0')
        {
            presentState='2';
        }
        else if(string[i] == 'a' && presentState == '1')
        {
            presentState='1';
        }
        else if(string[i] == 'b' && presentState == '1')
        {
            presentState='1';
        }
        else if(string[i] == 'a' && presentState == '2')
        {
            presentState='2';
        }
        else if(string[i] == 'b' && presentState == '2')
        {
            presentState='2';
        }
        else if(string[i] == '\0' && presentState != '1')
        {
            printf("DFA Rejects\n");
        }
        
    }
    
}