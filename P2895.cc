#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
const int M = 50005;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int m, nrange = 301, mrange = 301; // 由题意，超出300一定安全
int X[M], Y[M], T[M];
int unsafeTime[305][305]; // 每个格子的最早不安全时间
int arriveTime[305][305]; // 每个格子的最早抵达时间

// 原理：最早抵达时间小于最早不安全时间即可进行BFS扩展，率先抵达最早不安全时间为正无穷时即为答案

void initUnsafeTime() {
    memset(unsafeTime, 0x3f, sizeof unsafeTime); // 初始化不安全时间为正无穷，在算法竞赛中0x3f3f3f3f可以视为正无穷
    for (int i = 1; i <= m; i++) {
        // 本格子
        unsafeTime[X[i]][Y[i]] = min(unsafeTime[X[i]][Y[i]], T[i]);
        // 周围四个格子
        if (X[i] - 1 >= 0) unsafeTime[X[i] - 1][Y[i]] = min(unsafeTime[X[i] - 1][Y[i]], T[i]);
        if (Y[i] - 1 >= 0) unsafeTime[X[i]][Y[i] - 1] = min(unsafeTime[X[i]][Y[i] - 1], T[i]);
        unsafeTime[X[i] + 1][Y[i]] = min(unsafeTime[X[i] + 1][Y[i]], T[i]);
        unsafeTime[X[i]][Y[i] + 1] = min(unsafeTime[X[i]][Y[i] + 1], T[i]);
    }
}

void initArriveTime() {
    // 特判
    if (unsafeTime[0][0] == 0x3f3f3f3f) {
        cout << 0;
        return;
    }

    memset(arriveTime, -1, sizeof arriveTime);
    
    queue<pair<int, int>> q;
    q.push({0, 0});
    arriveTime[0][0] = 0;

    while (q.size()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        int now = arriveTime[x][y];
        for (int i = 0; i < 4; i++) {
            int xx = x + dx[i], yy = y + dy[i];
            if (xx < 0 || xx > nrange || yy < 0 || yy > mrange) // 范围外
                continue;
            if (arriveTime[xx][yy] != -1) // 已经访问过
                continue;
            if (unsafeTime[xx][yy] > now + 1) {
                if (unsafeTime[xx][yy] == 0x3f3f3f3f) { // 该格子永久安全
                    cout << now + 1;
                    return;
                }
                arriveTime[xx][yy] = now + 1;
                q.push({xx, yy});
            }
        }
    }

    cout << -1;
}

void solve() {
    initUnsafeTime();
    initArriveTime();
}

int main() {
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> X[i] >> Y[i] >> T[i];
    }
    solve();
    return 0;
}