#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct user {
    char username[20];
    char password[20];
    struct user* next;
} User;

typedef struct penumpang {
    char nama[30];
    int usia;
    char NIK[17];
    int NoKursi;
    char stasiunTujuan[30]; 
    char stasiunAsal[30];
    char KelasTiket[20];
    char namaKereta[30];
    struct penumpang* next;
} Penumpang;

User* users = NULL;
Penumpang* penumpang = NULL;
Penumpang daftarPenumpang[100];
int jumlahPenumpang = 0;

void signup();
void login();
User* findUser(char* username, char* password);
void addUser(char* username, char* password);
void userMenu();
void bookTicket();
void tampilkanPilihanStasiun();
void tampilkanPilihanKereta(int asal, int tujuan);
void seatMatrix(int JmlPenumpang, int* NoKursi);
void tampilkanPilihanKelas();
void addPassenger(char* nama, int usia, char* NIK, int NoKursi, char* stasiunTujuan, char* stasiunAsal, char* KelasTiket, char* namaKereta);
void printBookingSummary(char* stasiunAsal, char* stasiunTujuan, int JmlPenumpang, char* KelasTiket, int* NoKursi, char* namaKereta);
void checkTrainStatus();
void DisplayPenumpang();
void tambahPenumpang(char* nama, int usia, char* NIK, int NoKursi, char* stasiunTujuan, char* stasiunAsal, char* KelasTiket, char* namaKereta);
void batalkanTiket();

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


void addUser(char* username, char* password) {
    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->next = users;
    users = newUser;
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
                batalkanTiket();
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
    int JmlPenumpang, usia, NoKursi[10], i, pilihanKereta, pilihanKelas;
    char nama[30], KelasTiket[20], NIK[17], stasiunTujuan[30], stasiunAsal[30], namaKereta[30];

    while (1) {
        tampilkanPilihanStasiun();

        printf("Masukkan angka untuk stasiun asal: ");
        int stasiunAsalIdx;
        scanf("%d", &stasiunAsalIdx);

        printf("Masukkan angka untuk stasiun tujuan: ");
        int stasiunTujuanIdx;
        scanf("%d", &stasiunTujuanIdx);

        if (stasiunAsalIdx == stasiunTujuanIdx) {
            printf("Stasiun asal dan tujuan tidak boleh sama. Silakan coba lagi.\n");
            continue;  // Kembali ke awal loop jika stasiun asal dan tujuan sama
        }

        tampilkanPilihanKereta(stasiunAsalIdx, stasiunTujuanIdx);

        printf("Pilih angka untuk kereta yang ingin dipesan: ");
        scanf("%d", &pilihanKereta);

        const char* stasiun[] = {"Gambir", "Surabaya Gubeng", "Lempuyangan", "Bandung"};
        const char* kereta[4][4][2] = {
            {
                {"", ""}, 
                {"Kereta Sembrani", "Kereta Gumarang"}, 
                {"Kereta Senja Utama", "Kereta Pandalungan"}, 
                {"Kereta Cikuray", "Kereta Woosh"}
            },
            {
                {"Kereta Airlangga", "Kereta Bima"}, 
                {"", ""}, 
                {"Kereta Sancaka", "Kereta Ranggajati"}, 
                {"Kereta Harina", "Kereta Pasundan"}
            },
            {
                {"Kereta Argo Lawu", "Kereta Taksaka"}, 
                {"Kereta Brawijaya", "Kereta Majapahit"}, 
                {"", ""}, 
                {"Kereta Kahuripan", "Kereta Serayu"}
            },
            {
                {"Kereta Ciremai", "Kereta Sindoro"}, 
                {"Kereta Argo Parahyangan", "Kereta Mutiara Selatan"}, 
                {"Kereta Kutojaya", "Kereta Lodaya"}, 
                {"", ""}
            }
        };

        strcpy(stasiunAsal, stasiun[stasiunAsalIdx - 1]);
        strcpy(stasiunTujuan, stasiun[stasiunTujuanIdx - 1]);
        strcpy(namaKereta, kereta[stasiunAsalIdx - 1][stasiunTujuanIdx - 1][pilihanKereta - 1]);
        break;
    }

    printf("Masukkan jumlah penumpang: ");
    scanf("%d", &JmlPenumpang);

    seatMatrix(JmlPenumpang, NoKursi);

    tampilkanPilihanKelas();
    printf("Masukkan angka untuk kelas tiket (1-3): ");
    scanf("%d", &pilihanKelas);
    const char* kelas[] = {"Ekonomi", "Bisnis", "Eksekutif"};
    strcpy(KelasTiket, kelas[pilihanKelas - 1]);

    for (i = 0; i < JmlPenumpang; i++) {
        printf("Masukkan nama penumpang %d: ", i + 1);
        scanf("%s", nama);
        printf("Masukkan usia penumpang %d: ", i + 1);
        scanf("%d", &usia);
        printf("Masukkan NIK penumpang %d: ", i + 1);
        scanf("%s", NIK);
        addPassenger(nama, usia, NIK, NoKursi[i], stasiunTujuan, stasiunAsal, KelasTiket, namaKereta);
    }

    printBookingSummary(stasiunAsal, stasiunTujuan, JmlPenumpang, KelasTiket, NoKursi, namaKereta);
}


