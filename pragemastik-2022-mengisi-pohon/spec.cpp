#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int minn = 2;
const int maxn = 100;
const int mina = 1;
const int maxa = 1000000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int n;
    vector<int> a;
    vector<int> u, v;
    vector<int> ans;

    void InputFormat() {
        LINE(n);
        LINE(a % SIZE(n));
        LINES(u, v) % SIZE(n-1);
    }

    void OutputFormat() {
        LINE(ans % SIZE(n));
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(minn <= n && n <= maxn);
        CONS(eachElementBetween(a, mina, maxa));
        CONS(validTree(n, u, v));
    }

private:
    bool eachElementBetween(const vector<int>& a, int mn, int mx) {
        for (int x : a) {
            if (x != -1 && (x < mn || x > mx)) return false;
        }
        return true;
    }

    bool validTree(int n, const vector<int>& u, const vector<int>& v) {
        if (u.size() != n-1 || u.size() != v.size()) return false;
        vector<vector<int>> adjl(n+1);
        for (int i=0; i<(int)u.size(); i++) {
            adjl[u[i]].push_back(v[i]);
            adjl[v[i]].push_back(u[i]);
        }
        vector<bool> vis(n+1, false);
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int uu = q.front();
            q.pop();
            if (vis[uu]) continue;
            vis[uu] = true;
            for (int vv : adjl[uu]) q.push(vv);
        }
        for (int i=1; i<=n; i++) {
            if (!vis[i]) return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    // void SampleTestCase1() {
    //     Input({
    //     });
    //     Output({
    //     });
    // }

    void BeforeTestCase(){
        a.clear();
        u.clear();
        v.clear();
        ans.clear();
    }

    void TestCases() {
        CASE(n = 6, randomLine(n, u, v), randomYesArray(n, u, v, a, 1, 10, 0));
        CASE(n = 6, randomLine(n, u, v), randomYesArray(n, u, v, a, 1, 10, 25));
        CASE(n = 6, randomLine(n, u, v), randomYesArray(n, u, v, a, 1, 10, 50));
        CASE(n = 6, randomLine(n, u, v), randomYesArray(n, u, v, a, 1, 10, 75));
        CASE(n = 6, randomLine(n, u, v), randomYesArray(n, u, v, a, 1, 10, 100));
        CASE(n = 6, randomTree(n, u, v), randomArray(n, a, 1, 10, 25));
        CASE(n = 6, randomTree(n, u, v), randomArray(n, a, 1, 10, 50));
        CASE(n = 6, randomTree(n, u, v), randomArray(n, a, 1, 10, 75));
        CASE(n = 6, randomTree(n, u, v), randomArray(n, a, 1, 10, 100));
        
        for (int i=0; i<20; i++) {
            CASE(n = rnd.nextInt(minn, maxn), randomLine(n, u, v), randomYesArray(n, u, v, a, mina, maxa, rnd.nextInt(0, 100)));
            CASE(n = maxn, randomLine(n, u, v), randomYesArray(n, u, v, a, mina, maxa, rnd.nextInt(0, 100)));
        }

        for (int i=0; i<10; i++) {
            CASE(n = rnd.nextInt(minn, maxn), randomLine(n, u, v), randomArray(n, a, mina, maxa, rnd.nextInt(0, 100)));
        }

        for (int i=0; i<6; i++) {
            CASE(n = rnd.nextInt(minn, maxn), randomTree(n, u, v), randomArray(n, a, mina, maxa, rnd.nextInt(0, 100)));
            CASE(n = maxn, randomTree(n, u, v), randomArray(n, a, mina, maxa, rnd.nextInt(0, 100)));
        }
    }

private:
    void renumber(int n, vector<int>& u, vector<int>& v) {
        vector<int> permutation;
        for (int i = 1; i <= n; i++) {
            permutation.push_back(i);
        }
        rnd.shuffle(permutation.begin(), permutation.end());
        for (int i = 0; i < u.size(); i++) {
            u[i] = permutation[u[i]];
            v[i] = permutation[v[i]];
        }
    }

    void randomTree(int n, vector<int>& u, vector<int>& v) {
        for (int i = 1; i < n; i++) {
            u.push_back(i);
            v.push_back(rnd.nextInt(0, i - 1));
        }
        renumber(n, u, v);
    }

    void randomLine(int n, vector<int>& u, vector<int>& v) {
        for (int i=1; i<n; i++) {
            u.push_back(i-1);
            v.push_back(i);
        }
        renumber(n, u, v);
    }

    void randomArray(int n, vector<int>& a, int mn, int mx, int ratio) {
        for (int i=0; i<n; i++) {
            int gacha = rnd.nextInt(1, 100);
            if (gacha <= ratio) a.push_back(rnd.nextInt(mn, mx));
            else a.push_back(-1);
        }
    }

    void randomYesArray(int n, vector<int>& u, vector<int>& v, vector<int>& a, int mn, int mx, int ratio) {
        set<int> s;
        for (int i=0; i<n; i++) {
            int val = rnd.nextInt(mn, mx);
            while (s.count(val)) val = rnd.nextInt(mn, mx);
            s.insert(val);
        }

        vector<vector<int>> adjl(n+1);
        for (int i=0; i<(int)u.size(); i++) {
            adjl[u[i]].push_back(v[i]);
            adjl[v[i]].push_back(u[i]);
        }

        int leaf;
        for (int i=1; i<=n; i++) {
            if (adjl[i].size() == 1) leaf = i;
        }

        a.resize(n);
        queue<pair<int, int>> q;
        q.emplace(leaf, 0);
        while (!q.empty()) {
            int uu = q.front().first, p = q.front().second;
            q.pop();
            int gacha = rnd.nextInt(1, 100);
            if (gacha <= ratio) a[uu-1] = *s.begin();
            else a[uu-1] = -1;
            s.erase(s.begin());
            for (int vv : adjl[uu]) {
                if (vv != p) q.emplace(vv, uu);
            }
        }
    }
};