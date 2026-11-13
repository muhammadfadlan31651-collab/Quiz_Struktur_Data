# Quiz_Struktur_Data

## Identitas

| | |
|---|---|
| Nama | Fadlan |
| NIM | *(251401017)* |
| Lab 4| *(Lab 4)* |
| Mata Kuliah | Struktur Data |

## Deskripsi Program

### 1. `soal1.cpp` - Sistem Pengelolaan Nilai Mahasiswa

Program berbasis menu untuk mengelola data nilai mahasiswa dengan dua struktur data:

- **Linked List** menyimpan data mahasiswa (NIM, nama, nilai). NIM yang sama tidak boleh didaftarkan dua kali.
- **Dynamic Array** menyimpan kumpulan nilai dan kapasitasnya otomatis berlipat dua saat penuh.

Fitur: tambah data, tampilkan data, urutkan nilai dengan **Insertion Sort**, cari mahasiswa berdasarkan NIM dengan **Linear Search** (menampilkan jumlah langkah), dan cari nilai tertentu dengan **Binary Search** (hanya bisa setelah nilai diurutkan).

### 2. `soal2.cpp` - Antrean dan Pengelolaan Buku Perpustakaan

Program berbasis menu untuk simulasi peminjaman buku di perpustakaan:

- **Queue** (FIFO) untuk antrean mahasiswa yang ingin meminjam buku.
- **Stack** (LIFO) untuk riwayat pengembalian buku, dengan pengembalian terakhir di posisi paling atas.
- **Binary Search Tree** untuk katalog ID buku beserta status tersedia atau sedang dipinjam.

Fitur: tambah antrean, proses peminjaman, kembalikan buku, tampilkan antrean dan riwayat, tambah dan cari ID buku, serta tampilkan traversal **Pre-Order**, **In-Order**, dan **Post-Order**.

### 3. `soal3.cpp` - Pencarian Rute di Lingkungan Kampus

Program berbasis menu yang memodelkan lingkungan kampus sebagai graf berbobot tak berarah dengan 6 simpul (A sampai F) dan **adjacency matrix**.

Fitur: tampilkan adjacency matrix, penelusuran graf dengan **BFS** dan **DFS**, serta pencarian rute terpendek beserta total jaraknya dengan **algoritma Dijkstra**.

### 4. `soal4.cpp` - Hash Table Data Mahasiswa

Program berbasis menu yang menyimpan data mahasiswa (NIM sebagai key, nama sebagai value) pada hash table berukuran 20 dengan **double hashing**. Penghapusan memakai status `DIHAPUS` (lazy deletion) agar rantai probing tidak terputus.

Fitur: insert (menampilkan proses collision), search, remove, display tabel, dan pengujian otomatis dengan 15 data.

## Struktur Folder

```
.
├── README.md
├── soal1.cpp
├── soal2.cpp
├── soal3.cpp
└── soal4.cpp
```

## Cara Menjalankan Program

Syarat: compiler **g++** yang mendukung C++11 atau lebih baru.

1. Buka terminal di folder proyek.
2. Kompilasi dan jalankan program yang diinginkan:

```bash
g++ -std=c++17 soal1.cpp -o soal1
./soal1

g++ -std=c++17 soal2.cpp -o soal2
./soal2

g++ -std=c++17 soal3.cpp -o soal3
./soal3

g++ -std=c++17 soal4.cpp -o soal4
./soal4
```

Di Windows, jalankan hasil kompilasi dengan `soal1.exe` (dan seterusnya).

3. Pilih menu dengan mengetik nomor menu lalu tekan Enter. Ketik `0` untuk keluar.

## Video Penjelasan

Video penjelasan keempat program beserta contoh hasil eksekusinya:

Tonton di Youtube : https://youtu.be/7aeGirK-DbA?si= berukur