void tampilkanPilihanStasiun() {
    const char* stasiun[] = {"Gambir", "Surabaya Gubeng", "Lempuyangan", "Bandung"};
    printf("Pilihan Stasiun:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. Stasiun %s\n", i + 1, stasiun[i]);
    }
}

void tampilkanPilihanKereta(int asal, int tujuan) {
    const char* kereta[4][4][2] = {
        {
            {"", ""}, 
            {"Kereta Sembrani", "Kereta Gumarang"}, 
            {"Kereta Senja Utama", "Kereta Pandalungan"}, 
            {"Kereta Cikuray", "Kereta Woosh"}
        },
        {
            {"Kereta Airlangga", "Kereta Bima"}, 
            {"", ""}, 
            {"Kereta Sancaka", "Kereta Ranggajati"}, 
            {"Kereta Harina", "Kereta Pasundan"}
        },
        {
            {"Kereta Argo Lawu", "Kereta Taksaka"}, 
            {"Kereta Brawijaya", "Kereta Majapahit"}, 
            {"", ""}, 
            {"Kereta Kahuripan", "Kereta Serayu"}
        },
        {
            {"Kereta Ciremai", "Kereta Sindoro"}, 
            {"Kereta Argo Parahyangan", "Kereta Mutiara Selatan"}, 
            {"Kereta Kutojaya", "Kereta Lodaya"}, 
            {"", ""}
        }
    };

    printf("Pilihan Kereta dari Stasiun ");
    const char* stasiun[] = {"Gambir", "Surabaya Gubeng", "Lempuyangan", "Bandung"};
    printf("%s ke Stasiun %s:\n", stasiun[asal - 1], stasiun[tujuan - 1]);

    if (kereta[asal - 1][tujuan - 1][0][0] != '\0') {
        printf("1. %s\n", kereta[asal - 1][tujuan - 1][0]);
        printf("2. %s\n", kereta[asal - 1][tujuan - 1][1]);
    } else {
        printf("Tidak ada kereta tersedia.\n");
    }
}

void seatMatrix(int JmlPenumpang, int* NoKursi) {
    int i;
    printf("\t           -:Nomor Kursi:-        \n");
    printf("\t(A)   (B)       (C)   (D)       (E)\n\n");
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
    printf("Pilih nomor kursi: \n");
    for (i = 0; i < JmlPenumpang; i++) {
        scanf("%d", &NoKursi[i]);
    }
}

void tampilkanPilihanKelas() {
    const char* kelas[] = {"Ekonomi", "Bisnis", "Eksekutif"};
    printf("Pilihan Kelas Tiket:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, kelas[i]);
    }
}


void addPassenger(char* nama, int usia, char* NIK, int NoKursi, char* stasiunTujuan, char* stasiunAsal, char* KelasTiket, char* namaKereta) {
    Penumpang* newPenumpang = (Penumpang*)malloc(sizeof(Penumpang));
    strcpy(newPenumpang->nama, nama);
    newPenumpang->usia = usia;
    strcpy(newPenumpang->NIK, NIK);
    newPenumpang->NoKursi = NoKursi;
    strcpy(newPenumpang->stasiunTujuan, stasiunTujuan);
    strcpy(newPenumpang->stasiunAsal, stasiunAsal);
    strcpy(newPenumpang->KelasTiket, KelasTiket);
    strcpy(newPenumpang->namaKereta, namaKereta);
    newPenumpang->next = penumpang;
    penumpang = newPenumpang;
}


