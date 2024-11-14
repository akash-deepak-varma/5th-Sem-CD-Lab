#include <ctype.h>
#include <stdio.h>
#include <string.h>


void atStart(char* set ,char c){
    int i;
    for(i=0 ;set[i] != '\0' ;i++){
        if(set[i] == c)
        {
            return;
        }
    }
    set[i] = c;
    set[++i] = '\0';
}

void findFirst(char prod[10][10] ,char* set ,char c ,int n){
    char temp[10];
    temp[0] = '\0';

    if(!isupper(c)){
        atStart(set ,c);
    }

    for(int i=0 ;i<n ;i++){
        if(prod[i][0] == c){
            if(prod[i][2] == c){
                continue;
            }
            int j=2 ,epsilon;
            while(prod[i][j] != '\0'){
                findFirst(prod ,temp ,prod[i][j] ,n);
                epsilon=0;
                for(int k=0 ;temp[k] != '\0' ;k++){
                    if(temp[k] == '#'){
                        epsilon = 1;
                    }
                    else{
                        atStart(set ,temp[k]);
                    }
                }

                memset(temp ,0 ,sizeof(temp));

                if(!epsilon){
                    break;
                }
                else if(epsilon && prod[i][j+1] == '\0'){
                    atStart(set ,'#');
                }

                j++;
            }
            
        }
    }
}

int main()
{
    char prod[10][10];
    int n;
    printf("Enter the # of Productions:");
    scanf("%d" ,&n);

    for(int i=0 ; i<n; i++){
        scanf("%s" ,prod[i]);
    }

    char c;
    printf("Enter the Non-Terminal to Calculate The First Set for:");
    scanf(" %c" ,&c);

    char set[10];
    set[0] = '\0';

    findFirst(prod ,set ,c ,n);

    printf("First(%c) = {", c);
    for(int i=0; set[i] != '\0'; i++){
        printf("%c ", set[i]);
    }
    printf("}\n");
}