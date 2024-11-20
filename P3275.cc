// 若想通过hack数据，使用缩点后拓扑排序
#include <iostream>
#include <cstring>
#include <queue>
#include <stack>

#define STACK 

using namespace std;
const int N = 100005, M = 300005;

int n, K;
int h[N], e[M], ne[M], w[M], idx;
int dist[N], cnt[N], exist[N]; // 最长路 具体含义见spfa函数

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

bool spfa() {
    memset(dist, -1, sizeof dist); // 初始化为负无穷
    memset(cnt, 0, sizeof cnt); // cnt[i]表示从0到i的最长路所经历的边数
    memset(exist, false, sizeof exist); // 是否在队列中

#ifndef STACK
    queue<int> q;
    q.push(0);
    dist[0] = 0;
    exist[0] = true;

    while (q.size()) {
        int x = q.front();
        q.pop();
        exist[x] = false;

        for (int i = h[x]; ~i; i = ne[i]) {
            int y = e[i];
            if (dist[y] < dist[x] + w[i]) { // 求最长路
                dist[y] = dist[x] + w[i];
                cnt[y] = cnt[x] + 1;
                if (cnt[y] >= n + 1) // 经历的边数大于等于n + 1 说明存在正环
                    return false; 
                if (!exist[y]) {
                    q.push(y);
                    exist[y] = true;
                }
            }
        }
    }
#else 
    // 使用栈的原因是，始终保持cnt[]值较大的先考虑，可以更快的找到正环
    stack<int> q;
    q.push(0);
    dist[0] = 0;
    exist[0] = true;

    while (q.size()) {
        int x = q.top();
        q.pop();
        exist[x] = false;

        for (int i = h[x]; ~i; i = ne[i]) {
            int y = e[i];
            if (dist[y] < dist[x] + w[i]) { // 求最长路
                dist[y] = dist[x] + w[i];
                cnt[y] = cnt[x] + 1;
                if (cnt[y] >= n + 1) // 经历的边数大于等于n + 1 说明存在正环
                    return false; 
                if (!exist[y]) {
                    q.push(y);
                    exist[y] = true;
                }
            }
        }
    }
#endif 

    return true;
}

int main() {
    memset(h, -1, sizeof h); // 初始化链式前向星
    cin >> n >> K;
    while (K--) {
        int x, a, b;
        cin >> x >> a >> b;
        if (x == 1) {
            add(a, b, 0); // dist[b] >= dist[a] + 0
            add(b, a, 0); // dist[a] >= dist[b] + 0
        }
        else if (x == 2) {
            add(a, b, 1); // dist[b] >= dist[a] + 1
        }
        else if (x == 3) {
            add(b, a, 0); // dist[a] >= dist[b] + 0
        }
        else if (x == 4) {
            add(b, a, 1); // dist[a] >= dist[b] + 1
        }
        else if (x == 5) {
            add(a, b, 0); // dist[b] >= dist[a] + 0
        }
    }
    for (int i = 1; i <= n; i++) {
        add(0, i, 1); // dist[a] >= dist[0] + 1 (每个小朋友有糖果)
    }
    if (spfa() == false) {
        cout << -1 << endl;
    }
    else {
        long long res = 0;
        for (int i = 1; i <= n; i++) {
            res += dist[i];
        }
        cout << res << endl;
    }
    return 0;
}