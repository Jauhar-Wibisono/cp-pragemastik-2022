#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int maxn = 1000, maxm = 1e9;

class ProblemSpec : public BaseProblemSpec {
protected:
	int n;
    vector<int> x, y;
	int ans;

	void InputFormat() {
	 	LINE(n);
        LINE(x % SIZE(n));
        LINE(y % SIZE(n));
	}

    void OutputFormat() {
    	LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(0 < n && n < maxn);
        CONS(validCoordinates(x));
        CONS(validCoordinates(y));
    }
private:
    bool validCoordinates(const vector<int>& xy){
        bool toReturn = true;
        for(auto c: xy){
            toReturn = toReturn && (-maxm < c) && (c < maxm);
        }
        return toReturn;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "9",
            "-1 -1 -1 0 0 0 1 1 1",
            "-1 0 1 -1 0 1 -1 0 1"
        });
        Output({
        	"22"
        });
    }

    void SampleTestCase2(){
    	Input({
    		"35",
            "-3 -3 -3 -3 -3 -2 -2 -2 -2 -2 -1 -1 -1 -1 -1 0 0 0 0 0 1 1 1 1 1 2 2 2 2 2 3 3 3 3 3",
            "-2 -1 0 1 2 -2 -1 0 1 2 -2 -1 0 1 2 -2 -1 0 1 2 -2 -1 0 1 2 -2 -1 0 1 2 -2 -1 0 1 2"
    	});
    	Output({
    		"1968"
    	});
    }

    void BeforeTestCase(){
        x.clear(); y.clear();
    }

    void TestCases() {
        for (int maxVal = 2; maxVal <= 1024; maxVal *= 2) {
            for(int m=62; m<maxn; m*=2){
                CASE(n = generateCoordinates(m, rnd.nextInt(1, 2e5), rnd.nextInt(0, 2e5), maxVal, x, y));
            }
        }
    }

private:
    int generateCoordinates(int m, int multX, int multY, int maxVal, vector<int>& x, vector<int>& y){
        int offsetX = rnd.nextInt(-multX+1, multX-1);
        int offsetY = rnd.nextInt(-multY+1, multY-1);
        int roll = 0;
        pair<int, int> point;
        set<pair<int, int> > s;
        for(int i=0; i<m; i++){
            point.first = offsetX; point.second = offsetY;
            roll = rnd.nextInt(-maxVal+1, maxVal-1);
            point.first += roll * multX; point.second += roll * multY;
            roll = rnd.nextInt(-maxVal+1, maxVal-1);
            point.first -= roll * multY; point.second += roll * multX; 
            if(!(s.count(point))){
                x.push_back(point.first);
                y.push_back(point.second);
                s.insert(point);
            }
        }
        return x.size();
    }

};