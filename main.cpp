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

void fungsiGaris(){
    cout << "=================================================\n";
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
    string p;
    float waktuKeluar;
    int totalKeluar;

    cout << "Plat nomor kendaraan: ";
    cin.ignore();
    getline(cin, p);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < parkir[i].isi; ++j) {
            if (parkir[i].plat[j] == p) {
                cout << "Waktu keluar (jam.menit, contoh: 10.45): ";
                cin >> waktuKeluar;

                int jam = static_cast<int>(waktuKeluar);
                int menit = static_cast<int>((waktuKeluar - jam) * 100);
                totalKeluar = (jam * 60) + menit;

                int totalMasuk = parkir[i].masuk[j];
                int durasi = totalKeluar - totalMasuk;
                if (durasi < 0) durasi += 1440;

                int biaya = 0;
                if (parkir[i].jenis == "Mobil" || parkir[i].jenis == "mobil" || parkir[i].jenis == "MOBIL") {
                    biaya = (durasi / 60) * 5000;
                } else if (parkir[i].jenis == "Motor" || parkir[i].jenis == "motor" || parkir[i].jenis == "MOTOR") {
                    biaya = (durasi / 60) * 2000;
                } else if (parkir[i].jenis == "Sepeda" || parkir[i].jenis == "sepeda" || parkir[i].jenis == "SEPEDA") {
                    biaya = (durasi / 60) * 500;
                }

                fungsiGaris();
                cout << "Kendaraan dengan plat " << p << " diambil dari slot " << parkir[i].no << ".\n";
                cout << "Durasi: " << durasi / 60 << " jam " << durasi % 60 << " menit.\n";
                cout << "Biaya: Rp" << biaya << ".\n";
                fungsiGaris();

                for (int k = j; k < parkir[i].isi - 1; ++k) {
                    parkir[i].plat[k] = parkir[i].plat[k + 1];
                    parkir[i].masuk[k] = parkir[i].masuk[k + 1];
                }
                parkir[i].isi--;
                if (parkir[i].isi == 0) {
                    parkir[i].kosong = true;
                    parkir[i].jenis = "";
                }
                return 0;
            }
        }
    }

    cout << "Plat nomor tidak ditemukan.\n";
    return -1;
}

void kembali() {
    cout << "\nTekan Enter untuk kembali ke menu...\n";
    cin.ignore();
    cin.get();
    system("cls");
}

int main() {
    int n = 8;
    Slot parkir[n];

    for (int i = 0; i < n; ++i) {
        parkir[i].no = i + 1;
        parkir[i].kosong = true;
        parkir[i].isi = 0;
        parkir[i].jenis = "";
    }

    int menu;
    do {
        fungsiGaris();
        cout << "\tSELAMAT DATANG PADA PROGRAM PARKIR\n";
        fungsiGaris();

        cout << "\nMenu Parkir:\n";
        cout << "1. Tampilkan Status Parkir\n";
        cout << "2. Parkir Kendaraan\n";
        cout << "3. Ambil Kendaraan\n";
        cout << "4. Keluar\n";
        cout << "Pilih (1-4): ";
        cin >> menu;

        switch (menu) {
            case 1:
                tampilkanStatus(parkir, n);
                kembali();
                break;
            case 2:
                parkirKendaraan(parkir, n);
                kembali();
                break;
            case 3:
                ambilKendaraan(parkir, n);
                kembali();
                break;
            case 4:
                cout << "Keluar.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (menu != 4);

    return 0;
}

