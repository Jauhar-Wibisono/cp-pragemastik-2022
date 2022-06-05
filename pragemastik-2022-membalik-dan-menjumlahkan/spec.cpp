#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int maxn = 200000;
const int maxq = 100000;
const long long mina = 1;
const long long maxa = 1000000000;

class ProblemSpec : public BaseProblemSpec {
protected:
	int n, m, q;
    vector<long long> a;
    vector<int> b;
    vector<char> types;
    vector<vector<int>> ques;
	vector<long long> ans;

	void InputFormat() {
        LINE(n, m, q);
        LINE(a % SIZE(n));
        LINE(b % SIZE(m));
        LINES(types, ques) % SIZE(q);
	}

    void OutputFormat() {
    	LINES(ans);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= n && n <= maxn);
        CONS(0 <= m && m < n);
        CONS(1 <= q && q <= maxq);
        CONS(eachElementBetween(a, mina, maxa));
        CONS(eachElementBetween(b, 1, n-1));
        CONS(isSorted(b));
        CONS(validQueries(types, ques, n, m));
    }

private:
    bool eachElementBetween(vector<int> v, int a, int b){
        for(int i = 0; i < v.size(); i++){
            if(v[i] < a || v[i] > b)
                return false;
        }
        return true;
    }
    bool eachElementBetween(vector<long long> v, long long a, long long b){
        for(int i = 0; i < v.size(); i++){
            if(v[i] < a || v[i] > b)
                return false;
        }
        return true;
    }
    bool isSorted(vector<int> b) {
        vector<int> sb = b;
        sort(sb.begin(), sb.end());
        return b == sb;
    }
    bool validQueries(vector<char> types, vector<vector<int>> ques, int n, int m) {
        bool ada = false;
        if (types.size() != ques.size()) return false;
        for (int i=0; i<(int)types.size(); i++) {
            if (types[i] == 'B') {
                // balik
                if (ques[i][0] < 1 || ques[i][0] > m+1) {
                    return false;
                }
            } else {
                // jumlah
                ada = true;
                if (ques[i][0] > ques[i][1] || ques[i][0] < 1 || ques[i][1] > n) {
                    return false;
                }
            }
        }
        return ada;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
        	"8 3 12",
            "1 2 3 4 5 6 7 8",
            "2 5 6",
            "J 1 8",
            "J 4 6",
            "J 3 5",
            "B 2",
            "J 4 6",
            "J 3 5",
            "B 3",
            "J 4 6",
            "J 5 5",
            "B 1",
            "J 1 1",
            "J 2 3"
        });
        Output({
        	"36",
            "15",
            "12",
            "13",
            "12",
            "13",
            "3",
            "2",
            "6"
        });
    }

    void BeforeTestCase(){
    	a.clear();
        b.clear();
        types.clear();
        ques.clear();
        ans.clear();
    }

    void TestCases() {
        for (int i=0; i<2; i++) CASE(n = 20, m = 5, randomValues(n, a, 1, 100), randomPartitions(n, m, b), flipCheckQues(n, m, q, types, ques));
        CASE(n = 1, m = 0, randomValues(n, a, 1, 100), b = vector<int>(), flipCheckQues(n, m, q, types, ques));
        CASE(n = 20, m = 0, randomValues(n, a, 1, 100), b = vector<int>(), flipCheckQues(n, m, q, types, ques));
        CASE(n = 20, m = 19, randomValues(n, a, 1, 100), randomPartitions(n, m, b), flipCheckQues(n, m, q, types, ques));
        
        for (int i=0; i<3; i++) {
            CASE(n = rnd.nextInt(100, 500), 
                m = rnd.nextInt(0, n-1), 
                q = rnd.nextInt(100, 500), 
                randomValues(n, a, 1, 100), 
                randomPartitions(n, m, b), 
                randomQues(n, m, q, types, ques));
        }
        for (int i=0; i<2; i++) {
            CASE(n = maxn, 
                m = rnd.nextInt(0, n-1), 
                q = maxq, 
                randomValues(n, a, 1, maxa), 
                randomPartitions(n, m, b), 
                randomQues(n, m, q, types, ques));
        }
        CASE(n = maxn, 
                m = rnd.nextInt(0, n-1), 
                q = maxq, 
                randomValues(n, a, maxa, maxa), 
                randomPartitions(n, m, b), 
                randomQues(n, m, q, types, ques));
        CASE(n = maxn, 
                m = rnd.nextInt(0, n-1), 
                q = maxq, 
                randomValues(n, a, 1, maxa), 
                randomPartitions(n, m, b), 
                stressSumQues(n, q, types, ques));
        CASE(n = maxn, 
                m = rnd.nextInt(0, n-1), 
                q = maxq, 
                randomValues(n, a, 1, maxa), 
                randomPartitions(n, m, b), 
                stressFlipQues(n, m, q, types, ques));
    }

