#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include "tools.h"

#define ENTER 13
#define TAB 9
#define BKSP 8
#define MAX_ATTEMPTS 3

struct Barang {
    int idBarang;
    char namaBarang[100];
    int stokBarang;
    char pemasok[100];
    float Sprice;
    float Bprice;
    float untung;
};

// main func
void Login();
void menuUtama();
void kelolaBarang();
void kelolaTransaksi();
void ubahTampilan();
void logout();
// kelola barang
void printRow(struct Barang barang);
void printSeparator(int width);
void tulisListDiFile(FILE *fptr, struct Barang *barang);
int cekIDFile(int idBarang);
void tambahBarang();
void listBarang();
void cariID();
void updateBarang();
void updateBarangNext();
void hapusBarang();
// kelola transaksi
void pembelianBarang();
void penjualanBarang();
void beliBarang();
void jualBarang();
void tampilkanLogTransaksiBeli();
void tampilkanLogTransaksiJual();
void beli(int idBarang, int tambahStok, FILE *fptr);
void jual(int idBarang, int kurangStok, FILE *fptr);
void logTransaksiBeli(int idBarang, int jumlahBeli);
void logTransaksiJual(int idBarang, int jumlahBeli);

char *home[] = {"\n\n\t\t\t\tBeranda\n\n",NULL};
char *kelola_barang[] = {"\n\n\t\t\tBeranda","Kelola Barang\n\n",NULL};
char *kelola_transaksi[] = {"\n\n\t\t\tBeranda","Kelola Transaksi\n\n",NULL};
char *kelola_beli[] = {"\n\n\t\t\tBeranda","Kelola Barang","Kelola Pembelian\n\n",NULL};
char *kelola_jual[] = {"\n\n\t\t\tBeranda","Kelola Barang","Kelola Penjualan\n\n",NULL};
char *kelolaTampilan[] = {"\n\n\t\t\tBeranda","Ubah Tampilan\n\n",NULL};

int main()
{
    Login();
}

void Login() 
{
    char username[50] = "projectAkhir";
    char password[50] = "abcdefg";
    int maxLogin = 0;

    for (int i = 0; i < MAX_ATTEMPTS; i++) {

        printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t Masukkan Username Anda : ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        printf("\t\t\t\t\t Masukkan Password Anda : ");
        char ch;
        int j = 0;

        while (1) {
            ch = getch();
            if (ch == ENTER || ch == TAB) {
                password[j] = '\0';
                break;
            } else if (ch == BKSP) {
                if (j > 0) {
                    j--;
                    printf("\b \b");
                }
            } else {
                password[j++] = ch;
                printf("* \b");
            }
        }
        
        printf("\n\n\t\t\t\t\t\t MEMERIKSA USER");
        MarqueeText("\n\t\t\t        \xb3\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xb3\n",6999900);

        if (strcmp(username, "projectAkhir") == 0 && strcmp(password, "abcdefg") == 0) {
            printf("\n\t\t\t\t\t\t Login Berhasil!\n");
            Sleep(1000);
            menuUtama();
            break;
        } else {
            printf("\n\n\t\t\t\t\t Username atau Password Salah\n");
            maxLogin++;
            Sleep(1000);
            system("cls");
        }
    }

    if (maxLogin >= MAX_ATTEMPTS) {
        printf("\t\t\t\t Akun Anda Terblokir\n");
    }
}
void menuUtama()
{
    int pilih;
    int panjangArr = 1;
    menu:
    system("cls");
    Breadcrumb(home,panjangArr);
    printf("\t\t\t        \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf\n");
	printf("\t\t\t        \xb3         TOKO GROSIR DAN GERABAH PAK KHOLIS        \xb3\n");
	printf("\t\t\t        \xb3     Jl. Bogo - Kunjang, Ngino, Kec. Plemahan      \xb3\n");
	printf("\t\t\t        \xb3         Kabupaten Kediri, Jawa Timur 64155        \xb3\n");
	printf("\t\t\t        \xb3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb3\n");
	printf("\t\t\t        \xb3                 ====== Menu ======                \xb3\n");
	printf("\t\t\t        \xb3                                                   \xb3\n");
	printf("\t\t\t        \xb3                1. Kelola Barang                   \xb3\n");
    printf("\t\t\t        \xb3                                                   \xb3\n");
	printf("\t\t\t        \xb3                2. Kelola Transaksi                \xb3\n");
	printf("\t\t\t        \xb3                                                   \xb3\n");
	printf("\t\t\t        \xb3                3. Ubah Tampilan                   \xb3\n");
	printf("\t\t\t        \xb3                                                   \xb3\n");
	printf("\t\t\t        \xb3                4. Logout                          \xb3\n");
	printf("\t\t\t        \xb3                                                   \xb3\n");
    printf("\t\t\t        \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\n");
    printf("\t\t\t                           Pilih Menu : "); scanf("%d", &pilih);
    MarqueeText("\t\t\t        \xb3\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xb3\n",6999900);
    Sleep(500);

	system("cls");
    switch (pilih)
    {
     case 1:
        kelolaBarang();
        break;
     case 2:
        kelolaTransaksi();
        break;
     case 3:
        ubahTampilan();
        break;
     case 4:
        logout();
        break;
    default:
        printf("\t\t\t                           Masukan Pilihan Dengan Benar!! ");
        goto menu;
        break;
    }
}

