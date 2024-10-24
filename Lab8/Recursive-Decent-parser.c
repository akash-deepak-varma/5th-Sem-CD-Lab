#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char string[24];
char lookAhead;
int ptr = 0;

int N();
int E();
int T();
int F();
int V();
void error();

void error() {
    printf("String not accepted\n");
    exit(0);
}

int D() {
    if (lookAhead >= '0' && lookAhead <= '9') {
        ptr++;
        lookAhead = string[ptr];
        return 1;
    }
    return 0;
}

int N() {
    if (!D()) {
        return 0;
    }
    while (D()); // Allow multiple digits
    return 1;
}

int V() {
    if (lookAhead == 'x' || lookAhead == 'y' || lookAhead == 'z') {
        ptr++;
        lookAhead = string[ptr];
        return 1;
    }
    return 0;
}

int F() {
    if (lookAhead == '(') {
        ptr++;
        lookAhead = string[ptr];
        E();
        if (lookAhead == ')') {
            ptr++;
            lookAhead = string[ptr];
            return 1;
        } else {
            error();
        }
    } else if (lookAhead == '+') {
        ptr++;
        lookAhead = string[ptr];
        F();
        return 1;
    } else if (lookAhead == '-') {
        ptr++;
        lookAhead = string[ptr];
        F();
        return 1;
    }

    if (V() || N()) {
        return 1;
    }

    error();
    return 0; // This will never be reached
}

int T2() {
    if (lookAhead == '*') {
        ptr++;
        lookAhead = string[ptr];
        F();
        return T2(); // Recur for more terms
    } else if (lookAhead == '/') {
        ptr++;
        lookAhead = string[ptr];
        F();
        return T2(); // Recur for more terms
    }
    return 1; // Return on no more factors
}

int T() {
    F();
    return T2();
}

int E2() {
    if (lookAhead == '+') {
        ptr++;
        lookAhead = string[ptr];
        T();
        return E2(); // Recur for more expressions
    } else if (lookAhead == '-') {
        ptr++;
        lookAhead = string[ptr];
        T();
        return E2(); // Recur for more expressions
    }
    return 1; // Return on no more terms
}

int E() {
    T();
    return E2();
}

int S() {
    E();
    return 1; // Accept if E() completes without errors
}

int main() {
    printf("Enter the String: ");
    scanf("%s", string);

    int len = strlen(string);
    string[len] = '$'; // End marker
    string[len + 1] = '\0';

    printf("Given String is %s\n", string);

    lookAhead = string[0];
    S();

    if (lookAhead == '$') {
        printf("String Accepted\n");
    } else {
        printf("String not accepted\n");
    }

    return 0;
}
