/* Author: Jauhar Wibisono
 * O(NM + 2^M)
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+3, maxm = 20;
int n, m;
int a[maxn];
map<vector<int>, int> cnt;
long long ans;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i=0; i<n; i++) cin >> a[i];
	for (int len=1; len<=m; len++) {
		for (int l=0; l+len-1<n; l++) {
			int r = l+len-1;
			vector<int> tmp;
			for (int i=l; i<=r; i++) {
				tmp.push_back(a[i]);
			}
			sort(tmp.begin(), tmp.end());
			bool ok = true;
			for (int i=0; i+1<len; i++) {
				if (tmp[i] == tmp[i+1]) ok = false;
			}
			if (ok) cnt[tmp]++;
		}
	}
	ans = 0;
	for (auto &[v, c] : cnt) {
		vector<int> comp;
		for (int i=1; i<=m; i++) {
			if (!binary_search(v.begin(), v.end(), i)) comp.push_back(i);
		}
		ans += 1LL * c * cnt[comp];
	}
	cout << ans/2 << '\n';
	return 0;
}