void kelolaBarang()
{
    int pilih;
    int panjangArr = 2;
    kelolaBrg:
    system("cls");
    Breadcrumb(kelola_barang, panjangArr);
    printf("\t\t\t        \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf\n");
	printf("\t\t\t        \xb3         TOKO GROSIR DAN GERABAH PAK KHOLIS        \xb3\n");
	printf("\t\t\t        \xb3     Jl. Bogo - Kunjang, Ngino, Kec. Plemahan      \xb3\n");
	printf("\t\t\t        \xb3         Kabupaten Kediri, Jawa Timur 64155        \xb3\n");
	printf("\t\t\t        \xb3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb3\n");
	printf("\t\t\t        \xb3                 ====== Menu ======                \xb3\n");
	printf("\t\t\t        \xb3                                                   \xb3\n");
	printf("\t\t\t        \xb3                1. Tambah Barang                   \xb3\n");
    printf("\t\t\t        \xb3                                                   \xb3\n");
	printf("\t\t\t        \xb3                2. Update Barang                   \xb3\n");
	printf("\t\t\t        \xb3                                                   \xb3\n");
	printf("\t\t\t        \xb3                3. Hapus Barang                    \xb3\n");
	printf("\t\t\t        \xb3                                                   \xb3\n");
	printf("\t\t\t        \xb3                4. Cari Barang                     \xb3\n");
	printf("\t\t\t        \xb3                                                   \xb3\n");
	printf("\t\t\t        \xb3                5. Tampilkan Seluruh Barang        \xb3\n");
    printf("\t\t\t        \xb3                                                   \xb3\n");
    printf("\t\t\t        \xb3                0. Kembali                         \xb3\n");
	printf("\t\t\t        \xb3                                                   \xb3\n");
    printf("\t\t\t        \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\n");
    printf("\t\t\t                           Pilih Menu : "); scanf("%d", &pilih);
    MarqueeText("\t\t\t        \xb3\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xb3\n",6999900);
    Sleep(500);

    system("cls");
    switch (pilih)
    {
    case 1:
            tambahBarang();
            Sleep(1000);
            goto kelolaBrg;
        break;
    case 2:
            updateBarang();
            Sleep(1000);
            goto kelolaBrg;
        break;
    case 3:
            hapusBarang();
            Sleep(1000);
            goto kelolaBrg;
        break;
    case 4:
            cariID();
            Sleep(1000);
            goto kelolaBrg;
        break;
    case 5:
            listBarang();
            Sleep(1000);
            goto kelolaBrg;
        break;
    case 0:
            menuUtama();
            break;
    default:
            printf("\t\t\t                           Masukan Pilihan Dengan Benar!! ");
            goto kelolaBrg;
        break;
    }
}

void kelolaTransaksi()
{   
    int pilih;
    int panjangArr = 2;
    kelolaTrx:
    system("cls");
    Breadcrumb(kelola_transaksi, panjangArr);
    printf("\t\t\t        \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf\n");
	printf("\t\t\t        \xb3         TOKO GROSIR DAN GERABAH PAK KHOLIS        \xb3\n");
	printf("\t\t\t        \xb3     Jl. Bogo - Kunjang, Ngino, Kec. Plemahan      \xb3\n");
	printf("\t\t\t        \xb3         Kabupaten Kediri, Jawa Timur 64155        \xb3\n");
	printf("\t\t\t        \xb3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb3\n");
	printf("\t\t\t        \xb3                 ====== Menu ======                \xb3\n");
	printf("\t\t\t        \xb3                                                   \xb3\n");
	printf("\t\t\t        \xb3                1. Pembelian                       \xb3\n");
    printf("\t\t\t        \xb3                                                   \xb3\n");
	printf("\t\t\t        \xb3                2. Penjualan                       \xb3\n");
	printf("\t\t\t        \xb3                                                   \xb3\n");
    printf("\t\t\t        \xb3                0. Kembali                         \xb3\n");
	printf("\t\t\t        \xb3                                                   \xb3\n");
    printf("\t\t\t        \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\n");
    printf("\t\t\t                           Pilih Menu : "); scanf("%d", &pilih);
    MarqueeText("\t\t\t        \xb3\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xb3\n",6999900);
    Sleep(500);

    system("cls");
    switch (pilih)
    {
    case 1:
            pembelianBarang();
            Sleep(1000);
            goto kelolaTrx;
        break;
    case 2:
            penjualanBarang();
            Sleep(1000);
            goto kelolaTrx;
        break;
    case 0:
            menuUtama();
            break;
    default:
            printf("\t\t\t                           Masukan Pilihan Dengan Benar!! ");
            goto kelolaTrx;
        break;
    }
}

void pembelianBarang()
{   
    int pilih;
    int panjangArr = 3;
    kelolaBeli:
    system("cls");
    Breadcrumb(kelola_beli, panjangArr);
    printf("\t\t\t        \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf\n");
    printf("\t\t\t        \xb3         TOKO GROSIR DAN GERABAH PAK KHOLIS        \xb3\n");
    printf("\t\t\t        \xb3     Jl. Bogo - Kunjang, Ngino, Kec. Plemahan      \xb3\n");
    printf("\t\t\t        \xb3         Kabupaten Kediri, Jawa Timur 64155        \xb3\n");
    printf("\t\t\t        \xb3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb3\n");
    printf("\t\t\t        \xb3                 ====== Menu ======                \xb3\n");
    printf("\t\t\t        \xb3                                                   \xb3\n");
    printf("\t\t\t        \xb3                1. Pembelian                       \xb3\n");
    printf("\t\t\t        \xb3                                                   \xb3\n");
    printf("\t\t\t        \xb3                2. Data Pembelian                  \xb3\n");
    printf("\t\t\t        \xb3                                                   \xb3\n");
    printf("\t\t\t        \xb3                0. Kembali                         \xb3\n");
    printf("\t\t\t        \xb3                                                   \xb3\n");
    printf("\t\t\t        \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\n");
    printf("\t\t\t                           Pilih Menu : "); scanf("%d", &pilih);
    MarqueeText("\t\t\t        \xb3\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xb3\n",6999900);
    Sleep(500);

    system("cls");
    switch (pilih)
    {
    case 1:
            beliBarang();
            Sleep(1000);
            goto kelolaBeli;
        break;
    case 2:
            tampilkanLogTransaksiBeli();
            Sleep(1000);
            goto kelolaBeli;
        break;
    case 0:
            kelolaTransaksi();
            break;
    default:
            printf("\t\t\t                           Masukan Pilihan Dengan Benar!! ");
            goto kelolaBeli;
        break;
    }
}

