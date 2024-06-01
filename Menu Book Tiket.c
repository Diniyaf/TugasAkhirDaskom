#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user {
    char username[20];
    char password[20];
    struct user* next;
} User;

typedef struct passenger {
    char name[30];
    int age;
    char id[20];
    int seatNumber;
    char destination[30];
    char ticketClass[20];
    struct passenger* next;
} Passenger;

User* users = NULL;
Passenger* passengers = NULL;

void signup();
void login();
void userMenu();
User* findUser(char* username, char* password);
void addUser(char* username, char* password);
void bookTicket();
void addPassenger(char* name, int age, char* id, int seatNumber, char* destination, char* ticketClass);
void printBookingSummary(char* destination, int numPassengers, char* ticketClass, int* seatNumbers);
void checkBusStatus();

int main() {
    int choice;

    while (1) {
        printf("\n=== Welcome to the Bus Reservation System ===\n");
        printf("1. Signup\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signup();
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

void signup() {
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
                bookTicket();
                break;
            case 2:
                printf("Cancelling a Ticket...\n");
                // Implement ticket cancellation functionality
                break;
            case 3:
                checkBusStatus();
                break;
            case 4:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

void bookTicket() {
    char destination[30];
    int numPassengers, age, seatNumbers[10], i;
    char name[30], id[20], ticketClass[20];

    printf("Enter destination: ");
    scanf("%s", destination);
    printf("Enter number of passengers: ");
    scanf("%d", &numPassengers);

    printf("Available ticket classes:\n1. Economy\n2. Business\n3. First Class\n");
    printf("Enter ticket class: ");
    scanf("%s", ticketClass);

    printf("Available seats: \n");
    for (i = 1; i <= 50; i++) {
        printf("%d ", i);
        if (i % 10 == 0) printf("\n");
    }
    printf("\nEnter seat numbers: ");
    for (i = 0; i < numPassengers; i++) {
        scanf("%d", &seatNumbers[i]);
    }

    for (i = 0; i < numPassengers; i++) {
        printf("Enter name of passenger %d: ", i + 1);
        scanf("%s", name);
        printf("Enter age of passenger %d: ", i + 1);
        scanf("%d", &age);
        printf("Enter personal identification number of passenger %d: ", i + 1);
        scanf("%s", id);

        addPassenger(name, age, id, seatNumbers[i], destination, ticketClass);
    }

    printBookingSummary(destination, numPassengers, ticketClass, seatNumbers);
}

void addPassenger(char* name, int age, char* id, int seatNumber, char* destination, char* ticketClass) {
    Passenger* newPassenger = (Passenger*)malloc(sizeof(Passenger));
    strcpy(newPassenger->name, name);
    newPassenger->age = age;
    strcpy(newPassenger->id, id);
    newPassenger->seatNumber = seatNumber;
    strcpy(newPassenger->destination, destination);
    strcpy(newPassenger->ticketClass, ticketClass);
    newPassenger->next = passengers;
    passengers = newPassenger;
}

void printBookingSummary(char* destination, int numPassengers, char* ticketClass, int* seatNumbers) {
    Passenger* temp = passengers;
    printf("\n=== Booking Summary ===\n");
    printf("Destination: %s\n", destination);
    printf("Number of Passengers: %d\n", numPassengers);
    printf("Ticket Class: %s\n", ticketClass);

    for (int i = 0; i < numPassengers; i++) {
        printf("Passenger %d: \n", i + 1);
        printf("Name: %s\n", temp->name);
        printf("Age: %d\n", temp->age);
        printf("ID: %s\n", temp->id);
        printf("Seat Number: %d\n", seatNumbers[i]);
        temp = temp->next;
    }
    printf("\n");
}

void checkBusStatus() {
    Passenger* temp = passengers;
    if (temp == NULL) {
        printf("No bookings available.\n");
        return;
    }

    printf("\n=== Bus Status ===\n");
    while (temp != NULL) {
        printf("Destination: %s\n", temp->destination);
        printf("Passenger Name: %s\n", temp->name);
        printf("Age: %d\n", temp->age);
        printf("ID: %s\n", temp->id);
        printf("Seat Number: %d\n", temp->seatNumber);
        printf("Ticket Class: %s\n", temp->ticketClass);
        printf("-----------------------\n");
        temp = temp->next;
    }
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
