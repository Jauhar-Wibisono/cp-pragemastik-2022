#include <bits/stdc++.h>
using namespace std;

#define pll pair<int, int>

const int maxn = 4096;
long long n, ans, g;
pll xy[maxn], sum, dif;
pair<pll, pll> ppll[maxn*maxn/2];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> xy[i].first;
    }
    for(int i=0; i<n; i++){
        cin >> xy[i].second;
    }
    int idx = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            ppll[idx].first.first = xy[i].first + xy[j].first;
            ppll[idx].first.second = xy[i].second + xy[j].second;
            dif.first = xy[i].first - xy[j].first;
            dif.second = xy[i].second - xy[j].second;
            if(dif.first < 0){
                dif.first *= -1; dif.second *= -1;
            }
            g = abs(__gcd(dif.first, dif.second));
            ppll[idx].second.first = dif.first / g;
            ppll[idx].second.second = dif.second / g;
            idx++;
        }
        //cout << i << " " << mp.size() << endl;
    }
    sort(ppll, ppll+idx);
    g = 1;
    for(int i=1; i<idx; i++){
        if(ppll[i].first != ppll[i-1].first){
            ans += g*(g-1)/2;
            g = 1;
        }else{
            g++;
        }
    }
    ans += g*(g-1)/2;
    g = 1;
    for(int i=0; i<idx; i++){
        if(ppll[i]== ppll[i-1]){
            g++;
        }else{
            ans -= g*(g-1)/2;
            g = 1;
        }
    }
    ans -= g*(g-1)/2;
    cout << ans << endl;
}
