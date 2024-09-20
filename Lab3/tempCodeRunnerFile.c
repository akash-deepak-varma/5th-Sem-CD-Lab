#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTIONS 10
#define MAX_LENGTH 10

typedef struct {
    char lhs;
    char rhs[MAX_LENGTH];
} Production;


int matchesProduction(Production *productions, int n, char *str, int *used) {
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        
        int len = strlen(productions[i].rhs);
        if (strncmp(str, productions[i].rhs, len) == 0) {
            used[i] = 1;
            return len;
        }
    }
    return 0;
}

int canDerive(Production *productions, int n, char *str) {
    int len = strlen(str);
    if (len == 0) return 1;

    int used[MAX_PRODUCTIONS] = {0}; 
    int i = 0;

    while (i < len) {
        int matchLength = matchesProduction(productions, n, str + i, used);
        if (matchLength == 0) {
            return 0; 
        }
        i += matchLength; 
    }

    return 1;
}

int main() {
    Production productions[MAX_PRODUCTIONS];
    int n;

    char inputString[MAX_LENGTH];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter the Start symbol: ");
    char start;
    scanf(" %c", &start);

    printf("Enter the productions: \n");
    for (int i = 0; i < n; i++) {
        char prod[MAX_LENGTH];
        printf("Production %d: ", i + 1);
        scanf("%s", prod);
        productions[i].lhs = prod[0];
        strcpy(productions[i].rhs, prod + 3); 
    }

    printf("Given productions are:\n");
    for (int i = 0; i < n; i++) {
        printf("%c->%s\n", productions[i].lhs, productions[i].rhs);
    }

    printf("Enter the string: ");
    scanf("%s", inputString);

    
    if (canDerive(productions, n, inputString)) {
        printf("String can be derived\n");
    } else {
        printf("String can't be derived from the production\n");
    }

    return 0;
}
