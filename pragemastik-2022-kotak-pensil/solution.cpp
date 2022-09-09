/* Author: Jauhar Wibisono
 *
 */

#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<string> a(n);
	for (int i=0; i<n; i++) cin >> a[i];

	int ans = 0;
	for (int i=0; i<n; i++) {
		for (int l=0; l<m; ) {
			int r = l;
			while (r < m && a[i][r] == a[i][l]) r++;
			if (a[i][l] == '0') ans = max(ans, r-l);
			l = r;
		}
	}
	for (int i=0; i<m; i++) {
		for (int l=0; l<n; ) {
			int r = l;
			while (r < n && a[r][i] == a[l][i]) r++;
			if (a[l][i] == '0') ans = max(ans, r-l);
			l = r;
		}
	}

	cout << ans << '\n';
	return 0;
}