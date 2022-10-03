#include <bits/stdc++.h>
using namespace std;

#define pll pair<long long, long long>

const long long maxn = 131072;
long long q, type, xy[2], nbTeman=0;
long long teman[maxn][2], ab[maxn][2];

long long getPower(int idx){
    long long ans = 0;

    for(int i=0; i<nbTeman; i++){
        ans += min(abs(xy[idx] - teman[i][idx]), ab[i][idx]);
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> q;
    while(q--){
        cin >> type; type--;
        if(type){
            cin >> xy[0] >> xy[1];
            cout << getPower(0) + getPower(1) << endl;
        }else{
            cin >> teman[nbTeman][0] >> teman[nbTeman][1] >> ab[nbTeman][0] >> ab[nbTeman][1];
            nbTeman++;
        }
    }
    long long ans[2];
    ans[0] = 1e18; ans[1] = 1e18;
    for(int i=0; i<nbTeman; i++){
        for(int j=0; j<2; j++){
            xy[j] = teman[i][j];
            ans[j] = min(getPower(j), ans[j]);
        }
    }
    if(nbTeman){
        cout << ans[0] + ans[1] << endl;
    }else{
        cout << 0 << endl;
    }
}