private:
    void randomValues(int N, vector<long long> &v, long long lb, long long rb){
    	for (int i = 0; i < N; i++){
    		v.push_back(rnd.nextLongLong(lb, rb));
    	}
    }
    void randomPartitions(int n, int m, vector<int> &b){
    	for (int i=1; i<n; i++) b.push_back(i);
        rnd.shuffle(b.begin(), b.end());
        while (b.size() > m) b.pop_back();
        sort(b.begin(), b.end());
    }
    void flipCheckQues(int n, int m, int &q, vector<char> &types, vector<vector<int>> &ques) {
        for (int i=1; i<=n; i++) {
            types.push_back('J');
            ques.push_back({i, i});
        }
        for (int i=0; i<10; i++) {
            int l = rnd.nextInt(1, n), r = rnd.nextInt(1, n);
            if (l > r) swap(l, r);
            types.push_back('J');
            ques.push_back({l, r});
        }
        for (int i=1; i<=m+1; i++) {
            types.push_back('B');
            ques.push_back({i});
        }
        for (int i=1; i<=n; i++) {
            types.push_back('J');
            ques.push_back({i, i});
        }
        for (int i=0; i<10; i++) {
            types.push_back('J');
            int l = rnd.nextInt(1, n), r = rnd.nextInt(1, n);
            if (l > r) swap(l, r);
            ques.push_back({l, r});
        }
        q = ques.size();
    }
    void randomQues(int n, int m, int q, vector<char> &types, vector<vector<int>> &ques) {
        vector<vector<int>> tq;
        { // obligatory query
            int l = rnd.nextInt(1, n), r = rnd.nextInt(1, n);
            if (l > r) swap(l, r);
            tq.push_back({2, l, r});
        }
        for (int i=1; i<q; i++) {
            int type = rnd.nextInt(1, 2);
            if (type == 1) {
                int b = rnd.nextInt(1, m+1);
                tq.push_back({type, b});
            } else {
                int l = rnd.nextInt(1, n), r = rnd.nextInt(1, n);
                if (l > r) swap(l, r);
                tq.push_back({2, l, r});       
            }
        }
        rnd.shuffle(tq.begin(), tq.end());
        for (auto &que : tq) {
            if (que[0] == 1) {
                types.push_back('B');
                ques.push_back({que[1]});
            } else {
                types.push_back('J');
                ques.push_back({que[1], que[2]});
            }
        }
    }
    void stressSumQues(int n, int q, vector<char> &types, vector<vector<int>> &ques) {
        for (int i=0; i<q; i++) {
            types.push_back('J');
            ques.push_back({rnd.nextInt(1, 10), n-rnd.nextInt(0, 9)});       
        }
        rnd.shuffle(ques.begin(), ques.end());
    }
    void stressFlipQues(int n, int m, int q, vector<char> &types, vector<vector<int>> &ques) {
        vector<vector<int>> tq;
        { // obligatory query
            int l = rnd.nextInt(1, n), r = rnd.nextInt(1, n);
            if (l > r) swap(l, r);
            tq.push_back({2, l, r});
        }
        for (int i=1; i<q; i++) {
            tq.push_back({1, rnd.nextInt(1, m+1)});       
        }
        rnd.shuffle(tq.begin(), tq.end());
        for (auto &que : tq) {
            if (que[0] == 1) {
                types.push_back('B');
                ques.push_back({que[1]});
            } else {
                types.push_back('J');
                ques.push_back({que[1], que[2]});
            }
        }
    }
};