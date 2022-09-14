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
    void SampleTestCase1() {
        Input({
            "2",
            "1 2",
            "4 3"
        });
        Output({
        	"5"
        });
    }

    void SampleTestCase2(){
    	Input({
    		"3",
            "5 6 2",
            "9 1 8",
            "4 7 3"
    	});
    	Output({
    		"12"
    	});
    }

    void BeforeTestCase(){
    	a.clear();
    }

    void TestCases() {
        for (int i=0; i<20; i++) {
            CASE(n = rnd.nextInt(minn, 5), randomGrid(n, a));
        }
        for (int i=0; i<3; i++) {
            CASE(n = rnd.nextInt(minn, 5), niceGrid(n, a));
        }
        for (int i=0; i<10; i++) {
            CASE(n = rnd.nextInt(11, maxn), randomGrid(n, a));
        }
        for (int i=0; i<3; i++) {
            CASE(n = rnd.nextInt(11, maxn), niceGrid(n, a));
        }
        for (int i=0; i<10; i++) {
            CASE(n = maxn, randomGrid(n, a));
        }
        for (int i=0; i<2; i++) {
            CASE(n = maxn, niceGrid(n, a));
        }
        for (int i=0; i<3; i++) {
            CASE(sudokuLikeGrid(n, a));
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

    void sudokuLikeGrid(int& n, vector<vector<int>>& a) {
        n = 9;

        vector<vector<int>> perm(n);
        for (int i=1; i<=n*n; i++) perm[i%n].push_back(i);
        for (int i=0; i<n; i++) rnd.shuffle(perm[i].begin(), perm[i].end());

        vector<int> perm2(n);
        for (int i=0; i<n; i++) perm2[i] = i+1;
        rnd.shuffle(perm2.begin(), perm2.end());

        a.resize(n);
        for (int i=0; i<n; i++) a[i].resize(n);
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                for (int k=0; k<3; k++) {
                    for (int l=0; l<3; l++) {
                        int r = 3*i+k;
                        int c = 3*j+l;
                        a[r][c] = perm[perm2[3*i+j]][3*k+l];
                    }
                }
            }
        }
    }

    void niceGrid(int n, vector<vector<int>>& a) {
        a.resize(n);
        for (int i=0; i<n; i++) {
            a[i].resize(n);
            for (int j=0; j<n; j++) {
                a[i][j] = n*i+j+1;
            }
        }

        for (int i=0; i<n; i++) rnd.shuffle(a[i].begin(), a[i].end());
        rnd.shuffle(a.begin(), a.end());
    }
};