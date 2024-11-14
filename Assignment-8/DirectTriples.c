#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function to return precedence of operators
int prec(char c) {
    if (c == '^') return 3;
    else if (c == '*' || c == '/') return 2;
    else if (c == '+' || c == '-') return 1;
    else return -1;
}

// Function to check if a character is an operand (e.g., variable, number)
int isOperand(char c) {
    return isalnum(c);
}

// Function to handle the array index case
void handleArrayIndex(char* exp, int* i, char* result, int* j, char* stack, int* top) {
    char index[50];
    int k = 0;

    // Extract the array index (i) part
    while (exp[*i] != ']') {
        index[k++] = exp[*i];
        (*i)++;
    }
    index[k] = '\0';

    // Generate intermediate code for array access
    printf("t%d = %s[%s]\n", *j, stack[*top], index);

    // Store the result in the temporary variable
    stack[++(*top)] = 't' + (*j);
    (*j)++;
}

// Function to perform infix to postfix conversion
char* infixToPostfix(char *exp) {
    int len = strlen(exp);
    char* result = malloc((len + 1) * sizeof(char));  // To store the postfix expression
    char stack[len];  // Stack to store operators
    int j = 0;        // Index for the result
    int top = -1;     // Stack pointer

    for (int i = 0; i < len; i++) {
        char c = exp[i];

        // If the scanned character is an operand (letters or digits), add it to the result.
        if (isalnum(c)) {
            result[j++] = c;
        }
        // If the scanned character is an open parenthesis '(', push it to the stack.
        else if (c == '(') {
            stack[++top] = c;
        }
        // If the scanned character is a close parenthesis ')', pop from the stack until '(' is encountered.
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                result[j++] = stack[top--];
            }
            top--;  // Pop '('
        }
        // If the scanned character is '*' or '&' (dereferencing or address-of operator)
        else if (c == '*' || c == '&') {
            // Handle unary operations first
            while (top != -1 && (prec(c) <= prec(stack[top]))) {
                result[j++] = stack[top--];
            }
            stack[++top] = c;
        }
        // If the scanned character is a binary operator
        else {
            while (top != -1 && (prec(c) <= prec(stack[top]))) {
                result[j++] = stack[top--];
            }
            stack[++top] = c;
        }

        // Handle array indexing 'a[i]'
        if (c == '[') {
            handleArrayIndex(exp, &i, result, &j, stack, &top);
        }
    }

    // Pop all the remaining operators from the stack
    while (top != -1) {
        result[j++] = stack[top--];
    }

    result[j] = '\0';  // Null terminate the string

    printf("Postfix expression: %s\n", result); // Debug: Print postfix expression

    return result;
}

// Function to generate intermediate code for the postfix expression
void generateIntermediateCode(char* postfix) {
    int len = strlen(postfix);
    char stack[len];  // Stack for intermediate results
    int j = 1;        // Temporary variable counter
    int top = -1;     // Stack pointer

    printf("Intermediate Code:\n");

    for (int i = 0; i < len; i++) {
        char c = postfix[i];

        // If the character is an operand (variable or constant), push it onto the stack
        if (isalnum(c)) {
            stack[++top] = c;
        }
        else {
            char a, b;
            a = stack[top--];  // Pop two operands
            b = stack[top--];

            // For binary operators, generate intermediate code
            printf("t%d = %c %c %c\n", j, b, c, a);
            stack[++top] = 't' + j;  // Push the result (temporary variable) to the stack
            j++;  // Increment temporary variable counter
        }
    }
}

int main() {
    char expression[50];
    char* postfix;

    printf("Enter the expression: ");
    scanf("%s", expression);

    // Convert the infix expression to postfix
    postfix = infixToPostfix(expression);
    
    // Generate intermediate code for the postfix expression
    generateIntermediateCode(postfix);

    free(postfix);  // Free the allocated memory
    return 0;
}
