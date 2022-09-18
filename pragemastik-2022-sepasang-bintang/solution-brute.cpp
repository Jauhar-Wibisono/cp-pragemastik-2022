/* Author: Jauhar Wibisono
 * 
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+3, maxm = 2e5+3;
int n, m;
pair<int, int> edgl[maxm];
vector<int> adjl[maxn];
long long ans[maxn];

bool cek(int cn, int u, int v) {
	vector<bool> udah(cn+1, false);
	udah[u] = true;
	udah[v] = true;
	for (int w : adjl[u]) {
		if (udah[w]) return false;
		udah[w] = true;
	}
	for (int w : adjl[v]) {
		if (udah[w]) return false;
		udah[w] = true;
	}
	return true;
}

long long answer(int cn) {
	vector<vector<int>> who(cn+1);
	vector<pair<int, int>> degs;
	for (int i=1; i<=cn; i++) who[adjl[i].size()].push_back(i);
	for (int i=0; i<=cn-2-i; i++) {
		if (!who[i].empty() && !who[cn-2-i].empty()) degs.emplace_back(i, cn-2-i);
	}

	long long ret = 0;
	for (auto &[d1, d2] : degs) {
		if (d1 == d2) {
			for (int i=0; i<(int)who[d1].size(); i++) {
				for (int j=i+1; j<(int)who[d1].size(); j++) {
					ret += cek(cn, who[d1][i], who[d1][j]);
				}
			}
		} else {
			for (int u : who[d1]) {
				for (int v : who[d2]) {
					ret += cek(cn, u, v);
				}
			}
		}
	}

	return ret;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i=0; i<m; i++) cin >> edgl[i].first >> edgl[i].second;

	sort(edgl, edgl+m, [&](pair<int, int> a, pair<int, int> b) {
		return max(a.first, a.second) < max(b.first, b.second);
	});

	memset(ans, 0, sizeof ans);
	for (int cn=2, l=0; cn<=n; cn++) {
		int r = l;
		while (r < m && max(edgl[r].first, edgl[r].second) <= cn) r++;
		for (int i=l; i<r; i++) {
			adjl[edgl[i].first].push_back(edgl[i].second);
			adjl[edgl[i].second].push_back(edgl[i].first);
		}
		ans[cn] = answer(cn);
		l = r;
	}

	for (int i=2; i<=n; i++) cout << ans[i] << " \n"[i==n];
	return 0;
}