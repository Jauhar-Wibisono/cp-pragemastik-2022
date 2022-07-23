/* Author: Jauhar Wibisono
 *
 */

#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 5003, maxr = 5003;
int n, l, r;
int a[maxn];
bool dp[2][maxn][maxr];
int bit[maxr];
int ans;
 
void update(int i) {
	while (i < maxr) {
		bit[i]++;
		i += i&-i;
	}
}
 
int query(int i) {
	int ret = 0;
	while (i > 0) {
		ret += bit[i];
		i -= i&-i;
	}
	return ret;
}
 
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> l >> r;
	for (int i=0; i<n; i++) cin >> a[i];
	memset(dp, false, sizeof dp);
	dp[0][0][0] = dp[1][n+1][0] = true;
	for (int i=1; i<=n; i++) {
		for (int j=0; j<=r; j++) {
			if (j-a[i-1] >= 0) dp[0][i][j] |= dp[0][i-1][j-a[i-1]];
			dp[0][i][j] |= dp[0][i-1][j];
		}
	}
	for (int i=n; i>0; i--) {
		for (int j=0; j<=r; j++) {
			if (j-a[i-1] >= 0) dp[1][i][j] |= dp[1][i+1][j-a[i-1]];
			dp[1][i][j] |= dp[1][i+1][j];
		}
	}
	ans = 0;
	for (int i=1; i<=n; i++) {
		if (a[i-1] >= r) continue;
		memset(bit, 0, sizeof bit);
		bool ok = true;
		for (int j=l; j<=r; j++) {
			if (dp[0][i-1][j] || dp[1][i+1][j]) ok = false;
		}
		if (!ok) continue;
		for (int j=1; j<=r; j++) {
			if (dp[0][i-1][j]) update(j);
		}
		for (int j=1; j<r; j++) {
			if (!dp[1][i+1][j]) continue;
			int mn = max(1, l-j);
			int mx = r-j;
			if (query(mx) - query(mn-1) > 0) {
				ok = false;
				break;
			}
		}
		ans += ok;
	}
	cout << ans << '\n';
	return 0;
}