#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 100
#define MAX_LEN 10
#define MAX_TERMINALS 20

typedef struct {
    char left[MAX_LEN];
    char right[MAX_LEN][MAX_LEN];
    int prodCount;
} Production;

char firstSet[MAX_PROD][MAX_TERMINALS];
char followSet[MAX_PROD][MAX_TERMINALS];
Production grammar[MAX_PROD];

char parsingTable[MAX_PROD][MAX_TERMINALS][MAX_LEN];

char nonTerminals[MAX_PROD];
char terminals[MAX_TERMINALS];
int nonTermCount = 0, termCount = 0;
int prodCount = 0;

void findFirst(char nonTerminal, int index);
void findFollow(char nonTerminal);
void computeFirstAndFollowSets();
int getNonTerminalIndex(char nonTerminal);
int getTerminalIndex(char terminal);
void constructParsingTable();
void printParsingTable();
void addTerminal(char terminal);
void addNonTerminal(char nonTerminal);
void initializeGrammar(); // Function to hard-code the grammar

int main() {
    initializeGrammar(); // Initialize the grammar directly

    computeFirstAndFollowSets();
    constructParsingTable();
    printParsingTable();

    return 0;
}

void initializeGrammar() {
    // Grammar S = A C B
    strcpy(grammar[0].left, "S");
    strcpy(grammar[0].right[0], "ACB");
    grammar[0].prodCount = 1;

    // Grammar A = aA | #
    strcpy(grammar[1].left, "A");
    strcpy(grammar[1].right[0], "aA");
    strcpy(grammar[1].right[1], "#");
    grammar[1].prodCount = 2;

    // Grammar B = bB | #
    strcpy(grammar[2].left, "B");
    strcpy(grammar[2].right[0], "bB");
    strcpy(grammar[2].right[1], "#");
    grammar[2].prodCount = 2;

    // Grammar C = c
    strcpy(grammar[3].left, "C");
    strcpy(grammar[3].right[0], "c");
    grammar[3].prodCount = 1;

    prodCount = 4; // Total number of productions

    // Adding non-terminals
    addNonTerminal('S');
    addNonTerminal('A');
    addNonTerminal('B');
    addNonTerminal('C');

    // Adding terminals
    addTerminal('a');
    addTerminal('b');
    addTerminal('c');
    addTerminal('#');
}

void findFirst(char nonTerminal, int index) {
    int i, j;
    for (i = 0; i < prodCount; i++) {
        if (grammar[i].left[0] == nonTerminal) {
            for (j = 0; j < grammar[i].prodCount; j++) {
                char *production = grammar[i].right[j];
                int k = 0;
                while (production[k] != '\0') {
                    if (islower(production[k]) || production[k] == '#') {
                        if (!strchr(firstSet[index], production[k])) {
                            strncat(firstSet[index], &production[k], 1);
                        }
                        break;
                    } else {
                        int nonTermIndex = getNonTerminalIndex(production[k]);
                        findFirst(production[k], nonTermIndex);
                        for (int l = 0; l < strlen(firstSet[nonTermIndex]); l++) {
                            if (firstSet[nonTermIndex][l] != '#' &&
                                !strchr(firstSet[index], firstSet[nonTermIndex][l])) {
                                strncat(firstSet[index], &firstSet[nonTermIndex][l], 1);
                            }
                        }
                        if (!strchr(firstSet[nonTermIndex], '#')) {
                            break;
                        } else {
                            k++;
                        }
                    }
                }
                if (production[k] == '\0') {
                    if (!strchr(firstSet[index], '#')) {
                        strcat(firstSet[index], "#");
                    }
                }
            }
        }
    }
}

