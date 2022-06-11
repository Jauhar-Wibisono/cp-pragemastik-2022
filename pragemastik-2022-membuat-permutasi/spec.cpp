#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int minn = 1;
const int maxn = 200000;
const int minm = 2;
const int maxm = 20;

class ProblemSpec : public BaseProblemSpec {
protected:
	int n, m;
    vector<int> a;
    long long ans;

	void InputFormat() {
        LINE(n, m);
        LINE(a % SIZE(n));
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
        CONS(minm <= m && m <= maxm);
        CONS(eachElementBetween(a, 1, m));
    }

private:
    bool eachElementBetween(vector<int> v, int a, int b){
        for(int i = 0; i < v.size(); i++){
            if(v[i] < a || v[i] > b)
                return false;
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
    }

    void TestCases() {
        for (int i=0; i<2; i++) {
            CASE(n = 1, m = rnd.nextInt(minm, maxm), randomArray(n, m, a));
        }
        for (int i=0; i<3; i++) {
            CASE(n = rnd.nextInt(1, 10), m = rnd.nextInt(minm, n), randomArray(n, m, a));
        }
        for (int i=0; i<10; i++) {
            CASE(n = rnd.nextInt(10, 500), m = rnd.nextInt(minm, maxm), randomArray(n, m, a));
            CASE(n = rnd.nextInt(10, 500), m = rnd.nextInt(minm, maxm), uniformerArray(n, m, a));
        }
        CASE(n = rnd.nextInt(10, 500), m = minm, uniformArray(n, m, a));
        CASE(n = rnd.nextInt(10, 500), m = maxm, uniformArray(n, m, a));
        for (int i=0; i<3; i++) {
            CASE(n = maxn, m = rnd.nextInt(minm, maxm), randomArray(n, m, a));
            CASE(n = maxn, m = rnd.nextInt(minm, maxm), uniformerArray(n, m, a)); 
        }
        CASE(n = maxn, m = minm, uniformArray(n, m, a));
        CASE(n = maxn, m = maxm, uniformArray(n, m, a));
        CASE(n = maxn, m = minm, uniformerArray(n, m, a));
        CASE(n = maxn, m = maxm, uniformerArray(n, m, a));
    }

private:
    void randomArray(int n, int m, vector<int> &a) {
        for (int i=0; i<n; i++) a.push_back(rnd.nextInt(1, m));
    }
    void uniformerArray(int n, int m, vector<int> &a) {
        for (int i=0; i<n; i+=m) {
            for (int j=1; i+j-1<n && j<=m; j++) a.push_back(j);
            rnd.shuffle(a.begin()+i, a.end());
        }
    }
    void uniformArray(int n, int m, vector<int> &a) {
        for (int i=0; i<n; i++) a.push_back(i%m + 1);   
    }
};