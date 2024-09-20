/**
 * This the code for the DFA construction that will take l={a,b}, 
 * string from l and DFA accepects if string has lenght atleast 3 else rejects.
 */

#include<stdio.h>
#include<string.h>

void main()
{
    printf("C Program for the DFA Such that string has lenght 3 with a(e={a,b})\n");

    char state[4],string[100];
    char presentState;
    int lenght;

    presentState = '0';

    
    state[0] = '0';
    state[1] = '1';
    state[2] = '2';
    state[3] = '3';

    printf("Enter the String:");
    scanf("%[^\n]s" ,string);
    printf("entred string is:%s\n" ,string);
    //printf("%c\n" ,presentState);
    
    lenght=strlen(string);

    for(int i=0;i<=lenght;i++)
    {
        //printf("char-%c|| starte-%c\n" ,string[i] ,presentState);
        if(string[i] == '\0' && presentState == state[3])
        {
            printf("DFA Accepets\n");
            return;
        }
        else if ((string[i] == 'a' || string[i] == 'b') && presentState == state[0])
        {
            presentState = state[1];
        }
        else if((string[i] == 'a' || string[i] == 'b') && presentState == state[1])
        {
            presentState = state[2];
        }
        else if((string[i] == 'a' || string[i] == 'b') && presentState == state[2])
        {
            presentState = state[3];
        }
        else if((string[i] == 'a' || string[i] == 'b') && presentState == state[3])
        {
            presentState = state[3];
        }
        else if(string[i] == '\0' && presentState != state[3])
        {
            printf("DFA Rejects\n");
        }
        
    }
    
}
