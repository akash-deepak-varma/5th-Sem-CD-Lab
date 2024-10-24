

/*
1. S → E  
2. E → E + T | E - T | T  
3. T → T * F | T / F | F  
4. F → ( E ) | - F | + F | N | V  
5. V → x | y | z  
6. N → D | D N  
7. D → 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
*/

/* After removing left recursion and upon left factoring
S  → E
E  → TE'
E' → +TE' | -TE' | #
T  → FT'
T' → *FT' | /FT' | #
F  → (E) | -F | +F | N | V
V  → x | y | z
N  → DN'
N' → N | #
D  → 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int lk = 0; 
char str[20];

int S();
int E();
int T();
int Eprime();
int F();
int Tprime();
int N();
int V();
int D();
int Nprime();

void space(){
    if(str[lk] == ' '){
        lk++;
    }
}

//S → E
int S(){
    space();
    return E();
}

//E → TE'
int E(){
    space();
    if(!T()) return 0;
    return Eprime();
}

// E' → +TE' | -TE' | #
int Eprime(){
    space();
    if(str[lk] == '+'){
        lk++;
        if(!T()) return 0;
        return Eprime();
    }
    else if(str[lk] == '-'){
        lk++;
        if(!T()) return 0;
        return Eprime();
    }
    else{
        return 1;
    }
}

// T → FT'
int T(){
    space();
    if(!F()) return 0;
    return Tprime();
}

// T' → *FT' | /FT' | #
int Tprime(){
    space();
    if(str[lk] == '*'){
        lk++;
        if(!F()) return 0;
        return Tprime();
    }
    else if(str[lk] == '/'){
        lk++;
        if(!F()) return 0;
        return Tprime();
    }
    else{
        return 1;
    }
}

// F → (E) | -F | +F | N | V
int F(){
    space();
    if(str[lk] == '('){
        lk++;
        if(!E()) return 0;
        if(str[lk] == ')'){
            lk++;
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(str[lk] == '+'){
        lk++;
        return F();
    }
    else if(str[lk] == '-'){
        lk++;
        return F();
    }
    else if(N()){
        return 1;
    }
    else if(V()){
        return 1;
    }
    else{
        return 0;
    }
}

// V → x | y | z
int V(){
    space();
    if(str[lk] == 'x' || str[lk] == 'y' || str[lk] == 'z'){
        lk++;
        return 1;
    }
    return 0;
}

// N → DN'
int N(){
    space();
    if(!D()) return 0;
    return Nprime();
}

// N' → N | #
int Nprime(){
    space();
    if(N()){
        return 1;
    }
    else{
        return 1;
    }
}
// D -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
int D(){
    space();
    if(isdigit(str[lk])){
        lk++;
        return 1;
    }
    return 0;
}

int main(){
    printf("Enter string: ");
    scanf(" %[^\n]", str);
    int n = strlen(str);
    str[n] = '$';
    str[n+1] = '\0';
    
    if(S() && str[lk] == '$'){
        printf("Accepted\n");
    }
    else{
        printf("Rejected\n");
    }

    return 0;
}