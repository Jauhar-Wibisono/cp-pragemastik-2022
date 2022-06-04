/* Author: Jauhar Wibisono
 *
 */

#include<bits/stdc++.h>
using namespace std;

const long long maxx = 1e18+3;
const int maxn = 1e5+3;
int n;
long long m, r[maxn], c[maxn];
long long mnr, mnc;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	mnr = mnc = maxx;
	cin >> m >> n;
	for (int i=0; i<n; i++) cin >> r[i];
	for (int i=0; i<n; i++) cin >> c[i];
	sort(r, r+n);
	sort(c, c+n);
	for (int i=0; i+1<n; i++){
		mnr=min(mnr, r[i+1]-r[i]);
		mnc=min(mnc, c[i+1]-c[i]);
	}
	cout << max(mnr, mnc) << "\n";
}