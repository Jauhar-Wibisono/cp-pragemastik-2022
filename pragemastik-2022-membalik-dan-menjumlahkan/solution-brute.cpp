/* Author: Jauhar Wibisono
 *
 */


#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+3;
int n, m, q;
long long a[maxn];
int b[maxn];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> q;
	for (int i=1; i<=n; i++) cin >> a[i];
	for (int i=1; i<=m; i++) cin >> b[i];
	b[0] = 0;
	b[m+1] = n;
	while (q--) {
		char type;
		cin >> type;
		if (type == 'B') {
			int i;
			cin >> i;
			int l = b[i-1], r = b[i];
			reverse(a+l+1, a+r+1);
		}
		else {
			int l, r;
			cin >> l >> r;
			long long ans = 0;
			for (int i=l; i<=r; i++) ans += a[i];
			cout << ans << '\n';
		}
	}
	return 0;
}