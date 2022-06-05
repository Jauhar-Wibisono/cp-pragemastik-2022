/* Author: Jauhar Wibisono
 * Status: verified with bruteforce
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+3;
int n, m, q;
long long a[maxn];
int b[maxn];
long long p1[maxn], p2[maxn], p3[maxn];
bool f[maxn];
	
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> q;
	for (int i=1; i<=n; i++) cin >> a[i];
	
	for (int i=1; i<=m; i++) cin >> b[i];
	b[0] = 0;
	b[m+1] = n;

	p1[0] = 0;
	for (int i=1; i<=n; i++) p1[i] = p1[i-1] + a[i];
	
	for (int i=1; i<=m+1; i++) {
		int l = b[i-1]+1, r = b[i];
		p2[l] = a[l];
		for (int j=l+1; j<=r; j++) p2[j] = p2[j-1] + a[j];
		reverse(a+l, a+r+1);
		p3[l] = a[l];
		for (int j=l+1; j<=r; j++) p3[j] = p3[j-1] + a[j];
	}

	memset(f, false, sizeof f);
	while (q--) {
		char type;
		cin >> type;
		if (type == 'B') {
			int i;
			cin >> i;
			f[i-1] ^= 1;
		} else {
			int l, r;
			cin >> l >> r;
			int ll, rr;
			{
				int lll = 0, rrr = m+1;
				while (lll < rrr) {
					int mid = (lll+rrr)/2;
					if (b[mid] < l) lll = mid+1;
					else rrr = mid; 
				}
				ll = lll;
			}
			{
				int lll = 0, rrr = m+1;
				while (lll < rrr) {
					int mid = (lll+rrr+1)/2;
					if (b[mid] < r) lll = mid;
					else rrr = mid-1; 
				}
				rr = lll;
			}
			if (ll > rr) {
				if (f[rr]) cout << p3[r] - (l == b[rr]+1 ? 0 : p3[l-1]) << '\n';
				else cout << p2[r] - (l == b[rr]+1 ? 0 : p2[l-1]) << '\n';
			} else {
				long long ans = 0;
				if (f[ll-1]) ans += p3[b[ll]] - (l == b[ll-1]+1 ? 0 : p3[l-1]);
				else ans += p2[b[ll]] - (l == b[ll-1]+1 ? 0 : p2[l-1]);
				if (f[rr]) ans += p3[r];
				else ans += p2[r];
				ans += p1[b[rr]] - p1[b[ll]];
				cout << ans << '\n';
			}
		}
	} 
	return 0;
}

/*
8 3 12
1 2 3 4 5 6 7 8
2 5 6
2 1 8
2 4 6
2 3 5
1 2
2 4 6
2 3 5
1 3
2 4 6
2 5 5
1 1
2 1 1
2 2 3

36
15
12
13
12
13
*/