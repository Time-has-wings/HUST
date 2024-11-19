#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 105;

int F, V, val[N][N];
int f[N][N]; // f[i][j] 表示前i种花放在前j个瓶子中的最大值
pair<int, int>fa[N][N];

void solve() {
    memset(f, 0xcf, sizeof f); // 初始化为负无穷
    for (int i = 0; i <= V; i++) { // 0个花放在前i个瓶子中的最大值
        f[0][i] = 0;
    }

    for (int i = 1; i <= F; i ++) {
        for (int j = i; j <= V; j++) {
            if (f[i][j] < f[i][j - 1]) { // 第i种花不放在第j个瓶子中
                f[i][j] = f[i][j - 1];
                fa[i][j] = {i, j - 1};
            }
            if (f[i][j] < f[i - 1][j - 1] + val[i][j]) { // 第i种花放在第j的瓶子中
                f[i][j] = f[i - 1][j - 1] + val[i][j];
                fa[i][j] = {i - 1, j - 1};
            }

        }
    }

    int MAX = 0xcfcfcfcf;
    pair<int, int> pos;
    for (int i = F; i <= V; i++) {
        if (f[F][i] > MAX) {
            MAX = f[F][i];
            pos = {F, i};
        }
    }
    cout << MAX << endl;

    vector<int> ans;
    while (true) {
        pair<int, int> pa = fa[pos.first][pos.second];
        if (pa.first != pos.first) {
            ans.push_back(pos.second);
        }
        if (pa.first == 0)
            break;
        pos = pa;
    }
    reverse(ans.begin(), ans.end());
    for (auto it : ans) {
        cout << it << " ";
    }
}

int main() {
    cin >> F >> V;
    for (int i = 1; i <= F; i ++) {
        for (int j = 1; j <= V; j++) {
            cin >> val[i][j];
        }
    }
    solve();
    return 0;
}