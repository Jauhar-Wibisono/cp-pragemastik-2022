/* Author: Jauhar Wibisono
 * offline queries, O(SJ + Q log SJ), SJ = total jembatan
 */

#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int maxn = 1e5+3, maxq = 1e5+3;
int n, q;
priority_queue<pair<int, int>> pq;
pair<int, int> ques[maxq];
int cnt[maxn], cur; 
set<int> nz;
int ans[maxq];

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
			pq.emplace(-h, i);
		}
	}
	for (int i=0; i<q; i++) {
		cin >> ques[i].first;
		ques[i].second = i;
	}
	sort(ques, ques+q);
	memset(cnt, 0, sizeof cnt);
	cur = 0;
	for (int i=0; i<q; i++) {
		while (!pq.empty() && -pq.top().first <= ques[i].first) {
			int id = pq.top().second;
			if ((int)nz.size() == n) {
				cur = 1LL * cur * modinv(cnt[id]) % mod;
				cnt[id]++;
				cur = 1LL * cur * cnt[id] % mod;
			} else {
				cnt[id]++;
				if (cnt[id] == 1) {
					nz.insert(id);
					if ((int)nz.size() == n) {
						cur = 1;
						for (int j=0; j<n; j++) cur = 1LL * cur * cnt[j] % mod;
					}
				}
			}
			pq.pop();
		}
		ans[ques[i].second] = cur;
	}
	for (int i=0; i<q; i++) cout << ans[i] << '\n';
	return 0;
}