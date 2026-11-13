#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Antrean {
    string nama;
    int idBuku;
    Antrean* next;
};

class Queue {
private:
    Antrean* front;
    Antrean* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}
    ~Queue() {
        while (!kosong()) dequeue();
    }

    bool kosong() const { return front == nullptr; }

    void enqueue(const string& nama, int idBuku) {
        Antrean* baru = new Antrean{nama, idBuku, nullptr};
        if (rear == nullptr) front = rear = baru;
        else {
            rear->next = baru;
            rear = baru;
        }
    }

    bool dequeue(string* nama = nullptr, int* idBuku = nullptr) {
        if (kosong()) return false;
        Antrean* hapus = front;
        if (nama) *nama = hapus->nama;
        if (idBuku) *idBuku = hapus->idBuku;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete hapus;
        return true;
    }
    void tampil() const {
        if (kosong()) {
            cout << "Antrean kosong." << endl;
            return;
        }
        int no = 1;
        for (Antrean* p = front; p != nullptr; p = p->next)
            cout << no++ << ". " << p->nama << " (ingin meminjam buku ID "
                 << p->idBuku << ")" << endl;
    }
};

struct Riwayat {
    string nama;
    int idBuku;
    Riwayat* next;
};

class Stack {
private:
    Riwayat* top;

public:
    Stack() : top(nullptr) {}
    ~Stack() {
        while (top != nullptr) {
            Riwayat* hapus = top;
            top = top->next;
            delete hapus;
        }
    }

    void push(const string& nama, int idBuku) {
        top = new Riwayat{nama, idBuku, top};
    }

    void tampil() const {
        if (top == nullptr) {
            cout << "Belum ada riwayat pengembalian." << endl;
            return;
        }
        cout << "(paling atas = pengembalian terakhir)" << endl;
        int no = 1;
        for (Riwayat* p = top; p != nullptr; p = p->next)
            cout << no++ << ". " << p->nama << " mengembalikan buku ID "
                 << p->idBuku << endl;
    }
};

struct BSTNode {
    int id;
    bool tersedia;
    BSTNode* kiri;
    BSTNode* kanan;
};

class BST {
private:
    BSTNode* root;

    BSTNode* sisip(BSTNode* node, int id, bool& berhasil) {
        if (node == nullptr) {
            berhasil = true;
            return new BSTNode{id, true, nullptr, nullptr};
        }
        if (id < node->id) node->kiri = sisip(node->kiri, id, berhasil);
        else if (id > node->id) node->kanan = sisip(node->kanan, id, berhasil);
        else berhasil = false;
        return node;
    }

