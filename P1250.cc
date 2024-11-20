#include <iostream>
#include <cstring>
#include <queue>

using namespace std;
const int N = 30005, M = 5003 + N * 2;

int n, m;
int h[N], e[M], ne[M], w[M], idx; // 链式前向星
int dist[N]; // 最长路

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void spfa() {
    bool exist[N];
    memset(dist, -1, sizeof dist);
    memset(exist, false, sizeof exist);

    queue<int> q;
    q.push(0);
    exist[0] = true;
    dist[0] = 0;
    
    while (q.size()) {
        int x = q.front();
        q.pop();
        exist[x] = false;

        for (int i = h[x]; ~i; i = ne[i]) {
            int y = e[i];
            if (dist[y] < dist[x] + w[i]) { // 求最短路
                dist[y] = dist[x] + w[i];
                if (!exist[y]) {
                    q.push(y);
                    exist[y] = true;
                }
            }
        }
    }
}

int main() {
    memset(h, -1, sizeof h); // 初始化链式前向星
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a > b) swap(a, b); // 保证a < b
        // 增添不等式 sum[b] >= sum[a - 1] + c
        add(a - 1, b, c);
    }
    // 增添不等式 sum[i + 1] >= sum[i] + 0
    for (int i = 0; i < n; i++)
        add(i, i + 1, 0);
    // 增添不等式 sum[i] >= sum[i + 1] - 1(即sum[i + 1] <= sum[i] + 1)
    for (int i = 0; i < n; i++)
        add(i + 1, i, -1);
    spfa();
    cout << dist[n] << endl;
    return 0;
}