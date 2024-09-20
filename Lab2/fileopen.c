#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_ADDRESS_LENGTH 50
#define MAX_CONTACT_LENGTH 15
#define MAX_SPORT_LENGTH 50

struct Date {
    int day;
    int month;
    int year;
};

struct User {
    struct Date registerDate;
    int userId;
    char name[MAX_NAME_LENGTH];
    struct Date DOB;
    int age; 
    char address[MAX_ADDRESS_LENGTH];
    char contact[MAX_CONTACT_LENGTH];
    char isport[MAX_SPORT_LENGTH];
};

void displayTableHeader() {
    printf("%-20s | %-15s | %-10s | %-15s | %-15s | %-15s | %-15s\n",
           "Name", "DD-MM-YYYY", "User Id", "Contact", "DD-MM-YEAR", "Sport", "Address");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
}

void displayUser(struct User user) {
    printf("%-20s | %02d-%02d-%04d | %-10d | %-15s | %02d-%02d-%04d | %-15s | %-15s\n",
           user.name,
           user.registerDate.day, user.registerDate.month, user.registerDate.year,
           user.userId,
           user.contact,
           user.DOB.day, user.DOB.month, user.DOB.year,
           user.isport,
           user.address);
}

void displayAll(char *filename) {
    struct User user;
    FILE *fp = fopen(filename, "r");

    if (fp != NULL) {
        displayTableHeader();

        while (fscanf(fp, "%d;%d;%d;%d;%[^;];%d;%d;%d;%[^;];%[^;];%[^;];\n",
                      &user.registerDate.day,
                      &user.registerDate.month,
                      &user.registerDate.year,
                      &user.userId,
                      user.name,
                      &user.DOB.day,
                      &user.DOB.month,
                      &user.DOB.year,
                      user.address,
                      user.contact,
                      user.isport) != EOF) {
            displayUser(user);
        }

        fclose(fp);
    } else {
        perror("Error opening file");
    }
}

void displayWhere(char *filename, char *field, char *operator, int value) {
    struct User user;
    FILE *fp = fopen(filename, "r");

    if (fp != NULL) {
        displayTableHeader();

        while (fscanf(fp, "%d;%d;%d;%d;%[^;];%d;%d;%d;%[^;];%[^;];%[^;];\n",
                      &user.registerDate.day,
                      &user.registerDate.month,
                      &user.registerDate.year,
                      &user.userId,
                      user.name,
                      &user.DOB.day,
                      &user.DOB.month,
                      &user.DOB.year,
                      user.address,
                      user.contact,
                      user.isport) != EOF) {
            if (strcmp(field, "userid") == 0) {
                if (strcmp(operator, ">") == 0 && user.userId > value) {
                    displayUser(user);
                } else if (strcmp(operator, "=") == 0 && user.userId == value) {
                    displayUser(user);
                } else if (strcmp(operator, "<") == 0 && user.userId < value) {
                    displayUser(user);
                }
            } else {
                printf("Invalid field\n");
            }
        }

        fclose(fp);
    } else {
        perror("Error opening file");
    }
}

void displaySome(char *st[], int n) {
    struct User user;
    char *str;
    FILE *fp = fopen("data.txt", "r");

    if (fp != NULL) {
        //displayTableHeader();

        while (fscanf(fp, "%d;%d;%d;%d;%[^;];%d;%d;%d;%[^;];%[^;];%[^;];\n",
                      &user.registerDate.day,
                      &user.registerDate.month,
                      &user.registerDate.year,
                      &user.userId,
                      user.name,
                      &user.DOB.day,
                      &user.DOB.month,
                      &user.DOB.year,
                      user.address,
                      user.contact,
                      user.isport) != EOF) {
            if (n > 4 && strcmp(st[1], "select") == 0) {
                str = strdup(st[2]);

                // Tokenizing attributes and checking for a match
                char *token = strtok(str, ";");
                while (token != NULL) {
                    if (!strcmp(token, "name")) {
                        printf("%-20s |", user.name);
                    } else if (!strcmp(token, "rdate")) {
                        printf("%02d-%02d-%04d |", user.registerDate.day, user.registerDate.month, user.registerDate.year);
                    } else if (!strcmp(token, "contact")) {
                        printf("%-15s |", user.contact);
                    } else if (!strcmp(token, "sport")) {
                        printf("%-15s |", user.isport);
                    } else if (!strcmp(token, "dob")) {
                        printf("%02d-%02d-%04d |", user.DOB.day, user.DOB.month, user.DOB.year);
                    } else if (!strcmp(token, "id")) {
                        printf("%-10d |", user.userId);
                    } else if (!strcmp(token, "addr")) {
                        printf("%-15s |", user.address);
                    }
                    token = strtok(NULL, ";");
                }
                printf("\n");
                free(str);
            } else {
                printf("Invalid command-line arguments for displaySome\n");
            }
        }

        fclose(fp);
    } else {
        perror("Error opening file");
    }
}


int main(int argc, char *argv[]) {
    printf("%d\n" ,argc);
    if (argc == 5 && strcmp(argv[2], "x") == 0)
    {
        displayAll(argv[4]);
    } 
    else if (argc == 9 && strcmp(argv[1], "select") == 0)
    {
        displayWhere(argv[4], argv[6], argv[7], atoi(argv[8]));
    }
    else if(argc >=5 )
    {
        displaySome(argv ,argc);
    } 
    else
    {
        printf("Invalid command-line arguments\n");
    }

    return 0;
}