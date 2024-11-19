#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;
const int N = 200010;

int n, m, weight[N], val[N], l[N], r[N];
long long s, diff = 0x3f3f3f3f3f3f3f3f;

bool check(int mid){
	long long sum = 0, w[N], v[N];
	memset(w,0,sizeof(w));
	memset(v,0,sizeof(v));
	for (int i = 1; i <= n; i++) {
		if (weight[i] >= mid) { 
			w[i] = w[i - 1] + 1;
			v[i] = v[i - 1] + val[i];
		}
		else {
			w[i] = w[i - 1];
			v[i] = v[i - 1];
		}
	}
	for (int i = 1; i <= m; i ++)
		sum = sum + (v[r[i]] - v[l[i] - 1]) * (w[r[i]] - w[l[i] - 1]);

    diff = min(diff, llabs(sum - s));

	if (sum > s) return true;
	else return false;	
}

void solve() {
    int WMax = weight[0], WMin = weight[0];
    for (int i = 1; i <= n; i++) {
        if (weight[i] > WMax) WMax = weight[i];
        if (weight[i] < WMin) WMin = weight[i];
    }
    int L = WMin - 1, R = WMax + 1;
    while (L <= R) {
        int mid = (L + R) >> 1;
        if (check(mid)) L = mid + 1;
        else R = mid - 1;
    }
    cout << diff << endl;
}

int main(){
    cin >> n >> m >> s;
    for (int i = 1; i <= n; i++) 
        cin >> weight[i] >> val[i];
    for (int i = 1; i <= m; i++) 
        cin >> l[i] >> r[i];
    solve();
	return 0;
} 