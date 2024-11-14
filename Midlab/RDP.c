#include<stdio.h>
#include<string.h>
#include<ctype.h>

char str[20];
int lookAhead=0;
int E();
int N();

int D(){
    if(isdigit(str[lookAhead])){
        lookAhead++;
        return 1;
    }
    return 0;
}

int Nprime(){
    if(N()) return 1;

    return 1;
}

int N(){
    if(!D()) return 0;
    return Nprime();
}


int V(){
    if(str[lookAhead] == 'x' || str[lookAhead] == 'y' || str[lookAhead] == 'z'){
        lookAhead++;
        return 1;
    }
    else return 0;
}

int F(){
    if(str[lookAhead] == '('){
        lookAhead++;
        if(!E()) return 0;
        if(str[lookAhead] == ')'){
            lookAhead++;
            return 1;
        }
        else return 0;
    }
    else if((str[lookAhead] == '-') || (str[lookAhead] == '+')){
        lookAhead++;
        return F();
    }
    
    if(N()){
        return 1;
    }
    else if (V())
    {
        return 1;
    }
    else return 0;
    
}

int Tprime(){
     if((str[lookAhead] == '*') || (str[lookAhead] == '/')){
        lookAhead++;
        if(!F()) return 0;
        return Tprime();
    }
    return 1;
}

int T(){
    if(!F()) return 0;
    return Tprime();
}

int Eprime(){
    if((str[lookAhead] == '+') || (str[lookAhead] == '-')){
        lookAhead++;
        if(!T()) return 0;
        return Eprime();
    }
    return 1;
}

int E(){

    if(!T()) return 0;

    return Eprime();
}

int S(){
    return E();
}

int main()
{
    printf("Enter the String:");
    scanf("%[^\n]" ,str);
    int n = strlen(str);
    str[n] = '$';
    str[++n] = '\0';
    if(S() && str[lookAhead] == '$') printf("String Accepeted\n");
    else printf("Rejected\n");
    return 0;
}