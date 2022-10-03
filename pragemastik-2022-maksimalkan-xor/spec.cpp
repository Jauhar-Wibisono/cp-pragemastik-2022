#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int maxn = 1e5, maxA = 33554432;

class ProblemSpec : public BaseProblemSpec {
protected:
	int n;
    vector<int> a;
    int idx, ans;

	void InputFormat() {
        LINE(n);
        LINE(a % SIZE(n));
	}

    void OutputFormat() {
    	LINE(idx, ans);
    }

    void GradingConfig() {
        TimeLimit(3);
        MemoryLimit(524);
    }

    void Constraints() {
        CONS(0 < n && n < maxn);
        CONS(validA(n, a));
    }

private:
	bool validA(int n, const vector<int>& a) {
        if(a.size() != n){
            return false;
        }
        for(int i=0; i<n; i++){
            if(a[i] < 0 || a[i] >= maxA){
                return false;
            }
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    
    void SampleTestCase1() {
        Input({
            "2",
            "33554431 33554431",            
        });
        Output({
            "1 0"
        });
    }

    void SampleTestCase2() {
        Input({
            "3",
            "1 3 2"         
        });
        Output({
            "2 33554428"
        });
    }

    void BeforeTestCase(){
    	a.clear();
    }

    void TestCases() {
        CASE(n=1, generateA(n));
        for(int i=1; i<maxn; i*=10){
            for(int j=0; j<10; j++){
                CASE(n=rnd.nextInt(i, 10*i-1), generateA(n));
            }
        }
    }

private:
	void generateA(int n){
        for(int i=0; i<n; i++){
            a.push_back(rnd.nextInt(0, maxA-1));
        }
    }
};