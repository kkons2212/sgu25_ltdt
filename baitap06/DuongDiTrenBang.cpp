#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define FI "DuongDiTrenBang.INP" 
#define FO "DuongDiTrenBang.OUT"  

// Cấu trúc lưu thông tin mỗi ô trong bảng
struct Cell {
    int x, y;    // tọa độ ô
    int cost;    // tổng chi phí để đến ô này
    // Operator > dùng cho priority_queue kiểu min-heap
    bool operator>(const Cell &other) const {
        return cost > other.cost;
    }
};

const int INF = 1e9; // giá trị vô cực đại (dùng làm khởi tạo khoảng cách)
int dx[4] = {-1, 1, 0, 0}; // 4 hướng di chuyển: lên, xuống, trái, phải
int dy[4] = {0, 0, -1, 1};

int main() {
    // Mở file input/output
    freopen(FI, "r", stdin);
    freopen(FO, "w", stdout);

    int N, M;         // số hàng và cột của bảng
    int xi, yi;       // ô bắt đầu
    int xj, yj;       // ô kết thúc
    cin >> N >> M >> xi >> yi >> xj >> yj;

    // Nhập bảng chi phí đi qua các ô
    vector<vector<int>> A(N + 1, vector<int>(M + 1));
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            cin >> A[i][j];

    // Nếu ô đầu hoặc ô cuối là 0 → không thể đi
    if (A[xi][yi] == 0 || A[xj][yj] == 0) {
        cout << 0;
        return 0;
    }

    // Khởi tạo ma trận khoảng cách và ma trận truy vết
    vector<vector<int>> dist(N + 1, vector<int>(M + 1, INF));
    vector<vector<pair<int, int>>> prev(N + 1, vector<pair<int, int>>(M + 1, {-1, -1}));

    // Priority queue dùng cho thuật toán Dijkstra
    priority_queue<Cell, vector<Cell>, greater<Cell>> pq;
    dist[xi][yi] = 0;         // khoảng cách từ ô bắt đầu đến chính nó = 0
    pq.push({xi, yi, 0});     // đưa ô bắt đầu vào queue

    // Thuật toán Dijkstra
    while (!pq.empty()) {
        Cell u = pq.top();    // lấy ô có chi phí nhỏ nhất
        pq.pop();

        // Nếu chi phí này lớn hơn chi phí đã lưu → bỏ qua
        if (u.cost > dist[u.x][u.y]) continue;

        // Duyệt 4 ô kề
        for (int k = 0; k < 4; k++) {
            int nx = u.x + dx[k];
            int ny = u.y + dy[k];

            // Bỏ qua ô ngoài bảng
            if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
            // Bỏ qua ô không thể đi (giá trị 0)
            if (A[nx][ny] == 0) continue;

            // Tính chi phí đi đến ô kề
            int newCost = u.cost + A[nx][ny];

            // Không tính chi phí ô cuối
            if (make_pair(nx, ny) == make_pair(xj, yj)) newCost = u.cost;

            // Nếu tìm được đường đi rẻ hơn → cập nhật và push vào queue
            if (newCost < dist[nx][ny]) {
                dist[nx][ny] = newCost;
                prev[nx][ny] = {u.x, u.y};
                pq.push({nx, ny, newCost});
            }
        }
    }

    // Nếu ô cuối không thể đến → in 0
    if (dist[xj][yj] == INF) {
        cout << 0;
        return 0;
    }

    // Truy vết đường đi từ ô cuối về ô bắt đầu
    vector<pair<int, int>> path;
    for (pair<int, int> v = {xj, yj}; v.first != -1; v = prev[v.first][v.second])
        path.push_back(v);
    reverse(path.begin(), path.end()); // đảo ngược để từ đầu → cuối

    // In kết quả
    cout << 1 << "\n";                  // có đường đi
    cout << dist[xj][yj] << "\n";       // chi phí tổng
    for (auto [x, y] : path)            // in từng ô trong đường đi
        cout << x << " " << y << "\n";

    return 0;
}
