#include <bits/stdc++.h>
using namespace std;

const int ans[] = {3, 1, 5};
int n;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	cout << ans[n%3] << '\n';
	return 0;
}