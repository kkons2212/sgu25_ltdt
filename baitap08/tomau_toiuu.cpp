#include <iostream>
#include <vector>
using namespace std;


int n, m;                    // số đỉnh, số cạnh
vector<vector<int>> ke;       // danh sách kề
int best;                     // số màu tối thiểu cần tìm


void doc() {
    cin >> n >> m;
    ke.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        ke[u].push_back(v);
        ke[v].push_back(u);
    }
}

// ======= HÀM KIỂM TRA HỢP LỆ =======
bool hopLe(int u, int c, vector<int>& color) {
    for (int v : ke[u])
        if (color[v] == c) 
            return false; // không thể tô cùng màu với đỉnh kề
    return true;        // hợp lệ
}

// ======= HÀM BACKTRACKING =======
void thu(int u, int soMauDangCo, vector<int>& color) {
    if (u > n) { // đã tô xong tất cả các đỉnh
        if (soMauDangCo < best)
            best = soMauDangCo; // cập nhật số màu tối thiểu
        return;
    }

    // Thử tất cả màu từ 1 đến soMauDangCo + 1
    for (int c = 1; c <= soMauDangCo + 1; c++) {
        if (hopLe(u, c, color)) {  // nếu tô màu c được
            color[u] = c;          // tô màu
            thu(u + 1, max(soMauDangCo, c), color); // đệ quy cho đỉnh tiếp theo
            color[u] = 0;          // quay lui để thử màu khác
        }
    }
}

// ======= HÀM CHÍNH TO MÀU TỐI ƯU =======
void toMauToiUu() {
    best = n;                     // số màu tối đa ban đầu
    vector<int> color(n + 1, 0);  // chưa tô màu
    thu(1, 0, color);             // bắt đầu từ đỉnh 1

   // so mau toi uu
    cout<< best << "\n";
}

// ======= MAIN =======
int main() {
    freopen("tomau_toiuu.inp","r",stdin);
    doc();
    toMauToiUu();

    return 0;
}