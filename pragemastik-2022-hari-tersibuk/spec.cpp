#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int minn = 2;
const int maxn = 200000;
const int minh = 1;
const int maxh = 200000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int n, h;
    vector<int> p, l, r;
    vector<int> ans;

    void InputFormat() {
        LINE(n, h);
        LINE(p % SIZE(n-1));
        LINES(l, r) % SIZE(n);
    }

    void OutputFormat() {
        LINE(ans % SIZE(n));
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(minn <= n && n <= maxn);
        CONS(minh <= h && h <= maxh);
        CONS(validTree(n, p));
        CONS(validSegs(n, h, l, r));
    }

private:
    bool validTree(int n, vector<int> p) {
        if (p.size() != n-1) return false;
        vector<vector<int>> adjl(n+1);
        for (int i=0; i<(int)p.size(); i++) {
            adjl[p[i]].push_back(i+2);
        }
        vector<bool> vis(n+1, false);
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (vis[u]) return false;
            vis[u] = true;
            for (int v : adjl[u]) q.push(v);
        }
        for (int i=1; i<=n; i++) {
            if (!vis[i]) return false;
        }
        return true;
    }
    bool validSegs(int n, int h, vector<int> l, vector<int> r) {
        if (l.size() != n || r.size() != n) return false;
        for (int i=0; i<n; i++) {
            if (l[i] < 1 || l[i] > r[i] || r[i] > h) return false;
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
        p.clear();
        l.clear();
        r.clear();
        ans.clear();
    }

    void TestCases() {
        for (int i=0; i<3; i++) {
            CASE(n = i+7, h = 10, randomTree(n, p), randomSegs(n, h, l, r));
        }
        for (int i=0; i<15; i++) {
            CASE(n = rnd.nextInt(50, 500), h = rnd.nextInt(50, 500), randomTree(n, p), randomSegs(n, h, l, r));
        }
        for (int i=0; i<3; i++) {
            CASE(n = rnd.nextInt(50, 500), h = rnd.nextInt(50, 500), randomTree(n, p), randomUnitSegs(n, h, l, r));
        }
        CASE(n = rnd.nextInt(50, 500), h = 1, randomTree(n, p), randomSegs(n, h, l, r));
        CASE(n = rnd.nextInt(50, 500), h = rnd.nextInt(50, 500), kTree(n, 1, p), randomSegs(n, h, l, r));
        CASE(n = rnd.nextInt(50, 500), h = rnd.nextInt(50, 500), kTree(n, 2, p), randomSegs(n, h, l, r));
        CASE(n = rnd.nextInt(50, 500), h = rnd.nextInt(50, 500), kTree(n, 3, p), randomSegs(n, h, l, r));
        CASE(n = rnd.nextInt(50, 500), h = rnd.nextInt(50, 500), kTree(n, n-1, p), randomSegs(n, h, l, r));
        for (int i=0; i<3; i++) {
            CASE(n = maxn, h = maxh, randomTree(n, p), randomSegs(n, h, l, r));
        }
        CASE(n = maxn/4, h = maxh, kTree(n, 1, p), randomSegs(n, h, l, r));
        CASE(n = maxn, h = maxh, kTree(n, 2, p), randomSegs(n, h, l, r));
        CASE(n = maxn, h = maxh, kTree(n, n-1, p), randomSegs(n, h, l, r));
    }

private:
    void randomTree(int n, vector<int> &p) {
        for (int i=2; i<=n; i++) {
            int u = rnd.nextInt(1, i-1);
            p.push_back(u);
        }
    }
    void kTree(int n, int k, vector<int> &p) {
        for (int i=2; i<=n; i++) {
            p.push_back((i-2)/k + 1);
        }
    }
    void randomSegs(int n, int h, vector<int> &l, vector<int> &r) {
        for (int i=0; i<n; i++) {
            int ll = rnd.nextInt(minh, h);
            int rr = rnd.nextInt(minh, h);
            if (ll > rr) swap(ll, rr);
            l.push_back(ll);
            r.push_back(rr);
        }
    }
    void randomUnitSegs(int n, int h, vector<int> &l, vector<int> &r) {
        for (int i=0; i<n; i++) {
            int pos = rnd.nextInt(1, h);
            l.push_back(pos);
            r.push_back(pos);
        }
    }
};