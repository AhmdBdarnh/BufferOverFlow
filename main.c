#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 100
#define MAX_USERS 100
#define PASSWORD_LENGTH 8

struct User {
    char username[MAX_LINE_LENGTH];
    char password[MAX_LINE_LENGTH];
};

void registerUser() {
    struct User newUser;
    printf("Enter Username: ");
    scanf("%s", newUser.username);
    printf("Enter Password: ");
    scanf("%s", newUser.password);

    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%s %s\n", newUser.username, newUser.password);
    fclose(file);
    printf("User registered successfully!\n");
}
void print_Data() {
    char buff[32];
    FILE *fp;
    printf("\n phone Numbers: \n");
    fp = fopen("users.txt", "r");
    while (fgets(buff, 32, fp)) {
        fputs(buff, stdout);
    }
    fclose(fp);
}


bool authenticate(const char *userName, const char *password) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return false;
    }

    struct User user;
    while (fscanf(file, "%s %s", user.username, user.password) == 2) {
        if (strcmp(user.username, userName) == 0 && strcmp(user.password, password) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

int login() {
    bool authenticated = false;
    char password[PASSWORD_LENGTH] = {0};
    char UserName[PASSWORD_LENGTH] = {0};
    printf("auth: %d\n> ", authenticated);

    printf("Enter Username:\n> ");
    scanf("%s", UserName);
    printf("Enter Password:\n> ");
    while (getchar() != '\n'); 
    gets(password);
    printf("auth: %d\n> ", authenticated);

    if (authenticate(UserName, password) == true) {
        authenticated = true;
    }

    if (authenticated) {
        return 1;
    }
    return -1;
}




int main(int argc, char const *argv[]) {
    int choice;
    printf("1. Login\n2. Register\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int authResult = login();
        if (authResult == -1) {
            printf("You are not authenticated.\n");
            return 0;
        }
        print_Data();
    } else if (choice == 2) {
        registerUser();
        return 0;
    } else {
        printf("Invalid choice\n");
        return 0;
    }

    return 0;
}
