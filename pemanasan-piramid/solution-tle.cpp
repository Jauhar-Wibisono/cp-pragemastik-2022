#include <bits/stdc++.h>
using namespace std;

long long mod = 1e9+7;
int n, a[200069], ans;

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n;
    ans = 0;
    for(int i=n; i>0; i--){
        for(int j=0; j<i; j++){
            if(i==n){
                cin >> a[j];
            }else{
                a[j] = (a[j]+a[j+1])%mod;
            }
            ans = (ans+a[j])%mod;
        }
    }
    cout << ans << endl;
}