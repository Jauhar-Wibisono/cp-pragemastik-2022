/* Author: Jauhar Wibisono
 * O(N log N log H)
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+3, maxh = 2e5+3;
int n, h;
vector<int> adjl[maxn];
int l[maxn], r[maxn];
int sez[maxn], tin[maxn], tout[maxn], ver[maxn], tem;
int segt[4*maxh], lazy[4*maxh];
int ans[maxn];

void dfs1(int u) {
	sez[u] = 1;
	tin[u] = tem;
	ver[tem] = u;
	tem++;
	for (int v : adjl[u]) {
		dfs1(v);
		sez[u] += sez[v];		
	}
	tout[u] = tem;
}

void push(int v) {
	segt[v*2] += lazy[v];
	segt[v*2+1] += lazy[v];
	lazy[v*2] += lazy[v];
	lazy[v*2+1] += lazy[v];
	lazy[v] = 0; 
}

void update(int l, int r, int v, int lb, int rb, int val) {
	if (r < lb || l > rb) return;
	if (l >= lb && r <= rb) segt[v] += val, lazy[v] += val;
	else {
		push(v);
		int mid = (l+r)/2;
		update(l, mid, v*2, lb, rb, val);
		update(mid+1, r, v*2+1, lb, rb, val);
		segt[v] = max(segt[v*2], segt[v*2+1]);
	}
}

void dfs2(int u, bool keep) {
	int mx = -1, big = -1;
	for (int v : adjl[u]) {
		if (sez[v] > mx) {
			mx = sez[v];
			big = v;
		}
	}
	for (int v : adjl[u]) {
		if (v != big) dfs2(v, false);
	}
	if (big != -1) dfs2(big, true);
	for (int v : adjl[u]) {
		if (v != big) {
			for (int t=tin[v]; t<tout[v]; t++) {
				update(1, h, 1, l[ver[t]], r[ver[t]], 1);
			}
		}
	}
	update(1, h, 1, l[u], r[u], 1);
	ans[u] = segt[1];
	if (!keep) {
		for (int t=tin[u]; t<tout[u]; t++) {
			update(1, h, 1, l[ver[t]], r[ver[t]], -1);
		}
	}
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
	tem = 0;
	dfs1(1);
	memset(segt, 0, sizeof segt);
	memset(lazy, 0, sizeof lazy);
	dfs2(1, true);
	for (int i=1; i<=n; i++) {
		cout << ans[i] << (i == n ? '\n' : ' ');
	}
	return 0;
}