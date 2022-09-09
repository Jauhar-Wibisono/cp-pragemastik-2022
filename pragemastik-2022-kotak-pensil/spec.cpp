#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int maxn = 100;
const int maxm = 100;

class ProblemSpec : public BaseProblemSpec {
protected:
	int n, m;
    vector<string> a;
    int ans;

	void InputFormat() {
        LINE(n, m);
        LINES(a) % SIZE(n);
	}

    void OutputFormat() {
    	LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= n && n <= maxn);
        CONS(1 <= n && n <= maxm);
        CONS(validGridCharacters(a));
        CONS(exists0(a));
    }

private:
	bool validGridCharacters(const vector<string>& a) {
        for (auto r : a) {
            for (char c : r) {
                if (c != '0' && c != '1') return false;
            }
        }
        return true;
    }

    bool exists0(const vector<string>& a) {
        for (auto r : a) {
            for (char c : r) {
                if (c == '0') return true;
            }
        }
        return false;
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
    }

    void TestCases() {
        for (int i=0; i<10; i++) {
            CASE(n = rnd.nextInt(1, maxn), m = rnd.nextInt(1, maxm), randomGrid(n, m, a, 0));
        }
        for (int i=0; i<30; i++) {
            CASE(n = rnd.nextInt(1, 20), m = rnd.nextInt(1, 20), randomGrid(n, m, a, 50+50/(i+1)));   
        }
        for (int i=0; i<10; i++) {
            CASE(n = rnd.nextInt(1, maxn), m = rnd.nextInt(1, maxm), randomGrid(n, m, a, 50+50/(i+1)));      
        }
    }

private:
	void randomGrid(int n, int m, vector<string>& a, int ratio) {
        a.resize(n);
        for (int i=0; i<n; i++) a[i].assign(m, '.');

        {
            int r = rnd.nextInt(0, n-1);
            int c = rnd.nextInt(0, m-1);
            a[r][c] = '0';
        }

        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (a[i][j] != '.') continue;
                a[i][j] = (rnd.nextInt(1, 100) <= ratio ? '1' : '0');
            }
        }
    }
};