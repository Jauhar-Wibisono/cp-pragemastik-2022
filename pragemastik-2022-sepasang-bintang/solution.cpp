/* Author: Jauhar Wibisono
 * 
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+3, base[] = {2, 3}, mod[] = {1000000007, 998244353}, nh = 2;
int n, m;
vector<int> adjl[maxn];
int ha[maxn][nh], hu[maxn][nh];
map<pair<int, int>, long long> cnt; // lol lainnya array ini pair, nggatelin
long long ans[maxn];

int modpow(int a, int b, int md) {
	int ret = 1;
	for (; b; b>>=1) {
		if (b&1) ret = 1LL * ret * a % md;
		a = 1LL * a * a % md;
	}
	return ret;
} 

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i=0; i<m; i++) {
		int u, v;
		cin >> u >> v;
		if (u < v) swap(u, v);
		adjl[u].push_back(v);
	}

	for (int i=0; i<nh; i++) ha[0][i] = 0;
	for (int i=1; i<=n; i++) {
		for (int j=0; j<nh; j++) {
			hu[i][j] = modpow(base[j], i, mod[j]);
			ha[i][j] = (ha[i-1][j] + hu[i][j]) % mod[j];
		}
	}

	memset(ans, 0, sizeof ans);
	for (int u=1; u<=n; u++) {
		cnt[make_pair(hu[u][0], hu[u][1])]++;
		for (int v : adjl[u]) {
			cnt[make_pair(hu[u][0], hu[u][1])]--;
			cnt[make_pair(hu[v][0], hu[v][1])]--;
			for (int k=0; k<nh; k++) {
				hu[u][k] = (hu[u][k] + modpow(base[k], v, mod[k])) % mod[k];
				hu[v][k] = (hu[v][k] + modpow(base[k], u, mod[k])) % mod[k];
			}
			cnt[make_pair(hu[u][0], hu[u][1])]++;
			cnt[make_pair(hu[v][0], hu[v][1])]++;
		}

		adjl[u].push_back(u);
		for (int v : adjl[u]) {
			int h[nh];
			for (int k=0; k<2; k++)	h[k] = ((ha[u][k] - hu[v][k]) % mod[k] + mod[k]) % mod[k];
			ans[u] += cnt[make_pair(h[0], h[1])];
		}
	}

	for (int i=2; i<=n; i++) cout << ans[i] << " \n"[i == n];
	return 0;
}

/*
5 5
1 2
5 3
1 4
3 4
2 4 
*/