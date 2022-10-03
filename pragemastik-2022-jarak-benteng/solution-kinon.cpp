#include <bits/stdc++.h>
using namespace std;

const int maxn = 131072;
int n, a[maxn], ans = 0, cur;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> n;
	for(int j=0; j<2; j++){
        for(int i=0; i<n; i++){
            cin >> a[i];
        }
        sort(a, a+n);
        cur = a[1]-a[0];
        for(int i=2; i<n; i++){
            cur = min(a[i] - a[i-1], cur);
        }
        ans += cur;
	}
	cout << ans << endl;
	return 0;
}
