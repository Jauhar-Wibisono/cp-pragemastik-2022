#include <bits/stdc++.h>
using namespace std;

bool ansSmall[3][4] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1}
};
bool ansLarge[3][9] = {
    {1, 1, 0, 0, 1, 1, 1, 0, 0},
    {1, 1, 1, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 1}
};
int t, a;
string s;
long long ones, twos;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> t;
    while(t--){
        cin >> twos;
        cin >> twos;

        cin >> ones;
        cin >> ones;
        cin >> a; cin >> a;
        ones += a;

        cin >> a;
        twos += 3*a;

        if(twos > 3){
            if(ansLarge[ones%3][twos%9]){
                cout << "Arcello" << endl;
            }else{
                cout << "Bisono" << endl;
            }
        }else{
            if(ansSmall[ones%3][twos%9]){
                cout << "Arcello" << endl;
            }else{
                cout << "Bisono" << endl;
            }
        }
    }
}