/* 
TUGAS BESAR ALGORITMA DAN PEMROGRAMAN
Judul: SMART PARKING SLOT SYSTEM

Kelompok 04
Kelas D3TK-48-01

Anggota:
Muhammad Rakha Syahvirchan 	607022400009
Teddy Agustio Mulky		    607022400053
Ibrahim fauzi Rahman		607022400009

Rabu, 01 Januari 2025
*/

#include <iostream>
#include <string>
using namespace std;

struct Slot {
    int no;         // nilai Nomor Slot
    string plat[4]; // nilai plat nomor kendaraan
    bool kosong;    // kosong tidaknya Slot
    int isi;        // isi (dalam integer)
    string jenis;   // jenis Kendaraan
    int masuk[4];   // Waktu masuk dalam menit total
};

int fungsiGaris()   // menampilkan garis untuk estetika
{
    cout<<"========================================================="<<endl;
    return 0;
}

int fungsiMenu(){   // menampilkan navigasi utama
    fungsiGaris();
    cout << "SELAMAT DATANG PADA PROGRAM PARKIR\n";
    fungsiGaris();

    cout << "\nMenu Parkir:\n";
    cout << "1. Tampilkan Status Parkir\n";
    cout << "2. Parkir Kendaraan\n";
    cout << "3. Ambil Kendaraan\n";
    cout << "4. Keluar\n";
    return 0;
}

