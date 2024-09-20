#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int isDelimiter(char ch) {
    return (ch == ' ' || ch == '\n' || ch == '\t' || ch == ',' || ch == ';' || ch == '.' || ch == '!' || ch == '?' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '-' || ch == '_');
}

int main() {
    FILE *file;
    char ch;
    int inToken = 0;
    int tokenCount = 0;

    // Open the file
    file = fopen("prog.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file prog.txt\n");
        return 1;
    }

    // Read the file character by character
    while ((ch = fgetc(file)) != EOF) {
        if (isDelimiter(ch)) {
            if (inToken) {
                tokenCount++;
                inToken = 0;
            }
        } else {
            inToken = 1;
        }
    }

    // If the last character is part of a token
    if (inToken) {
        tokenCount++;
    }
    

    fclose(file);

    printf("Total number of tokens in the file: %d\n", tokenCount);

    return 0;
}