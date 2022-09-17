#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9+7, inv2 = (mod+1)/2, inv3 = (mod+1)/3;
long long t, n, m, ans;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n >> m;
        //2*ans = sigma[i=1..n+1][j=1..m+1](i*j C 2 - ekslusi) - (n+1)*(m+1)C2
        //2*ans = 0.5*sigma[i=1..n+1][j=1..m+1](i*i*j*j - i*j - ekslusi) - 0.5((n+1)**2 (m+1)**2 - (n+1)(m+1))
        //2*ans = 0.5(n+1)(n+2)(2n+3)/6 (m+1)(m+2)(2m+3)/6 - 0.5(n+1)(n+2)/2 (m+1)(m+2)/2 - ... - 0.5 sigma (ekslusi)
        long long nSum = n*(n+1)%mod *inv2%mod;
        long long mSum = m*(m+1)%mod *inv2%mod;
        long long nSumSquare = nSum *(2*n+1)%mod *inv3%mod;
        long long mSumSquare = mSum *(2*m+1)%mod *inv3%mod;
        ans = nSumSquare * mSumSquare % mod;
        ans += mod - nSum * mSum % mod; 
        ans %= mod;
        ans += mod - (n*n%mod) *(m*m%mod) %mod;
        ans = (ans + n*m) % mod;
        cout << ans << endl;
        
        //ekslusi(i, j) = (n-2i)(m-2j) + (n-3i)(m-3j) + ... = 
        long long sigmaEkslusi = 0;
        for(int i=1; i<=min(n, m); i++){ // Ulang berdasarkan kemunculan suku
            long long nDivCount = (n+i-1)/i;
            long long mDivCount = (m+i-1)/i;
            sigmaEkslusi += nDivCount*mDivCount%mod *n%mod *m%mod; 
            sigmaEkslusi %= mod;
            long long nSumDiv = nDivCount*(nDivCount+1)%mod *inv2%mod;
            long long mSumDiv = mDivCount*(mDivCount+1)%mod *inv2%mod;
            sigmaEkslusi += nSumDiv*mSumDiv%mod *i%mod *i%mod;
            sigmaEkslusi %= mod;

            sigmaEkslusi += mod - nSumDiv*i%mod *mDivCount%mod *m%mod;
            sigmaEkslusi %= mod;
            sigmaEkslusi += mod - mSumDiv*i%mod *nDivCount%mod *n%mod;
            sigmaEkslusi %= mod;
            cout << sigmaEkslusi << endl;
        }
        sigmaEkslusi += mod - nSum * mSum % mod;
        sigmaEkslusi % mod;
        cout << sigmaEkslusi << endl;

        ans += mod - sigmaEkslusi;
        ans %= mod;
        ans = ans * inv2%mod *inv2%mod;
        cout << ans << endl;
    }
}