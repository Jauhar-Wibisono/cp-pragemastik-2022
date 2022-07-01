#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+3, maxa = 1000000000;
int n, a[maxn];
vector<int> adjl[maxn];
vector<int> leaf;
int ans[2][maxn];
queue<pair<int, int>> q;
bool ok;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; i++) cin >> a[i];
	for (int i=1; i<n; i++) {
		int u, v;
		cin >> u >> v;
		adjl[u].push_back(v);
		adjl[v].push_back(u);
	}
	for (int i=1; i<=n; i++) {
		if (adjl[i].size() == 1) {
			leaf.push_back(i);
		} else if (adjl[i].size() > 2) {
			cout << "-1\n";
			return 0;
		}
	}
	memset(ans, -1, sizeof ans);
	q.emplace(leaf[0], 1);
	while (!q.empty()) {
		int u = q.front().first, w = q.front().second;
		q.pop();
		if (ans[0][u] != -1) continue;
		if (a[u] == -1) ans[0][u] = w;
		else ans[0][u] = a[u];
		for (int v : adjl[u]) q.emplace(v, ans[0][u] + 1);
	}
	q.emplace(leaf[0], maxa);
	while (!q.empty()) {
		int u = q.front().first, w = q.front().second;
		q.pop();
		if (ans[0][u] != -1) continue;
		if (a[u] == -1) ans[0][u] = w;
		else ans[0][u] = a[u];
		for (int v : adjl[u]) q.emplace(v, ans[0][u] - 1);
	}
	for (int i=0; i<2; i++) {
		ok = true;
		for (int u=1; u<=n; u++) {
			vector<int> cnt(2, 0);
			for (int v : adjl[u]) cnt[ans[i][u] < ans[i][v]]++;
			if (cnt[0] > 1 || cnt[1] > 1) ok = false;
		}
		if (ok) {
			for (int u=1; u<=n; u++) cout << ans[i][u] << (u == n ? "\n" : " ");
			return 0;
		}
	}
	cout << "-1\n";
	return 0;
}