void penjualanBarang()
{   
    int pilih;
    int panjangArr = 3;
    kelolaJual:
    system("cls");
    Breadcrumb(kelola_jual, panjangArr);
    printf("\t\t\t        \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf\n");
    printf("\t\t\t        \xb3         TOKO GROSIR DAN GERABAH PAK KHOLIS        \xb3\n");
    printf("\t\t\t        \xb3     Jl. Bogo - Kunjang, Ngino, Kec. Plemahan      \xb3\n");
    printf("\t\t\t        \xb3         Kabupaten Kediri, Jawa Timur 64155        \xb3\n");
    printf("\t\t\t        \xb3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb3\n");
    printf("\t\t\t        \xb3                 ====== Menu ======                \xb3\n");
    printf("\t\t\t        \xb3                                                   \xb3\n");
    printf("\t\t\t        \xb3                1. Penjualan                       \xb3\n");
    printf("\t\t\t        \xb3                                                   \xb3\n");
    printf("\t\t\t        \xb3                2. Data Penjualan                  \xb3\n");
    printf("\t\t\t        \xb3                                                   \xb3\n");
    printf("\t\t\t        \xb3                0. Kembali                         \xb3\n");
    printf("\t\t\t        \xb3                                                   \xb3\n");
    printf("\t\t\t        \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\n");
    printf("\t\t\t                           Pilih Menu : "); scanf("%d", &pilih);
    MarqueeText("\t\t\t        \xb3\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xb3\n",6999900);
    Sleep(500);

    system("cls");
    switch (pilih)
    {
    case 1:
            jualBarang();
            Sleep(1000);
            goto kelolaJual;
        break;
    case 2:
            tampilkanLogTransaksiJual();
            Sleep(1000);
            goto kelolaJual;
        break;
    case 0:
            kelolaTransaksi();
            break;
    default:
            printf("\t\t\t                           Masukan Pilihan Dengan Benar!! ");
            goto kelolaJual;
        break;
    }
}

void ubahTampilan()
{           int panjangArr2 = 2;
            int pilih;
            system("cls");
            Breadcrumb(kelolaTampilan, panjangArr2);
            printf("\t\t\t        \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf\n");	
		    printf("\t\t\t        \xb3             ====== TAMPILAN ======              \xb3\n");
            printf("\t\t\t        \xb3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb3\n");
			printf("\t\t\t        \xb3                                                 \xb3\n");
			printf("\t\t\t        \xb3                1. LIGHT MODE                    \xb3\n");
			printf("\t\t\t        \xb3                                                 \xb3\n");
			printf("\t\t\t        \xb3                2. DARK MODE                     \xb3\n");
			printf("\t\t\t        \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\n");		
			printf("\t\t\t                           Pilih Menu : "); scanf("%d", &pilih);
            MarqueeText("\t\t\t        \xb3\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xb3\n",6999900);
            Sleep(500);
			switch(pilih){
				case 1:
					system("color F0");
                    menuUtama();
				break;
				case 2:
					system("color 07");
                    menuUtama();
				break;
				default:
			    	system("cls");
                    menuUtama();
			    break;
			}
			printf("\n   \xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4 \n");
			printf("   Tekan Mana Saja Untuk Kembali . . . "); getch();
			system("cls");			
			menuUtama();
}

void logout()
{   
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t Logout Berhasil ");
    exit(0);
}

// Bagian dari kelola barang

void printSeparator(int width) {
    printf("\t\t");
    printf("+");
    for (int i = 0; i < width - 2; i++) {
        printf("-");
    }
    printf("+\n");
}

void printRow(struct Barang barang) {
    printf("\t\t| %-4d |  %-14s|  %-5d |   %-10s|   %-10.2f |   %-10.2f |  %-10.2f  |\n", barang.idBarang, barang.namaBarang, barang.stokBarang, barang.pemasok, barang.Bprice, barang.Sprice, barang.untung);
}

void tulisListDiFile(FILE *fptr, struct Barang *barang)
{
    fptr = fopen("barang.txt", "a+");
    if (fptr == NULL)
    {
        printf("\n\t\t\t Erorr Membuka File!\n");
        exit(0);
    }
    else
    {
        fprintf(fptr, "ID Barang             : %d\n", barang->idBarang);
        fprintf(fptr, "Nama Barang           : %s\n", barang->namaBarang);
        fprintf(fptr, "Jumlah Stok Barang    : %d\n", barang->stokBarang);
        fprintf(fptr, "Pemasok Barang        : %s\n\n", barang->pemasok);
        fprintf(fptr, "Harga Beli Barang     : %f\n\n", barang->Bprice);
        fprintf(fptr, "Harga Jual Barang     : %f\n\n", barang->Sprice);
    }
    fclose(fptr);
}

