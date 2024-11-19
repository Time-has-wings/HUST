#include <iostream>

using namespace std;
const int N = 100005;

int n, Q, mod, a[N];

struct SEG {
    int l, r;
    long long add, mul, sum;
} tr[N << 2];

void pushup(int u) {
    tr[u].sum = (tr[u << 1].sum + tr[u << 1 | 1].sum) % mod;
}

void build(int u, int l, int r) {
    tr[u] = {l, r, 0, 1};
    if (l == r) {
        tr[u].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void pushdown(int u) {
    long long ADD = tr[u].add, MUL = tr[u].mul;
    tr[u].add = 0, tr[u].mul = 1;

    tr[u << 1].sum = ((tr[u << 1].sum * MUL % mod + ADD * (tr[u << 1].r - tr[u << 1].l + 1)) % mod) % mod;
    tr[u << 1].mul = (tr[u << 1].mul * MUL) % mod;
    tr[u << 1].add = (tr[u << 1].add * MUL + ADD) % mod;

    tr[u << 1 | 1].sum = ((tr[u << 1 | 1].sum * MUL % mod + ADD * (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1)) % mod) % mod;
    tr[u << 1 | 1].mul = (tr[u << 1 | 1].mul * MUL) % mod;
    tr[u << 1 | 1].add = (tr[u << 1 | 1].add * MUL + ADD) % mod;
}

void add(int u, int l, int r, long long k) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum = (tr[u].sum + k * (tr[u].r - tr[u].l + 1)) % mod;
        tr[u].add = (tr[u].add + k) % mod;
        return;
    }
    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (l <= mid) add(u << 1, l, r, k);
    if (r > mid) add(u << 1 | 1, l, r, k);
    pushup(u);
}

void mul(int u, int l, int r, long long k) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum = (tr[u].sum * k) % mod;
        tr[u].mul = (tr[u].mul * k) % mod;
        tr[u].add = (tr[u].add * k) % mod;
        return;
    }
    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (l <= mid) mul(u << 1, l, r, k);
    if (r > mid) mul(u << 1 | 1, l, r, k);
    pushup(u);
}

long long query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].sum;
    }
    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1;
    long long val = 0;
    if (l <= mid) val = (val + query(u << 1, l, r)) % mod;
    if (r > mid) val = (val + query(u << 1 | 1, l, r)) % mod;
    return val;
}

int main() {
    cin >> n >> Q >> mod;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build(1, 1, n);
    while (Q --) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            long long k;
            cin >> k;
            mul(1, l, r, k);
        }
        else if (op == 2) {
            long long k;
            cin >> k;
            add(1, l, r, k);
        }
        else {
            cout << query(1, l, r) << endl;
        }
    }
    return 0;
}