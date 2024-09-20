#include <stdio.h>

int isCapital(char c){
    if(c >= 65 && c <= 91){
        return 1;
    }
    return 0;
}

void addAtStart(char *set, char c){
    int k;
    for(k=0;set[k] != '\0';k++){
        if(set[k] == c){
            return;
        }
    }
    set[k] = c;
    set[k+1] = '\0';
}

void first(char prod[10][10], char* set, char c, int n){
    char temp[10];
    int epsilon, j;
    temp[0] = '\0';

    if(!isCapital(c)){
        addAtStart(set, c);
        return;
    }

    for(int i=0;i<n;i++){
        if(prod[i][0] == c){
            if(prod[i][2] == c) continue;
            if(prod[i][2] == '$'){
                addAtStart(set, '$');
            }
            else{
                j = 2;
                while(prod[i][j] != '\0'){
                    epsilon = 0;
                    first(prod, temp, prod[i][j], n);
                    //add temp to set
                    for(int k=0;temp[k]!='\0';k++){
                        addAtStart(set, temp[k]);
                    }

                    for(int k=0;temp[k]!='\0';k++){
                        if(temp[k] == '$'){
                            epsilon = 1;
                            break;
                        }
                    }

                    if(!epsilon){
                        break;
                    }

                    j++;
                }
            }
        }
    }

    return;
}

int main(){
    char productions[10][10];
    char set[10]; 
    char c;
    int n;
    set[0] = '\0';

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter the productions: \n");
    for(int i=0;i<n;i++){
        printf("Production %d: ", i+1);
        scanf("%s", productions[i]);
    }

    printf("Enter Non-terminal to find the First set for: ");
    scanf(" %c", &c);

    first(productions, set, c, n);
    for(int i=0;set[i]!='\0';i++){
        printf("%c ", set[i]);
    }

    // for(int i=0;i<n;i++){
    //     for(int j=0;prod[i][j] != '\0';j++){
    //         printf("%c", prod[i][j]);
    //     }
    //     printf("\n");
    // }
    
}