#include <bits/stdc++.h>
using namespace std;

const long long maxn = 262144;
long long n, temp, a[25][maxn], to[maxn], delta[maxn];
long long prefix[maxn][2], suffix[maxn][2], xorCount[2];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> temp;
        for(int j=0; j<25; j++){
            a[j][i] = temp%2;
            temp /= 2;
        }
        to[i] = 0; delta[i] = 0;
    }
    long long pow2 = 1;
    for(int i=0; i<25; i++){
        for(int j=0; j<2; j++){
            prefix[0][j] = 1-j;
            suffix[n][j] = 1-j;
        }

        for(int j=1; j<=n; j++){
            prefix[j][0] = prefix[j-1][a[i][j-1]];
            prefix[j][1] = prefix[j-1][1-a[i][j-1]];
            prefix[j][a[i][j-1]]++;
        }
        for(int j=n-1; j>=0; j--){
            suffix[j][0] = suffix[j+1][a[i][j]];
            suffix[j][1] = suffix[j+1][1-a[i][j]];
            suffix[j][a[i][j]]++;
        }

        for(int j=0; j<n; j++){
            xorCount[0] = prefix[j][0] * suffix[j+1][0] + prefix[j][1] * suffix[j+1][1];
            xorCount[1] = prefix[j][0] * suffix[j+1][1] + prefix[j][1] * suffix[j+1][0];
            if(a[i][j]){
                // Addition kalau ganti bit
                if(xorCount[1] >= xorCount[0]){
                    delta[j] += pow2*(xorCount[1]-xorCount[0]);
                }else{
                    to[j] += pow2;
                }
            }else{
                // Addition kalau ganti bit
                if(xorCount[0] > xorCount[1]){
                    delta[j] += pow2*(xorCount[0]-xorCount[1]);
                    to[j] += pow2;
                }
            }
        }

        pow2 *= 2;
    }

    long long maxIdx = 0;
    for(int i=1; i<n; i++){
        if(delta[i] > delta[maxIdx]){
            maxIdx = i;
        }
    }
    cout << maxIdx+1 << " " << to[maxIdx] << endl;
}