#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING 30
#define MAX_KERETA 2
#define MAX_PENUMPANG 10

typedef struct {
    char nama[MAX_STRING];
    int usia;
    char NIK[MAX_STRING];
    int NoKursi;
    char stasiunTujuan[MAX_STRING];
    char stasiunAsal[MAX_STRING];
    char KelasTiket[MAX_STRING];
    char namaKereta[MAX_STRING];
} Penumpang;

Penumpang penumpang[MAX_PENUMPANG];
int totalPenumpang = 0;

const char* stasiun[] = {"Gambir", "Surabaya Gubeng", "Lempuyangan", "Bandung"};

const char* kereta[4][4][MAX_KERETA] = {
    { // Stasiun Asal Gambir
        {"", ""}, // Tujuan Gambir (invalid)
        {"Kereta Sembrani", "Kereta Gumarang"}, // Tujuan Surabaya Gubeng
        {"Kereta Senja Utama", "Kereta Pandalungan"}, // Tujuan Lempuyangan
        {"Kereta Cikuray", "Kereta Woosh"} // Tujuan Bandung
    },
    { // Stasiun Asal Surabaya Gubeng
        {"Kereta Airlangga", "Kereta Bima"}, // Tujuan Gambir
        {"", ""}, // Tujuan Surabaya Gubeng (invalid)
        {"Kereta Sancaka", "Kereta Ranggajati"}, // Tujuan Lempuyangan
        {"Kereta Harina", "Kereta Pasundan"} // Tujuan Bandung
    },
    { // Stasiun Asal Lempuyangan
        {"Kereta Argo Lawu", "Kereta Taksaka"}, // Tujuan Gambir
        {"Kereta Brawijaya", "Kereta Majapahit"}, // Tujuan Surabaya Gubeng
        {"", ""}, // Tujuan Lempuyangan (invalid)
        {"Kereta Kahuripan", "Kereta Serayu"} // Tujuan Bandung
    },
    { // Stasiun Asal Bandung
        {"Kereta Ciremai", "Kereta Sindoro"}, // Tujuan Gambir
        {"Kereta Argo Parahyangan", "Kereta Mutiara Selatan"}, // Tujuan Surabaya Gubeng
        {"Kereta Kutojaya", "Kereta Lodaya"}, // Tujuan Lempuyangan
        {"", ""} // Tujuan Bandung (invalid)
    }
};

void tampilkanPilihanStasiun() {
    printf("Stasiun yang tersedia:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, stasiun[i]);
    }
}

void tampilkanPilihanKereta(int asal, int tujuan) {
    if (asal == tujuan) {
        printf("Stasiun asal dan tujuan tidak boleh sama.\n");
        return;
    }

    printf("Pilihan Kereta dari Stasiun %s ke Stasiun %s:\n", stasiun[asal - 1], stasiun[tujuan - 1]);

    for (int i = 0; i < MAX_KERETA; i++) {
        if (strlen(kereta[asal - 1][tujuan - 1][i]) > 0) {
            printf("%d. %s\n", i + 1, kereta[asal - 1][tujuan - 1][i]);
        }
    }
}

void seatMatrix(int JmlPenumpang, int NoKursi[MAX_PENUMPANG]) {
    for (int i = 0; i < JmlPenumpang; i++) {
        printf("Masukkan nomor kursi untuk penumpang %d: ", i + 1);
        scanf("%d", &NoKursi[i]);
    }
}

void addPassenger(char* nama, int usia, char* NIK, int NoKursi, char* stasiunTujuan, char* stasiunAsal, char* KelasTiket, char* namaKereta) {
    strcpy(penumpang[totalPenumpang].nama, nama);
    penumpang[totalPenumpang].usia = usia;
    strcpy(penumpang[totalPenumpang].NIK, NIK);
    penumpang[totalPenumpang].NoKursi = NoKursi;
    strcpy(penumpang[totalPenumpang].stasiunTujuan, stasiunTujuan);
    strcpy(penumpang[totalPenumpang].stasiunAsal, stasiunAsal);
    strcpy(penumpang[totalPenumpang].KelasTiket, KelasTiket);
    strcpy(penumpang[totalPenumpang].namaKereta, namaKereta);
    totalPenumpang++;
}

void printBookingSummary(char* stasiunAsal, char* stasiunTujuan, int JmlPenumpang, char* KelasTiket, int NoKursi[MAX_PENUMPANG], char* namaKereta) {
    printf("\nBooking Summary:\n");
    printf("Stasiun Asal: %s\n", stasiunAsal);
    printf("Stasiun Tujuan: %s\n", stasiunTujuan);
    printf("Jumlah Penumpang: %d\n", JmlPenumpang);
    printf("Kelas Tiket: %s\n", KelasTiket);
    printf("Nama Kereta: %s\n", namaKereta);
    for (int i = 0; i < JmlPenumpang; i++) {
        printf("Penumpang %d:\n", i + 1);
        printf("Nama: %s\n", penumpang[i].nama);
        printf("Usia: %d\n", penumpang[i].usia);
        printf("NIK: %s\n", penumpang[i].NIK);
        printf("Nomor Kursi: %d\n", penumpang[i].NoKursi);
    }
}

void bookTicket() {
    int JmlPenumpang, usia, NoKursi[MAX_PENUMPANG], i, pilihanKereta;
    char nama[MAX_STRING], KelasTiket[MAX_STRING], NIK[MAX_STRING];
    char stasiunAsal[MAX_STRING], stasiunTujuan[MAX_STRING], namaKereta[MAX_STRING];

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
            continue; // Kembali ke awal loop jika stasiun asal dan tujuan sama
        }

        tampilkanPilihanKereta(stasiunAsalIdx, stasiunTujuanIdx);

        printf("Pilih angka untuk kereta yang ingin dipesan: ");
        scanf("%d", &pilihanKereta);

        // Set nama kereta berdasarkan pilihan
        strcpy(stasiunAsal, stasiun[stasiunAsalIdx - 1]);
        strcpy(stasiunTujuan, stasiun[stasiunTujuanIdx - 1]);
        strcpy(namaKereta, kereta[stasiunAsalIdx - 1][stasiunTujuanIdx - 1][pilihanKereta - 1]);

        printf("Jumlah Penumpang: ");
        scanf("%d", &JmlPenumpang);

        seatMatrix(JmlPenumpang, NoKursi);

        printf("Kelas Kereta (Ekonomi/Bisnis/VIP): ");
        scanf("%s", KelasTiket);

        break;
    }

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

int main() {
    bookTicket();
    return 0;
}
