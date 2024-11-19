#include <iostream>
#include <queue>

using namespace std;
const int N = 10005;
int n, a[N];

void solve() {
    int ans = 0;
    priority_queue<int> heap;
    for (int i = 1; i <= n; i++)
        heap.push(-a[i]); // 由于C++的priority_queue默认是大根堆，所以我们将所有元素取负值，使其变为小根堆
    while (heap.size() > 1) {
        int x = -heap.top(); heap.pop();
        int y = -heap.top(); heap.pop();
        heap.push(-(x + y));
        ans += x + y;
    }
    cout << ans;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    solve();
    return 0;
}