#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Class parent untuk data dasar pengguna
class User {
protected:
    string idUser;
    string nama;

public:
    User(string id, string n) : idUser(id), nama(n) {}
    virtual ~User() {}

    void setNama(string n) { nama = n; }
    string getNama() { return nama; }
    void setIdUser(string id) { idUser = id; }
    string getIdUser() { return idUser; }
};

// Class child yang mewarisi properti dari class User
class Tamu : public User {
private:
    string nomorKamar;

public:
    Tamu(string id, string n, string kamar) : User(id, n), nomorKamar(kamar) {}
    ~Tamu() {}

    void setNomorKamar(string kamar) { nomorKamar = kamar; }
    string getNomorKamar() { return nomorKamar; }
};

// Class untuk mengelola entitas ruangan dan status ketersediaannya
class Kamar {
private:
    string nomorKamar;
    bool isKosong;

public:
    Kamar(string nomor) : nomorKamar(nomor), isKosong(true) {}
    ~Kamar() {}

    string getNomorKamar() { return nomorKamar; }
    bool getStatus() { return isKosong; }
    void setStatus(bool status) { isKosong = status; }
};

// Class utama untuk menampung vector dan menjalankan operasi CRUD
class SistemHotel {
private:
    vector<Kamar> daftarKamar;
    vector<Tamu> daftarTamu;

public:
    SistemHotel() {
        daftarKamar.push_back(Kamar("101"));
        daftarKamar.push_back(Kamar("102"));
        daftarKamar.push_back(Kamar("103"));
        daftarKamar.push_back(Kamar("201"));
        daftarKamar.push_back(Kamar("202"));
    }
    ~SistemHotel() {}

    // Fungsi Create: Memasukkan data tamu baru ke kamar yang kosong
    void tambahData() {
        string id, nama, kamarPilihan;
        cout << "\nMasukkan ID Tamu: "; cin >> id;
        cin.ignore();
        cout << "Masukkan Nama Tamu: "; getline(cin, nama);

        cout << "Kamar Tersedia: ";
        bool adaKosong = false;
        for (int i = 0; i < daftarKamar.size(); i++) {
            if (daftarKamar[i].getStatus()) {
                cout << daftarKamar[i].getNomorKamar() << " ";
                adaKosong = true;
            }
        }
        cout << endl;

        if (!adaKosong) {
            cout << "Maaf, semua kamar penuh!\n";
            return;
        }

        cout << "Pilih Nomor Kamar: "; cin >> kamarPilihan;

        for (int i = 0; i < daftarKamar.size(); i++) {
            if (daftarKamar[i].getNomorKamar() == kamarPilihan && daftarKamar[i].getStatus()) {
                daftarKamar[i].setStatus(false);
                daftarTamu.push_back(Tamu(id, nama, kamarPilihan));
                cout << "Check-in berhasil!\n";
                return;
            }
        }
        cout << "Kamar tidak valid atau sudah terisi.\n";
    }

    // Fungsi Read: Menampilkan daftar seluruh tamu yang sedang menginap
    void tampilData() {
        if (daftarTamu.empty()) {
            cout << "\nTidak ada tamu saat ini.\n";
            return;
        }
        cout << "\n--- Daftar Tamu ---\n";
        for (int i = 0; i < daftarTamu.size(); i++) {
            cout << "ID: " << daftarTamu[i].getIdUser() 
                 << " | Nama: " << daftarTamu[i].getNama() 
                 << " | Kamar: " << daftarTamu[i].getNomorKamar() << "\n";
        }
    }

    // Fungsi Update: Mengubah data nama tamu berdasarkan pencarian ID
    void editData() {
        if (daftarTamu.empty()) {
            cout << "\nBelum ada data tamu.\n";
            return;
        }
        string idCari;
        cout << "\nMasukkan ID Tamu yang ingin diedit: "; cin >> idCari;
        
        for (int i = 0; i < daftarTamu.size(); i++) {
            if (daftarTamu[i].getIdUser() == idCari) {
                string namaBaru;
                cin.ignore();
                cout << "Masukkan Nama Baru: "; getline(cin, namaBaru);
                daftarTamu[i].setNama(namaBaru);
                cout << "Data berhasil diubah!\n";
                return;
            }
        }
        cout << "ID Tamu tidak ditemukan.\n";
    }

    // Fungsi Delete: Menghapus data tamu dan mengembalikan status kamar
    void hapusData() {
        if (daftarTamu.empty()) {
            cout << "\nTidak ada tamu yang menginap.\n";
            return;
        }
        string nomorKamarKeluar;
        cout << "\nMasukkan Nomor Kamar untuk Check-out: "; cin >> nomorKamarKeluar;

        for (int i = 0; i < daftarTamu.size(); i++) {
            if (daftarTamu[i].getNomorKamar() == nomorKamarKeluar) {
                for (int j = 0; j < daftarKamar.size(); j++) {
                    if (daftarKamar[j].getNomorKamar() == nomorKamarKeluar) {
                        daftarKamar[j].setStatus(true);
                        break;
                    }
                }
                daftarTamu.erase(daftarTamu.begin() + i);
                cout << "Check-out berhasil!\n";
                return;
            }
        }
        cout << "Kamar tidak ditemukan atau sudah kosong.\n";
    }

    // Fungsi antarmuka loop konsol untuk navigasi menu pengguna
    void jalankanMenu() {
        int pilihan;
        do {
            cout << "\n=== SISTEM RESERVASI HOTEL ===\n";
            cout << "1. Tambah Data\n2. Tampil Data\n3. Edit Data\n4. Hapus Data\n5. Keluar\nPilihan: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1: tambahData(); break;
                case 2: tampilData(); break;
                case 3: editData(); break;
                case 4: hapusData(); break;
                case 5: break;
                default: cout << "Pilihan tidak valid!\n";
            }
        } while (pilihan != 5);
    }
};

// Titik awal eksekusi program C++
int main() {
    SistemHotel hotel;
    hotel.jalankanMenu();
    return 0;
}