#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MAXN 100

class ProblemSpec : public BaseProblemSpec {
protected:
    string s;
    int ans;

	void InputFormat() {
        LINE(s);
	}

    void OutputFormat() {
    	LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= s.length() && s.length() <= MAXN);
        CONS(isValidS(s));
    }

private:
    bool isValidS(string s){
        if (s.length() > 1 && s[0] == '0') return false;
        for (char c : s){
            if (c < '0' || c > '9') return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
        	"100"
        });
        Output({
        	"1"
        });
    }

    void SampleTestCase2() {
        Input({
            "1337"
        });
        Output({
            "3"
        });
    }

    void SampleTestCase3() {
        Input({
            "0"
        });
        Output({
            "0"
        });
    }

    void BeforeTestCase(){
    	s.clear();
    }

    void TestCases() {
        CASE(s = "0");
        for (int i=1; i<=10; i++) CASE(generateRandomS(s, rnd.nextInt(1, 10), rnd.nextInt(1, 9)));
        for (int i=1; i<=10; i++) CASE(generateRandomS(s, rnd.nextInt(50, 100), rnd.nextInt(1, 9)));
        CASE(generateRandomS(s, 100, 9));
    }

private:
    void generateRandomS(string &s, int n, int mx){
        s.push_back((char)(rnd.nextInt(1, mx) + '0'));
        for (int i=1; i<n; i++) s.push_back((char)(rnd.nextInt(0, mx) + '0'));
    }
};