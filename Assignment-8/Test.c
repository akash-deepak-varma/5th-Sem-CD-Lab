#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int l=0;

int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

void infixtopostfix(char *exp, char *result) {
    int len = strlen(exp);
    char stack[len];
    int j = 0, top = -1;

    for (int i = 0; i < len; i++) {
        char c = exp[i];
        
        if (isalnum(c) || c == '[' || c == ']') {  // If it's an operand or array index
            result[j++] = c;
            if (!(isalnum(exp[i + 1]) || exp[i + 1] == '[' || exp[i + 1] == ']')) {
                result[j++] = ' ';  // Separate complete operand
            }
        }
        else if (c == '(') {
            stack[++top] = '(';
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(')
                result[j++] = stack[top--];
            top--;
        }
        else if (c == '*' && (i == 0 || exp[i - 1] == '(')) {  // Dereference
            result[j++] = 'D';  // Represent dereference differently in postfix
        }
        else {  // Operator
            while (top != -1 && prec(c) <= prec(stack[top]))
                result[j++] = stack[top--];
            stack[++top] = c;
        }
    }
    while (top != -1)
        result[j++] = stack[top--];
    result[j] = '\0';
}

void TAC(char *postfix) {
    int len = strlen(postfix);
    char stack[len][20];
    int temp = 1;
    int stackIndex = 0;
    
    for (int i = 0; i < len; i++) {
        char c = postfix[i];
        
        if (isalnum(c)) { // If it's an operand
            char operand[20];
            int k = 0;

            while (isalnum(postfix[i]) || postfix[i] == '[' || postfix[i] == ']') {
                operand[k++] = postfix[i++];
            }
            i--; // Adjust for extra increment
            operand[k] = '\0';
            strcpy(stack[stackIndex++], operand);
        }
        else if (c == 'D') { // Handle dereference
            char op[20];
            strcpy(op, stack[--stackIndex]);
            snprintf(stack[stackIndex++], sizeof(stack[stackIndex]), "*%s", op);
        }
        else if (c == ' ') { // Skip spaces
            continue;
        }
        else {  // Operator
            char op2[20], op1[20], result[20];
            strcpy(op2, stack[--stackIndex]);
            strcpy(op1, stack[--stackIndex]);
            if(op1[0]=='D')
            op1[0]='*';
            if(op2[0]=='D')
            op1[0]='*';
            snprintf(result, sizeof(result), "T%d", temp++);
            printf("%d %s. %c  ,%s  ,%s  \n",l,result, c, op1, op2);
            l++;
            strcpy(stack[stackIndex++], result);
        }
    }
    printf("%d T%d. =  ,x  ,T%d\n",l,temp, temp - 1);
}

int main() {
    char exp[100];
    printf("Enter the expression: ");
    scanf("%s",exp);
    printf("Given expression is: %s \n", exp);
    char postfix[100];
    infixtopostfix(exp, postfix);
    //printf("Postfix expression is: %s \n", postfix);
    printf("Intermediate Code Generation Direct and Indirect Tuple: \n");
    TAC(postfix);

    return 0;
}