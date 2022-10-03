#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+3, loga = 25;
int n;
long long a[maxn];
long long cnt[2][loga][maxn][2];
long long mxd;
pair<int, int> ans;

bool on(long long x, long long y) {
    return (x >> y) & 1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++) cin >> a[i];

    for (int i=0; i<loga; i++) {
        cnt[0][i][0][0] = cnt[0][i][0][1] = 0;
        for (int j=1; j<=n; j++) {
            for (int k=0; k<2; k++) {
                cnt[0][i][j][k] = cnt[0][i][j-1][k^on(a[j], i)];
            }
            cnt[0][i][j][on(a[j], i)]++;
        }

        cnt[1][i][n+1][0] = cnt[1][i][n+1][1] = 0;
        for (int j=n; j>0; j--) {
            for (int k=0; k<2; k++) {
                cnt[1][i][j][k] = cnt[1][i][j+1][k^on(a[j], i)];
            }
            cnt[1][i][j][on(a[j], i)]++;
        }
    }

    // for (int i=1; i<=n; i++) cout << cnt[0][i][0] << ' ';

    mxd = -1;
    ans = make_pair(1, a[1]);
    for (int i=1; i<=n; i++) {
        long long d = 0;
        int val = 0;
        for (int j=0; j<loga; j++) {
            long long oc = cnt[0][j][i-1][!on(a[i], j)] * cnt[1][j][i+1][0] + cnt[0][j][i-1][on(a[i], j)] * cnt[1][j][i+1][1];
            long long nc = cnt[0][j][i-1][on(a[i], j)] * cnt[1][j][i+1][0] + cnt[0][j][i-1][!on(a[i], j)] * cnt[1][j][i+1][1];
            // cout << i << ' ' << j << ' ' << oc << ' ' << nc << '\n';
            if (oc < nc || (nc == oc && on(a[i], j))) {
                d += nc - oc;
                val |= (!on(a[i], j) << j);
            }
        }
        if (d > mxd) {
            mxd = d;
            ans = make_pair(i, val);
        }
    }

    cout << ans.first << ' ' << ans.second << '\n';
}