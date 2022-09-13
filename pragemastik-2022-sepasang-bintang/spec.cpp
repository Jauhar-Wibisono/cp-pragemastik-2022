#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int minn = 2;
const int maxn = 100000;
const int maxm = 200000;

class ProblemSpec : public BaseProblemSpec {
protected:
	int n, m;
    vector<int> u, v;
    vector<long long> ans;

	void InputFormat() {
        LINE(n, m);
        LINES(u, v) % SIZE(m);
	}

    void OutputFormat1() {
    	LINE(ans % SIZE(n-1));
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(minn <= n && n <= maxn);
        CONS(0 <= m && m <= maxm);
        CONS(eachElementBetween(u, 1, n));
        CONS(eachElementBetween(v, 1, n));
        CONS(noSelfLoop(m, u, v));
        CONS(noMultiEdge(n, m, u, v));
    }

private:
    bool eachElementBetween(vector<int> v, int a, int b){
        for(int i = 0; i < v.size(); i++){
            if(v[i] < a || v[i] > b)
                return false;
        }
        return true;
    }

    bool noSelfLoop(int m, vector<int>& u, vector<int>& v) {
        for (int i=0; i<m; i++) {
            if (u[i] == v[i]) return false;
        }
        return true;
    }
    
    bool noMultiEdge(int n, int m, const vector<int>& u, const vector<int>& v) {
        vector<set<int>> adjl(n+1);
        for (int i=0; i<m; i++) {
            if (adjl[u[i]].count(v[i])) return false;
            if (adjl[v[i]].count(u[i])) return false;
            adjl[u[i]].insert(v[i]);
            adjl[v[i]].insert(u[i]);
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
        	"6 7",
            "1 3",
            "2 5",
            "6 1",
            "1 5",
            "4 2",
            "4 5",
            "5 6"
        });
        Output({
        	"1 2 4 2 0"
        });
    }

    void SampleTestCase2() {
        Input({
            "6 6",
            "1 3",
            "2 5",
            "3 6",
            "1 5",
            "4 2",
            "4 5"
        });
        Output({
            "1 2 4 2 3"
        });
    }

    void BeforeTestCase(){
    	u.clear();
        v.clear();
    }

    void TestCases() {
        for (int i=0; i<30; i++) {
            CASE(n = rnd.nextInt(10, 30), m = rnd.nextInt(0, n*(n-1)/2), randomGraph(n, m, u, v));
        }

        for (int i=0; i<10; i++) {
            CASE(n = rnd.nextInt(10, 100), m = rnd.nextInt(0, (n-1)*(n-2)/2), bigStarPairGraph(n, m, u, v, rnd.nextInt(0, n-2)));
            CASE(n = 100, m = maxm, pairOfCompleteGraph(n, m, u, v, 5*(i+1)));
        }

        for (int i=0; i<2; i++) {
            CASE(n = rnd.nextInt(100, 1000), m = maxm, randomGraph(n, m, u, v));
            CASE(n = rnd.nextInt(maxn/3, maxn), m = maxm, randomGraph(n, m, u, v));    
        }

        for (int i=0; i<6; i++) {
            CASE(n = rnd.nextInt(100, 1000), m = maxm, bigStarPairGraph(n, m, u, v, rnd.nextInt(0, n-2)));
            CASE(n = rnd.nextInt(maxn/3, maxn), m = maxm, bigStarPairGraph(n, m, u, v, rnd.nextInt(0, n-2)));
            CASE(n = rnd.nextInt(100, 1000), m = maxm, pairOfCompleteGraph(n, m, u, v, rnd.nextInt(1, n)));
            CASE(n = rnd.nextInt(maxn/3, maxn), m = maxm, pairOfCompleteGraph(n, m, u, v, rnd.nextInt(1, (int)sqrt(maxm))));
        }

        CASE(n = sqrt(maxm), m = maxm, pairOfCompleteGraph(n, m, u, v, 1));
        CASE(n = sqrt(maxm), m = maxm, pairOfCompleteGraph(n, m, u, v, n/2));
    }

private:
    void permute(vector<int>& u, vector<int>& v) {
        int n = u.size();
        vector<int> perm(n);
        for (int i=0; i<n; i++) perm[i] = i;
        rnd.shuffle(perm.begin(), perm.end());
        vector<int> ou = u, ov = v;
        for (int i=0; i<n; i++) {
            u[i] = ou[perm[i]];
            v[i] = ov[perm[i]];
        }
    }

    void randomSwap(vector<int>& u, vector<int>& v) {
        int n = u.size();
        for (int i=0; i<n; i++) {
            int gacha = rnd.nextInt(1, 100);
            if (gacha <= 50) swap(u[i], v[i]);
        }
    }

    // might need to rework approach if too slow
    void randomGraph(int n, int& m, vector<int>& u, vector<int>& v) {
        set<pair<int, int>> st; 
        while (u.size() < m) {
            int cu = rnd.nextInt(1, n);
            int cv = rnd.nextInt(1, n);
            for (int i=0; i<100 && (cu == cv || st.count(make_pair(cu, cv)) || st.count(make_pair(cv, cu))); i++) {
                cu = rnd.nextInt(1, n);
                cv = rnd.nextInt(1, n);
            }
            if (cu == cv || st.count(make_pair(cu, cv)) || st.count(make_pair(cv, cu))) break;
            st.emplace(cu, cv);
            u.push_back(cu);
            v.push_back(cv);
        }
        m = u.size();
    }

    void bigStarPairGraph(int n, int& m, vector<int>& u, vector<int>& v, int s1) {
        m = max(m, n-2);

        vector<int> perm(n);
        for (int i=0; i<n; i++) perm[i] = i+1;
        rnd.shuffle(perm.begin(), perm.end());
        
        for (int i=0; i<s1; i++) {
            int swap = rnd.nextInt(0, 1);
            u.push_back((swap ? perm[0] : perm[i+2]));
            v.push_back((swap ? perm[i+2] : perm[0]));
        }
        for (int i=s1; i+2<n; i++) {
            int swap = rnd.nextInt(0, 1);
            u.push_back((swap ? perm[1] : perm[i+2]));
            v.push_back((swap ? perm[i+2] : perm[1]));   
        }

        set<pair<int, int>> st; 
        while (u.size() < m) {
            int i = rnd.nextInt(2, n-1);
            int j = rnd.nextInt(2, n-1);
            for (int k=0; k<100 && (i == j || st.count(make_pair(i, j)) || st.count(make_pair(j, i))); k++) {
                int i = rnd.nextInt(2, n-1);
                int j = rnd.nextInt(2, n-1);
            }
            if (i == j || st.count(make_pair(i, j)) || st.count(make_pair(j, i))) break;
            st.emplace(i, j);
            u.push_back(perm[i]);
            v.push_back(perm[j]);
        }

        m = u.size();
    }

    void pairOfCompleteGraph(int n, int& m, vector<int>& u, vector<int>& v, int s1) {
        for (int i=2; i<=s1 && u.size()<m; i++){
            for (int j=1; j<i && u.size()<m; j++) {
                u.push_back(i);
                v.push_back(j);
            }
        }
        for (int i=s1+2; i<=n && u.size()<m; i++){
            for (int j=s1+1; j<i && u.size()<m; j++) {
                u.push_back(i);
                v.push_back(j);
            }
        }

        m = u.size();
        permute(u, v);
        randomSwap(u, v);
    }
};