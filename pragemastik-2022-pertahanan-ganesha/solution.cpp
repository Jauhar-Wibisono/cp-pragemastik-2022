/* Author: Jauhar Wibisono
 * V0: berapa banyak elemen yang kalo dihapus, gaada subset yang jumlahnya di antara [L, R]? 	-> bikin tcnya susah
 * V1: berapa minimum #subset yang sumnya x? 													-> perlu mod, bad
 * V2: berapa minimum distinct number di range [L, R] yang bisa diconstruct? 					-> perlu fft, susah 
 * V3: dpnya jadi dp[j] = max profit kalo sum weight = j, minimize maximum profit 				-> bahkan gabisa fft lol
 * V4: ganti range [L, R] jadi point X 															-> jadi lebih ez, gaperlu fenwick/fft
 * 
 */

#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 5003, maxx = 5003;
int n, x;
int a[maxn];
bool dp[2][maxn][maxx];
int ans;
 
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> x;
	for (int i=0; i<n; i++) cin >> a[i];
	memset(dp, false, sizeof dp);
	dp[0][0][0] = dp[1][n+1][0] = true;
	for (int i=1; i<=n; i++) {
		for (int j=0; j<=x; j++) {
			if (j-a[i-1] >= 0) dp[0][i][j] |= dp[0][i-1][j-a[i-1]];
			dp[0][i][j] |= dp[0][i-1][j];
		}
	}
	for (int i=n; i>0; i--) {
		for (int j=0; j<=x; j++) {
			if (j-a[i-1] >= 0) dp[1][i][j] |= dp[1][i+1][j-a[i-1]];
			dp[1][i][j] |= dp[1][i+1][j];
		}
	}
	ans = 0;
	for (int i=1; i<=n; i++) {
		bool ok = true;
		for (int j=0; j<=x; j++) {
			if (dp[0][i-1][j] && dp[1][i+1][x-j]) {
				// cout << j << ' ' << x-j << '\n';
				ok = false;
				break;
			}
		}
		ans += ok;
	}
	cout << ans << '\n';
	return 0;
}
