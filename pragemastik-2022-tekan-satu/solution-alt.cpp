/* Author: Jauhar Wibisono
 * 
 */

#include <bits/stdc++.h>
using namespace std;

int n;
int ans;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	ans = 0;
	for (int i=0; i<n; i++) {
		ans *= 10;
		ans += 1;
		ans %= 6;
	}
	cout << ans << '\n';
	return 0;
}