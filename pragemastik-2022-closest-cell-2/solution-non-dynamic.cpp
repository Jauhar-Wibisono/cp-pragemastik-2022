#include <bits/stdc++.h>
using namespace std;

#define pll pair<long long, long long>

const long long maxn = 131072, maxm = 131072;
long long segtree[2][2][4*maxm];

void build(){
    for(int i=0; i<maxm; i++){
        segtree[0][0][i] = 0;
        segtree[0][1][i] = 0;
        segtree[1][0][i] = 0;
    }
}
void update(int id, int deg, int idx, int val){
    idx += 3*maxm;
    segtree[id][deg][idx] += val;
    idx /= 2;
    while(idx>0){
        segtree[id][deg][idx] += val;
        idx /= 2;
    }
}
long long query(int id, int deg, int lo, int hi){
    lo += 3*maxm; hi += 3*maxm;
    long long toReturn = 0;
    while(lo <= hi){
        if(lo%2){
            toReturn += segtree[id][deg][lo];
        }lo = (lo+1)/2;
        if(!(hi%2)){
            toReturn += segtree[id][deg][hi];
        }hi = (hi-1)/2;
    }
    return toReturn;
}

int q, type, nbTeman = 0;
pll teman[maxn], ab, abTot, wisp;

long long getPower(){
    return (
        abTot.first + abTot.second
        - query(0, 0, -maxm, wisp.first) - wisp.first * query(0, 1, -maxm, wisp.first)
        - query(1, 0, -maxm, wisp.second) - wisp.second * query(1, 1, -maxm, wisp.second)
    );
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    build();
    abTot.first = 0; abTot.second = 0;
    cin >> q;
    while(q--){
        cin >> type; type--;
        if(type){
            cin >> wisp.first >> wisp.second;
            cout << getPower() << endl;
        }else{
            cin >> teman[nbTeman].first >> teman[nbTeman].second >> ab.first >> ab.second;
            abTot.first += ab.first;
            abTot.second += ab.second;

            //cout << "masuk" << endl;
            update(0, 1, teman[nbTeman].first - ab.first + 1, 1); 
            update(0, 1, teman[nbTeman].first + 1, -2);
            update(0, 1, teman[nbTeman].first + ab.first + 1, 1);
            update(0, 0, teman[nbTeman].first - ab.first + 1, - teman[nbTeman].first + ab.first);
            update(0, 0, teman[nbTeman].first + 1, 2 * teman[nbTeman].first);
            update(0, 0, teman[nbTeman].first + ab.first + 1, - teman[nbTeman].first - ab.first);
            //cout << "masuk" << endl;
            update(1, 1, teman[nbTeman].second - ab.second + 1, 1); 
            update(1, 1, teman[nbTeman].second + 1, -2);
            update(1, 1, teman[nbTeman].second + ab.second + 1, 1);
            update(1, 0, teman[nbTeman].second - ab.second + 1, - teman[nbTeman].second + ab.second);
            update(1, 0, teman[nbTeman].second + 1, 2 * teman[nbTeman].second);
            update(1, 0, teman[nbTeman].second + ab.second + 1, - teman[nbTeman].second - ab.second);
            //cout << "masuk" << endl;

            nbTeman++;
        }
    }
    long long minPower[2] = {1e18, 1e18};
    for(int i=0; i<nbTeman; i++){
        minPower[0] = min(abTot.first - query(0, 0, -maxm, teman[i].first) - teman[i].first * query(0, 1, -maxm, teman[i].first), minPower[0]);
        minPower[1] = min(abTot.second - query(1, 0, -maxm, teman[i].second) - teman[i].second * query(1, 1, -maxm, teman[i].second), minPower[1]);
    }
    cout << minPower[0] + minPower[1] << endl;
}