#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int maxt = 1e5, maxnm = 1e7;

class ProblemSpec : public BaseProblemSpec {
protected:
	int t;
    vector<int> n, m;
    vector<long long> ans;

	void InputFormat() {
	 	LINE(t);
        LINES(n, m) % SIZE(t);
	}

    void OutputFormat() {
    	LINES(ans) % SIZE(t);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(0 < t && t < maxt);
        CONS(validNM(t, n, m));
    }
private:
    bool validNM(int t, const vector<int>& n, const vector<int>& m){
        bool toReturn = (n.size() == t) && (m.size() == t);
        if (!toReturn){return false;}
        long long sum = 0;
        for(int i=0; i<t; i++){
            toReturn = toReturn && (max(n[i], m[i]) < maxnm);
            sum += n[i] + m[i];
        }
        return toReturn && (sum < maxnm);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "2",
            "3 3",
            "5 7"
        });
        Output({
        	"22",
            "1968",
        });
    }

    void TestCases() {
        n.clear(); m.clear();
        int tot = 0;
        for(i=1; i<=100; i++){
            for(int j=1; j<=i; j++){
                int roll = rnd.nextInt(0, 1);
                if(roll){
                    n.push_back(i); m.push_back(j);
                }else{
                    m.push_back(i); n.push_back(j);
                }
                tot++;
            }
        }
        CASE(t=tot);
        for(int i=1024; i>0; i/=2){
            for(int j=0; j<5; j++){
                CASE(t = rnd.nextInt(i, 2*i-1), generateNM(t, n, m));
            }
        }
    }

private:
    void generateNM(int t, vector<int>& n, vector<int>& m){
        int maxSumNM = maxnm/t;
        n.clear(); m.clear();
        for(int i=0; i<t; i++){
            int sumNM = rnd.nextInt(maxSumNM/2, maxSumNM-1);
            int toN = rnd.nextInt(1, sumNM-1);
            n.push_back(toN);
            m.push_back(sumNM - toN);
        }
    }

};