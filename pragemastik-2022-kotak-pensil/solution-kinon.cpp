#include <bits/stdc++.h>
using namespace std;

const int maxn = 128;
int n, m, ans, cur;
string board[maxn];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m; ans = 0;
	for(int i=0; i<n; i++){
        cin >> board[i];
        cur = 0;
        for(int j=0; j<m; j++){
            if(board[i][j] == '0'){
                cur ++;
            }else{
                ans = max(ans, cur); cur = 0;
            }
        }
        ans = max(ans, cur);
	}
	for(int i=0; i<m; i++){
        cur = 0;
        for(int j=0; j<n; j++){
            if(board[j][i] == '0'){
                cur ++;
            }else{
                ans = max(ans, cur); cur = 0;
            }
        }
        ans = max(ans, cur);
	}
	cout << ans << endl;
	return 0;
}
