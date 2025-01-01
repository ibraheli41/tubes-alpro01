#include <iostream>
#include <string>
using namespace std;

struct Slot {
    int no;
    string plat[4];
    bool kosong;
    int isi;
    string jenis;
    int masuk[4]; // Waktu masuk dalam menit total
};

void fungsiGaris()
{
    cout <<"=========================================================" <<endl;
}

void fungsiMenu()
{
    fungsiGaris();
    cout << "SELAMAT DATANG PADA PROGRAM PARKIR\n";
    fungsiGaris();

    cout << "\nMenu Parkir:\n";
    cout << "1. Tampilkan Status Parkir\n";
    cout << "2. Parkir Kendaraan\n";
    cout << "3. Ambil Kendaraan\n";
    cout << "4. Keluar\n";
}

int tampilkanStatus(Slot parkir[], int n) {
    for (int i = 0; i < n; ++i) // mengeprint sebanyak n
    {
        if (parkir[i].kosong) {
            cout << "Slot " << parkir[i].no << " kosong.\n";
        } else {
            cout << "Slot " << parkir[i].no << " terisi oleh " << parkir[i].jenis;
            for (int j = 0; j < parkir[i].isi; ++j) {
                int jam = parkir[i].masuk[j] / 60;
                int menit = parkir[i].masuk[j] % 60;
                cout << " dengan plat: " << parkir[i].plat[j]
                     << " (Masuk: " << jam << ":" << (menit < 10 ? "0" : "") << menit << ")";
            }
            cout << endl;
        }
    }
    return 0;
}

int parkirKendaraan(Slot parkir[], int n) {
    // Inisialisasi Varibel
    int slot, totalMasuk;
    string p, jenis;
    float waktu;

    // Tampilkan untuk User memasukan nilai Jenis
    // Nilai jenis berupa string antara mobil motor atau sepeda
    cout << "Jenis kendaraan (Mobil/Motor/Sepeda): ";
    cin >> jenis;

    // Tentukan jenis kendaraan
    bool mobil = (jenis == "Mobil" || jenis == "mobil" || jenis == "MOBIL");
    bool motor = (jenis == "Motor" || jenis == "motor" || jenis == "MOTOR");
    bool sepeda = (jenis == "Sepeda" || jenis == "sepeda" || jenis == "SEPEDA");

    // Error Check: Jika bukan mobil AND bukan motor AND bukan Sepeda maka muncul peringatan
    if (!mobil && !motor && !sepeda) 
    {
        cout << "Jenis kendaraan tidak dikenali.\n";
        system("cls"); 
		fungsiMenu();
		return parkirKendaraan(parkir, n); // kembali hanya ke tampilan ambil kendaraan
    }

    // Menampilkan slot yang tersedia untuk Jenis
    cout << "Slot kosong untuk " << jenis << ":\n";

    // Inisialsiasi variabel ada; tipe data boolean
    // Memasukan nilai ada = salah.
    bool ada = false;

    // n adalah?
    // flowchart for loop
    for (int i = 0; i < n; ++i) 
    {
        
        if (sepeda && (i == 6 || i == 7) && parkir[i].isi < 4) 
        {
            cout << "Slot " << parkir[i].no << " tersedia (" << parkir[i].isi << "/4 sepeda).\n";
            ada = true;
        } 
        
        else if (motor && i >= 4 && i < 6 && parkir[i].isi < 2) 
        {
            cout << "Slot " << parkir[i].no << " tersedia (" << parkir[i].isi << "/2 motor).\n";
            ada = true;
        } 
        
        else if (mobil && i < 4 && parkir[i].kosong) 
        {
            cout << "Slot " << parkir[i].no << " tersedia.\n";
            ada = true;
        }
    }

    if (!ada) 
    {
        cout << "Tidak ada slot kosong.\n";
        return -1;
    }

    cout << "Pilih slot: ";
    cin >> slot;
    cout << "Plat nomor: ";
    cin.ignore();
    getline(cin, p);
    cout << "Waktu masuk (jam.menit, contoh: 8.30): ";
    cin >> waktu;

    int jam = static_cast<int>(waktu);
    int menit = static_cast<int>((waktu - jam) * 100);
    totalMasuk = (jam * 60) + menit;

    int idx = slot - 1;
    parkir[idx].plat[parkir[idx].isi] = p;
    parkir[idx].masuk[parkir[idx].isi] = totalMasuk;
    parkir[idx].isi++;
    parkir[idx].kosong = false;
    parkir[idx].jenis = jenis;

    cout << jenis << " dengan plat " << p << " diparkir di slot " << slot
         << " pada " << jam << ":" << (menit < 10 ? "0" : "") << menit << ".\n";
    return 0;
}

