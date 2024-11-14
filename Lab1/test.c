#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULES 100
#define MAX_LENGTH 100

typedef struct {
    char non_terminal;
    char productions[MAX_RULES][MAX_LENGTH];
    int num_productions;
} Rule;

void convertLeftRecursiveToRightRecursive(Rule *rule) {
    char new_non_terminal = rule->non_terminal + 1;
    int has_left_recursion = 0;

    for (int i = 0; i < rule->num_productions; ++i) {
        if (rule->productions[i][0] == rule->non_terminal) {
            has_left_recursion = 1;
            break;
        }
    }

    if (!has_left_recursion) {
        for (int i = 0; i < rule->num_productions; ++i) {
            printf("%c → %s\n", rule->non_terminal, rule->productions[i]);
        }
        return;
    }

    printf("Productions for %c:\n", rule->non_terminal);

    for (int i = 0; i < rule->num_productions; ++i) {
        if (rule->productions[i][0] != rule->non_terminal) {
            printf("%c → %s%c'\n", rule->non_terminal, rule->productions[i], new_non_terminal);
        }
    }

    printf("%c' → ", new_non_terminal);
    for (int i = 0; i < rule->num_productions; ++i) {
        if (rule->productions[i][0] == rule->non_terminal) {
            printf("%s%c' | ", &rule->productions[i][1], new_non_terminal);
        }
    }
    printf("ep\n");
}

int main() {
    Rule rules[MAX_RULES];
    int num_rules;

    printf("Enter number of rules: ");
    scanf("%d", &num_rules);

    for (int i = 0; i < num_rules; ++i) {
        printf("Enter non-terminal for rule %d: ", i + 1);
        scanf(" %c", &rules[i].non_terminal);

        printf("Enter number of productions for %c: ", rules[i].non_terminal);
        scanf("%d", &rules[i].num_productions);

        printf("Enter productions for %c:\n", rules[i].non_terminal);
        for (int j = 0; j < rules[i].num_productions; ++j) {
            scanf("%s", rules[i].productions[j]);
        }
    }

    printf("\nConverted Right-Recursive Rules:\n");
    for (int i = 0; i < num_rules; ++i) {
        convertLeftRecursiveToRightRecursive(&rules[i]);
    }

    return 0;
}