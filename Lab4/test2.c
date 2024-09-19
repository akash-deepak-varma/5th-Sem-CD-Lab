#include<stdio.h>
#include<ctype.h>

int numOfProductions;
char productionSet[10][10];

void addToResultSet(char Result[],char val)
{
    int k;
    for(k=0 ;Result[k]!='\0';k++)
        if(Result[k]==val)
            return;
    Result[k]=val;
    Result[k+1]='\0';
}

void First(char* Result,char c)
{
    int i,j,k;
    char subResult[20];
    int foundEpsilon;
    subResult[0]='\0';
    Result[0]='\0';
    
    if(!(isupper(c)))
    {
        addToResultSet(Result,c);
               return ;
    }
    
    for(i=0;i<numOfProductions;i++)
    {

        if(productionSet[i][0]==c)
        {

 if(productionSet[i][2]=='#') addToResultSet(Result,'#');
           
      else
            {
                j=2;
                while(productionSet[i][j]!='\0')
                {
                foundEpsilon=0;
                printf("case-4\n");
                First(subResult,productionSet[i][j]);
                for(k=0;subResult[k]!='\0';k++)
                    addToResultSet(Result,subResult[k]);
                 for(k=0;subResult[k]!='\0';k++)
                     if(subResult[k]=='$')
                     {
                         foundEpsilon=1;
                         break;
                     }
                 
                 if(!foundEpsilon)
                     break;
                 j++;
                }
            }
    }
}
    return ;
}

  

int isPresent(char A[], char a){
    for(int i=0;A[i]!='\0';i++){
          if(A[i]==a) return 1;
    }

    return 0;
}
 
void Follow(char* Result, char *follow_result,char c){
    int i,j,k;
    char sub_result[20];
    int foundEpsilon;
    sub_result[0]='\0';
    follow_result[0]='\0';

    if(c==productionSet[0][0]){
      
        addToResultSet(follow_result,'$');
        return;
    }

    
    for(int i=0;i<numOfProductions;i++)
{
    for(int j=2;productionSet[j]!='\0';j++){
    if(productionSet[i][j]==c){
    
        if(productionSet[i][j+1]=='\0'){
           
            Follow(Result,sub_result,productionSet[i][0]);
            for(int k=0;sub_result[k]!='\0';k++)
                    addToResultSet(follow_result,sub_result[k]);
            

        }

        else if(isupper(productionSet[i][j+1])){
                
               First(Result,productionSet[i][j+1]);
               if(!(isPresent(Result,'#'))){
                    for(int k=0;Result[k]!='\0';k++)
                    addToResultSet(follow_result,Result[k]);
               }
               else {

                    
                    for(int k=0;Result[k]!='\0';k++){
                       if(Result[k]=='#') continue;
                       addToResultSet(follow_result,Result[k]);
                    } 
                    
                 /*  Follow(Result,sub_result,productionSet[i][j+1]);
                     for(int k=0;sub_result[k]!='\0';k++)
                     addToResultSet(follow_result,sub_result[k]);*/

                      Follow(Result,sub_result,productionSet[i][0]);
                     for(int k=0;sub_result[k]!='\0';k++)
                     addToResultSet(follow_result,sub_result[k]);
               }
    }
      else{
        
        addToResultSet(follow_result,productionSet[i][j+1]);
        return;
      }
}
}
    
}

return;

}



int main()
{
    int choice; 
    char c;
    char result[20];
    char follow_result[20];
    printf("How many number of productions ? :");
    scanf(" %d",&numOfProductions);
    for(int i=0;i<numOfProductions;i++)
    {
        printf("Enter productions Number %d : ",i+1);
        scanf(" %s",productionSet[i]);
    }


     do
    {

        printf("\n Find the Follow of  :");
        scanf(" %c",&c);
        Follow(result,follow_result,c);
        printf("\n FIRST(%c)= { ",c);
        for(int i=0;follow_result[i]!='\0';i++)
           printf(" %c ",follow_result[i]);       
        printf("}\n");
        
        printf("\n\nPress 1  to continue : \nPress 2 to EXIT\n");
        scanf(" %d",&choice);
    }
    while(choice==1); 


  

return 0;
}