#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int maxn = 100000;
const int maxsb = 200000; // sum bridge
const int maxq = 100000;
const int minh = 1;
const int maxh = 1000000000;

class ProblemSpec : public BaseProblemSpec {
protected:
	int n, q;
	vector<int> bn;
	vector<vector<int>> bh;
	vector<int> qh;
	vector<int> ans;

	void InputFormat() {
        LINE(n, q);
        LINES(bn, bh) % SIZE(n);
        LINES(qh) % SIZE(q);
	}

    void OutputFormat() {
    	LINES(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= n && n <= maxn);
        CONS(1 <= q && q <= maxq);
        CONS(sumNotBiggerThan(bn, maxsb));
        CONS(eachElementBetween(bh, minh, maxh));
        CONS(eachElementBetween(qh, minh, maxh));
    }

private:
	bool sumNotBiggerThan(vector<int> a, int mx) {
		int sum = 0;
		for (int i=0; i<(int)a.size(); i++) {
			sum += a[i];
			if (sum > mx) return false;
		}
		return true;
	}
    bool eachElementBetween(vector<int> v, int a, int b){
        for(int i=0; i<(int)v.size(); i++){
            if(v[i] < a || v[i] > b)
                return false;
        }
        return true;
    }
    bool eachElementBetween(vector<vector<int>> v, int a, int b){
        for(int i=0; i<(int)v.size(); i++){
        	for (int j=0; j<(int)v[i].size(); j++) {
	            if(v[i][j] < a || v[i][j] > b)
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
            "5 7",
            "3 2 1 5",
            "1 3",
            "2 1 4",
            "1 1",
            "4 1 3 5 6",
            "1",
            "3",
            "5",
            "2",
            "4",
            "6",
            "7"
        });
        Output({
            "0",
            "4",
            "18",
            "0",
            "8",
            "24",
            "24"
        });
    }

    void BeforeTestCase(){
    	bn.clear();
        bh.clear();
        qh.clear();
        ans.clear();
    }

    void TestCases() {
        for (int i=0; i<4; i++) {
            CASE(n = rnd.nextInt(1, 50), 
                q = rnd.nextInt(1, 50),
                randomBridges(n, bn, bh, rnd.nextInt(n, 200), minh, 100),
                randomQueries(q, qh, minh, 200)
            );
            CASE(n = rnd.nextInt(1, 50), 
                q = rnd.nextInt(1, 50),
                randomBridges(n, bn, bh, rnd.nextInt(n, 200), minh, maxh),
                randomQueries(q, qh, minh, maxh)
            );
            CASE(n = rnd.nextInt(1, 50), 
                q = rnd.nextInt(1, 50),
                nonZeroBridges(n, bn, bh, rnd.nextInt(n, 200), minh, maxh),
                randomQueries(q, qh, minh, maxh)
            );
        }
        for (int i=0; i<8; i++) {
        	CASE(n = rnd.nextInt(1, 500), 
        		q = rnd.nextInt(1, 500),
        		randomBridges(n, bn, bh, rnd.nextInt(n, 2000), minh, 2000),
        		randomQueries(q, qh, minh, 2000)
        	);
        	CASE(n = rnd.nextInt(1, 500), 
        		q = rnd.nextInt(1, 500),
        		randomBridges(n, bn, bh, rnd.nextInt(n, 2000), minh, maxh),
        		randomQueries(q, qh, minh, maxh)
        	);
            CASE(n = rnd.nextInt(1, 500), 
                q = rnd.nextInt(1, 500),
                nonZeroBridges(n, bn, bh, rnd.nextInt(n, 2000), minh, maxh),
                randomQueries(q, qh, minh, maxh)
            );
        }
        for (int i=0; i<3; i++) {
        	CASE(n = maxn, 
        		q = maxq,
        		randomBridges(n, bn, bh, maxsb, minh, maxh),
        		randomQueries(q, qh, minh, maxh)
        	);
            CASE(n = maxn, 
                q = maxq,
                nonZeroBridges(n, bn, bh, maxsb, minh, maxh/10),
                randomQueries(q, qh, minh, maxh/10)
            );
        }
        CASE(n = 1, 
            q = maxq, 
            randomBridges(n, bn, bh, maxsb, minh, maxh), 
            randomQueries(q, qh, minh, maxh)
        );
    }

private:
	void randomBridges(int n, vector<int> &bn, vector<vector<int>> &bh, int nb, int minh, int maxh) {
		bn.assign(n, 1);
		nb -= n;
		for (int i=0; i<nb; i++) bn[rnd.nextInt(0, n-1)]++;
		bh.resize(n);
		for (int i=0; i<n; i++) {
			bh[i].resize(bn[i]);
			for (int j=0; j<bn[i]; j++) bh[i][j] = rnd.nextInt(minh, maxh);
		}
	}
    void nonZeroBridges(int n, vector<int> &bn, vector<vector<int>> &bh, int nb, int minh, int maxh) {
        bn.assign(n, 1);
        nb -= n;
        for (int i=0; i<nb; i++) bn[rnd.nextInt(0, n-1)]++;
        bh.resize(n);
        for (int i=0; i<n; i++) {
            bh[i].resize(bn[i]);
            bh[i][0] = 1;
            for (int j=1; j<bn[i]; j++) bh[i][j] = rnd.nextInt(minh, maxh);
        }   
    }
	void randomQueries(int q, vector<int> &qh, int minh, int maxh) {
		for (int i=0; i<q; i++) qh.push_back(rnd.nextInt(minh, maxh));
	}
};