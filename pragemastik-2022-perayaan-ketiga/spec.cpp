#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int minn = 4;
const int maxn = 100000;
const long long minxy = -1000000;
const long long maxxy = 1000000;

class ProblemSpec : public BaseProblemSpec {
protected:
	int n;
	vector<long long> x, y;
	long long ans;

	void InputFormat() {
	  LINE(n);
	  LINES(x, y) % SIZE(n);
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
        CONS(eachElementBetween(x, minxy, maxxy));
        CONS(eachElementBetween(y, minxy, maxxy));
        CONS(isValidPolygon(x, y));
    }

private:
    bool eachElementBetween(vector<long long> v, long long a, long long b){
        for(int i = 0; i < v.size(); i++){
            if(v[i] < a || v[i] > b)
                return false;
        }
        return true;
    }
    bool cw(long long xa, long long ya, long long xb, long long yb, long long xc, long long yc){
        return xa*(yb-yc)+xb*(yc-ya)+xc*(ya-yb) <= 0;
    }
    bool isValidPolygon(vector<long long> x, vector<long long> y){
        // valid polygon itu punya > 2 vertices, convex, clockwise, mulai dari kiri-bawah, dan semua titiknya distinct
        // cek convex & clockwise 
        int n = x.size();
        if (n < 3) return false;
        for (int i = 0; i < n; i++){
            if (!cw(x[i],y[i],x[(i+1)%n],y[(i+1)%n],x[(i+2)%n],y[(i+2)%n]))
                return false;
        }
        // cek mulai dari kiri-bawah
        for (int i = 1; i < n; i++){
            if (x[i] < x[0] || (x[i] == x[0] && y[i] < y[0]))
                return false;
        }
        // cek titik distinct
        set<pair<long long, long long>> udah;
        for (int i = 0; i < n; i++){
            if (udah.count(make_pair(x[i],y[i])))
                return false;
            udah.insert(make_pair(x[i],y[i]));
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
   //  void SampleTestCase1() {
   //      Input({
   //      	"10 5",
			// "9 1 6 7 2",
			// "4 10 4 8 3"
   //      });
   //      Output({
   //      	"1"
   //      });
   //  }

   //  void SampleTestCase2(){
   //  	Input({
   //  		"2 2",
   //  		"2 1",
   //  		"1 2"
   //  	});
   //  	Output({
   //  		"1"
   //  	});
   //  }

   //  void SampleTestCase3(){
   //  	Input({
   //  		"5 3",
   //  		"1 2 1",
   //  		"4 4 5"
   //  	});
   //  	Output({
   //  		"0"
   //  	});
   //  }

   //  void SampleTestCase4(){
   //  	Input({
   //  		"200 3",
   //  		"17 130 55",
   //  		"187 23 79"
   //  	});
   //  	Output({
   //  		"56"
   //  	});
   //  }

    void BeforeTestCase(){
    	x.clear();
    	y.clear();
    }

    void TestCases() {
        CASE(n = 4, x = {-1, -1, 1, 1}, y = {-1, 1, 1, -1});
        CASE(n = 4, x = {-1, 0, 1, 0}, y = {0, 1, 0, -1}); // min answer
        CASE(n = 4, x = {-maxxy, -maxxy, maxxy, maxxy}, y = {-maxxy, maxxy, maxxy, -maxxy}); // max answer
        for (int i=0; i<10; i++) CASE(n = rnd.nextInt(4, 10), randomConvexPolygon(x, y, n, minxy, maxxy));
        for (int i=0; i<10; i++) CASE(n = rnd.nextInt(11, 100), randomConvexPolygon(x, y, n, -100, 100));
        for (int i=0; i<10; i++) CASE(n = rnd.nextInt(11, 500), randomConvexPolygon(x, y, n, minxy, maxxy));
        for (int i=0; i<4; i++) CASE(n = maxn, randomConvexPolygon(x, y, n, minxy, maxxy));
    }

private:
    void randomConvexPolygon(vector<long long> &px, vector<long long> &py, int n, long long mn, long long mx){
        // https://cglab.ca/~sander/misc/ConvexGeneration/convex.html: convex polygon randomizer
        vector<long long> x, y;
        set<long long> udah_x, udah_y;
        for (int i=0; i<n; i++){
            long long gacha;
            do{
                gacha = rnd.nextLongLong(mn,mx);
            } while (udah_x.count(gacha));
            udah_x.insert(gacha);
            x.push_back(gacha);
        }
        for (int i=0; i<n; i++){
            long long gacha;
            do{
                gacha = rnd.nextLongLong(mn,mx);
            } while (udah_y.count(gacha));
            udah_y.insert(gacha);
            y.push_back(gacha);
        }
        sort(x.begin(),x.end());
        sort(y.begin(),y.end());
        vector<long long> xvec, yvec;
        long long lx = x[0], rx = x[0], ly = y[0], ry = y[0];
        for (int i=1; i+1<n; i++){
            if (rnd.nextInt(0,1)){
                xvec.push_back(x[i]-rx);
                rx = x[i];
            }
            else{
                xvec.push_back(lx-x[i]);
                lx = x[i];
            }
            if (rnd.nextInt(0,1)){
                yvec.push_back(y[i]-ry);
                ry = y[i];
            }
            else{
                yvec.push_back(ly-y[i]);
                ly = y[i];
            }
        }
        xvec.push_back(x[n-1]-rx);
        xvec.push_back(lx-x[n-1]);
        yvec.push_back(y[n-1]-ry);
        yvec.push_back(ly-y[n-1]);
        rnd.shuffle(yvec.begin(),yvec.end());
        vector<pair<long long, long long>> vec;
        for (int i=0; i<n; i++) vec.emplace_back(xvec[i],yvec[i]);
        sort(vec.begin(),vec.end(),[](pair<long long, long long> a, pair<long long, long long> b){
            return atan2(a.second,a.first) > atan2(b.second,b.first);
        });
        vector<pair<long long, long long>> pts;
        long long cur_x = 0, cur_y = 0, mnx = 0, mny = 0;
        for (int i=0; i<n; i++){
            pts.emplace_back(cur_x,cur_y);
            cur_x += vec[i].first;
            cur_y += vec[i].second;
            mnx = min(mnx,cur_x);
            mny = min(mny,cur_y);
        }
        for (int i=0; i<n; i++){
            pts[i].first += x[0] - mnx;
            pts[i].second += y[0] - mny;
        }
        pair<long long, long long> kiri_bawah = {1e18,1e18};
        int start;
        for (int i=0; i<n; i++){
            if (pts[i].first < kiri_bawah.first || (pts[i].first == kiri_bawah.first && pts[i].second < kiri_bawah.second)){
                kiri_bawah = pts[i];
                start = i;
            }
        }
        for (int i=0; i<n; i++){
            px.push_back(pts[(start+i)%n].first);
            py.push_back(pts[(start+i)%n].second);
        }
    }
};