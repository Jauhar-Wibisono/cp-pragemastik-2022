#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int minn = 1;
const int maxn = 1000;

class ProblemSpec : public BaseProblemSpec {
protected:
	int n;
	int ans;

	void InputFormat() {
	 	LINE(n);
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
    }

    void StyleConfig() {
        CustomScorer(); // validator.cpp/scorer.cpp is used
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "3"
        });
        Output({
        	"15"
        });
    }

    void SampleTestCase2(){
    	Input({
    		"4"
    	});
    	Output({
    		"-1"
    	});
    }

    void TestCases() {
        for (int i=0; i<30; i++) {
            CASE(n = rnd.nextInt(minn, maxn));
        }
    }
};