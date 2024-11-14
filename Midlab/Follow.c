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

void follow(char prods[10][20], char *set, int n, char symbol){
    char temp[10];
    char temp_first[10];
    int j;
    temp[0] = '\0';
    temp_first[0] = '\0';

    if(symbol == prods[0][0]){
        add(set, '$');
    }

    for(int i=0;i<n;i++){
        int j = 2, epsilon;
        while(prods[i][j] != '\0'){
            if(prods[i][j] == symbol){
                epsilon = 0;
                if(prods[i][j+1] == '\0'){
                    if(prods[i][j] == prods[i][0]) break;
                    follow(prods, set, n, prods[i][0]);
                    return;
                }
                
                first(prods, temp_first, n, prods[i][j+1]);
                for(int k=0;temp_first[k] != '\0';k++){
                    if(temp_first[k] == '#') epsilon = 1;
                    else add(set, temp_first[k]);
                }
                memset(temp_first, 0, sizeof(temp_first));
                temp_first[0] = '\0';

                if(epsilon){
                    follow(prods, temp, n, prods[i][0]);
                    first(prods, temp_first, n, prods[i][j+2]);
                    for(int k=0;temp[k] != '\0';k++){
                        if(temp[k] == '$'){
                            printf("yes %c", prods[i][j+2]);
                            if(prods[i][j+2] == '\0'){
                                add(set, '$');
                            }
                        }
                        else add(set, temp[k]);
                    }
                    for(int k=0;temp_first[k] != '\0';k++){
                        add(set, temp_first[k]);
                    }
                    memset(temp_first, 0, sizeof(temp_first));
                    temp_first[0] = '\0';
                    memset(temp, 0, sizeof(temp));
                    temp[0] = '\0';
                }
            }
            j++;
        }
    }
}

int main(){
    char set[10];
    set[0] = '\0';
    char productions[10][20];
    int n;
    char c;
    // printf("Enter the number of productions: ");
    // scanf("%d", &n);
    
    // printf("Enter the productions: \n");
    // for(int i=0;i<n;i++){
    //     scanf("%s", productions[i]);
    // }

    // n=5;
    // strcpy(productions[0], "S=(L)");
    // strcpy(productions[1], "S=a");
    // strcpy(productions[2], "L=SM");
    // strcpy(productions[3], "M=,SM");
    // strcpy(productions[4], "M=#");
    
    // n = 9;
    // strcpy(productions[0], "S=aBDh");
    // strcpy(productions[1], "B=cC");
    // strcpy(productions[2], "C=bC");
    // strcpy(productions[3], "C=#");
    // strcpy(productions[4], "D=EF");
    // strcpy(productions[5], "E=g");
    // strcpy(productions[6], "E=#");
    // strcpy(productions[7], "F=f");
    // strcpy(productions[8], "F=#");

    n=6;
    strcpy(productions[0], "S=A");
    strcpy(productions[1], "A=aBD");
    strcpy(productions[2], "D=dD");
    strcpy(productions[3], "D=#");
    strcpy(productions[4], "B=b");
    strcpy(productions[5], "C=g");

    printf("Enter the symbol: ");
    scanf(" %c", &c);
    
    follow(productions, set, n, c);
    printf("Follow(%c) = {", c);
    for(int i=0;set[i]!='\0';i++){
        printf("%c ", set[i]);
    }
    printf("}\n");

    return 0;

}