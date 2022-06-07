/* Author: Jauhar Wibisono
 * yang ini online query, O(SJ + Q log SJ), SJ = total jembatan
 */

#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int maxn = 1e5+3, maxq = 1e5+3, maxsb = 2e5+3;
int n, q;
vector<pair<int, int>> b;
int cnt[maxn]; 
int cur;
vector<pair<int, int>> ans;
set<int> nz;

int modpow(int a, int b) {
	int ret = 1;
	for (; b; b>>=1) {
		if (b&1) ret = 1LL * ret * a % mod;
		a = 1LL * a * a % mod;
	}
	return ret;
}

int modinv(int a) {
	return modpow(a, mod-2);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	for (int i=0; i<n; i++) {
		int k;
		cin >> k;
		for (int j=0; j<k; j++) {
			int h;
			cin >> h;
			b.emplace_back(h, i);
		}
	}
	sort(b.begin(), b.end());
	memset(cnt, 0, sizeof cnt);
	cur = 0;
	ans.emplace_back(0, cur);
	for (int l=0; l<(int)b.size(); ) {
		int r = l;
		while (r < (int)b.size() && b[l].first == b[r].first) r++;
		for (int i=l; i<r; i++) {
			cnt[b[i].second]++;
			if ((int)nz.size() < n) {
				if (cnt[b[i].second] == 1) nz.insert(b[i].second);
				if ((int)nz.size() == n) {
					cur = 1;
					for (int j=0; j<n; j++) cur = 1LL * cur * cnt[j] % mod;
				}
			} else {
				cur = 1LL * cur * modinv(cnt[b[i].second] - 1) % mod * cnt[b[i].second] % mod;
			}

		}
		ans.emplace_back(b[l].first, cur);
		l = r;
	}
	while (q--) {
		int h;
		cin >> h;
		int l = 0, r = ans.size()-1;
		while (l < r) {
			int mid = (l+r+1)/2;
			if (ans[mid].first <= h) l = mid;
			else r = mid-1;
		}
		cout << ans[l].second << '\n';
	}
}