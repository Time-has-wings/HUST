#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;
const int mod = 80112002, N = 5005, M = 500005;
int n, m;

int h[N], e[M], ne[M], idx; // 链式前向星
int in[N], out[N], DP[N][N]; // 入度 出度 DP[i][j]表示以i为终点，j为起点的食物链总数

void add(int a, int b) { // 添加一条边a->b 被吃的->吃的
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void topSort() {
    vector<int> Bottom, Top; // 食物链最低端的所有生物 食物链最高端的所有生物
    queue<int>q;
    for (int i = 1; i <= n; i++) {
        if (!in[i]) q.push(i), Bottom.push_back(i), DP[i][i] = 1; // 初始化dp[i][i] = 1
        if (!out[i]) Top.push_back(i);
    }

    while (q.size()) {
        int x = q.front();
        q.pop();
        for (int i = h[x]; ~i; i = ne[i]) {
            int y = e[i];
            for (auto bottom : Bottom) {
                DP[y][bottom] = (DP[y][bottom] + DP[x][bottom]) % mod;
            }
            in[y]--;
            if (!in[y]) {
                q.push(y);
            }
        }
    }

    int res = 0;
    for (auto top : Top) {
        for (auto bottom : Bottom) {
            res = (res + DP[top][bottom]) % mod;
        }
    }
    cout << res << endl;
}

int main() {
    memset(h, -1, sizeof h); // 初始化链式前向星
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b; 
        cin >> a >> b;
        add(a, b);
        out[a]++, in[b]++; // 记录每个点的入度和出度
    }
    topSort();
    return 0;
}