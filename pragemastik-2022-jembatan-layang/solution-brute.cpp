#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int maxn = 1e5+3;
int n, q;
vector<int> h[maxn];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	for (int i=0; i<n; i++) {
		int k;
		cin >> k;
		h[i].resize(k);
		for (int j=0; j<k; j++) cin >> h[i][j];
		sort(h[i].begin(), h[i].end());
	}
	while (q--) {
		int x;
		cin >> x;
		int ans = 1;
		for (int i=0; i<n; i++) ans = 1LL * ans * (upper_bound(h[i].begin(), h[i].end(), x) - h[i].begin()) % mod;
		cout << ans << '\n';
	}
	return 0;
}