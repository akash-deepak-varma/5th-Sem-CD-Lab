#include <stdio.h>
#include <string.h>

int main() {
    char state[2] = {'0', '1'};
    char string[100];
    char presentState = '0';
    int length;

    printf("Enter the String: ");
    scanf("%s", string);
    printf("Entered string is: %s\n", string);

    length = strlen(string);

    for (int i = 0; i < length; i++) {
        //printf("char - %c || state - %c\n", string[i], presentState);

        if (presentState == '0') {
            if (string[i] == 'a') {
                presentState = '1';
            } else if (string[i] == 'b') {
                presentState = '0';
            } else {
                printf("Error: Invalid character %c\n", string[i]);
                return 1;
            }
        } else if (presentState == '1') {
            if (string[i] == 'a') {
                presentState = '1';
            } else if (string[i] == 'b') {
                presentState = '0';
            } else {
                printf("Error: Invalid character %c\n", string[i]);
                return 1;
            }
        }
    }

    if (presentState == '1') {
        printf("DFA Accepts\n");
    } else {
        printf("DFA Rejects\n");
    }

    return 0;
}
