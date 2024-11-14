#include <stdio.h>
#include <string.h>
#include <ctype.h>

void add(char *set, char c){
    int i;
    for(i=0; set[i] != '\0'; i++){
        if(set[i] == c){
            return;
        }
    }
    set[i] = c;
    set[i+1] = '\0';
}

void first(char prods[10][20], char *set, int n, char symbol){
    char temp[10];
    temp[0] = '\0';

    if(!isupper(symbol)){
        add(set, symbol);
        return;
    }

    for(int i=0;i<n;i++){
        if(prods[i][0] == symbol){
            //printf("%c\n", symbol);
            if(prods[i][2] == symbol) continue;

            int j = 2, epsilon;
            while(prods[i][j] != '\0'){
                epsilon = 0;
                first(prods, temp, n, prods[i][j]);
                
                for(int k=0;temp[k]!='\0';k++){
                    if(temp[k] == '#') epsilon = 1;
                    else add(set, temp[k]);
                    //printf("%c - epsilon %d ", prods[i][j], epsilon);
                }
                //printf("\n");
                memset(temp, 0, sizeof(temp));

                if(!epsilon){
                    break;
                }
                else if(epsilon && prods[i][j+1] == '\0'){
                    add(set, '#');
                }

                j++;
            }
        }
    }

}