void findFollow(char nonTerminal) {
    int i, j, k;
    int index = getNonTerminalIndex(nonTerminal);

    if (nonTerminal == grammar[0].left[0]) {
        strcat(followSet[index], "$");
    }

    for (i = 0; i < prodCount; i++) {
        for (j = 0; j < grammar[i].prodCount; j++) {
            char *production = grammar[i].right[j];
            for (k = 0; k < strlen(production); k++) {
                if (production[k] == nonTerminal) {
                    if (production[k + 1] == '\0') {
                        int lhsIndex = getNonTerminalIndex(grammar[i].left[0]);
                        if (lhsIndex != index) {
                            findFollow(grammar[i].left[0]);
                            for (int l = 0; l < strlen(followSet[lhsIndex]); l++) {
                                if (!strchr(followSet[index], followSet[lhsIndex][l])) {
                                    strncat(followSet[index], &followSet[lhsIndex][l], 1);
                                }
                            }
                        }
                    } else {
                        int nextCharIndex = getNonTerminalIndex(production[k + 1]);
                        if (islower(production[k + 1])) {
                            if (!strchr(followSet[index], production[k + 1])) {
                                strncat(followSet[index], &production[k + 1], 1);
                            }
                        } else {
                            for (int l = 0; l < strlen(firstSet[nextCharIndex]); l++) {
                                if (firstSet[nextCharIndex][l] != '#' &&
                                    !strchr(followSet[index], firstSet[nextCharIndex][l])) {
                                    strncat(followSet[index], &firstSet[nextCharIndex][l], 1);
                                }
                            }
                            if (strchr(firstSet[nextCharIndex], '#')) {
                                int lhsIndex = getNonTerminalIndex(grammar[i].left[0]);
                                if (lhsIndex != index) {
                                    findFollow(grammar[i].left[0]);
                                    for (int l = 0; l < strlen(followSet[lhsIndex]); l++) {
                                        if (!strchr(followSet[index], followSet[lhsIndex][l])) {
                                            strncat(followSet[index], &followSet[lhsIndex][l], 1);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void computeFirstAndFollowSets() {
    for (int i = 0; i < nonTermCount; i++) {
        findFirst(nonTerminals[i], i);
    }

    for (int i = 0; i < nonTermCount; i++) {
        findFollow(nonTerminals[i]);
    }
}

int getNonTerminalIndex(char nonTerminal) {
    for (int i = 0; i < nonTermCount; i++) {
        if (nonTerminals[i] == nonTerminal) {
            return i;
        }
    }
    return -1;
}

int getTerminalIndex(char terminal) {
    for (int i = 0; i < termCount; i++) {
        if (terminals[i] == terminal) {
            return i;
        }
    }
    return -1;
}

void constructParsingTable() {
    for (int i = 0; i < prodCount; i++) {
        for (int j = 0; j < grammar[i].prodCount; j++) {
            char *production = grammar[i].right[j];
            int nonTermIndex = getNonTerminalIndex(grammar[i].left[0]);
            char firstChar = production[0];

            if (islower(firstChar)) {
                int termIndex = getTerminalIndex(firstChar);
                strcpy(parsingTable[nonTermIndex][termIndex], production);
            } else if (firstChar == '#') {
                for (int k = 0; k < strlen(followSet[nonTermIndex]); k++) {
                    int termIndex = getTerminalIndex(followSet[nonTermIndex][k]);
                    strcpy(parsingTable[nonTermIndex][termIndex], production);
                }
            } else {
                int firstIndex = getNonTerminalIndex(firstChar);
                for (int k = 0; k < strlen(firstSet[firstIndex]); k++) {
                    if (firstSet[firstIndex][k] != '#') {
                        int termIndex = getTerminalIndex(firstSet[firstIndex][k]);
                        strcpy(parsingTable[nonTermIndex][termIndex], production);
                    } else {
                        for (int l = 0; l < strlen(followSet[nonTermIndex]); l++) {
                            int termIndex = getTerminalIndex(followSet[nonTermIndex][l]);
                            strcpy(parsingTable[nonTermIndex][termIndex], production);
                        }
                    }
                }
            }
        }
    }
}

void printParsingTable() {
    printf("\nLL(1) Parsing Table:\n");
    printf("\n");
    printf("   \t");
    for (int i = 0; i < termCount; i++) {
        printf("%c\t", terminals[i]);
    }
    printf("\n--------------------------------------------------\n");

    for (int i = 0; i < nonTermCount; i++) {
        printf("%c\t", nonTerminals[i]);
        for (int j = 0; j < termCount; j++) {
            if (strlen(parsingTable[i][j]) != 0) {
                printf("%s\t", parsingTable[i][j]);
            } else {
                printf("-\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void addTerminal(char terminal) {
    if (strchr(terminals, terminal) == NULL) {
        terminals[termCount++] = terminal;
    }
}

void addNonTerminal(char nonTerminal) {
    if (strchr(nonTerminals, nonTerminal) == NULL) {
        nonTerminals[nonTermCount++] = nonTerminal;
    }
}