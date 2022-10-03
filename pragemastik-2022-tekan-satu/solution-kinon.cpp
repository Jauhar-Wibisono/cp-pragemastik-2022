#include <bits/stdc++.h>
using namespace std;

int n;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	cout << (9 - n%3*2)%6 << endl;
	return 0;
}
