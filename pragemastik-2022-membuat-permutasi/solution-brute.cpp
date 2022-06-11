/* Author: Jauhar Wibisono
 * O(N^2 * M)
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+3, maxm = 20;
int n, m;
int a[maxn];
long long ans = 0;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i=0; i<n; i++) cin >> a[i];
	for (int len1=1; len1<m; len1++) {
		int len2 = m-len1;
		for (int l1=0; l1+m-1<n; l1++) {
			int r1 = l1+len1-1;
			for (int l2=l1+len1; l2+len2-1<n; l2++) {
				int r2 = l2+len2-1;
				bool ok = true;
				int mask = 0;
				for (int i=l1; i<=r1; i++) {
					if (mask & (1<<(a[i]-1))) ok = false;
					mask |= 1 << (a[i]-1);
				}
				for (int i=l2; i<=r2; i++) {
					if (mask & (1<<(a[i]-1))) ok = false;
					mask |= 1 << (a[i]-1);
				}
				if (ok) ans++;
			}
		}
	}
	cout << ans << '\n';
	return 0;
}