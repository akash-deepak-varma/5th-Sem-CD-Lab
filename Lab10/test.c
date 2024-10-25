#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function to return precedence of operators
int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Function to perform infix to postfix conversion
char* infixToPostfix(const char *exp) {
    int len = strlen(exp);
    char *result = malloc(len + 1);
    char *stack = malloc(len);
    int j = 0;
    int top = -1;

    for (int i = 0; i < len; i++) {
        char c = exp[i];

        // If the scanned character is an operand, add it to the output string.
        if (isalnum(c))
            result[j++] = c;

        // If the scanned character is an ‘(‘, push it to the stack.
        else if (c == '(')
            stack[++top] = c;

        // If the scanned character is an ‘)’,
        // pop and add to the output string from the stack 
        // until an ‘(‘ is encountered.
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                result[j++] = stack[top--];
            }
            top--; // Remove the '(' from the stack
        }

        // If an operator is scanned
        else {
            while (top != -1 && (prec(c) <= prec(stack[top]))) {
                result[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    // Pop all the remaining elements from the stack
    while (top != -1) {
        result[j++] = stack[top--];
    }

    result[j] = '\0';
    free(stack);
    return result;
}

// Function to evaluate the postfix expression
int evaluatePostfix(const char *postfix) {
    int len = strlen(postfix);
    int *stack = malloc(len * sizeof(int));
    int top = -1;

    for (int i = 0; i < len; i++) {
        char c = postfix[i];

        if (isdigit(c)) {
            stack[++top] = c - '0'; // Convert char to int
        } else {
            int a = stack[top--]; // Top operand
            int b = stack[top--]; // Second operand
            int result;

            switch (c) {
                case '+': result = b + a; break;
                case '-': result = b - a; break;
                case '*': result = b * a; break;
                case '/': result = b / a; break;
                // Handle other operators if needed
                default: result = 0; break;
            }
            stack[++top] = result;
        }
    }

    int finalResult = stack[top];
    free(stack);
    return finalResult;
}

int main() {
    char string[50];

    printf("Enter the expression: ");
    scanf("%s", string);

    char *postfix = infixToPostfix(string);
    printf("Postfix: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);

    free(postfix);
    return 0;
}
