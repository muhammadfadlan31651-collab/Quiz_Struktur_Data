#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <cctype>
#include <limits>
using namespace std;

const int V = 6; 

class Graph {
private:
    int adj[V][V];

public:
    Graph() {
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++) adj[i][j] = 0;
    }

    void tambahSisi(int u, int v, int bobot) {
        adj[u][v] = bobot;
        adj[v][u] = bobot; 
    }

    void tampilMatrix() const {
        cout << "Adjacency Matrix:" << endl << "   ";
        for (int i = 0; i < V; i++) cout << char('A' + i) << "  ";
        cout << endl;
        for (int i = 0; i < V; i++) {
            cout << char('A' + i) << "  ";
            for (int j = 0; j < V; j++) cout << adj[i][j] << "  ";
            cout << endl;
        }
    }

    void bfs(int mulai) const {
        bool dikunjungi[V] = {false};
        queue<int> q;
        dikunjungi[mulai] = true;
        q.push(mulai);
        cout << "BFS dari " << char('A' + mulai) << ": ";
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << char('A' + u) << " ";
            for (int v = 0; v < V; v++) {
                if (adj[u][v] && !dikunjungi[v]) {
                    dikunjungi[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
    }

    void dfsRekursif(int u, bool dikunjungi[]) const {
        dikunjungi[u] = true;
        cout << char('A' + u) << " ";
        for (int v = 0; v < V; v++)
            if (adj[u][v] && !dikunjungi[v]) dfsRekursif(v, dikunjungi);
    }

    void dfs(int mulai) const {
        bool dikunjungi[V] = {false};
        cout << "DFS dari " << char('A' + mulai) << ": ";
        dfsRekursif(mulai, dikunjungi);
        cout << endl;
    }

    void dijkstra(int awal, int tujuan) const {
        int jarak[V];
        int induk[V];
        bool selesai[V];
        for (int i = 0; i < V; i++) {
            jarak[i] = INT_MAX;
            induk[i] = -1;
            selesai[i] = false;
        }
        jarak[awal] = 0;

        for (int count = 0; count < V; count++) {
            int u = -1;
            for (int i = 0; i < V; i++)
                if (!selesai[i] && jarak[i] != INT_MAX && (u == -1 || jarak[i] < jarak[u]))
                    u = i;
            if (u == -1) break;
            selesai[u] = true;

            for (int v = 0; v < V; v++) {
                if (adj[u][v] && !selesai[v] && jarak[u] + adj[u][v] < jarak[v]) {
                    jarak[v] = jarak[u] + adj[u][v];
                    induk[v] = u;
                }
            }
        }

        if (jarak[tujuan] == INT_MAX) {
            cout << "Tidak ada rute dari " << char('A' + awal)
                 << " ke " << char('A' + tujuan) << "." << endl;
            return;
        }

        vector<int> jalur;
        for (int v = tujuan; v != -1; v = induk[v]) jalur.push_back(v);
        reverse(jalur.begin(), jalur.end());

        cout << "Rute terpendek: ";
        for (size_t i = 0; i < jalur.size(); i++) {
            cout << char('A' + jalur[i]);
            if (i + 1 < jalur.size()) cout << " -> ";
        }
        cout << endl << "Total jarak   : " << jarak[tujuan] << endl;
    }
};

int bacaVertex(const char* prompt) {
    cout << prompt;
    char c;
    if (!(cin >> c)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    c = toupper(c);
    if (c < 'A' || c >= 'A' + V) {
        cout << "Vertex tidak valid (pilih A sampai F)." << endl;
        return -1;
    }
    return c - 'A';
}

int main() {
    Graph g;
    g.tambahSisi(0, 1, 4); 
    g.tambahSisi(0, 2, 2); 
    g.tambahSisi(1, 2, 1); 
    g.tambahSisi(1, 3, 5); 
    g.tambahSisi(1, 4, 3); 
    g.tambahSisi(2, 3, 8); 
    g.tambahSisi(2, 4, 6); 
    g.tambahSisi(3, 4, 2); 
    g.tambahSisi(3, 5, 4); 
    g.tambahSisi(4, 5, 3); 

    int pilihan;
    do {
        cout << "\n===== PENCARIAN RUTE DI LINGKUNGAN KAMPUS =====" << endl;
        cout << "1. Tampilkan adjacency matrix" << endl;
        cout << "2. Telusuri graf dengan BFS" << endl;
        cout << "3. Telusuri graf dengan DFS" << endl;
        cout << "4. Cari rute terpendek (Dijkstra)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = -1;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pilihan == 1) {
            g.tampilMatrix();
        } else if (pilihan == 2 || pilihan == 3) {
            int s = bacaVertex("Vertex awal (A-F): ");
            if (s == -1) continue;
            if (pilihan == 2) g.bfs(s);
            else g.dfs(s);
        } else if (pilihan == 4) {
            int s = bacaVertex("Vertex awal   (A-F): ");
            if (s == -1) continue;
            int t = bacaVertex("Vertex tujuan (A-F): ");
            if (t == -1) continue;
            g.dijkstra(s, t);
        } else if (pilihan != 0) {
            cout << "Menu tidak tersedia." << endl;
        }
    } while (pilihan != 0);

    cout << "Program selesai." << endl;
    return 0;
}
