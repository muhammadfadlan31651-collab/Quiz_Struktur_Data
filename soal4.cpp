#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int UKURAN = 20;

enum Status { KOSONG, TERISI, DIHAPUS };

struct Slot {
    long long key;     
    string value;      
    Status status;
    Slot() : key(0), value(""), status(KOSONG) {}
};

class HashTable {
private:
    Slot tabel[UKURAN];

    int hash1(long long key) const { return key % 20; }
    int hash2(long long key) const { return 19 - (key % 19); }

    int probe(long long key, int i) const {
        return (hash1(key) + (long long)i * hash2(key)) % UKURAN;
    }

public:
    void insert(long long key, const string& nama) {
        int slotTujuan = -1;
        int pertamaDihapus = -1;
        int jumlahCollision = 0;

        cout << "Insert " << key << " (" << nama << "): h1=" << hash1(key)
             << ", h2=" << hash2(key) << endl;

        for (int i = 0; i < UKURAN; i++) {
            int idx = probe(key, i);
            if (tabel[idx].status == TERISI) {
                if (tabel[idx].key == key) {
                    cout << "  Gagal: key " << key << " sudah ada di indeks " << idx << endl;
                    return;
                }
                jumlahCollision++;
                cout << "  Collision di indeks " << idx << " (berisi key "
                     << tabel[idx].key << "), probing i=" << i + 1 << endl;
            } else if (tabel[idx].status == DIHAPUS) {
                if (pertamaDihapus == -1) pertamaDihapus = idx;
            } else {
                slotTujuan = (pertamaDihapus != -1) ? pertamaDihapus : idx;
                break;
            }
        }
        if (slotTujuan == -1) slotTujuan = pertamaDihapus;

        if (slotTujuan == -1) {
            cout << "  Gagal: tabel penuh / tidak ada slot yang terjangkau probing." << endl;
            return;
        }
        tabel[slotTujuan].key = key;
        tabel[slotTujuan].value = nama;
        tabel[slotTujuan].status = TERISI;
        cout << "  Disimpan di indeks " << slotTujuan
             << " (collision: " << jumlahCollision << ")" << endl;
    }

    int cariIndeks(long long key) const {
        for (int i = 0; i < UKURAN; i++) {
            int idx = probe(key, i);
            if (tabel[idx].status == KOSONG) return -1;
            if (tabel[idx].status == TERISI && tabel[idx].key == key) return idx;
        }
        return -1;
    }

    void search(long long key) const {
        int idx = cariIndeks(key);
        if (idx == -1) cout << "Key " << key << " tidak ditemukan." << endl;
        else cout << "Ditemukan di indeks " << idx << ": " << tabel[idx].key
                  << " -> " << tabel[idx].value << endl;
    }

    void remove(long long key) {
        int idx = cariIndeks(key);
        if (idx == -1) {
            cout << "Key " << key << " tidak ditemukan, tidak ada yang dihapus." << endl;
            return;
        }
        cout << "Menghapus " << tabel[idx].key << " (" << tabel[idx].value
             << ") dari indeks " << idx << endl;
        tabel[idx].status = DIHAPUS; 
        tabel[idx].value = "";
    }

    void display() const {
        cout << "Indeks | Status | NIM        | Nama" << endl;
        cout << "-------+--------+------------+----------------" << endl;
        for (int i = 0; i < UKURAN; i++) {
            cout << (i < 10 ? "  " : " ") << i << "   | ";
            if (tabel[i].status == TERISI)
                cout << "isi    | " << tabel[i].key << " | " << tabel[i].value;
            else if (tabel[i].status == DIHAPUS)
                cout << "hapus  | -          | -";
            else
                cout << "kosong | -          | -";
            cout << endl;
        }
    }
};

void bersihkanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void ujiOtomatis(HashTable& ht) {
    struct { long long nim; const char* nama; } data[] = {
        {251401001, "Andi"},   {251401021, "Budi"},   {251401041, "Citra"},
        {251401005, "Dewi"},   {251401025, "Eko"},    {251401010, "Fitri"},
        {251401030, "Gilang"}, {251401050, "Hana"},   {251401017, "Indra"},
        {251401037, "Joko"},   {251401002, "Kiki"},   {251401022, "Lina"},
        {251401013, "Maya"},   {251401033, "Nanda"},  {251401019, "Oki"}
    };

    cout << "\n--- TAHAP 1: Insert 15 data ---" << endl;
    for (auto& d : data) ht.insert(d.nim, d.nama);

    cout << "\n--- TAHAP 2: Tampilkan tabel ---" << endl;
    ht.display();

    cout << "\n--- TAHAP 3: Search (data collision & data yang tidak ada) ---" << endl;
    ht.search(251401041); 
    ht.search(251401050);
    ht.search(251401099); 

    cout << "\n--- TAHAP 4: Remove ---" << endl;
    ht.remove(251401001);  
    ht.remove(251401099);  
    cout << "Cari data yang berada setelah slot terhapus pada rantai probing:" << endl;
    ht.search(251401021);
    ht.search(251401001);  

    cout << "\n--- TAHAP 5: Insert lagi (memakai slot bekas hapus) ---" << endl;
    ht.insert(251401061, "Putri"); 
    ht.insert(251401005, "Duplikat"); 

    cout << "\n--- TAHAP 6: Tabel akhir ---" << endl;
    ht.display();
}

int main() {
    HashTable ht;
    int pilihan;
    do {
        cout << "\n===== HASH TABLE DATA MAHASISWA (Double Hashing) =====" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Search" << endl;
        cout << "3. Remove" << endl;
        cout << "4. Display" << endl;
        cout << "5. Jalankan pengujian otomatis (15 data)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        if (!(cin >> pilihan)) {
            bersihkanInput();
            pilihan = -1;
            continue;
        }
        bersihkanInput();

        if (pilihan == 1) {
            long long nim;
            string nama;
            cout << "NIM  : ";
            if (!(cin >> nim) || nim < 0) {
                bersihkanInput();
                cout << "NIM harus berupa angka." << endl;
                continue;
            }
            bersihkanInput();
            cout << "Nama : ";
            getline(cin, nama);
            ht.insert(nim, nama);
        } else if (pilihan == 2 || pilihan == 3) {
            long long nim;
            cout << "NIM  : ";
            if (!(cin >> nim) || nim < 0) {
                bersihkanInput();
                cout << "NIM harus berupa angka." << endl;
                continue;
            }
            bersihkanInput();
            if (pilihan == 2) ht.search(nim);
            else ht.remove(nim);
        } else if (pilihan == 4) {
            ht.display();
        } else if (pilihan == 5) {
            ujiOtomatis(ht);
        } else if (pilihan != 0) {
            cout << "Menu tidak tersedia." << endl;
        }
    } while (pilihan != 0);

    cout << "Program selesai." << endl;
    return 0;
}