int cekIDFile(int idBarang)
{
    FILE *fptr = fopen("barang.txt", "r");
    if (fptr == NULL)
    {
        printf("\n\t\t\t Barang Gagal Dimuat");
        exit(0);
    }
    else
    {
        struct Barang barang;

        while (fscanf(fptr, "ID Barang             : %d\n", &barang.idBarang) == 1)
        {
            fscanf(fptr, "Nama Barang          : %[^\n]\n", barang.namaBarang);
            fscanf(fptr, "Jumlah Stok Barang   : %d\n", &barang.stokBarang);
            fscanf(fptr, "Pemasok Barang       : %[^\n]\n\n", barang.pemasok);
            fscanf(fptr, "Harga Beli Barang    : %f\n\n", &barang.Bprice);
            fscanf(fptr, "Harga Jual Barang    : %f\n\n", &barang.Sprice);

            if (barang.idBarang == idBarang)
            {
                fclose(fptr);
                return 1;
            }
        }
        fclose(fptr);
        return 0;
    }
}

void tambahBarang()
{
    FILE *fptr = fopen("barang.txt", "a+");
    if (fptr == NULL)
    {
        printf("\n\t\t\tBarang Gagal Dimuat");
        exit(0);
    }
    else
    {   
        system("cls");
        char *tmbh_Barang[] = {"\n\n\t\tBeranda","Kelola Barang","Tambahkan Barang\n\n",NULL};
        int panjangArr = 3;
        Breadcrumb(tmbh_Barang, panjangArr);
        struct Barang barang;
        int jumlahBarangBaru;
        printf("\n");
        printf("\n\t\t\t\t Input Jumlah Barang Yang Ingin Ditambah : ");
        scanf("%d", &jumlahBarangBaru);
        Sleep(1000);
        for (int i = 0; i < jumlahBarangBaru; i++)
        {	
        	system("cls");
            printf("\n\t\t\t\t Masukkan Informasi Barang!\n\n");
            printf("\n\t\t\t\t Masukkan ID Barang        : ");
            scanf("%d", &barang.idBarang);

            if (cekIDFile(barang.idBarang))
            {
                printf("\n\t\t\t\t  ID Barang sudah terdaftar. Masukkan ID lain.\n");
                i--;
                continue;
            }

           while (getchar() != '\n')
                ;

            printf("\t\t\t\t Masukkan Nama Barang      : ");
            fgets(barang.namaBarang, sizeof(barang.namaBarang), stdin);
            barang.namaBarang[strcspn(barang.namaBarang, "\n")] = '\0';

            printf("\t\t\t\t Masukkan Jumlah Stok      : ");
            scanf("%d", &barang.stokBarang);

            while (getchar() != '\n')
                ;

            printf("\t\t\t\t Masukkan Pemasok          : ");
            fgets(barang.pemasok, sizeof(barang.pemasok), stdin);
            barang.pemasok[strcspn(barang.pemasok, "\n")] = '\0';

            printf("\t\t\t\t Masukkan Harga Beli Barang: ");
            scanf("%f", &barang.Bprice);

            while (getchar() != '\n')
                ;

            printf("\t\t\t\t Masukkan Harga Jual Barang: ");
            scanf("%f", &barang.Sprice);

            while (getchar() != '\n')
                ;

            printf("\n");

            tulisListDiFile(fptr, &barang);
        }
        fclose(fptr);
        printf("\t\t\t\t Loading ");
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf("\n\t\t\t\t Data Barang Berhasil di Input!\n");
        printf("\t\t\t\t Ke Menu Awal");
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf("\n");
    }
}

void listBarang()
{
    FILE *fptr = fopen("barang.txt", "r");
    if (fptr == NULL)
    {
        printf("\n\t\t\t\t Barang Gagal Dimuat\n");
        exit(0);
    }
    else
    {
        system("cls");
        char *tampilkanBarang[] = {"\n\n\tBeranda","Kelola Barang","Tampilkan Barang\n\n",NULL};
        int panjangArr = 3;
        Breadcrumb(tampilkanBarang, panjangArr);
        struct Barang barang;
        int kosong = 1;

        printSeparator(93);
        printf("\t\t|  ID  |      Nama      |  Stok  |   Pemasok   |  Harga Beli  |  Harga Jual  |  Keuntungan  |\n");
        printSeparator(93);

        while (fscanf(fptr, "ID Barang             : %d\n", &barang.idBarang) == 1)
        {
            kosong = 0;
            fscanf(fptr, "Nama Barang          : %[^\n]\n", barang.namaBarang);
            fscanf(fptr, "Jumlah Stok Barang   : %d\n", &barang.stokBarang);
            fscanf(fptr, "Pemasok Barang       : %[^\n]\n\n", barang.pemasok);
            fscanf(fptr, "Harga Beli Barang    : %f\n\n", &barang.Bprice);
            fscanf(fptr, "Harga Jual Barang    : %f\n\n", &barang.Sprice);
            barang.untung = barang.Sprice - barang.Bprice;
            printRow(barang);
            printSeparator(93);
        }

        if (kosong)
        {
            printf("\n\t\t\t\t\t Tidak Ada Barang Yang Terdaftar!\n\n");
        }

        getch();

        fclose(fptr);
    }
}

