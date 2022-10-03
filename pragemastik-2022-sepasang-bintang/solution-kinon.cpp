#include <bits/stdc++.h>
using namespace std;

#define pll pair<int, int>

const long long maxn = 131072;
long long n, m, u, v;
long long score[maxn][2], tot[2], ans;
vector<long long> al[maxn];
pll temp;
map<pll, long long> mp;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    while(m--){
        cin >> u >> v;
        al[max(u, v)].push_back(min(u, v));
    }
    tot[0] = 0; tot[1] = 0;
    for(int i=1; i<=n; i++){
        score[i][0] = i*i; score[i][1] = i*i*i;
        for(int j=0; j<al[i].size(); j++){
            //cout << i << " " << al[i][j] << endl;
            temp.first = score[al[i][j]][0];
            temp.second = score[al[i][j]][1];
            mp[temp]--;
            score[al[i][j]][0] += i*i; score[al[i][j]][1] += i*i*i;
            temp.first = score[al[i][j]][0];
            temp.second = score[al[i][j]][1];
            //cout << "tambah " << temp.first << "," << temp.second << endl;
            mp[temp]++;

            score[i][0] += al[i][j]*al[i][j];
            score[i][1] += al[i][j]*al[i][j]*al[i][j];
        }
        temp.first = score[i][0];
        temp.second = score[i][1];
        mp[temp]++;

        al[i].push_back(i);
        ans = 0; tot[0] += i*i; tot[1] += i*i*i;
        for(int j=0; j<al[i].size(); j++){
            temp.first = tot[0] - score[al[i][j]][0];
            temp.second = tot[1] - score[al[i][j]][1];
            ans += mp[temp];
        }
        if(i>1){
            cout << ans << " ";
        }
    }
    cout << endl;
}
