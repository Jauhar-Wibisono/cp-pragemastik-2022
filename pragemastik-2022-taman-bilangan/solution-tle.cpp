/* Author: Jauhar Wibisono
 * O((n!)^(n+1))
 * WARNING: might cause memory explosion
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 12, maxi = 1e9+3;
int n;
vector<pair<int, int>> coords[maxn];
int dist[maxn][maxn][maxn][maxn]; // dist[group 1][group 2][id 1][id 2]
int ans;
vector<vector<int>> perms;

void solve(vector<int> &pi, int m) {
	// cout << '\n';
	if ((int)pi.size() == m+1) {
		int sum = 0;
		for (int i=0; i<m; i++) {
			for (int j=1; j<m; j++) {
				int g = perms[pi[m]][i];
				int s = perms[pi[i]][j-1];
				int t = perms[pi[i]][j];
				sum += dist[g][g][s][t];
			}
		}
		for (int i=1; i<m; i++) {
			int g1 = perms[pi[m]][i-1];
			int g2 = perms[pi[m]][i];
			int s = perms[pi[i-1]][m-1];
			int t = perms[pi[i]][0];
			sum += dist[g1][g2][s][t];
		}
		// cout << pi.size() << ' ' << n+1 << '\n';
		// for (int i : pi) cout << i << ' ';
		// cout << ": " << sum << '\n';
		ans = min(ans, sum);
		return;
	}
	for (int i=0; i<(int)perms.size(); i++) {
		vector<int> npi = pi;
		npi.push_back(i);
		solve(npi, m);
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			int a;
			cin >> a;
			coords[a%n].emplace_back(i, j);
		}
	}
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			for (int k=0; k<n; k++) {
				for (int l=0; l<n; l++) {
					dist[i][j][k][l] = 
						abs(coords[i][k].first - coords[j][l].first) + 
						abs(coords[i][k].second - coords[j][l].second);
				}
			}
		}
	}

	vector<int> perm;
	for (int i=0; i<n; i++) perm.push_back(i);
	do {
		perms.push_back(perm);
	} while (next_permutation(perm.begin(), perm.end()));
	ans = maxi;
	vector<int> v;
	solve(v, n);
	cout << ans << '\n';
}