void printBookingSummary(char* stasiunAsal, char* stasiunTujuan, int JmlPenumpang, char* KelasTiket, int* NoKursi, char* namaKereta) {
    Penumpang* temp = penumpang;
    printf("\n=== Status Pemesanan ===\n");
    printf("Asal: %s\n", stasiunAsal);
    printf("Tujuan: %s\n", stasiunTujuan);
    printf("Nama Kereta: %s\n", namaKereta);
    printf("Jumlah Penumpang: %d\n", JmlPenumpang);
    printf("Kelas Tiket: %s\n", KelasTiket);

    for (int i = 0; i < JmlPenumpang; i++) {
        printf("Penumpang %d: \n", i + 1);
        printf("Nama: %s\n", temp->nama);
        printf("Usia: %d\n", temp->usia);
        printf("NIK: %s\n", temp->NIK);
        printf("Nomor Kursi: %d\n", NoKursi[i]);
        temp = temp->next;
    }
    printf("\n");
}


void checkTrainStatus() {
    Penumpang* temp = penumpang;
    if (temp == NULL) {
        printf("Tidak ada pemesanan tiket.\n");
        return;
    }

    printf("\n=== Status Pemesanan ===\n");
    while (temp != NULL) {
        printf("Tujuan: %s\n", temp->stasiunTujuan);
        printf("Asal: %s\n", temp->stasiunAsal);
        printf("Nama: %s\n", temp->nama);
        printf("Usia: %d\n", temp->usia);
        printf("NIK: %s\n", temp->NIK);
        printf("Nomor Kursi: %d\n", temp->NoKursi);
        printf("Kelas Tiket: %s\n", temp->KelasTiket);
        printf("Nama Kereta: %s\n", temp->namaKereta);
        printf("-----------------------\n");
        temp = temp->next;
    }
}


void batalkanTiket(){
    if (jumlahPenumpang == 0) {
        printf("Tidak ada pemesanan tiket.\n");
        return;
    }

    printf("\n=== Batalkan Tiket ===\n");
    DisplayPenumpang();

    printf("Masukkan nomor penumpang yang ingin dibatalkan: ");
    int nomorPembatalan;
    scanf("%d", &nomorPembatalan);

    if (nomorPembatalan < 1 || nomorPembatalan > jumlahPenumpang) {
        printf("Nomor penumpang tidak valid. Silakan coba lagi.\n");
        return;
    }

    for (int i = nomorPembatalan - 1; i < jumlahPenumpang - 1; i++) {
        daftarPenumpang[i] = daftarPenumpang[i + 1];
    }

    jumlahPenumpang--;

    printf("Tiket berhasil dibatalkan.\n");
}


void DisplayPenumpang(){
    printf("Daftar Penumpang yang Sudah Dipesan:\n");
    for (int i = 0; i < jumlahPenumpang; i++) {
    printf("%d. Nama: %s, NIK: %s, No Kursi: %d, Kereta: %s, Kelas: %s, Asal: %s, Tujuan: %s\n", 
            i + 1, daftarPenumpang[i].nama, daftarPenumpang[i].NIK, daftarPenumpang[i].NoKursi, 
            daftarPenumpang[i].namaKereta, daftarPenumpang[i].KelasTiket, daftarPenumpang[i].stasiunAsal, 
            daftarPenumpang[i].stasiunTujuan);
    }
}


void tambahPenumpang(char* nama, int usia, char* NIK, int NoKursi, char* stasiunTujuan, char* stasiunAsal, char* KelasTiket, char* namaKereta) {
    strcpy(daftarPenumpang[jumlahPenumpang].nama, nama);
    daftarPenumpang[jumlahPenumpang].usia = usia;
    strcpy(daftarPenumpang[jumlahPenumpang].NIK, NIK);
    daftarPenumpang[jumlahPenumpang].NoKursi = NoKursi;
    strcpy(daftarPenumpang[jumlahPenumpang].stasiunTujuan, stasiunTujuan);
    strcpy(daftarPenumpang[jumlahPenumpang].stasiunAsal, stasiunAsal);
    strcpy(daftarPenumpang[jumlahPenumpang].KelasTiket, KelasTiket);
    strcpy(daftarPenumpang[jumlahPenumpang].namaKereta, namaKereta);
    jumlahPenumpang++;
}
 
