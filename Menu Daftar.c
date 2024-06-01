#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user {
    char username[20];
    char password[20];
    struct user* next;
} User;

User* users = NULL;

void daftar();
void login();
void userMenu();
User* findUser(char* username, char* password); //menyimpan pendaftaran
void addUser(char* username, char* password); //membuat akun baru

//Menu Awal//
int main() {
    int choice;

    while (1) {
        printf("\n=== Selamat Datang di KAI Lite Version ===\n");
        printf("1. Daftar\n");
        printf("2. Masuk\n");
        printf("3. Keluar\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                daftar();
                break;
            case 2:
                login();
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void daftar() {
    char username[20], password[20];
    printf("Enter a username: ");
    scanf("%s", username);
    printf("Enter a password: ");
    scanf("%s", password);

    if (findUser(username, password) != NULL) {
        printf("Username already exists. Please try a different username.\n");
    } else {
        addUser(username, password);
        printf("Signup successful. You can now log in.\n");
    }
}

void login() {
    char username[20], password[20];
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    User* user = findUser(username, password);
    if (user != NULL) {
        printf("Login successful. Welcome, %s!\n", username);
        userMenu();
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

void userMenu() {
    int choice;
    do {
        printf("\n=== User Menu ===\n");
        printf("1. Book a Ticket\n");
        printf("2. Cancel a Ticket\n");
        printf("3. Check Bus Status\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Booking a Ticket...\n");
                // Implement ticket booking functionality
                break;
            case 2:
                printf("Cancelling a Ticket...\n");
                // Implement ticket cancellation functionality
                break;
            case 3:
                printf("Checking Bus Status...\n");
                // Implement bus status checking functionality
                break;
            case 4:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

User* findUser(char* username, char* password) {
    User* temp = users;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 && strcmp(temp->password, password) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void addUser(char* username, char* password) {
    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->next = users;
    users = newUser;
}

