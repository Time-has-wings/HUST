#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
const int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
const int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};
int n, m, X, Y;

void solve() {
    int ans[405][405];
    memset(ans, -1, sizeof ans);
    queue<pair<int, int>>q;
    q.push({X, Y});
    ans[X][Y] = 0;
    while (q.size()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int i = 0; i < 8; i++) {
            int xx = x + dx[i], yy = y + dy[i];
            if (xx < 1 || xx > n || yy < 1 || yy > m) // 是否在棋盘内
                continue;
            if (ans[xx][yy] == -1) { // 是否已经访问过
                ans[xx][yy] = ans[x][y] + 1;
                q.push({xx, yy});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    cin >> n >> m >> X >> Y;
    solve();
    return 0;
}