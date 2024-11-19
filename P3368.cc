#include<iostream>

using namespace std;

const int N = 500005;
int n, m, opt, x, y, k;
int a[N], sum[N];

int lowbit(int x) {
    return x & -x;
}

int ask(int x) {
	int ans = a[x];
	while (x) {
		ans += sum[x];
		x -= lowbit(x);
	}
	return ans;
}

void modify(int x, int k) {
	while (x <= n) {
		sum[x] += k;
		x += lowbit(x);
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
    while (m --) {
        int op, x, y, k;
        cin >> op;
		if (op == 1) {
			cin >> x >> y >> k;
			modify(x, k);
			modify(y + 1, -k);
		}
		else {
			cin >> x;
			cout << ask(x) << endl;
		}
	}
	return 0;
}