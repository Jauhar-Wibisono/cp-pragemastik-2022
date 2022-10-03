#include <bits/stdc++.h>
using namespace std;

const int maxn = 131072;
long long n, xy[maxn][2], srt[2*maxn];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> xy[i][0] >> xy[i][1];
    }
    for(int i=0; i<n; i++){
        srt[2*i] = abs(
            xy[(i+1)%n][0] * xy[(i+2)%n][1] - xy[(i+1)%n][1] * xy[(i+2)%n][0]
            + xy[(i+2)%n][0] * xy[i][1] - xy[(i+2)%n][1] * xy[i][0]
            + xy[i][0] * xy[(i+1)%n][1] - xy[i][1] * xy[(i+1)%n][0]
        );
        srt[2*i+1] = abs(
            xy[(i+1)%n][0] * xy[(i+2)%n][1] - xy[(i+1)%n][1] * xy[(i+2)%n][0]
            + xy[(i+2)%n][0] * xy[(i+3)%n][1] - xy[(i+2)%n][1] * xy[(i+3)%n][0]
            + xy[(i+3)%n][0] * xy[i][1] - xy[(i+3)%n][1] * xy[i][0]
            + xy[i][0] * xy[(i+1)%n][1] - xy[i][1] * xy[(i+1)%n][0]
        );
    }
    sort(srt, srt + 2*n);
    cout << srt[2] << endl;
    return 0;
}

