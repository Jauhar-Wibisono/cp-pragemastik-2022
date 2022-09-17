#include <bits/stdc++.h>
using namespace std;

#define pll pair<long long, long long>

const long long maxn = 131072, maxm = 2e9;
long long node[2][2] = {{0, 0}, {0, 0}};
long long segtree[2][2][50*maxn], range[2][2][50*maxn][2], childID[2][2][50*maxn][2];

void create(int id, int deg, long long l, long long r){
    //cout << node << " " << l << " " << r << endl;
    range[id][deg][node[id][deg]][0] = l;
    range[id][deg][node[id][deg]][1] = r;
    segtree[id][deg][node[id][deg]] = 0;
    childID[id][deg][node[id][deg]][0] = -1;
    childID[id][deg][node[id][deg]][1] = -1;
    node[id][deg]++;
}
void update(int id, int deg, long long k, long long val){
    long long curnode = 0;
    while(range[id][deg][curnode][0] < range[id][deg][curnode][1]){
        segtree[id][deg][curnode] += val;
        long long sum = range[id][deg][curnode][0] + range[id][deg][curnode][1];
        long long mid = sum/2;
        if(sum < 0){mid = (sum-1)/2;}

        long long child = 0, l = range[id][deg][curnode][0], r = mid;
        if(k>mid){
            child = 1;
            l = mid+1;
            r = range[id][deg][curnode][1];
        }
        if(childID[id][deg][curnode][child] < 0){
            childID[id][deg][curnode][child] = node[id][deg];
            create(id, deg, l, r);
        }
        curnode = childID[id][deg][curnode][child];
    }
    segtree[id][deg][curnode] += val;
}
long long query(int id, int deg, long long l, long long r, long long curnode=0){
    //cout << "queried " << curnode << " " << l << " " << r << endl;
    if(l == range[id][deg][curnode][0] && r == range[id][deg][curnode][1]){
        return segtree[id][deg][curnode];
    }
 
    long long toReturn = 0;
    long long sum = range[id][deg][curnode][0] + range[id][deg][curnode][1];
    long long mid = sum/2;
    if(sum < 0){mid = (sum-1)/2;}

    if(childID[id][deg][curnode][0] >= 0 && l<=mid){
        toReturn += query(id, deg, l, min(mid, r), childID[id][deg][curnode][0]);
    }
    if(childID[id][deg][curnode][1] >= 0 && r>mid){
        toReturn += query(id, deg, max(mid+1, l), r, childID[id][deg][curnode][1]);
    }
    return toReturn;
}

int q, type, nbTeman = 0;
pll teman[maxn], ab, abTot, wisp;

long long getPower(){
    return (
        (long long) abTot.first + abTot.second
        - query(0, 0, -maxm, wisp.first) - wisp.first * query(0, 1, -maxm, wisp.first)
        - query(1, 0, -maxm, wisp.second) - wisp.second * query(1, 1, -maxm, wisp.second)
    );
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    create(0, 0, -maxm, maxm);
    create(0, 1, -maxm, maxm);
    create(1, 0, -maxm, maxm);
    create(1, 1, -maxm, maxm);

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