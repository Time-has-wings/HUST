#include <iostream>

using namespace std;
const int N = 100005;

int m, n, a[N];

struct SEG {
    int l, r, MIN;
} tr[N << 2];

void pushup(int u) {
    tr[u].MIN = min(tr[u << 1].MIN, tr[u << 1 | 1].MIN);
}

void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) {
        tr[u].MIN = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

int query(int u, int l, int r) {
    if (l <= tr[u].l && tr[u].r <= r) {
        return tr[u].MIN;
    }
    int mid = (tr[u].l + tr[u].r) >> 1;
    int val = 0x3f3f3f3f;
    if (l <= mid) val = min(val, query(u << 1, l, r));
    if (r > mid) val = min(val, query(u << 1 | 1, l, r));
    return val;
}

int main() {
    cin >> m >> n; // 先输入m 后输入n
    for (int i = 1; i <= m; i++)
        cin >> a[i];
    build(1, 1, m);
    while (n --) {
        int st, ed;
        cin >> st >> ed;
        cout << query(1, st, ed) << ' ';
    }
    return 0;
}