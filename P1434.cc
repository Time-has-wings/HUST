#include<iostream>
#include<algorithm>

using namespace std;
const int N = 105, dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

int R, C, h[N][N], DP[N][N];

struct NODE {
    int x, y, h, length;

    bool operator < (const NODE& node) const {
        return h > node.h;
    }
} a[N * N];

void solve() {
    sort(a + 1, a + R * C + 1);

    for (int i = 1; i <= R * C; i++) {
        int x = a[i].x, y = a[i].y;
        for (int k = 0; k < 4; k++) {
            int xx = x + dx[k], yy = y + dy[k];
            if (xx < 1 || xx > R || yy < 1 || yy > C) // 不合法
                continue;
            if (h[x][y] > h[xx][yy]) { // (xx, yy)比(x, y)低，故而(xx, yy)可以由(x, y)直接得来，由此由(x, y)更新(xx, yy)
                DP[xx][yy] = max(DP[xx][yy], DP[x][y] + 1);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            ans = max(ans, DP[i][j]);
        }
    }
    cout << ans + 1; // 由于DP[i][j]表示的是(i, j)为终点的最长路径，所以最终答案需要+1，即加上(i, j)本身
}

int main() {
	cin >> R >> C;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> h[i][j];
            a[(i - 1) * C + j] = {i, j, h[i][j], 1};
		}
	}
    solve();
	return 0;
}