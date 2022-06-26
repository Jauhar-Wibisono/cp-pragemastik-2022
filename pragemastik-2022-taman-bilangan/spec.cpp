#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int minn = 2;
const int maxn = 12;

class ProblemSpec : public BaseProblemSpec {
protected:
	int n;
	vector<vector<int>> a;
	int ans;

	void InputFormat() {
	  LINE(n);
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
        CONS(minn <= n && n <= maxn);
        CONS(isPermutation(a, n));
    }

private:
    bool isPermutation(vector<vector<int>> a, int n) {
        vector<int> b;
        for (auto r : a) {
            for (int x : r) {
                b.push_back(x);
            }
        }
        sort(b.begin(), b.end());
        int nb = b.size();
        if (nb != n*n) return false;
        for (int i=0; i<nb; i++) {
            if (b[i] != i+1) return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    // void SampleTestCase1() {
    //     Input({
    //         "5",
    //         "-2 2",
    //         "-1 5",
    //         "2 5",
    //         "4 0",
    //         "0 -3"
    //     });
    //     Output({
    //     	"15"
    //     });
    // }

    // void SampleTestCase2(){
    // 	Input({
    // 		"4",
    //         "0 0",
    //         "1 1",
    //         "2 0",
    //         "1 -1"
    // 	});
    // 	Output({
    // 		"2"
    // 	});
    // }

    void BeforeTestCase(){
    	a.clear();
    }

    void TestCases() {
        for (int i=0; i<20; i++) {
            CASE(n = rnd.nextInt(minn, 10), randomGrid(n, a));
        }
        for (int i=0; i<10; i++) {
            CASE(n = rnd.nextInt(11, maxn), randomGrid(n, a));
        }
        for (int i=0; i<10; i++) {
            CASE(n = maxn, randomGrid(n, a));
        }
    }

private:
    void randomGrid(int n, vector<vector<int>> &a) {
        vector<int> perm;
        for (int i=1; i<=n*n; i++) perm.push_back(i);
        rnd.shuffle(perm.begin(), perm.end());
        a.resize(n);
        for (int i=0; i<n; i++) {
            a[i].resize(n);
            for (int j=0; j<n; j++) {
                a[i][j] = perm[n*i+j];
            }
        }
    }
};