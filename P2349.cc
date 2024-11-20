#include <iostream>
#include <cstring>
#include <queue>

using namespace std;
const int N = 105, M = 4005, INF = 300 * 2005; // 根据题意设置INF

int n, m;
int h[N], e[M], ne[M], w[M], idx; // 链式前向星

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void spfa(int S, int dist[], int limit) { // S为源点 dist为距离数组 limit为限制的边
    bool exist[N]; // 是否在队列中
    for (int i = 1; i <= n; i++) // 初始化为无穷大
        dist[i] = INF;
    memset(exist, false, sizeof exist);

    queue<int> q;
    q.push(S);
    dist[S] = 0;
    exist[S] = true;

    while (q.size()) {
        int x = q.front();
        q.pop();
        exist[x] = false;

        for (int i = h[x]; ~i; i = ne[i]) {
            if (i == limit || i == limit + 1 || w[i] > w[limit]) // 不能走这条边和权重超出这条边的边
                continue;
            int y = e[i];
            if (dist[y] > dist[x] + w[i]) {
                dist[y] = dist[x] + w[i];
                if (!exist[y]) {
                    q.push(y);
                    exist[y] = true;
                }
            }
        }
    }
}

// 思路:枚举每条边i <a,b,weight>，求出满足以下两个限制的关于起点1和起点n的最短路，最后取dist1[a] + distn[b] + 2 * w[i]和dist1[b] + distn[a] + 2 * w[i]的最小值
// 1. 不能经过这条边
// 2. 不能经过这条边的反向边
// 3. 不能经过这条边的权重大于这条边的边
void solve() {
    int distS[N], distT[N];
    int res = INF;

    for (int i = 0; i < idx; i += 2) {
        int a = e[i], b = e[i ^ 1], limit = i;
        spfa(1, distS, limit);
        spfa(n, distT, limit);
        int cost = min(distS[a] + distT[b], distS[b] + distT[a]) + 2 * w[limit];
        res = min(res, cost);
    }
    cout << res << endl;
}

int main() {
    memset(h, -1, sizeof h); // 初始化链式前向星
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }
    solve();
    return 0;
}