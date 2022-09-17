#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int maxt = 1e5, maxm = 1e7;

class ProblemSpec : public BaseProblemSpec {
protected:
	int t;
    vector<int> m, k, a1, a2, a3, a4, a5;
    vector<string> ans;

	void InputFormat() {
	 	LINE(t);
        LINES(m, k, a1, a2, a3, a4, a5) % SIZE(t);
	}

    void OutputFormat() {
    	LINES(ans) % SIZE(t);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(0 < t && t < maxt);
        CONS(validVec(t, m, k, a1, a2, a3, a4, a5));
    }
private:
    bool validVec(int t, const vector<int>& m, const vector<int>& k, const vector<int>& a1,
        const vector<int>& a2, const vector<int>& a3, const vector<int>& a4, const vector<int>& a5
    ){
        bool toReturn = (m.size() == t) && (k.size() == t) && (a1.size() == t) && (a2.size() == t)
            && (a3.size() == t) && (a4.size() == t) && (a5.size() == t);
        if (!toReturn){return false;}
        
        for(int i=0; i<t; i++){
            toReturn = toReturn && (0 < m[i]) && (m[i] < maxm);
            toReturn = toReturn && (1 <= k[i]) && (k[i] <= 3);
            toReturn = toReturn && (0 <= a1[i]) && (a1[i] < maxm);
            toReturn = toReturn && (0 <= a2[i]) && (a2[i] < maxm);
            toReturn = toReturn && (0 <= a3[i]) && (a3[i] < maxm);
            toReturn = toReturn && (0 <= a4[i]) && (a4[i] < maxm);
            toReturn = toReturn && (0 <= a5[i]) && (a5[i] < maxm);
        }
        return toReturn;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "2",
            "1 3 0 1 0 0 0",
            "2 2 0 0 0 1 0",
        });
        Output({
        	"Bisono",
            "Arcello",
        });
    }

    void TestCases() {
        CASE(t = 3000, smallVec());
        for(int i=1; i<1e5; i*=10){
            for(int j=1e3; j<=maxm; j*=10){
                CASE(t = rnd.nextInt(i, 10*i-1), randomVec(t, j));
            }
        }
    }

private:
    void clearVec(){
        m.clear(); k.clear();
        a1.clear(); a2.clear(); a3.clear(); a4.clear(); a5.clear();
    }
    void smallVec(){
        clearVec();
        for(int a_2=0; a_2<=9; a_2++){
            for(int a_4=0; a_4<=9; a_4++){
                for(int a_5=0; a_5<=9; a_5++){
                    for(int toK=1; toK<=3; toK++){
                        m.push_back(rnd.nextInt(1, maxm-1));
                        k.push_back(toK);
                        a1.push_back(rnd.nextInt(0, maxm-1));
                        a2.push_back(a_2);
                        a3.push_back(rnd.nextInt(0, maxm-1));
                        a4.push_back(a_4);
                        a5.push_back(a_5);
                    }
                }
            }
        }
    }
    void randomVec(int t, int j){
        clearVec();
        for(int i=0; i<t; i++){
            m.push_back(rnd.nextInt(1, j-1));
            k.push_back(rnd.nextInt(1, 3));
            a1.push_back(rnd.nextInt(0, j-1));
            a2.push_back(rnd.nextInt(0, j-1));
            a3.push_back(rnd.nextInt(0, j-1));
            a4.push_back(rnd.nextInt(0, j-1));
            a5.push_back(rnd.nextInt(0, j-1));
        }
    }

};