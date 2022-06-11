/* Author: Jauhar Wibisono
 * O(NH)
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3+3, maxh = 1e3+3;
int n, h;
vector<int> adjl[maxn];
int l[maxn], r[maxn];
int ans[maxn];
int dp[maxn][maxh];

void dfs(int u) {
	for (int i=l[u]; i<=r[u]; i++) dp[u][i]++;
	for (int v : adjl[u]) {
		dfs(v);
		for (int i=1; i<=h; i++) dp[u][i] += dp[v][i];
	}
	int mx = -1;
	for (int i=1; i<=h; i++) mx = max(mx, dp[u][i]);
	ans[u] = mx;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> h;
	for (int i=2; i<=n; i++) {
		int p;
		cin >> p;
		adjl[p].push_back(i);
	}
	for (int i=1; i<=n; i++) cin >> l[i] >> r[i];
	memset(dp, 0, sizeof dp);
	dfs(1);
	for (int i=1; i<=n; i++) {
		cout << ans[i] << (i == n ? '\n' : ' ');
	}
	return 0;
}