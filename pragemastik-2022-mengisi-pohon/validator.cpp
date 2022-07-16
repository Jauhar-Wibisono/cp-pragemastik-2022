#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int EXIT_AC = 42;
const int EXIT_WA = 43;

const int mina = 1, maxa = 1000000;

int wa() {
    exit(EXIT_WA);
}

int ac() {
    exit(EXIT_AC);
}

int main(int argc, char* argv[]) {
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);
    string feedback_path = argv[3];
    feedback_path += "/judgeerror.txt";
    ofstream feedback(feedback_path);

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

    bool impossible = false;
    for (int i=1; i<=n; i++) {
        if (adjl[i].size() > 2) impossible = true;
    }

    if (impossible) {
        int ans;
        if (!(cin >> ans)) {
            feedback << "no output" << endl;
            return wa();
        }
        if (ans != -1) {
            feedback << "contestant has answer while judge doesn't" << endl;
            return wa(); 
        }
        return ac();
    } else {
        vector<int> ans(n+1);
        for (int i=1; i<=n; i++) {
            if (!cin >> ans[i]) {
                feedback << "not enough values" << endl;
                return wa();
            }
            if (ans[i] < mina || ans[i] > maxa) {
                feedback << "value out of bounds" << endl;
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
            feedback << "non-sorted path exists" << endl;
            return wa();
        }

        return ac();
    }
}