#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int minn = 1;
const int maxn = 1337;

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
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "1"
        });
        Output({
        	"1"
        });
    }

    void SampleTestCase2(){
    	Input({
    		"3"
    	});
    	Output({
    		"3"
    	});
    }

    void TestCases() {
        for (int i=0; i<111; i++) {
            CASE(n = rnd.nextInt(minn, maxn));
        }
    }
};