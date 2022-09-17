#include <bits/stdc++.h>
using namespace std;

#define pll pair<long long, long long>

map<pll, map<pll, long long> > mp;
const int maxn = 8192;
long long n, ans, gcd;
pll xy[maxn], sum, dif, zeros;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    ans = 0;
    zeros.first = 0; zeros.second = 0;
    for(int i=0; i<n; i++){
        cin >> xy[i].first;
    }
    for(int i=0; i<n; i++){
        cin >> xy[i].second;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            sum.first = xy[i].first + xy[j].first;
            sum.second = xy[i].second + xy[j].second;
            dif.first = xy[i].first - xy[j].first;
            dif.second = xy[i].second - xy[j].second;
            if(dif.first < 0){
                dif.first *= -1; dif.second *= -1;
            }

            gcd = abs(__gcd(dif.first, dif.second));
            dif.first /= gcd;
            dif.second /= gcd;

            ans += mp[sum][zeros]; mp[sum][zeros]++;
            ans -= mp[sum][dif]; mp[sum][dif]++;
        }
        //cout << ans << endl;
    }
    cout << ans << endl;
}