int ambilKendaraan(Slot parkir[], int n) {
    string platNomorKendaraan;
    float waktuKeluar;
    int totalKeluar;
    bool kendaraanDitemukan = false; // Flag untuk mengecek apakah kendaraan ditemukan

    while (!kendaraanDitemukan) { // Loop hingga kendaraan ditemukan atau pengguna keluar
        cout << "Plat nomor kendaraan (ketik 'batal' untuk kembali ke menu): ";
        cin.ignore(); // Membersihkan buffer input
        getline(cin, platNomorKendaraan);

        // Jika pengguna ingin membatalkan proses
        if (platNomorKendaraan == "batal" || platNomorKendaraan == "Batal") {
            cout << "Proses pengambilan kendaraan dibatalkan.\n";
            return 0; // Kembali ke menu utama
        }

        // Cari plat nomor kendaraan
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < parkir[i].isi; ++j) {
                if (parkir[i].plat[j] == platNomorKendaraan) { // Kendaraan ditemukan
                    kendaraanDitemukan = true;

                    // Meminta waktu keluar kendaraan
                    cout << "Waktu keluar (jam.menit, contoh: 10.45): ";
                    cin >> waktuKeluar;

                    // Konversi waktu keluar ke menit
                    int jam = static_cast<int>(waktuKeluar);
                    int menit = static_cast<int>((waktuKeluar - jam) * 100);
                    totalKeluar = (jam * 60) + menit;

                    int totalMasuk = parkir[i].masuk[j];
                    int durasi = totalKeluar - totalMasuk;
                    if (durasi < 0) durasi += 1440; // Jika durasi negatif, tambahkan 1440 menit

                    // Hitung biaya berdasarkan jenis kendaraan
                    int biaya = 0;
                    if (parkir[i].jenis == "Mobil" || parkir[i].jenis == "mobil" || parkir[i].jenis == "MOBIL") {
                        biaya = (durasi / 60) * 5000;
                    } else if (parkir[i].jenis == "Motor" || parkir[i].jenis == "motor" || parkir[i].jenis == "MOTOR") {
                        biaya = (durasi / 60) * 2000;
                    } else if (parkir[i].jenis == "Sepeda" || parkir[i].jenis == "sepeda" || parkir[i].jenis == "SEPEDA") {
                        biaya = (durasi / 60) * 500;
                    }

                    // Tampilkan informasi pengambilan kendaraan
                    fungsiGaris();
                    cout << "Kendaraan dengan plat " << platNomorKendaraan << " diambil dari slot " << parkir[i].no << ".\n";
                    cout << "Durasi: " << durasi / 60 << " jam " << durasi % 60 << " menit.\n";
                    cout << "Biaya: Rp" << biaya << ".\n";
                    fungsiGaris();

                    // Hapus kendaraan dari slot
                    for (int k = j; k < parkir[i].isi - 1; ++k) {
                        parkir[i].plat[k] = parkir[i].plat[k + 1];
                        parkir[i].masuk[k] = parkir[i].masuk[k + 1];
                    }
                    parkir[i].isi--;
                    if (parkir[i].isi == 0) {
                        parkir[i].kosong = true;
                        parkir[i].jenis = "";
                    }
                    return 0; // Kembali ke menu utama setelah berhasil mengambil kendaraan
                }
            }
        }

        // Jika kendaraan tidak ditemukan
        cout << "Plat nomor tidak ditemukan. Silakan coba lagi.\n";
    }
    return 0; // Selesai
}

void kembali() 
{        // Fungsi untuk kembali ke MENU UTAMA
    string inputExit ;  // inisialisasi variabel untuk masukan user ketika ingin kembali

    cout << "\nTekan Enter untuk kembali ke menu...\n";

    cin.clear();        // menghapus nilai dari masukan user
    cin.ignore();       // mengabaikan masukan dari user

    getline(cin, inputExit);    // meminta user memasukan input
    system("cls");              // perintah untuk membersihkan layar terminal
}

int main() 
{
    int totalSlotParkir = 8;          // Inisialisasi Variabel totalSlotParkir dengan Nilai 8
    Slot parkir[totalSlotParkir];     // membuat object array parkir dengan nilai array dari totalSlotParkir

    for (int i = 0; i < totalSlotParkir; ++i) // mengatur nilai variabel ketika program pertama kali mulai. member berupa no, kosong, isi, jenis 
    {   
        parkir[i].no = i + 1;
        parkir[i].kosong = true;
        parkir[i].isi = 0;
        parkir[i].jenis = "";
    }

    string menu;                     // Varriabel Menu untuk memasukan nilai user
    
    do // Perulangan DO-WHILE agar program berjalan terus menerus. Berakhir 
    {
        fungsiGaris();
        cout << "\tSELAMAT DATANG PADA PROGRAM PARKIR\n";
        fungsiGaris();

        /* TAMPILAN MENU UTAMA */
        cout << "\nMenu Parkir:\n";
        cout << "1. Tampilkan Status Parkir\n";
        cout << "2. Parkir Kendaraan\n";
        cout << "3. Ambil Kendaraan\n";
        cout << "4. Keluar\n";
        cout << "Pilih (1-4): ";

        cin >> menu;                        // Input nilai Menu


        if (menu == "1")                    // User menginputkan 1
        {
            tampilkanStatus(parkir, totalSlotParkir); // object parkir dan jumlah slot parkir yang ada
            kembali();
        } 
        else if (menu == "2")               // User menginputkan 2
        {
            parkirKendaraan(parkir, totalSlotParkir);
            kembali();
        } 
        else if (menu == "3")               // User menginputkan 3
        {
            ambilKendaraan(parkir, totalSlotParkir);
            kembali();
        } 

        else {                              // kembali ke menu
            system("cls");
        }


    } while (menu != "4");                  // User menginputkan diluar 1-3

    return 0;
}