void cariID() {
    int idTarget;
    FILE *fptr = fopen("barang.txt", "r");
    struct Barang barang;
    int found = 0;

    if (fptr == NULL) {
        printf("\n\t\t\t\t Barang Gagal Dimuat");
        exit(0);
    }

    system("cls");
    char *cariBarang[] = {"\n\n\tBeranda","Kelola Barang","Cari Barang\n\n",NULL};
    int panjangArr = 3;
    Breadcrumb(cariBarang, panjangArr);
    printf("\n");
    printf("\n\t\t\t\t Masukan ID Barang Yang Akan Dicari: ");
    scanf("%d", &idTarget);

    printf("\n\t\t\t\t Searching");
    for (int i = 0; i < 3; ++i) {
        Sleep(500);
        printf(".");
    }
    printf("\n");

    while (fscanf(fptr, "ID Barang             : %d\n", &barang.idBarang) == 1) {
        fscanf(fptr, "Nama Barang          : %[^\n]\n", barang.namaBarang);
        fscanf(fptr, "Jumlah Stok Barang   : %d\n", &barang.stokBarang);
        fscanf(fptr, "Pemasok Barang       : %[^\n]\n\n", barang.pemasok);
        fscanf(fptr, "Harga Beli Barang    : %f\n\n", &barang.Bprice);
        fscanf(fptr, "Harga Jual Barang    : %f\n\n", &barang.Sprice);

        if (barang.idBarang == idTarget) {
            barang.untung = barang.Sprice - barang.Bprice;
            printSeparator(93);
            printf("\t\t|  ID  |      Nama      |  Stok  |   Pemasok   |  Harga Beli  |  Harga Jual  |  Keuntungan  |\n");
            printSeparator(93);
            printRow(barang);
            printSeparator(93);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n\t\t\t\t ID Barang Tidak Ditemukan\n");
    }

    fclose(fptr);

    char jalaninFungsiLagi;
    do {
        printf("\n\t\t\t\t Apakah Anda Ingin Menggunakan Menu Ini Lagi? (Y / N) : ");
        scanf(" %c", &jalaninFungsiLagi);

        if (jalaninFungsiLagi == 'y' || jalaninFungsiLagi == 'Y') {
            return cariID();
        } else if (jalaninFungsiLagi == 'n' || jalaninFungsiLagi == 'N') {
            printf("\n\t\t\t\t Kembali ke Menu Awal\n");
            return;
        } else {
            printf("\n\t\t\t\t Input Tidak Valid!\n");
        }
    } while (1);
}

void updateBarang()
{
    FILE *fptr = fopen("barang.txt", "r+");
    if (fptr == NULL)
    {
        printf("\n\t\t\t\t Barang Gagal Dimuat\n");
        exit(0);
    }
    else
    {    
        system("cls");   
        char *update_Barang[] = {"\n\n\t\tBeranda","Kelola Barang","Update Barang\n\n",NULL};
        int panjangArr = 3;
        Breadcrumb(update_Barang, panjangArr);
        int idTarget;
        struct Barang barang;
        FILE *tempFile = fopen("tempbarang.txt", "w");
        if (tempFile == NULL)
        {
            printf("\n\t\t\t\t Barang Gagal Dimuat\n");
            exit(0);
        }
        printf("\n");
        printf("\n\t\t\t\t Input ID Barang Yang Ingin DiUpdate : ");
        scanf("%d", &idTarget);

        int found = 0;
        printf("\n\t\t\t\t Data Barang Yang Ingin DiUpdate!\n");
        printSeparator(93);
        printf("\t\t|  ID  |      Nama      |  Stok  |   Pemasok   |  Harga Beli  |  Harga Jual  |  Keuntungan  |\n");
        printSeparator(93);

        while (fscanf(fptr, "ID Barang             : %d\n", &barang.idBarang) == 1)
        {
            fscanf(fptr, "Nama Barang          : %[^\n]\n", barang.namaBarang);
            fscanf(fptr, "Jumlah Stok Barang   : %d\n", &barang.stokBarang);
            fscanf(fptr, "Pemasok Barang       : %[^\n]\n\n", barang.pemasok);
            fscanf(fptr, "Harga Beli Barang    : %f\n\n", &barang.Bprice);
            fscanf(fptr, "Harga Jual Barang    : %f\n\n", &barang.Sprice);

            if (barang.idBarang == idTarget)
            {   
                barang.untung = barang.Sprice - barang.Bprice;
                printRow(barang);
                printSeparator(93);
                found = 1;
                break;
            }
            else
            {
                fprintf(tempFile, "ID Barang             : %d\n", barang.idBarang);
                fprintf(tempFile, "Nama Barang           : %s\n", barang.namaBarang);
                fprintf(tempFile, "Jumlah Stok Barang    : %d\n", barang.stokBarang);
                fprintf(tempFile, "Pemasok Barang        : %s\n\n", barang.pemasok);
                fprintf(tempFile, "Harga Beli Barang     : %.2f\n\n", barang.Bprice);
                fprintf(tempFile, "Harga Jual Barang     : %.2f\n\n", barang.Sprice);
            }
        }
        fclose(fptr);
        fclose(tempFile);
        remove("barang.txt");
        rename("tempbarang.txt", "barang.txt");

        updateBarangNext();

        if (!found)
        {
            printf("\n\t\t\t\t ID Barang Tidak Ditemukan\n");
        }

        char apusIDLagi;
    pesan:
        printf("\n\t\t\t\t Apakah Anda Ingin Menjalankan Fungsi Kembali? (Y / N) : ");
        scanf(" %c", &apusIDLagi);

        if (apusIDLagi == 'y' || apusIDLagi == 'Y')
        {
            updateBarang();
        }
        else if (apusIDLagi == 'n' || apusIDLagi == 'N')
        {
            printf("\n\t\t\t\t Program Berakhir");
        }
        else
        {
            printf("\n\t\t\t\t Input Tidak Valid!");
            goto pesan;
        }
    }
}

void hapusBarang()
{
    FILE *fptr = fopen("barang.txt", "r+");
    if (fptr == NULL)
    {
        printf("\n\t\t\t\t Barang Gagal Dimuat\n");
        exit(0);
    }
    else
    {   
        system("cls");
        char *hapus_Barang[] = {"\n\n\t\tBeranda","Kelola Barang","Hapus Barang\n\n",NULL};
        int panjangArr = 3;
        Breadcrumb(hapus_Barang, panjangArr);
        int idTarget;
        struct Barang barang;
        FILE *tempFile = fopen("tempbarang.txt", "w");
        if (tempFile == NULL)
        {
            printf("\n\t\t\t\t Barang Gagal Dimuat\n");
            exit(0);
        }
        printf("\n");
        printf("\n\t\t\t\t Input ID Barang Yang Akan Dihapus: ");
        scanf("%d", &idTarget);

        int found = 0;

        while (fscanf(fptr, "ID Barang             : %d\n", &barang.idBarang) == 1)
        {
            fscanf(fptr, "Nama Barang          : %[^\n]\n", barang.namaBarang);
            fscanf(fptr, "Jumlah Stok Barang   : %d\n", &barang.stokBarang);
            fscanf(fptr, "Pemasok Barang       : %[^\n]\n\n", barang.pemasok);
            fscanf(fptr, "Harga Beli Barang    : %f\n\n", &barang.Bprice);
            fscanf(fptr, "Harga Jual Barang    : %f\n\n", &barang.Sprice);

            if (barang.idBarang == idTarget)
            {
                found = 1;
                printf("\n\t\t\t\t Barang dengan ID %d berhasil dihapus!\n", barang.idBarang);
            }
            else
            {
                fprintf(tempFile, "ID Barang             : %d\n", barang.idBarang);
                fprintf(tempFile, "Nama Barang           : %s\n", barang.namaBarang);
                fprintf(tempFile, "Jumlah Stok Barang    : %d\n", barang.stokBarang);
                fprintf(tempFile, "Pemasok Barang        : %s\n\n", barang.pemasok);
                fprintf(tempFile, "Harga Beli Barang     : %.2f\n\n", barang.Bprice);
                fprintf(tempFile, "Harga Jual Barang     : %.2f\n\n", barang.Sprice);
            }
        }
        fclose(fptr);
        fclose(tempFile);
        remove("barang.txt");
        rename("tempbarang.txt", "barang.txt");

        if (!found)
        {
            printf("\n\t\t\t\t ID Barang Tidak Ditemukan\n");
        }
    }

    char apusIDLagi;
pesan:
    printf("\n\t\t\t\t Apakah Anda Ingin Menghapus ID Kembali? (Y / N) : ");
    scanf(" %c", &apusIDLagi);

    if (apusIDLagi == 'y' || apusIDLagi == 'Y')
    {
        hapusBarang();
    }
    else if (apusIDLagi == 'n' || apusIDLagi == 'N')
    {
        printf("\n\t\t\t\t Program Berakhir");
    }
    else
    {
        printf("\n\t\t\t\t Input Tidak Valid!");
        goto pesan;
    }
}
void updateBarangNext()
{
    FILE *fptr = fopen("barang.txt", "a+");
    if (fptr == NULL)
    {
        printf("\n\t\t\t\t Barang Gagal Dimuat");
        exit(0);
    }
    else
    {
        struct Barang barang;

        printf("\n\t\t\t\tMasukkan Informasi Baru Untuk Barang!\n\n");
        ulangupdate:
        printf("\n\t\t\t\t Masukkan ID Barang        : ");
        scanf("%d", &barang.idBarang);

            if (cekIDFile(barang.idBarang))
            {
                printf("\n\t\t\t\tID Barang sudah terdaftar. Masukkan ID lain.\n");
                goto ulangupdate;
            }

           while (getchar() != '\n')
                ;

            printf("\t\t\t\t Masukkan Nama Barang      : ");
            fgets(barang.namaBarang, sizeof(barang.namaBarang), stdin);
            barang.namaBarang[strcspn(barang.namaBarang, "\n")] = '\0';

            printf("\t\t\t\t Masukkan Jumlah Stok      : ");
            scanf("%d", &barang.stokBarang);

            while (getchar() != '\n')
                ;

            printf("\t\t\t\t Masukkan Pemasok          : ");
            fgets(barang.pemasok, sizeof(barang.pemasok), stdin);
            barang.pemasok[strcspn(barang.pemasok, "\n")] = '\0';

            printf("\t\t\t\t Masukkan Harga Beli Barang: ");
            scanf("%f", &barang.Bprice);

            while (getchar() != '\n')
                ;

            printf("\t\t\t\t Masukkan Harga Jual Barang: ");
            scanf("%f", &barang.Sprice);

            while (getchar() != '\n')
                ;

            printf("\n");

            tulisListDiFile(fptr, &barang);
    }
    fclose(fptr);
}

// function kelola transaksi

void logTransaksiBeli(int idBarang, int jumlahBeli) {
    FILE *logFile = fopen("log_transaksi_beli.txt", "a");
    if (logFile == NULL) {
        printf("\n\t\t\t\tGagal membuka file log transaksi pembelian\n");
        exit(0);
    } else {
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        fprintf(logFile, "ID Barang: %d, Jumlah: %d, Tanggal: %s", idBarang, jumlahBeli, asctime(timeinfo));
        fclose(logFile);
    }
}

void beli(int idBarang, int tambahStok, FILE *fptr) {
    if (fptr == NULL) {
        printf("\n\t\t\t\tBarang Gagal Dimuat");
        exit(0);
    } else {
        struct Barang barang;
        long int pos = 0;
        FILE *temp = fopen("temp.txt", "w");

        if (temp == NULL) {
            printf("\n\t\t\t\tGagal membuat file sementara\n");
            exit(0);
        }

        while (fscanf(fptr, "ID Barang             : %d\n", &barang.idBarang) == 1) {
            pos = ftell(fptr);
            fscanf(fptr, "Nama Barang          : %[^\n]\n", barang.namaBarang);
            fscanf(fptr, "Jumlah Stok Barang   : %d\n", &barang.stokBarang);
            fscanf(fptr, "Pemasok Barang       : %[^\n]\n\n", barang.pemasok);
            fscanf(fptr, "Harga Beli Barang    : %f\n\n", &barang.Bprice);
            fscanf(fptr, "Harga Jual Barang    : %f\n\n", &barang.Sprice);

            if (barang.idBarang == idBarang) {
                barang.stokBarang += tambahStok;

                fprintf(temp, "ID Barang             : %d\n", barang.idBarang);
                fprintf(temp, "Nama Barang           : %s\n", barang.namaBarang);
                fprintf(temp, "Jumlah Stok Barang    : %d\n", barang.stokBarang);
                fprintf(temp, "Pemasok Barang        : %s\n\n", barang.pemasok);
                fprintf(temp, "Harga Beli Barang     : %.2f\n\n", barang.Bprice);
                fprintf(temp, "Harga Jual Barang     : %.2f\n\n", barang.Sprice);
                
                printf("\n\t\t\t\tStok Barang telah diperbarui!\n");
            } else {
                fprintf(temp, "ID Barang             : %d\n", barang.idBarang);
                fprintf(temp, "Nama Barang           : %s\n", barang.namaBarang);
                fprintf(temp, "Jumlah Stok Barang    : %d\n", barang.stokBarang);
                fprintf(temp, "Pemasok Barang        : %s\n\n", barang.pemasok);
                fprintf(temp, "Harga Beli Barang     : %.2f\n\n", barang.Bprice);
                fprintf(temp, "Harga Jual Barang     : %.2f\n\n", barang.Sprice);
            }
        }

        fclose(fptr);
        fclose(temp);
        remove("barang.txt");
        rename("temp.txt", "barang.txt");
        logTransaksiBeli(idBarang, tambahStok);
    }
}
void beliBarang() {
    FILE *fptr = fopen("barang.txt", "r+");
    if (fptr == NULL) {
        printf("\n\t\t\t\tBarang Gagal Dimuat\n");
        exit(0);
    } else {
        int idTarget;
        int jmlBeli;
        char *beli_nav[] = {"\n\n\t\tBeranda","Kelola Transaksi","Kelola Pembelian","Pembelian\n\n",NULL};
        int panjangArr = 4;
        Breadcrumb(beli_nav, panjangArr);

        printf("\n\t\t\t\tJumlah item yang akan dibeli : ");
        scanf("%d", &jmlBeli);

        for (int i = 0; i < jmlBeli; i++) {
            printf("\n\t\t\t\tInput ID Barang : ");
            scanf("%d", &idTarget);
            int tambahStok;
            printf("\n\t\t\t\tMasukkan jumlah barang yang dibeli : ");
            scanf("%d", &tambahStok);
            
            fseek(fptr, 0, SEEK_SET);
            beli(idTarget, tambahStok, fptr);
        }
    }
    getch();
}

void tampilkanLogTransaksiBeli() {
    FILE *logFile = fopen("log_transaksi_beli.txt", "r");
    if (logFile == NULL) {
        printf("\n\t\t\t\tFile log transaksi kosong atau tidak ditemukan\n");
        return;
    } else {
        char *dataBeli_nav[] = {"\n\n\t\tBeranda","Kelola Transaksi","Kelola Pembelian","Data Pembelian\n\n",NULL};
        int panjangArr = 4;
        Breadcrumb(dataBeli_nav, panjangArr);
        printf("\n\t\t\t\t\t\t=== Log Transaksi Pembelian ===\n\n");
        
        printf("\n\n\t\t\t\t\t| %-5s | %-5s |   %-25s|\n", "ID", "Jumlah", "Tanggal");
        printf("\t\t\t\t\t----------------------------------------------\n");

        int idBarang;
        int jumlah;
        char tanggal[100];

        while (fscanf(logFile, "ID Barang: %d, Jumlah: %d, Tanggal: %[^\n]\n", &idBarang, &jumlah, tanggal) == 3) {
            printf("\t\t\t\t\t| %-5d |   %-5d|  %-20s  |\n ", idBarang, jumlah, tanggal);
            printf("\t\t\t\t\t----------------------------------------------\n");
        }
        fclose(logFile);
    }
    getch();
}

void logTransaksiJual(int idBarang, int jumlahBeli) {
    FILE *logFile1 = fopen("log_transaksi_jual.txt", "a");
    if (logFile1 == NULL) {
        printf("\n\t\t\t\tGagal membuka file log transaksi\n");
        exit(0);
    } else {
        struct Barang barang;
        float totalPengeluaran = 0;
        float totalPendapatan = 0;

        FILE *fptr = fopen("barang.txt", "r");
        if (fptr == NULL) {
            printf("\n\t\t\t\tBarang Gagal Dimuat\n");
            exit(0);
        }

        while (fscanf(fptr, "ID Barang             : %d\n", &barang.idBarang) == 1) {
            fscanf(fptr, "Nama Barang          : %[^\n]\n", barang.namaBarang);
            fscanf(fptr, "Jumlah Stok Barang   : %d\n", &barang.stokBarang);
            fscanf(fptr, "Pemasok Barang       : %[^\n]\n\n", barang.pemasok);
            fscanf(fptr, "Harga Beli Barang    : %f\n\n", &barang.Bprice);
            fscanf(fptr, "Harga Jual Barang    : %f\n\n", &barang.Sprice);

            if (barang.idBarang == idBarang) {
                totalPengeluaran = barang.Bprice * jumlahBeli;
                totalPendapatan = barang.Sprice * jumlahBeli;

                time_t rawtime;
                struct tm *timeinfo;
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                
                float keuntungan = totalPendapatan - totalPengeluaran;

                fprintf(logFile1, "ID Barang: %d, Jumlah: %d, Keuntungan: %.2f, Tanggal: %s",
                        idBarang, jumlahBeli, keuntungan, asctime(timeinfo));
                fclose(fptr);
                fclose(logFile1);
                return;
            }
        }
        printf("\n\t\t\t\tID Barang Tidak Ditemukan\n");
        fclose(fptr);
        fclose(logFile1);
    }
}

void jual(int idBarang, int kurangStok, FILE *fptr) {
    if (fptr == NULL) {
        printf("\n\t\t\t\tBarang Gagal Dimuat");
        exit(0);
    } else {
        struct Barang barang;
        long int pos = 0;
        FILE *temp = fopen("temp.txt", "w");

        if (temp == NULL) {
            printf("\n\t\t\t\tGagal membuat file sementara\n");
            exit(0);
        }

        while (fscanf(fptr, "ID Barang             : %d\n", &barang.idBarang) == 1) {
            pos = ftell(fptr);
            fscanf(fptr, "Nama Barang          : %[^\n]\n", barang.namaBarang);
            fscanf(fptr, "Jumlah Stok Barang   : %d\n", &barang.stokBarang);
            fscanf(fptr, "Pemasok Barang       : %[^\n]\n\n", barang.pemasok);
            fscanf(fptr, "Harga Beli Barang    : %f\n\n", &barang.Bprice);
            fscanf(fptr, "Harga Jual Barang    : %f\n\n", &barang.Sprice);

            if (barang.idBarang == idBarang) {
                barang.stokBarang -= kurangStok;

                fprintf(temp, "ID Barang             : %d\n", barang.idBarang);
                fprintf(temp, "Nama Barang           : %s\n", barang.namaBarang);
                fprintf(temp, "Jumlah Stok Barang    : %d\n", barang.stokBarang);
                fprintf(temp, "Pemasok Barang        : %s\n\n", barang.pemasok);
                fprintf(temp, "Harga Beli Barang     : %.2f\n\n", barang.Bprice);
                fprintf(temp, "Harga Jual Barang     : %.2f\n\n", barang.Sprice);
                
                printf("\n\t\t\t\tStok Barang telah diperbarui!\n");
            } else {
                fprintf(temp, "ID Barang             : %d\n", barang.idBarang);
                fprintf(temp, "Nama Barang           : %s\n", barang.namaBarang);
                fprintf(temp, "Jumlah Stok Barang    : %d\n", barang.stokBarang);
                fprintf(temp, "Pemasok Barang        : %s\n\n", barang.pemasok);
                fprintf(temp, "Harga Beli Barang     : %.2f\n\n", barang.Bprice);
                fprintf(temp, "Harga Jual Barang     : %.2f\n\n", barang.Sprice);
            }
        }

        fclose(fptr);
        fclose(temp);
        remove("barang.txt");
        rename("temp.txt", "barang.txt");
        logTransaksiJual(idBarang, kurangStok);
    }
}
void jualBarang() {
    FILE *fptr = fopen("barang.txt", "r+");
    if (fptr == NULL) {
        printf("\n\t\t\t\tBarang Gagal Dimuat\n");
        exit(0);
    } else {
        int idTarget;
        int jmlBeli;
        char *jual_nav[] = {"\n\n\t\tBeranda","Kelola Transaksi","Kelola Pembelian","Penjualan\n\n",NULL};
        int panjangArr = 4;
        Breadcrumb(jual_nav, panjangArr);

        printf("\n\t\t\t\tJumlah item yang akan dibeli : ");
        scanf("%d", &jmlBeli);

        for (int i = 0; i < jmlBeli; i++) {
            printf("\n\t\t\t\tInput ID Barang : ");
            scanf("%d", &idTarget);
            int kurangStok;
            printf("\n\t\t\t\tMasukkan jumlah barang yang dijual : ");
            scanf("%d", &kurangStok);
            
            fseek(fptr, 0, SEEK_SET);
            jual(idTarget, kurangStok, fptr);
        }
    }
    getch();
}

void tampilkanLogTransaksiJual() {
    FILE *logFile1 = fopen("log_transaksi_jual.txt", "r");
    if (logFile1 == NULL) {
        printf("\n\t\t\t\tFile log transaksi kosong atau tidak ditemukan\n");
        return;
    } else {
        char *dataJual_nav[] = {"\n\n\t\tBeranda","Kelola Transaksi","Kelola Pembelian","Data Penjualan\n\n",NULL};
        int panjangArr = 4;
        Breadcrumb(dataJual_nav, panjangArr);
        printf("\n\t\t\t\t\t\t=== Log Transaksi Penjualan ===\n\n");
        printf("\n\n\t\t\t\t|  %-5s| %-5s | %-10s |   %-25s|\n", "ID", "Jumlah", "Keuntungan", "Tanggal");
        printf("\t\t\t\t------------------------------------------------------------\n");

        int idBarang;
        int jumlah;
        float keuntungan;
        char tanggal[100];

        while (fscanf(logFile1, "ID Barang: %d, Jumlah: %d, Keuntungan: %f, Tanggal: %[^\n]\n", 
                      &idBarang, &jumlah, &keuntungan, tanggal) == 4) {
            printf("\t\t\t\t|  %-5d|   %-5d| %-10.2f |  %-25s |  \n", idBarang, jumlah, keuntungan, tanggal);
            printf("\t\t\t\t------------------------------------------------------------\n");
        }

        fclose(logFile1);
    }
    getch();
}