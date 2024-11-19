#include<iostream>
#include<string>

using namespace std;
const int N = 22;
string word[N];
char st;
int n, ans;
int f[N][N], used[N]; // f[i][j]为第i个和第j个单词可衔接的最小长度

void dfs(string dragon, int last) {
	ans = max(ans, (int)dragon.length());
	used[last]++;
	for (int i = 1; i <= n; i++)
		if (used[i] < 2 && f[last][i])
			dfs(dragon + word[i].substr(f[last][i]), i);
	used[last]--;
}

void solve() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			string a = word[i], b = word[j];
			for (int k = 1; k < min(a.size(), b.size()); k++) {
				if (a.substr(a.length() - k, k) == b.substr(0, k)) {
					f[i][j] = k;
					break;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++)
		if (word[i][0] == st)
			dfs(word[i], i);
	cout << ans;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> word[i];
	cin >> st;
    solve();
	return 0;
}