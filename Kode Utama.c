#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Defining Structure for user credentials
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
    char source[30];
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
void addPassenger(char* source, char* name, int age, char* id, int seatNumber, char* destination, char* ticketClass);
void printBookingSummary(char* source, char* destination, int numPassengers, char* ticketClass, int* seatNumbers);
void checkTrainStatus();

void tampilkanPilihanStasiun() {
    printf("Pilihan Stasiun:\n");
    printf("1. Stasiun Gambir\n");
    printf("2. Stasiun Surabaya Gubeng\n");
    printf("3. Stasiun Lempuyangan\n");
    printf("4. Stasiun Bandung\n");
}

void tampilkanPilihanKereta(int asal, int tujuan) {
    printf("Pilihan Kereta dari Stasiun ");
    switch(asal) {
        case 1:
            printf("Gambir ");
            break;
        case 2:
            printf("Surabaya Gubeng ");
            break;
        case 3:
            printf("Lempuyangan ");
            break;
        case 4:
            printf("Bandung ");
            break;
    }
    printf("ke Stasiun ");
    switch(tujuan) {
        case 1: 
            printf("Gambir:\n"); 
            if (asal==2){ //SBY-JAK
                printf("1. Kereta Airlangga\n");
                printf("2. Kereta Bima\n");
            } else if (asal==3){ //YK-JAK
                printf("1. Kereta Argo Lawu\n");
                printf("2. Kereta Taksaka\n");
            } else if (asal==4){ //BDG-JAK
                printf("1. Kereta Ciremai\n");
                printf("2. Kereta Sindoro\n");
            }
            break;
        case 2:
            printf("Surabaya Gubeng:\n");
            if (asal==1){ //JAK-SBY
                printf("1. Kereta Sembrani\n");
                printf("2. Kereta Gumarang\n");
            } else if (asal==3){ //YK-SBY
                printf("1. Kereta Brawijaya\n");
                printf("2. Kereta Majapahit\n");
            }else if (asal==4){ //BDG-SBY
                printf("1. Kereta Argo Parahyangan\n");
                printf("2. Kereta Mutiara Selatan\n");
            }
            break;
        case 3:
            printf("Lempuyangan:\n");
            if (asal==1){ //JAK-YK
                printf("1. Kereta Senja Utama\n");
                printf("2. Kereta Pandalungan \n");
            } else if (asal==2){ //SBY-YK
                printf("1. Kereta Sancaka\n");
                printf("2. Kereta Ranggajati\n");
            } else if (asal==4){ //BDG-YK
                printf("1. Kereta Kutojaya\n");
                printf("2. Kereta Lodaya\n");
            }
            break;
            case 4:
            printf("Bandung:\n");
            if (asal==1){ //JAK-BDG
                printf("1. Kereta Cikuray\n");
                printf("2. Kereta Woosh\n");
            } else if (asal==2){ //SBY-BDG
                printf("1. Kereta Harina\n");
                printf("2. Kereta Pasundan\n");
            } else if (asal==4){ //YK-BDG
                printf("1. Kereta Kahuripan\n");
                printf("2. Kereta Serayu\n");
            }
    }
}