    void preOrder(BSTNode* n) const {
        if (!n) return;
        cout << n->id << " ";
        preOrder(n->kiri);
        preOrder(n->kanan);
    }
    void inOrder(BSTNode* n) const {
        if (!n) return;
        inOrder(n->kiri);
        cout << n->id << " ";
        inOrder(n->kanan);
    }
    void postOrder(BSTNode* n) const {
        if (!n) return;
        postOrder(n->kiri);
        postOrder(n->kanan);
        cout << n->id << " ";
    }
    void inOrderStatus(BSTNode* n) const {
        if (!n) return;
        inOrderStatus(n->kiri);
        cout << "   ID " << n->id << " - "
             << (n->tersedia ? "tersedia" : "sedang dipinjam") << endl;
        inOrderStatus(n->kanan);
    }
    void hancurkan(BSTNode* n) {
        if (!n) return;
        hancurkan(n->kiri);
        hancurkan(n->kanan);
        delete n;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { hancurkan(root); }

    bool tambah(int id) {
        bool berhasil = false;
        root = sisip(root, id, berhasil);
        return berhasil;
    }

    BSTNode* cari(int id) const {
        BSTNode* p = root;
        while (p != nullptr) {
            if (id == p->id) return p;
            p = (id < p->id) ? p->kiri : p->kanan;
        }
        return nullptr;
    }

    bool kosong() const { return root == nullptr; }

    void tampilTraversal() const {
        if (!root) {
            cout << "BST kosong." << endl;
            return;
        }
        cout << "Pre-Order  : "; preOrder(root);  cout << endl;
        cout << "In-Order   : "; inOrder(root);   cout << endl;
        cout << "Post-Order : "; postOrder(root); cout << endl;
    }

    void tampilIsi() const {
        if (!root) {
            cout << "BST kosong." << endl;
            return;
        }
        tampilTraversal();
        cout << "Status buku (urut ID):" << endl;
        inOrderStatus(root);
    }
};

void bersihkanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool bacaInt(const string& prompt, int& hasil) {
    cout << prompt;
    if (!(cin >> hasil)) {
        bersihkanInput();
        cout << "Input harus berupa angka." << endl;
        return false;
    }
    bersihkanInput();
    return true;
}

int main() {
    Queue antrean;
    Stack riwayat;
    BST buku;

    int awal[] = {50, 30, 70, 20, 40, 60, 80};
    for (int id : awal) buku.tambah(id);

    int pilihan;
    do {
        cout << "\n===== SISTEM ANTREAN & PENGELOLAAN BUKU PERPUSTAKAAN =====" << endl;
        cout << "1. Tambah mahasiswa ke antrean peminjaman" << endl;
        cout << "2. Proses peminjaman (layani antrean terdepan)" << endl;
        cout << "3. Kembalikan buku" << endl;
        cout << "4. Tampilkan antrean" << endl;
        cout << "5. Tampilkan riwayat pengembalian" << endl;
        cout << "6. Tambah ID buku ke BST" << endl;
        cout << "7. Cari ID buku" << endl;
        cout << "8. Tampilkan traversal & isi BST" << endl;
        cout << "0. Keluar" << endl;
        if (!bacaInt("Pilihan: ", pilihan)) {
            pilihan = -1;
            continue;
        }

        if (pilihan == 1) {
            string nama;
            int id;
            cout << "Nama mahasiswa: ";
            getline(cin, nama);
            if (!bacaInt("ID buku yang ingin dipinjam: ", id)) continue;
            antrean.enqueue(nama, id);
            cout << nama << " masuk antrean." << endl;

        } else if (pilihan == 2) {
            string nama;
            int id;
            if (!antrean.dequeue(&nama, &id)) {
                cout << "Antrean kosong." << endl;
                continue;
            }
            cout << "Melayani: " << nama << " (buku ID " << id << ")" << endl;
            BSTNode* b = buku.cari(id);
            if (b == nullptr) cout << "Gagal: buku ID " << id << " tidak ada di katalog." << endl;
            else if (!b->tersedia) cout << "Gagal: buku ID " << id << " sedang dipinjam." << endl;
            else {
                b->tersedia = false;
                cout << "Berhasil: " << nama << " meminjam buku ID " << id << "." << endl;
            }

        } else if (pilihan == 3) {
            string nama;
            int id;
            cout << "Nama mahasiswa: ";
            getline(cin, nama);
            if (!bacaInt("ID buku yang dikembalikan: ", id)) continue;
            BSTNode* b = buku.cari(id);
            if (b == nullptr) cout << "Buku ID " << id << " tidak ada di katalog." << endl;
            else if (b->tersedia) cout << "Buku ID " << id << " tidak sedang dipinjam." << endl;
            else {
                b->tersedia = true;
                riwayat.push(nama, id);
                cout << "Buku ID " << id << " berhasil dikembalikan oleh " << nama << "." << endl;
            }

        } else if (pilihan == 4) {
            cout << "\nAntrean peminjaman (FIFO):" << endl;
            antrean.tampil();

        } else if (pilihan == 5) {
            cout << "\nRiwayat pengembalian (LIFO):" << endl;
            riwayat.tampil();

        } else if (pilihan == 6) {
            int id;
            if (!bacaInt("ID buku baru: ", id)) continue;
            if (buku.tambah(id)) cout << "ID " << id << " ditambahkan ke BST." << endl;
            else cout << "ID " << id << " sudah ada." << endl;

        } else if (pilihan == 7) {
            int id;
            if (!bacaInt("ID buku yang dicari: ", id)) continue;
            BSTNode* b = buku.cari(id);
            if (b) cout << "Buku ID " << id << " ditemukan ("
                        << (b->tersedia ? "tersedia" : "sedang dipinjam") << ")." << endl;
            else cout << "Buku ID " << id << " tidak ditemukan." << endl;

        } else if (pilihan == 8) {
            cout << "\nIsi BST:" << endl;
            buku.tampilIsi();

        } else if (pilihan != 0) {
            cout << "Menu tidak tersedia." << endl;
        }
    } while (pilihan != 0);

    cout << "Program selesai." << endl;
    return 0;
}
