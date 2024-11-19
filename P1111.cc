#include <iostream>
#include <algorithm>

using namespace std;
const int N = 1005, M = 100005;

int n, m;
struct ROAD {
    int x, y, t;
    
    bool operator < (const ROAD& road) const {
        return t < road.t;
    }
}road[M];

int fa[N];

void init() {
    for (int i = 1; i <= n; i++)
        fa[i] = i;
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y) {
    fa[find(x)] = find(y);
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> road[i].x >> road[i].y >> road[i].t;
    }
    sort(road + 1, road + m + 1);
    init();
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        int x = find(road[i].x), y = find(road[i].y);
        if (x != y) {
            unite(x, y);
            cnt ++;
            if (cnt == n - 1) { // 由于是最小生成树，所以边数为n-1
                cout << road[i].t << endl;
                return 0;
            }
        }
    }
    cout << -1 << endl;
    return 0;
}