void seatMatrix(int numPassengers, int* seatNumbers) {
    int i;
    printf("\t           -:SEAT MATRIX:-        \n");
    printf("\t(U)    (M)        (L)    (L)        (U)\n\n");
    printf("\t01    02        03    04        05\n\n");
    printf("\t06    07        08    09        10\n");
    printf("\t11    12        13    14        15\n\n");
    printf("\t16    17        18    19        20\n");
    printf("\t21    22        23    24        25\n\n");
    printf("\t26    27        28    29        30\n");
    printf("\t31    32        33    34        35\n\n");
    printf("\t36    37        38    39        40\n");
    printf("\t41    42        43    44        45\n\n");
    printf("\t46    47        48    49        50\n");
    printf("\t51    52        53    54        55\n\n");
    printf("\t56    57        58    59        60\n");
    printf("Enter Seat Numbers: \n");
    for (i = 0; i < numPassengers; i++) {
        scanf("%d", &seatNumbers[i]);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n=== Selamat Datang di KAI Access Lite Version ===\n");
        printf("1. Daftar\n");
        printf("2. Masuk\n");
        printf("3. Keluar\n");
        printf("Masukkan pilihan Anda: ");
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
    printf("Buat username: ");
    scanf("%s", username);
    printf("Buat password: ");
    scanf("%s", password);

    if (findUser(username, password) != NULL) {
        printf("Username sudah ada. Silakan coba username lain.\n");
    } else {
        addUser(username, password);
        printf("Berhasil mendaftar. Silakan log in pada menu awal.\n");
    }
}

void login() {
    char username[20], password[20];
    printf("Masukkan username: ");
    scanf("%s", username);
    printf("Masukkan password: ");
    scanf("%s", password);

    User* user = findUser(username, password);
    if (user != NULL) {
        printf("Berhasil Masuk. Selamat Datang, %s!\n", username);
        userMenu();
    } else {
        printf("Username dan password salah. Silakan coba lagi.\n");
    }
}

void userMenu() {
    int choice;
    do {
        printf("\n=== Menu Utama KAI Access Lite Version ===\n");
        printf("1. Pesan Tiket Kereta\n");
        printf("2. Batalkan Pemesanan\n");
        printf("3. Cek Status Pemesanan\n");
        printf("4. Keluar\n");
        printf("Masukkan pilihan Anda: ");
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
                checkTrainStatus();
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
    char source[30];
    int numPassengers, age, seatNumbers[10], i, stasiunAsal, stasiunTujuan, pilihanKereta;
    char name[30], id[20], ticketClass[20];

    tampilkanPilihanStasiun();

    printf("Masukkan angka untuk stasiun asal: ");
    scanf("%d", &stasiunAsal);

    printf("Masukkan angka untuk stasiun tujuan: ");
    scanf("%d", &stasiunTujuan);

    tampilkanPilihanKereta(stasiunAsal, stasiunTujuan);

    printf("Pilih angka untuk kereta yang ingin dipesan: ");
    scanf("%d", &pilihanKereta);

    printf("Jumlah Penumpang: ");
    scanf("%d", &numPassengers);

    seatMatrix(numPassengers, seatNumbers);

    printf("Kelas Kereta:\n1. Ekonomi\n2. Bisnis\n3. VIP\n");
    printf("Masukkan kelas kereta: ");
    scanf("%s", ticketClass);

    for (i = 0; i < numPassengers; i++) {
        printf("Masukkan nama penumpang %d: ", i + 1);
        scanf("%s", name);
        printf("Masukkan usia penumpang %d: ", i + 1);
        scanf("%d", &age);
        printf("Masukkan NIK penumpang %d: ", i + 1);
        scanf("%s", id);

        addPassenger(source, name, age, id, seatNumbers[i], destination, ticketClass);
    }

    printBookingSummary(source, destination, numPassengers, ticketClass, seatNumbers);
}

void addPassenger(char* source, char* name, int age, char* id, int seatNumber, char* destination, char* ticketClass) {
    Passenger* newPassenger = (Passenger*)malloc(sizeof(Passenger));
    strcpy(newPassenger->name, name);
    newPassenger->age = age;
    strcpy(newPassenger->id, id);
    newPassenger->seatNumber = seatNumber;
    strcpy(newPassenger->source, source);
    strcpy(newPassenger->destination, destination);
    strcpy(newPassenger->ticketClass, ticketClass);
    newPassenger->next = passengers;
    passengers = newPassenger;
}

void printBookingSummary(char* source, char* destination, int numPassengers, char* ticketClass, int* seatNumbers) {
    Passenger* temp = passengers;
    printf("\n=== Status Pemesanan ===\n");
    printf("Tujuan: %s\n", destination);
    printf("Asal: %s\n", source);
    printf("Jumlah Penumpang: %d\n", numPassengers);
    printf("Kelas Tiket: %s\n", ticketClass);

    for (int i = 0; i < numPassengers; i++) {
        printf("Penumpang %d: \n", i + 1);
        printf("Nama: %s\n", temp->name);
        printf("Usia: %d\n", temp->age);
        printf("NIK: %s\n", temp->id);
        printf("Nomor Kursi: %d\n", seatNumbers[i]);
        temp = temp->next;
    }
    printf("\n");
}

void checkTrainStatus() {
    Passenger* temp = passengers;
    if (temp == NULL) {
        printf("Tidak ada pemesanan tiket.\n");
        return;
    }

    printf("\n=== Status Pemesanan ===\n");
    while (temp != NULL) {
        printf("Tujuan: %s\n", temp->destination);
        printf("Asal: %s\n", temp->source);
        printf("Nama: %s\n", temp->name);
        printf("Usia: %d\n", temp->age);
        printf("NIK: %s\n", temp->id);
        printf("Nomor Kursi: %d\n", temp->seatNumber);
        printf("Kelas Tiket: %s\n", temp->ticketClass);
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