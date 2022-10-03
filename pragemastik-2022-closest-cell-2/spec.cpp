#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int maxn = 1e5, maxm = 2e8;

class ProblemSpec : public BaseProblemSpec {
protected:
	int n, askCount;
    vector<vector<int> > query;
	vector<long long> ans;

	void InputFormat() {
	 	LINE(n);
        LINES(query) % SIZE(n);
	}
    void OutputFormat() {
    	LINES(ans);
    }
    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }
    void Constraints() {
        CONS(0 < n && n < maxn);
        CONS(validQuery(n, query));
    }
private:
    bool validQuery(int n, const vector<vector<int> >& q){
        bool toReturn = q.size() == n;
        for(int i=0; i<n; i++){
            toReturn = toReturn && (q[i].size() == 7-2*q[i][0]);
            for(int j=1; j<3; j++){
                toReturn = toReturn && (-maxm < q[i][j] && q[i][j] < maxm);
            }
            for(int j=3; j<q[i].size(); j++){
                toReturn = toReturn && (0 <= q[i][j] && q[i][j] < maxm);
            }
        }
        return toReturn;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "20",
            "1 -1 -1 3 2",
            "1 2 0 2 2",
            "1 0 1 5 5",
            "1 0 2 1 1",
            "2 -1 -1",
            "2 -1 0",
            "2 -1 1",
            "2 -1 2",
            "2 0 -1",
            "2 0 0",
            "2 0 1",
            "2 0 2",
            "2 1 -1",
            "2 1 0",
            "2 1 1",
            "2 1 2",
            "2 2 -1",
            "2 2 0",
            "2 2 1",
            "2 2 2"
        });
        Output({
        	"8",
            "7",
            "8",
            "9",
            "7",
            "6",
            "7",
            "8",
            "9",
            "8",
            "9",
            "10",
            "10",
            "9",
            "10",
            "11",
            "6"
        });
    }


    void BeforeTestCase(){
        query.clear();
    }

    void TestCases() {
        cout << "HALO" << endl;
        for (long long j=2; j<=maxm; j*=100) {
            for(int i=1; i<maxn; i*=10){
                for(int k=1; k<4; k++){
                    CASE(n = rnd.nextInt(i, 10*i-1), generateQuery(n, j, k, query));
                }
            }
        }
    }

private:
    void generateQuery(int n, int maxlocal, int prob4, vector<vector<int> >& query){
        vector<int> dummy;
        for(int i=0; i<n; i++){
            int roll = rnd.nextInt(0, 3);
            query.push_back(dummy);
            if(roll < prob4){
                query[i].push_back(1);
                query[i].push_back(rnd.nextInt(-maxlocal+1, maxlocal-1));
                query[i].push_back(rnd.nextInt(-maxlocal+1, maxlocal-1));
                query[i].push_back(rnd.nextInt(0, maxlocal-1));
                query[i].push_back(rnd.nextInt(0, maxlocal-1));
            }else{
                query[i].push_back(2);
                query[i].push_back(rnd.nextInt(-maxlocal+1, maxlocal-1));
                query[i].push_back(rnd.nextInt(-maxlocal+1, maxlocal-1));
            }
        }
    }
};