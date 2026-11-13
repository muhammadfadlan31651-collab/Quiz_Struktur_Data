#include <iostream>
#include <string>
#include <limits>
using namespace std;

class DynamicArray {
private:
    double* data;
    int size;
    int capacity;

    void perbesar() {
        capacity *= 2;
        double* baru = new double[capacity];
        for (int i = 0; i < size; i++) baru[i] = data[i];
        delete[] data;
        data = baru;
    }

public:
    DynamicArray(int cap = 4) : size(0), capacity(cap) {
        data = new double[capacity];
    }
    ~DynamicArray() { delete[] data; }
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    void tambah(double nilai) {
        if (size == capacity) perbesar();
        data[size++] = nilai;
    }

    int getSize() const { return size; }
    int getCapacity() const { return capacity; }

    void insertionSort() {
        for (int i = 1; i < size; i++) {
            double kunci = data[i];
            int j = i - 1;
            while (j >= 0 && data[j] > kunci) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = kunci;
        }
    }
    int binarySearch(double target) const {
        int kiri = 0, kanan = size - 1;
        while (kiri <= kanan) {
            int tengah = kiri + (kanan - kiri) / 2;
            if (data[tengah] == target) return tengah;
            if (data[tengah] < target) kiri = tengah + 1;
            else kanan = tengah - 1;
        }
        return -1;
    }

    void tampil() const {
        if (size == 0) {
            cout << "(kosong)" << endl;
            return;
        }
        cout << "[ ";
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << "]" << endl;
    }
};
struct Node {
    string nim;
    string nama;
    double nilai;
    Node* next;
};

class DaftarMahasiswa {
private:
    Node* head;
    Node* tail;
    int jumlah;

public:
    DaftarMahasiswa() : head(nullptr), tail(nullptr), jumlah(0) {}
    ~DaftarMahasiswa() {
        while (head != nullptr) {
            Node* hapus = head;
            head = head->next;
            delete hapus;
        }
    }
    bool adaNIM(const string& nim) const {
        for (Node* p = head; p != nullptr; p = p->next)
            if (p->nim == nim) return true;
        return false;
    }

    void tambah(const string& nim, const string& nama, double nilai) {
        Node* baru = new Node{nim, nama, nilai, nullptr};
        if (head == nullptr) head = tail = baru;
        else {
            tail->next = baru;
            tail = baru;
        }
        jumlah++;
    }
    Node* linearSearch(const string& nim, int& langkah) const {
        langkah = 0;
        for (Node* p = head; p != nullptr; p = p->next) {
            langkah++;
            if (p->nim == nim) return p;
        }
        return nullptr;
    }

    void tampil() const {
        if (head == nullptr) {
            cout << "Belum ada data mahasiswa." << endl;
            return;
        }
        int no = 1;
        for (Node* p = head; p != nullptr; p = p->next) {
            cout << no++ << ". NIM: " << p->nim
                 << " | Nama: " << p->nama
                 << " | Nilai: " << p->nilai << endl;
        }
    }

    void tampilByNilai(double nilai) const {
        for (Node* p = head; p != nullptr; p = p->next)
            if (p->nilai == nilai)
                cout << "   -> " << p->nim << " | " << p->nama << endl;
    }
};

void bersihkanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    DaftarMahasiswa daftar;
    DynamicArray nilaiArr;
    bool sudahUrut = true; 

    struct { const char* nim; const char* nama; double nilai; } contoh[] = {
        {"2514010001", "Andi", 85},
        {"2514010002", "Budi", 70},
        {"2514010003", "Citra", 92},
        {"2514010004", "Dewi", 60},
        {"2514010005", "Eko", 78}
    };
    for (auto& c : contoh) {
        daftar.tambah(c.nim, c.nama, c.nilai);
        nilaiArr.tambah(c.nilai);
    }
    sudahUrut = false;

    int pilihan;
    do {
        cout << "\n===== SISTEM PENGELOLAAN NILAI MAHASISWA =====" << endl;
        cout << "1. Tambah data mahasiswa" << endl;
        cout << "2. Tampilkan data mahasiswa & nilai" << endl;
        cout << "3. Urutkan nilai/Insertion Sort" << endl;
        cout << "4. Cari mahasiswa berdasarkan NIM (Linear Search)" << endl;
        cout << "5. Cari nilai tertentu (Binary Search)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        if (!(cin >> pilihan)) {
            bersihkanInput();
            cout << "Input tidak valid." << endl;
            pilihan = -1;
            continue;
        }
        bersihkanInput();

        if (pilihan == 1) {
            string nim, nama;
            double nilai;
            cout << "NIM   : ";
            getline(cin, nim);
            if (daftar.adaNIM(nim)) {
                cout << "NIM sudah terdaftar." << endl;
                continue;
            }
            cout << "Nama  : ";
            getline(cin, nama);
            cout << "Nilai : ";
            if (!(cin >> nilai)) {
                bersihkanInput();
                cout << "Nilai harus berupa angka." << endl;
                continue;
            }
            bersihkanInput();
            daftar.tambah(nim, nama, nilai);
            nilaiArr.tambah(nilai);
            sudahUrut = false;
            cout << "Data berhasil ditambahkan." << endl;

        } else if (pilihan == 2) {
            cout << "\nData mahasiswa (Linked List):" << endl;
            daftar.tampil();
            cout << "\nKumpulan nilai (Dynamic Array, "
                 << (sudahUrut ? "sudah terurut" : "belum terurut")
                 << ", kapasitas " << nilaiArr.getCapacity() << "):" << endl;
            nilaiArr.tampil();

        } else if (pilihan == 3) {
            nilaiArr.insertionSort();
            sudahUrut = true;
            cout << "Nilai setelah diurutkan (kecil -> besar):" << endl;
            nilaiArr.tampil();

        } else if (pilihan == 4) {
            string nim;
            cout << "Masukkan NIM yang dicari: ";
            getline(cin, nim);
            int langkah;
            Node* hasil = daftar.linearSearch(nim, langkah);
            if (hasil) {
                cout << "Ditemukan (" << langkah << " langkah): "
                     << hasil->nim << " | " << hasil->nama
                     << " | Nilai: " << hasil->nilai << endl;
            } else {
                cout << "NIM tidak ditemukan (" << langkah << " langkah)." << endl;
            }

        } else if (pilihan == 5) {
            if (!sudahUrut) {
                cout << "Data nilai belum terurut. Urutkan dulu lewat menu 3." << endl;
                continue;
            }
            double target;
            cout << "Masukkan nilai yang dicari: ";
            if (!(cin >> target)) {
                bersihkanInput();
                cout << "Nilai harus berupa angka." << endl;
                continue;
            }
            bersihkanInput();
            int idx = nilaiArr.binarySearch(target);
            if (idx != -1) {
                cout << "Nilai " << target << " ditemukan pada indeks " << idx
                     << " (array terurut). Mahasiswa dengan nilai ini:" << endl;
                daftar.tampilByNilai(target);
            } else {
                cout << "Nilai " << target << " tidak ditemukan." << endl;
            }

        } else if (pilihan != 0) {
            cout << "Menu tidak tersedia." << endl;
        }
    } while (pilihan != 0);

    cout << "Program selesai." << endl;
    return 0;
}
