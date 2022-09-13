/* Author: Jauhar Wibisono
 *
 */

#include<bits/stdc++.h>
using namespace std;

const int maxx = 1e9+3;
const int maxn = 103;
int n;
int m, r[maxn], c[maxn];
int mnr, mnc;

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
	cout << mnr + mnc << "\n";
}