int tampilkanStatus(Slot parkir[], int n) // fungsi menampilkan status parkir yang ada
{
    for (int i = 0; i < n; ++i) // perulangan untuk menampilkan slot parkir yang tersedia
    {
        if (parkir[i].kosong)   // jika slot kosong 
        {
            cout << "Slot " << parkir[i].no << " kosong.\n";
        } 
        else // jika slot terisi maka akan menampilakan NO SLOT, JENIS, JAM-MENIT, PLAT NOMOR
        {
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
    return 0;   // mengembalikan nilai 
}

int parkirKendaraan(Slot parkir[], int n) // fungsi parkir kendaraan; n = totalSlotParkir (nilai default = 8)
{
    /* DEKLARASI VARIABEL */
    int slot, totalMasuk;               // slot = slot parkir, totalMasuk = waktu total masuk kendaraan
    string platNomorKendaraan, jenis;   // plat nomor kendaraan dan jenis kendaraan
    float waktu;                        // waktu

    cout << "Jenis kendaraan (Mobil/Motor/Sepeda): ";
    cin >> jenis;                       // masukan jenis kendaraan

    // Menentukan jenis kendaraan
    bool mobil = (jenis == "Mobil" || jenis == "mobil" || jenis == "MOBIL");
    bool motor = (jenis == "Motor" || jenis == "motor" || jenis == "MOTOR");
    bool sepeda = (jenis == "Sepeda" || jenis == "sepeda" || jenis == "SEPEDA");

    /* Jika bukan mobil AND motor AND sepeda, maka muncul notifikasi*/
    if (!mobil && !motor && !sepeda) {
        cout << "Jenis kendaraan tidak dikenali.\n";
        system("cls"); // membersihkan terminal
		fungsiMenu();   // memanggil fungsi menu
		return parkirKendaraan(parkir, n); // kembali hanya ke tampilan ambil kendaraan (n = 8)
    }
    
    // menampilkan slot kosong untuk jenis yang dimasukkan oleh user
    cout << "Slot kosong untuk " << jenis << ":\n"; 

    bool ada = false; // deklarasi variabel ada dgn nilai false

    /* menampilkan slot yang kosong berdasarkan jenis kendaraan*/
    for (int i = 0; i < n; ++i) // n = 8 (nilai totalSlotParkir)
    {
        if (sepeda && (i == 6 || i == 7) && parkir[i].isi < 4) // Sepeda slot 6-7
        {
            cout << "Slot " << parkir[i].no << " tersedia (" << parkir[i].isi << "/4 sepeda).\n";
            ada = true;
        } 
        else if (motor && i >= 4 && i < 6 && parkir[i].isi < 2) // MOTOR slot 4-6
        {
            cout << "Slot " << parkir[i].no << " tersedia (" << parkir[i].isi << "/2 motor).\n";
            ada = true;
        } 
        else if (mobil && i < 4 && parkir[i].kosong)    // MOBIL slot 1-4
        {
            cout << "Slot " << parkir[i].no << " tersedia.\n";
            ada = true;
        }
    }

    if (!ada) // jika ada = false maka print tidak ada slot kosong
    {
        cout << "Tidak ada slot kosong.\n";
        return -1;  // mengembalikan nilai jika tidak ada elemen yang tidak ditemukan
    }


    cout << "Pilih slot: "; // pengguna memilih slot
    cin >> slot;
    
    cout << "Plat nomor: "; // pengguna memilih plat
    cin.ignore();           // mengabaikan masukan
    getline(cin, platNomorKendaraan);   // memasukan nilai platnomor kendaraan, pakai getline karena string
    
    cout << "Waktu masuk (jam.menit, contoh: 8.30): "; // pengguna memasukan waktu masuk
    cin >> waktu;

    /* Konversi waktu masuk dari FLOAT ke INTEGER*/
    int jam = static_cast<int>(waktu);
    int menit = static_cast<int>((waktu - jam) * 100);
    totalMasuk = (jam * 60) + menit;

    /* Memilih array variabel parkir dengan indeks dari 0*/
    int idx = slot - 1;
    parkir[idx].plat[parkir[idx].isi] = platNomorKendaraan; // memasukan nilai platNomorKendaraan ke parkir.plat
    parkir[idx].masuk[parkir[idx].isi] = totalMasuk;        // memasukan nilai totalMasuk ke parkir.masuk
    parkir[idx].isi++;                                      // increment nilai isi 
    parkir[idx].kosong = false;                             // mengubah nilai parkir.kosong = false
    parkir[idx].jenis = jenis;                              // memasukan nilai jenis ke parkir.jenis

    /* menampilkan hasil akhir dari yang dimasukan user */
    cout << jenis << " dengan plat " << platNomorKendaraan << " diparkir di slot " << slot
         << " pada " << jam << ":" << (menit < 10 ? "0" : "") << menit << ".\n";
    
    return 0; // mengembalikan nilai
}

int ambilKendaraan(Slot parkir[], int n)    // fungsi ambil kendaraan; n = totalSlotParkir (nilai default = 8)
{
    string platNomor;   // variabel untuk menyimpan PLAT NOMOR
    float waktuKeluar;  // variabel untuk menyimpan WAKTU KELUAR KENDARAAN
    int totalKeluar;    // variabel untuk menyimpan PERHITUNGAN WAKTU KELUAR KENDARAAN

    cout << "Plat nomor kendaraan: ";
    getline(cin ,platNomor);    // menginput PLAT NOMOR

    for (int i = 0; i < n; ++i) // perulangan sebanyak nilai totalSlotParkir (nilai default = 8)
    {
        for (int j = 0; j < parkir[i].isi; ++j) {
            if (parkir[i].plat[j] == platNomor)     // Jika input PLAT NOMOR == PLAT NOMOR YANG TERPARKIR
            {
                cout << "Waktu keluar (jam.menit, contoh: 10.45): ";
                cin >> waktuKeluar;                 // input WAKTU KELUAR KENDARAAN

                /* KONVERSI FLOAT KE INTEGER */
                int jam = static_cast<int>(waktuKeluar);
                int menit = static_cast<int>((waktuKeluar - jam) * 100);

                totalKeluar = (jam * 60) + menit;   // perhitungan Nilai Total Keluar (konversi jam ke menit)

                int totalMasuk = parkir[i].masuk[j];    // TOTAL MASUK = Nilai dari variabel parkir.masuk
                int durasi = totalKeluar - totalMasuk;  // perhitungan DURASI = WAKTU TOTAL KELUAR - WAKTU TOTAL MASUK

                if (durasi < 0) durasi += 1440;     // jika durasi kurang dari 0 maka durasi + 1440

                int biaya = 0;  // deklarasi variabel BIAYA

                /* PERHITUNGAN BIAYA PARKIR. MOBIL = 5000, MOTOR = 2000, SEPEDA = 500*/

                if (parkir[i].jenis == "Mobil" || parkir[i].jenis == "mobil" || parkir[i].jenis == "MOBIL") 
                {
                    biaya = (durasi / 60) * 5000;
                } 
                else if (parkir[i].jenis == "Motor" || parkir[i].jenis == "motor" || parkir[i].jenis == "MOTOR") 
                {
                    biaya = (durasi / 60) * 2000;
                } 
                else if (parkir[i].jenis == "Sepeda" || parkir[i].jenis == "sepeda" || parkir[i].jenis == "SEPEDA") 
                {
                    biaya = (durasi / 60) * 500;
                }

                /* MENAMPIKAN BIAYA PARKIR */
                fungsiGaris();
                cout << "Kendaraan dengan plat " << platNomor << " diambil dari slot " << parkir[i].no << ".\n";
                cout << "Durasi: " << durasi / 60 << " jam " << durasi % 60 << " menit.\n";
                cout << "Biaya: Rp" << biaya << ".\n";
                fungsiGaris();

                /* MENGATUR ULANG NILAI VARIABEL DARI OBJEK PARKIR */
                for (int k = j; k < parkir[i].isi - 1; ++k) {
                    parkir[i].plat[k] = parkir[i].plat[k + 1];
                    parkir[i].masuk[k] = parkir[i].masuk[k + 1];
                }
                parkir[i].isi--;
                if (parkir[i].isi == 0) {
                    parkir[i].kosong = true;
                    parkir[i].jenis = "";
                }
                return -1; // mengembalikan jika elemen tidak ditemukan
            }
        }
    }
    cout << "Plat nomor tidak ditemukan.\n";
    system("cls"); 
	fungsiMenu();
    return ambilKendaraan(parkir, n);
}

void kembali()      // fungsi kembali ke menu
{
    cout << "\nTekan Enter untuk kembali ke menu...\n";
    
    string inputExit ;  // Deklarasi variabel inputExit untuk menyimpan masukan user
    cin.clear();        // menghabus nilai masukan user
    cin.ignore();       // mengabaikan masukan

    getline(cin, inputExit);    // meminta memasukan nilai inputExit
    system("cls");              // membersihkan layar terminal
}

int main() // fungsi program utama
{
    int totalSlotParkir = 8;          // Inisialisasi Variabel totalSlotParkir dengan Nilai 8 (Jumlah Parkir yang tersedia)
    Slot parkir[totalSlotParkir];     // totalSlotParkir menjadi nilai jumlah array object parkir

    for (int i = 0; i < totalSlotParkir; ++i) // mengatur nilai variabel dari struct parkir ketika program mulai
    {   
        parkir[i].no = i + 1;           // nilai dimulai dari 1 (jangan 0)
        parkir[i].kosong = true;        // dimulai true karena slot parkir kosong
        parkir[i].isi = 0;              // nilai 0 karena belum terisi
        parkir[i].jenis = "";           // nilai jenis belum terisi
    }

    string menu;                // inisialisasi variabel Menu untuk menyimpan masukkan pengguna

    do // Perulangan Do-While agar program jalan terus-menerus
    {
        fungsiGaris();
        cout << "\tSELAMAT DATANG PADA PROGRAM PARKIR\n";
        fungsiGaris();

        cout << "\nMenu Parkir:\n";
        cout << "1. Tampilkan Status Parkir\n";
        cout << "2. Parkir Kendaraan\n";
        cout << "3. Ambil Kendaraan\n";
        cout << "4. Keluar\n";
        cout << "Pilih (1-4): ";

        cin >> menu;            // Input pilihan menu user

        if (menu == "1")        // Jika input = 1
        {
            tampilkanStatus(parkir, totalSlotParkir);
            kembali();
        } 
        else if (menu == "2")   // Jika input = 2
        {
            parkirKendaraan(parkir, totalSlotParkir);
            kembali();
        } 
        else if (menu == "3")   // Jika input = 3
        {
            ambilKendaraan(parkir, totalSlotParkir);
            kembali();
        } 
        else {
            system("cls");      // membersihkan layar terminal
        }

    } while (menu != "4");      // Jika input user salah

    return 0;
}