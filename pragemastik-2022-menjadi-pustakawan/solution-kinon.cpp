#include <bits/stdc++.h>
using namespace std;

#define pll pair<int, int>

const int maxn = 262144;
int n, m, q;
long long h[maxn], p[maxn], dppart[maxn], ans;
bool isInv[maxn];
vector<long long> dp[maxn];
char tipe;
int x, y, mappart[maxn], mx, my;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m >> q;
    for(int i=0; i<n; i++){
        cin >> h[i];
    }
    p[0] = 0;
    dppart[0] = 0;
    long long sum = 0;
    for(int i=0; i<m; i++){
        isInv[i] = false;
        cin >> p[i+1];
        dp[i].push_back(0);
        sum = 0;
        for(int j=p[i]; j<p[i+1]; j++){
            mappart[j] = i;
            sum += h[j];
            dp[i].push_back(sum);
        }
        dppart[i+1] = dppart[i] + sum;
    }
    p[m+1] = n;
    isInv[m] = false;
    dp[m].push_back(0);
    sum = 0;
    for(int j=p[m]; j<p[m+1]; j++){
        mappart[j] = m;
        sum += h[j];
        dp[m].push_back(sum);
    }
    dppart[m+1] = dppart[m] + sum;

    while(q--){
        cin >> tipe;
        if(tipe == 'B'){
            cin >> x; x--;
            isInv[x] = !isInv[x];
        }else{
            cin >> x >> y; x--; y--;
            mx = mappart[x]; my = mappart[y];
            ans = dppart[my] - dppart[mx+1];
            //cout << ans << endl;
            if(isInv[mx]){
                ans += dp[mx][p[mx+1]-x];
            }else{
                ans += dppart[mx+1] - dppart[mx] - dp[mx][x-p[mx]];
            }
            //cout << ans << endl;
            if(isInv[my]){
                //cout << dppart[my+1] << " " << dppart[my] << " " << dp[my][p[my+1]-y-1] << endl;
                ans += dppart[my+1] - dppart[my] - dp[my][p[my+1]-y-1];
            }else{
                ans += dp[my][y-p[my]+1];
            }
            cout << ans << endl;
        }
    }
}
