#include<stdio.h>
#include<string.h>

char start;

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

void follow(char prod[10][10], char* set, char c, int n)
{
    int epsilion=0;

    if(start == c)
    {
        addAtStart(set, '#');
    }

    for(int i=0;i<n;i++)
    {
        int size = strlen(prod[i]);
        if(size<=3)
        {
            addAtStart(set,'#');
        }
        if(prod[i][size-2] == c && !isCapital(prod[i][size-1]))
        {
            addAtStart(set, prod[i][size-1]);
        }
    }

    for(int i=0;i<n;i++)
    {
        int size = strlen(prod[i]);
        if(prod[i][size-1] == c)
        {
            follow(prod, set, prod[i][0], n);
        }
    }

    for(int i=0;i<n;i++)
    {
        int size = strlen(prod[i]);
        if(prod[i][size-2] == c && isCapital(prod[i][size-1]))
        {
            char tempfirst[10];

            first(prod, tempfirst, prod[i][size-1], n);

            for(int k=0;tempfirst[k]!='\0';k++){
                        if(tempfirst[k] == '$'){
                            follow(prod, set, prod[i][0], n);
                            continue;
                        }

                        addAtStart(set ,tempfirst[k]);
                    }


        }
    }



}

int main()
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

    while(flag)
    {
        char c;
        char setfirst[10];
        char setfollow[10];
        setfirst[0] = '\0';
        setfollow[0] = '\0';

        printf("Enter Non-terminal to find the Follow set for: ");
        scanf(" %c", &c);


        //first(productions, setfirst, c, n);

        follow(productions, setfollow, c, n);
        for(int i=0;setfollow[i]!='\0';i++){
            printf("%c ", setfollow[i]);
        }
        printf("\n");

        printf("Do you want to continue?:(Yes:1 ,NO:0):");
        scanf("%d" ,&flag);

    }

    
    return 0;
}