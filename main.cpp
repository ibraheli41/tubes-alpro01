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

int fungsiGaris(){
    cout << "=================================================\n";
    return 0;
}

int tampilkanStatus(Slot parkir[], int n) {
    for (int i = 0; i < n; ++i) {
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
    int slot, totalMasuk;
    string p, jenis;
    float waktu;

    cout << "Jenis kendaraan (Mobil/Motor/Sepeda): ";
    cin >> jenis;

    // Tentukan jenis kendaraan
    bool mobil = (jenis == "Mobil" || jenis == "mobil" || jenis == "MOBIL");
    bool motor = (jenis == "Motor" || jenis == "motor" || jenis == "MOTOR");
    bool sepeda = (jenis == "Sepeda" || jenis == "sepeda" || jenis == "SEPEDA");

    if (!mobil && !motor && !sepeda) {
        cout << "Jenis kendaraan tidak dikenali.\n";
        return -1;
    }

    cout << "Slot kosong untuk " << jenis << ":\n";
    bool ada = false;

    for (int i = 0; i < n; ++i) {
        if (sepeda && (i == 6 || i == 7) && parkir[i].isi < 4) {
            cout << "Slot " << parkir[i].no << " tersedia (" << parkir[i].isi << "/4 sepeda).\n";
            ada = true;
        } else if (motor && i >= 4 && i < 6 && parkir[i].isi < 2) {
            cout << "Slot " << parkir[i].no << " tersedia (" << parkir[i].isi << "/2 motor).\n";
            ada = true;
        } else if (mobil && i < 4 && parkir[i].kosong) {
            cout << "Slot " << parkir[i].no << " tersedia.\n";
            ada = true;
        }
    }

    if (!ada) {
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
    
    /* Deklarasi variabel untuk input dan perhitungan*/
    string input_platNomor;
    float waktuKeluar;
    int totalKeluar;
    
    /* Setingan Biaya Parkir Kendaraan*/
    int biayaMobil = 5000;
    int biayaMotor = 2000;
    int biayaSepeda = 1000;
    
    /* Input pengguna plat nomor kendaraan*/
    cout << "Plat nomor kendaraan: ";
    cin.ignore();
    getline(cin, input_platNomor);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < parkir[i].isi; ++j) {
            
            /* Jika plat nomor dan daftar plat yang ada sesuai */
            if (parkir[i].plat[j] == input_platNomor) {
                
                /* Input untuk waktuKeluar */
                cout << "Waktu keluar (jam.menit, contoh: 10.45): ";
                cin >> waktuKeluar;

                /* Konversi waktu keluar dari float ke int */
                int jam = static_cast<int>(waktuKeluar);
                int menit = static_cast<int>((waktuKeluar - jam) * 100);
                totalKeluar = (jam * 60) + menit;

                /* Perhitungan Durasi Parkir */
                int totalMasuk = parkir[i].masuk[j];
                int durasi = totalKeluar - totalMasuk;
                if (durasi < 0) durasi += 1440;                 // ????

                /**********************************************************************/
                /* Percabangan untuk menghitung biaya berdasarkan jenis kendaraan */
                int biaya = 0; // menyimpan nilai biaya
                /* === Mobil === */
                if (parkir[i].jenis == "Mobil" || parkir[i].jenis == "mobil" || parkir[i].jenis == "MOBIL") 
                {
                    biaya = (durasi / 60) * biayaMobil;
                } 
                /* === Motor  === */
                else if (parkir[i].jenis == "Motor" || parkir[i].jenis == "motor" || parkir[i].jenis == "MOTOR") 
                {
                    biaya = (durasi / 60) * biayaMotor;
                } 
                /* === Sepeda  === */
                else if (parkir[i].jenis == "Sepeda" || parkir[i].jenis == "sepeda" || parkir[i].jenis == "SEPEDA") 
                {
                    biaya = (durasi / 60) * biayaSepeda;
                }
                /**********************************************************************/

                /**********************************************************************/
                /* Print total biaya */
                fungsiGaris();
                cout << "Kendaraan dengan plat " << input_platNomor << " diambil dari slot " << parkir[i].no << ".\n";
                cout << "Durasi: " << durasi / 60 << " jam " << durasi % 60 << " menit.\n";
                cout << "Biaya: Rp" << biaya << ".\n";
                fungsiGaris();
                /**********************************************************************/

                /**********************************************************************/
                /* Menghapus daftar kendaraan dengan memindahkan ke variabel lain*/
                for (int k = j; k < parkir[i].isi - 1; ++k) 
                {
                    parkir[i].plat[k] = parkir[i].plat[k + 1];
                    parkir[i].masuk[k] = parkir[i].masuk[k + 1];
                }
                parkir[i].isi--;

                /* Jika parkir[i].isi == 0 maka print kosong dan mengahapus nilai jenis */
                if (parkir[i].isi == 0) 
                {
                    parkir[i].kosong = true;
                    parkir[i].jenis = "";
                }
                /**********************************************************************/
                return 0;
            }
        }
    }
    /* Print jika plat nomor tidak ditemukan */
    cout << "Plat nomor tidak ditemukan.\n";
    return -1;
}


/**********************************************************************/
/* Fungsi untuk kembali ke Menu */ 
void kembali() 
{
    cout << "\nTekan Enter untuk kembali ke menu...\n";
    
    string inputExit;           // Deklarasi variabel untuk input pengguna
    
    cin.clear();                // Clear Nilai cin
    cin.ignore();               // Mengabaikan cin
    getline(cin, inputExit);    // input cin
    system("cls");              // Clear screen
}
/**********************************************************************/


int main() 
{
    
    /**********************************************************************/
    /* Jumlah Slot yang Ada -> Inisialisasi Variabel n dengan Nilai 8
    Array parkir berdasarkan nilai n */ 
    int n = 8;                     
    Slot parkir[n];    
    /**********************************************************************/ 

    /* Mengatur nilai variabel dari struct parkir */ 
    for (int i = 0; i < n; ++i)  
    {   
        parkir[i].no = i + 1;
        parkir[i].kosong = true;
        parkir[i].isi = 0;
        parkir[i].jenis = "";
    }

    /* Deklarasi variabel menu untuk input pengguna. 
    Pemilihan string ditujukan untuk menggunakan karakter dan angka*/ 
    string menu;                               
    
    /* Perulangan Do supaya program berjalan terus menerus*/
    do {
        /**********************************************************************/ 
        /* Print Tampilan Menu*/
        fungsiGaris();
        cout << "\tSELAMAT DATANG PADA PROGRAM PARKIR\n";
        fungsiGaris();
        cout << "\nMenu Parkir:\n";
        cout << "1. Tampilkan Status Parkir\n";
        cout << "2. Parkir Kendaraan\n";
        cout << "3. Ambil Kendaraan\n";
        cout << "4. Keluar\n";
        cout << "Pilih (1-4): ";
        /**********************************************************************/ 
        
        /* Input nilai Menu */ 
        cin >> menu;

        /**********************************************************************/
        /* Perulangan if else untuk memilih fitur program */ 
        if (menu == "1")
        {
            tampilkanStatus(parkir, n);
            kembali();
        } 
        else if (menu == "2")
        {
            parkirKendaraan(parkir, n);
            kembali();
        } 
        else if (menu == "3")
        {
            ambilKendaraan(parkir, n);
            kembali();
        } 
        else 
        {
            system("cls");
        }
        /**********************************************************************/

    } while (menu != "4");  // Tekan 4 untuk keluar

    return 0;
}

