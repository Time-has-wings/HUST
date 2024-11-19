#include<iostream>

using namespace std;
const int N = 500005;
int n, m;

int a[N], pre[N], sum[N];

int lowbit(int x) {
    return x & -x;
}

void init(int n) {
	for (int i = 1; i <= n; i++)
		pre[i] = pre[i - 1] + a[i];
	for (int i = 1; i <= n; i++)
		sum[i] = pre[i] - pre[i - lowbit(i)];
}

void modify(int x, int k) {
    while (x <= n) {
        sum[x] += k;
        x += lowbit(x);
    }
}

int ask(int x) {
	int ans = 0;
	while (x) {
		ans += sum[x];
		x -= lowbit(x);
	}
	return ans;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	init(n);

    while (m --) {
        int op, x, k;
		cin >> op >> x >> k;
		if (op == 1) modify(x, k);
		else cout << ask(k) - ask(x - 1) << endl;
    }
	return 0;
}