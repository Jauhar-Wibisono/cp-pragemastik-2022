#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int minn = 1;
const int maxn = 5000;
const int mina = 1;
const int maxa = 5000;

class ProblemSpec : public BaseProblemSpec {
protected:
	int n, x;
	vector<int> a;
	int ans;

	void InputFormat() {
	  LINE(n, x);
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
        CONS(mina <= x && x <= maxa);
        CONS(eachElementBetween(a, mina, maxa));
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
        for (int i=0; i<30; i++) {
            CASE(n = maxn, x = rnd.nextInt(maxa/2, maxa), randomArray(n, a, mina, maxa));
        }
    }

private:
    void randomArray(int n, vector<int>& a, int mn, int mx) {
        for (int i=0; i<n; i++) {
            a.push_back(rnd.nextInt(mn, mx));
        }
    }
};