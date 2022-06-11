/* Author: Jauhar Wibisono
 * O(NM + 2^M)
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+3, maxm = 20;
int n, m;
int a[maxn];
int cnt[1 << maxm];
long long ans;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i=0; i<n; i++) cin >> a[i];
	for (int len=1; len<=m; len++) {
		for (int l=0; l+len-1<n; l++) {
			int r = l+len-1;
			bool ok = true;
			int mask = 0;
			for (int i=l; i<=r; i++) {
				if (mask & (1<<(a[i]-1))) {
					ok = false;
					break;
				}
				mask |= 1 << (a[i]-1);
			}
			if (ok) cnt[mask]++;
		}
	}
	ans = 0;
	for (int mask=1; mask+1<(1<<m); mask++) {
		ans += 1LL * cnt[mask] * cnt[~mask & ((1<<m)-1)];
	}
	cout << ans/2 << '\n';
	return 0;
}