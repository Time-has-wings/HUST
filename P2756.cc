// https://www.acwing.com/problem/content/video/2177/
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;
const int N = 205, M = N * N * 2, INF = 1e9;

int n, m, S, T, X, Y;
int h[N], e[M], ne[M], f[M], idx;
int dist[N], cur[N];//d用于构建分层图 cur用于弧优化
int pre[N];//设置前驱节点 因为是二分图 故而无误

void add(int a, int b, int c) {
	e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx++;
	e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx++;
}

bool BFS() {
	memset(dist, -1, sizeof dist);
	dist[S] = 0;
	queue<int>q;
	q.push(S);
	cur[S] = h[S];
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = h[x]; ~i; i = ne[i]) {
			int y = e[i];
			cur[y] = h[y];
			if (dist[y] == -1 && f[i]) {
				dist[y] = dist[x] + 1;
				q.push(y);
				if (y == T) return true;
			}
		}
	}
	return false;
}

int find(int start, int limit) {
	//递归边界
	if (start == T) return limit;
	int flow = 0;
	for (int i = cur[start]; ~i && flow < limit; i = ne[i]) {
		cur[start] = i;//弧优化
		int y = e[i];
		if (dist[y] == dist[start] + 1 && f[i]) {
			int icr = find(y, min(f[i], limit - flow));
			if (!icr) dist[y] = -1;//在分层图中删除 表示从y出发找不到路径
			else {
				f[i] -= icr, f[i ^ 1] += icr, flow += icr;
				pre[y] = start;
			}
		}
	}
	return flow;
}

int dinic() {
	int res = 0, flow;
	while (BFS()) 
		while ((flow = find(S, INF)))
			res += flow;
	return res;
}

int main() {
	memset(h, -1, sizeof h);
	cin >> m >> n;
	while ((cin >> X >> Y) && X != -1)
		add(X, Y, 1);
	S = 0, T = n + m + 1;
	for (int i = 1; i <= m; i++)
		add(S, i, 1);
	for (int i = m + 1; i <= m + n; i++)
		add(i, T, 1);
	cout << dinic() << endl;
	for (int i = m + 1; i <= m + n; i++) 
		if (pre[i])
			cout << pre[i] << " " << i << endl;
	return 0;
}
