#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int EXIT_AC = 42;
const int EXIT_WA = 43;

const int mina = 1, maxa = 1000000;

int wa() {
    cout << "WA" << endl;
    return 0;
}

int ac() {
    cout << "AC" << endl;
    return 0;
}

int main(int argc, char* argv[]) {
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);
    ifstream con_out(argv[3]);

    int n;
    tc_in >> n;
    vector<int> a(n+1);
    for (int i=1; i<=n; i++) tc_in >> a[i];
    vector<vector<int>> adjl(n+1);
    for (int i=1; i<n; i++) {
        int u, v;
        tc_in >> u >> v;
        adjl[u].push_back(v);
        adjl[v].push_back(u);
    }

    vector<int> ans(n+1);
    if (!(con_out >> ans[1])) {
        cerr << "not enough values" << endl;
        return wa();
    }
    int impossible;
    tc_out >> impossible;
    if (impossible == -1) {
        if (ans[1] != -1) {
            cerr << "contestant has solution while judge doesn't" << endl;
            return wa();
        } else {
            return ac();
        }
    }

    for (int i=2; i<=n; i++) {
        if (!(con_out >> ans[i])) {
            cerr << "not enough values" << endl;
            return wa();
        }
    }

    for (int i=1; i<=n; i++) {
        if (ans[i] < mina || ans[i] > maxa) {
            cerr << "value out of bounds: " << ans[i] << " on node " << i << endl;
            return wa();
        }
    }

    for (int i=1; i<=n; i++) {
        if (a[i] != -1 && ans[i] != a[i]) {
            cerr << "contestant overwrote a non-(-1) value on node " << i << endl;
            return wa();
        }
    }

    int leaf;
    for (int i=1; i<=n; i++) {
        if (adjl[i].size() == 1) leaf = i;
    }

    vector<int> ord;
    queue<pair<int, int>> q;
    q.emplace(leaf, 0);
    while (!q.empty()) {
        int u = q.front().first, p = q.front().second;
        q.pop();
        ord.push_back(ans[u]);
        for (int v : adjl[u]) {
            if (v == p) continue;
            q.emplace(v, u);
        }
    }

    vector<int> asc = ord, desc = ord;
    sort(asc.begin(), asc.end());
    sort(desc.rbegin(), desc.rend());
    if (ord != asc && ord != desc) {
        cerr << "non-sorted path exists" << endl;
        return wa();
    }

    return ac();
}