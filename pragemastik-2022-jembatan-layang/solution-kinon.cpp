#include <bits/stdc++.h>
using namespace std;

#define pll pair<int, int>

const long long maxn = 131072, mod = 998244353;
pll bridges[2*maxn], queries[maxn];
long long n, q, nbh;
long long ans[maxn], segtree[2*maxn];

void build(){
    for(int i=0; i<maxn; i++){
        if(i<n){
            segtree[maxn+i] = 0;
        }else{
            segtree[maxn+i] = 1;
        }
    }
}
void update(int idx, int val){
    idx += maxn;
    segtree[idx] += val;
    idx /= 2;
    while(idx>0){
        segtree[idx] = segtree[2*idx] * segtree[2*idx+1] % mod;
        idx /= 2;
    }
}
long long query(int lo, int hi){
    lo += maxn; hi += maxn;
    long long res = 1;
    while(lo <= hi){
        if(lo%2){
            res = res * segtree[lo] % mod;
        } lo = (lo+1)/2;
        if(!(hi%2)){
            res = res * segtree[hi] % mod;
        } hi = (hi-1)/2;
    }
    return res;
}
long long print(int lo, int hi){
    lo += maxn; hi += maxn;
    long long res = 1;
    while(lo <= hi){
        for(int i=lo; i<=hi; i++){
            cout << segtree[i] << " ";
        }cout << endl;
        lo = (lo+1)/2;
        hi = (hi-1)/2;
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    int idx = 0;
    for(int i=0; i<n; i++){
        cin >> nbh;
        while(nbh--){
            cin >> bridges[idx].first;
            bridges[idx].second = i;
            idx++;
        }
    }
    sort(bridges, bridges + idx);
    for(int i=0; i<q; i++){
        cin >> queries[i].first;
        queries[i].second = i;
    }
    sort(queries, queries+q);
    /*
    for(int i=0; i<idx; i++){
        cout << bridges[i].first << " " << bridges[i].second << endl;
    }
    */
    int idxb = 0;
    for(int i=0; i<q; i++){
        while(idxb < idx && bridges[idxb].first <= queries[i].first){
            //cout << bridges[idxb].first << " " << bridges[idxb].second << endl;
            update(bridges[idxb].second, 1); idxb++;
        }
        //cout << endl; print(0, n-1); cout << endl;
        ans[queries[i].second] = query(0, n-1);
    }

    for(int i=0; i<q; i++){
        cout << ans[i] << endl;
    }
}
