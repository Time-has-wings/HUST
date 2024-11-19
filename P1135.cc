#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
const int N = 205;
int n, a, b;
int delta[N];

void BFS() {
    if (a == b) {
        cout << 0 << endl;
        return;
    }

    queue<pair<int, int>> q;
    bool vis[N];
    memset(vis, false, sizeof(vis));
    q.push({a, 0});
    vis[a] = true;
    while (q.size()) {
        int x = q.front().first, step = q.front().second;
        q.pop();
        int up = x + delta[x], down = x - delta[x];
        if (up <= n && vis[up] == false) {
            if (up == b) {
                cout << step + 1 << endl;
                return;
            }
            q.push({up, step + 1});
            vis[up] = true;
        }
        if (down >= 1 && vis[down] == false) {
            if (down == b) {
                cout << step + 1 << endl;
                return;
            }
            q.push({down, step + 1});
            vis[down] = true;
        }
    }

    cout << -1 << endl;
}

int main() {
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++) {
        cin >> delta[i];
    }
    BFS();
    return 0;
}