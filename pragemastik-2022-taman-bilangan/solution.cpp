#include <bits/stdc++.h>
using namespace std;

const int maxn = 12, maxi = 1e9+3;
int n;
vector<pair<int, int>> coords[maxn];
int dist[maxn][maxn][maxn][maxn]; // dist[group 1][group 2][id 1][id 2]
int dp[maxn][maxn][maxn][1<<maxn];  // dp[group][start][end][mask]
int dp2[1<<maxn][maxn][maxn]; // dp2[mask][last group][last id]
int ans;

bool on(int x, int y) {
	return (x&(1<<y)) > 0;
}

void self_min(int &x, int y) {
	x = min(x, y);
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
	if (n == 1) {
		cout << 0 << '\n';
		return 0;
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
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			for (int k=0; k<n; k++) {
				for (int l=0; l<(1<<n); l++) {
					dp[i][j][k][l] = maxi;
				}
			}
		}
	}
	// O(2^n * n^4)
	for (int i=0; i<n; i++) {
		for (int s=0; s<n; s++) {
			dp[i][s][s][1<<s] = 0;
			for (int j=0; j<n; j++) {
				if (j == s) continue;
				dp[i][s][j][(1<<s)|(1<<j)] = dist[i][s][i][j];
			}
			for (int mask=1; mask<(1<<n); mask++) {
				if (__builtin_popcount(mask) < 2) continue;
				for (int j=0; j<n; j++) {
					if (j == s || !on(mask, j)) continue;
					for (int k=0; k<n; k++) {
						if (!on(mask, k)) self_min(dp[i][s][k][mask|(1<<k)], dp[i][s][j][mask] + dist[i][i][j][k]);
					}
				}
			}
		}
	}
	for (int i=0; i<(1<<n); i++) {
		for (int j=0; j<n; j++) {
			for (int k=0; k<n; k++) {
				dp2[i][j][k] = maxi;
			}
		}
	}
	// O(2^n * n^5)
	for (int mask=1; mask<(1<<n); mask++) {
		if (__builtin_popcount(mask) == 1) {
			int pos = __builtin_ctz(mask);
			for (int i=0; i<n; i++) {
				for (int j=0; j<n; j++) {
					if (i == j) continue;
					self_min(dp2[mask][pos][j], dp[pos][i][j][(1<<n)-1]);
				}
			}
		} else {
			for (int i=0; i<n; i++) {
				if (!on(mask, i)) continue;
				for (int j=0; j<n; j++) {
					if (i == j || !on(mask, j)) continue;
					for (int k=0; k<n; k++) {
						for (int l=0; l<n; l++) {
							for (int m=0; m<n; m++) {
								if (l == m) continue;
								self_min(dp2[mask][j][m], dp2[mask&~(1<<j)][i][k] + dist[i][j][k][l] + dp[j][l][m][(1<<n)-1]);
							}
						}
					}
				}
			}
		}
	}

	ans = maxi;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			self_min(ans, dp2[(1<<n)-1][i][j]);
		}
	}
	cout << ans << '\n';

	return 0;
}