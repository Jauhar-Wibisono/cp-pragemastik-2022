/* Author: Jauhar Wibisono
 *
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+3;
int n;
long long x[maxn], y[maxn];
vector<long long> areas;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n; i++) cin >> x[i] >> y[i];
	for (int i=0; i<n; i++) {
		{
			long long area = 0;
			for (int j=0; j<3; j++) area += x[(i+j)%n] * y[(i+j+1)%n] - x[(i+j+1)%n] * y[(i+j)%n];
			areas.push_back(area);
		}
		if (n > 4) {
			long long area = 0;
			for (int j=0; j<4; j++) area += x[(i+j)%n] * y[(i+j+1)%n] - x[(i+j+1)%n] * y[(i+j)%n];
			areas.push_back(area);
		}
	}
	sort(areas.begin(), areas.end());
	cout << areas[2] << '\n';
	return 0;
}