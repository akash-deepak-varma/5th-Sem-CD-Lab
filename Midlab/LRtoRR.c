#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 50

char productions[MAX][MAX];
int num;

void convert_to_right() {
    char temp[MAX][MAX];
    int temp_count = 0;
    int non_terminal_count = 1;
    char new_non_terminal[MAX] = {0};

    for (int i = 0; i < num; i++) {
        char current = productions[i][0];

        // Check for left recursion in the production
        if (current == productions[i][2]) {
            char alpha[MAX] = {0}, beta[MAX] = {0};

            int j = 3, k = 0;

            // Extract alpha
            while (productions[i][j] != '=' && productions[i][j] != '\0' && productions[i][j] != '|') {
                alpha[k++] = productions[i][j++];
            }
            alpha[k] = '\0';
            printf("Alpha is %s\n" ,alpha);

            if (productions[i][j] == '|') {
                j++; // Move past '|'
            }

            // Extract beta
            k = 0;
            while (productions[i][j] != '\0') {
                beta[k++] = productions[i][j++];
            }
            beta[k] = '\0';
            printf("Beta is %s\n" ,beta);

            // Format a new non-terminal for right recursion
            snprintf(new_non_terminal, sizeof(new_non_terminal), "%d", non_terminal_count);
            printf("Non terminal is %s\n" ,new_non_terminal);

            // Production for non-left-recursive part (beta)
            snprintf(temp[temp_count], MAX, "%c=%s%s", current, beta, new_non_terminal);
            printf("temp is %s\n" ,temp[temp_count]);
            temp_count++;

            // Production for recursive part (alpha)
            snprintf(temp[temp_count], MAX, "%s=%s%s|#", new_non_terminal, alpha, new_non_terminal);
            printf("temp is %s\n" ,temp[temp_count]);
            temp_count++;

            non_terminal_count++;
        } else {
            // If no left recursion, copy production as is
            snprintf(temp[temp_count], MAX, "%s", productions[i]);
            temp_count++;
        }
    }

    // Copy converted productions back to original array
    num = temp_count;
    for (int i = 0; i < num; i++) {
        strcpy(productions[i], temp[i]);
    }
}

int main() {
    printf("Enter the number of productions: ");
    scanf("%d", &num);

    printf("Enter the productions (FORMAT: A=Aa|b): \n");
    for (int i = 0; i < num; i++) {
        scanf("%s", productions[i]);
    }

    printf("Left recursive grammar:\n");
    for (int i = 0; i < num; i++) {
        printf("%s\n", productions[i]);
    }

    convert_to_right();

    printf("Right recursive grammar:\n");
    for (int i = 0; i < num; i++) {
        printf("%s\n", productions[i]);
    }

    return 0;
}