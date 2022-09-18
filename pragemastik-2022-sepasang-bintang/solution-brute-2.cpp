/* Author: Jauhar Wibisono
 * 
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+3, maxm = 2e5+3;
int n, m;
vector<int> iadjl[maxn], adjl[maxn];
long long ans[maxn];
set<int> who[maxn];

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
	vector<pair<int, int>> degs;
	for (int i=0; i<=cn-2-i; i++) {
		if (!who[i].empty() && !who[cn-2-i].empty()) degs.emplace_back(i, cn-2-i);
	}

	long long ret = 0;
	for (auto &[d1, d2] : degs) {
		if (d1 == d2) {
			for (auto itu=who[d1].begin(); itu!=who[d1].end(); itu++) {
				for (auto itv=itu; itv!=who[d1].end(); itv++) {
					if (itu == itv) continue;
					ret += cek(cn, *itu, *itv);
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
	for (int i=0; i<m; i++) {
		int u, v;
		cin >> u >> v;
		if (u < v) swap(u, v);
		iadjl[u].push_back(v);
	}

	memset(ans, 0, sizeof ans);
	for (int cn=1; cn<=n; cn++) {
		who[iadjl[cn].size()].insert(cn);
		for (int u : iadjl[cn]) {
			who[adjl[u].size()].erase(u);
			adjl[u].push_back(cn);
			adjl[cn].push_back(u);
			who[adjl[u].size()].insert(u);
		}
		if (cn > 1) ans[cn] = answer(cn);
	}

	for (int i=2; i<=n; i++) cout << ans[i] << " \n"[i==n];
	return 0;
}