#include <bits/stdc++.h>
using namespace std;

const int maxn = 131072;
long long n, ord[maxn], isi[maxn], ans[maxn];
vector<long long> al[maxn];

void init(){
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> isi[i];
    }
    long long u, v;
    for(int i=1; i<n; i++){
        cin >> u >> v;
        al[u].push_back(v);
        al[v].push_back(u);
    }

}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    init();
    for(int i=1; i<=n; i++){
        if(al[i].size() > 2){
            cout << -1 << endl;
            return 0;
        }else if(al[i].size() == 1){
            ord[0] = i;
        }
    }
    ord[1] = al[ord[0]][0];
    for(int i=1; i<n-1; i++){
        if(al[ord[i]][0] == ord[i-1]){
            ord[i+1] = al[ord[i]][1];
        }else{
            ord[i+1] = al[ord[i]][0];
        }
    }
    bool mungkin = true;
    ans[ord[0]] = max((long long)1, isi[ord[0]]);
    for(int i=1; i<n && mungkin; i++){
        if(isi[ord[i]] < 0){
            ans[ord[i]] = ans[ord[i-1]]+1;
        }else if(isi[ord[i]] > ans[ord[i-1]]){
            ans[ord[i]] = isi[ord[i]];
        }else{
            mungkin = false;
        }
    }
    if(mungkin && ans[ord[n-1]] <= 1e6){
        for(int i=1; i<=n; i++){
            cout << ans[i] << " ";
        }cout << endl;
        return 0;
    }
    mungkin = true;
    if(isi[ord[0]] < 0){
        ans[ord[0]] = 1e6;
    }else{
        ans[ord[0]] = isi[ord[0]];
    }
    for(int i=1; i<n && mungkin; i++){
        if(isi[ord[i]] < 0){
            ans[ord[i]] = ans[ord[i-1]]-1;
        }else if(isi[ord[i]] < ans[ord[i-1]]){
            ans[ord[i]] = isi[ord[i]];
        }else{
            mungkin = false;
        }
    }
    if(mungkin && ans[ord[n-1]] > 0){
        for(int i=1; i<=n; i++){
            cout << ans[i] << " ";
        }cout << endl;
        return 0;
    }
    cout << -1 << endl;
    return 0;
}

