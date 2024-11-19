#include <iostream>
#include <cmath>

using namespace std;
const int N = 30005;

int T;
int fa[N], sz[N], pos[N]; // fa[i]表示i的父亲节点，sz[i]表示i所在集合的大小，pos[i]表示舰队在集合中的位置

void init() {
    for (int i = 1; i < N; i ++)
        fa[i] = i, sz[i] = 1;
}

int find(int x) {
    if (x == fa[x]) return x;
    int pa = find(fa[x]);
    pos[x] += pos[fa[x]]; // pos[fa[x]]在递归中会被更新，随后根据pos[fa[x]]更新pos[x]
    return fa[x] = pa;
}

void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    fa[x] = y;
    pos[x] = sz[y];
    sz[y] += sz[x];
}

int main() {
    init();
    cin >> T;
    while (T --) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'M') {
            unite(x, y);
        }
        else {
            if (find(x) == find(y)) {
                cout << max(0, abs(pos[x] - pos[y]) - 1) << endl;
            }
            else {
                cout << -1 << endl;
            }
        }
    }
    return 0;
}