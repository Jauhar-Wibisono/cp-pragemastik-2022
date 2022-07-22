#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int minn = 4;
const int maxn = 100000;
const long long minxy = -400000000;
const long long maxxy = 400000000;

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
        return xa*(yb-yc)+xb*(yc-ya)+xc*(ya-yb) < 0;
    }
    bool isValidPolygon(vector<long long> x, vector<long long> y){
        // valid polygon itu punya > 2 vertices, convex, clockwise, dan semua titiknya distinct
        // cek convex & clockwise 
        int n = x.size();
        if (n < 3) return false;
        for (int i = 0; i < n; i++){
            if (!cw(x[i],y[i],x[(i+1)%n],y[(i+1)%n],x[(i+2)%n],y[(i+2)%n]))
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
    void SampleTestCase1() {
        Input({
            "5",
            "-2 2",
            "-1 5",
            "2 5",
            "4 0",
            "0 -3"
        });
        Output({
        	"15"
        });
    }

    void SampleTestCase2(){
    	Input({
    		"4",
            "0 0",
            "1 1",
            "2 0",
            "1 -1"
    	});
    	Output({
    		"2"
    	});
    }

    void BeforeTestCase(){
    	x.clear();
    	y.clear();
    }

    void TestCases() {
        CASE(n = 4, x = {-1, -1, 1, 1}, y = {-1, 1, 1, -1});
        CASE(n = 4, x = {-1, 0, 1, 0}, y = {0, 1, 0, -1}); // min answer
        CASE(n = 4, x = {-maxxy, -maxxy, maxxy, maxxy}, y = {-maxxy, maxxy, maxxy, -maxxy}); // max answer
        for (int i=0; i<10; i++) CASE(n = rnd.nextInt(4, 10), randomConvexPolygon(x, y, n, minxy, maxxy));
        for (int i=0; i<10; i++) CASE(n = rnd.nextInt(11, 100), randomConvexPolygon(x, y, n, -1000, 1000));
        for (int i=0; i<10; i++) CASE(n = rnd.nextInt(11, 500), randomConvexPolygon(x, y, n, minxy, maxxy));
        for (int i=0; i<4; i++) CASE(n = rnd.nextInt(maxn/2, maxn), randomConvexPolygon(x, y, n, minxy, maxxy));
        for (int i=0; i<4; i++) CASE(n = maxn, randomConvexPolygon(x, y, n, minxy, maxxy)); // answer will probably be 1
    }

private:
    struct pt {
        long long x, y;
        pt() {}
        pt(long long _x, long long _y): x(_x), y(_y) {}
    };

    int orientation(pt a, pt b, pt c) {
        double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
        if (v < 0) return -1; // clockwise
        if (v > 0) return +1; // counter-clockwise
        return 0;
    }

    bool cw(pt a, pt b, pt c, bool include_collinear) {
        int o = orientation(a, b, c);
        return o < 0 || (include_collinear && o == 0);
    }
    bool ccw(pt a, pt b, pt c, bool include_collinear) {
        int o = orientation(a, b, c);
        return o > 0 || (include_collinear && o == 0);
    }

    void convex_hull(vector<pt>& a, bool include_collinear = false) {
        if (a.size() == 1)
            return;

        sort(a.begin(), a.end(), [](pt a, pt b) {
            return make_pair(a.x, a.y) < make_pair(b.x, b.y);
        });
        pt p1 = a[0], p2 = a.back();
        vector<pt> up, down;
        up.push_back(p1);
        down.push_back(p1);
        for (int i = 1; i < (int)a.size(); i++) {
            if (i == a.size() - 1 || cw(p1, a[i], p2, include_collinear)) {
                while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i], include_collinear))
                    up.pop_back();
                up.push_back(a[i]);
            }
            if (i == a.size() - 1 || ccw(p1, a[i], p2, include_collinear)) {
                while (down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i], include_collinear))
                    down.pop_back();
                down.push_back(a[i]);
            }
        }

        if (include_collinear && up.size() == a.size()) {
            reverse(a.begin(), a.end());
            return;
        }
        a.clear();
        for (int i = 0; i < (int)up.size(); i++)
            a.push_back(up[i]);
        for (int i = down.size() - 2; i > 0; i--)
            a.push_back(down[i]);
    }

    void randomConvexPolygon(vector<long long> &px, vector<long long> &py, int n, long long mn, long long mx){
        // https://cglab.ca/~sander/misc/ConvexGeneration/convex.html: convex polygon randomizer
        // above algorithm is modified further: generate polygon of 2n vertices, build convex hull out of it, then randomly pick n vertices
        while (true) {
            int nn = 2*n;
            vector<long long> x, y;
            set<long long> udah_x, udah_y;
            for (int i=0; i<nn; i++){
                long long gacha;
                do{
                    gacha = rnd.nextLongLong(mn,mx);
                } while (udah_x.count(gacha));
                udah_x.insert(gacha);
                x.push_back(gacha);
            }
            for (int i=0; i<nn; i++){
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
            for (int i=1; i+1<nn; i++){
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
            xvec.push_back(x[nn-1]-rx);
            xvec.push_back(lx-x[nn-1]);
            yvec.push_back(y[nn-1]-ry);
            yvec.push_back(ly-y[nn-1]);
            rnd.shuffle(yvec.begin(),yvec.end());
            vector<pair<long long, long long>> vec;
            for (int i=0; i<nn; i++) vec.emplace_back(xvec[i],yvec[i]);
            sort(vec.begin(),vec.end(),[](pair<long long, long long> a, pair<long long, long long> b){
                return atan2(a.second,a.first) > atan2(b.second,b.first);
            });
            vector<pt> pts;
            long long cur_x = 0, cur_y = 0, mnx = 0, mny = 0;
            for (int i=0; i<nn; i++){
                pts.emplace_back(cur_x,cur_y);
                cur_x += vec[i].first;
                cur_y += vec[i].second;
                mnx = min(mnx,cur_x);
                mny = min(mny,cur_y);
            }
            for (int i=0; i<nn; i++){
                pts[i].x += x[0] - mnx;
                pts[i].y += y[0] - mny;
            }
             
            // cout << "pts size: " << pts.size() << '\n';   
            convex_hull(pts, false);
            // cout << "ch size: " << pts.size() << '\n';
            if (pts.size() < n) continue;

            int m = pts.size();
            vector<int> gacha(m);
            for (int i=0; i<m; i++) gacha[i] = i;
            rnd.shuffle(gacha.begin(), gacha.end());
            sort(gacha.begin(), gacha.begin()+n);
            
            for (int i=0; i<n; i++) {
                px.push_back(pts[gacha[i]].x);
                py.push_back(pts[gacha[i]].y);
            }
            break;
        }
    }
};