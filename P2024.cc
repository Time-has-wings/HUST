#include <iostream>

using namespace std;
const int N = 50005;

int n, K;
int fa[N * 3], ans = 0; // fa[x]表示x的同类，fa[x + n]表示x吃的集合，fa[x + 2 * n]表示x被吃的集合

void init() {
    for (int i = 1; i <= n * 3; i++)
        fa[i] = i;
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y) {
    fa[find(x)] = find(y);
}

int main() {
    cin >> n >> K;
    init();

    while (K --) {
        int op, x, y;
        cin >> op >> x >> y;
        if (x > n || y > n) {
            ans ++;
        }
        else if (op == 2 && x == y) {
            ans ++;
        }
        else {
            if (op == 1) {
                // 判断是否已经确定不是同类
                if (find(x) == find(y + n) || find(x) == find(y + 2 * n)) {
                    ans ++;
                }
                else {
                    unite(x, y);
                    unite(x + n, y + n);
                    unite(x + 2 * n, y + 2 * n);
                }
            }
            else {
                // 判断是否已经确定不是x吃y的关系
                if (find(x) == find(y) || find(x) == find(y + n)) {
                    ans ++;
                }
                else {
                    unite(x, y + 2 * n);
                    unite(x + n, y);
                    unite(x + 2 * n, y + n);
                }
            }
        }
    }
    cout << ans;
    return 0;
}