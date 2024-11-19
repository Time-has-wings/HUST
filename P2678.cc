#include <iostream>

using namespace std;

const int N = 50005;
int L, n, m;
int dist[N];

// 原理：二分答案，随后逐一枚举每个石头，若该石头与下一个石头的距离会小于mid，则需要移除下一个石头。待此方法结束后，判断移除䣌石头数量是否小于等于m即可
bool check(int mid) {
    int remove = 0, last = 0; // remove:表示移除的石头数 last:表示上一个石头的位置
    for (int i = 1; i <= n + 1; i++) {
        if (dist[i] - last < mid) {
            remove++;
        } else {
            last = dist[i];
        }
    }
    return remove <= m;
}

void solve() {
    int l = 0, r = L;
    while (l <= r) { // 二分模板
        int mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1;
        else r = mid - 1;
    }
    cout << r << endl;
}

int main() {
    cin >> L >> n >> m;
    for (int i = 1; i <= n; i++) 
        cin >> dist[i];
    dist[n + 1] = L; // 表示终点
    solve();
    return 0;
}