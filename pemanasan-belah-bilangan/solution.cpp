#include <bits/stdc++.h>
using namespace std;

const int maxd = 12;
string s;
int lg2[maxd];
int ans;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	lg2[0] = 0;
	for (int i=1; i<maxd; i++) lg2[i] = lg2[i/2] + 1;
	cin >> s;
	ans = 0;
	for (char c : s) ans = max(ans, lg2[c-'0']);
	cout << ans << '\n';
	return 0;
}