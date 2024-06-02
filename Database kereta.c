

// Fungsi untuk menampilkan pilihan stasiun
void tampilkanPilihanStasiun() {
    printf("Pilihan Stasiun:\n");
    printf("1. Stasiun A\n");
    printf("2. Stasiun B\n");
    printf("3. Stasiun C\n");
    printf("4. Stasiun D\n");
    // Tambahkan stasiun lainnya sesuai kebutuhan
}


// Fungsi untuk menampilkan pilihan kereta sesuai dengan asal dan tujuan
void tampilkanPilihanKereta(int asal, int tujuan) {
    printf("Pilihan Kereta dari Stasiun ");
    switch (asal) {
        case 1:
            printf("A ");
            break;
        case 2:
            printf("B ");
            break;
        case 3:
            printf("C ");
            break;
        case 4:
            printf("D ");
            break; 
        // Tambahkan stasiun lainnya sesuai kebutuhan
    }
    printf("ke Stasiun ");
    switch (tujuan) {
        case 1:
            printf("A:\n");
            // Kereta dari stasiun asal ke tujuan
            if (asal == 2) {
                printf("1. Kereta Y\n");
                printf("2. Kereta Z\n");
            } else if (asal == 3) {
                printf("1. Kereta X\n");
                printf("2. Kereta Z\n");
            } else if (asal == 4) {
                printf("1. Kereta B\n");
                printf("2. Kereta D\n");
            }
            break;
        case 2:
            printf("B:\n");
            if (asal == 1) {
                printf("1. Kereta X\n");
                printf("2. Kereta Y\n");
            } else if (asal == 3) {
                printf("1. Kereta X\n");
                printf("2. Kereta Z\n");
            }
            break;
        case 3:
            printf("C:\n");
            if (asal == 1) {
                printf("1. Kereta X\n");
                printf("2. Kereta Y\n");
            } else if (asal == 2) {
                printf("1. Kereta Y\n");
                printf("2. Kereta Z\n");
            }
            break;
        // Tambahkan stasiun lainnya sesuai kebutuhan
    }
}


int main() {
    int stasiunAsal, stasiunTujuan, pilihanKereta;


    while (1) {
        // Menampilkan pilihan stasiun
        tampilkanPilihanStasiun();


        // Meminta input stasiun asal
        printf("Masukkan angka untuk stasiun asal: ");
        scanf("%d", &stasiunAsal);


        // Meminta input stasiun tujuan
        printf("Masukkan angka untuk stasiun tujuan: ");
        scanf("%d", &stasiunTujuan);


        // Memeriksa apakah stasiun asal dan tujuan sama
        if (stasiunAsal == stasiunTujuan) {
            printf("Stasiun asal dan tujuan tidak boleh sama. Silakan coba lagi.\n");
            continue;  // Kembali ke awal loop jika stasiun asal dan tujuan sama
        }


        // Menampilkan pilihan kereta sesuai dengan asal dan tujuan
        tampilkanPilihanKereta(stasiunAsal, stasiunTujuan);


        // Meminta input pilihan kereta
        printf("Pilih angka untuk kereta yang ingin dipesan: ");
        scanf("%d", &pilihanKereta);


        // Tampilkan konfirmasi
        printf("Anda telah memesan tiket kereta.\n");


        break;  // Keluar dari loop setelah pemesanan tiket berhasil
    }


    return 0;
}
