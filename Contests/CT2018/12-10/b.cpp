#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp> //__gnu_pbds::priority_queue
 
using std::pair;
using std::vector;
using std::string;

typedef long long ll;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) std::make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int N = 100000;
const int oo = 0x3f3f3f3f;
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

const double eps = 1e-9;

typedef struct Point {
    double x, y;
    Point() { }
    Point(double x_, double y_): x(x_), y(y_) { }
} Vector;

Point operator - (const Point& a, const Point& b) { return Point(a.x - b.x, a.y - b.y); }
Point operator + (const Point& a, const Point& b) { return Point(a.x + b.x, a.y + b.y); }
Point operator * (const Point& a, const double&b) { return Point(a.x * b, a.y * b); }
Point operator / (const Point& a, const double&b) { return Point(a.x / b, a.y / b); }

double dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}
double len(const Point& a) { return sqrt(dot(a, a)); }
Point unit(const Point& a) { return a / len(a); }


double T;
int n, m;
Point p[N + 5];

typedef pair<int, double> pid;
typedef pair<double, double> pdd;

int dcmp(double x) {
    return (x > -eps) - (x < eps);
}

vector<pdd> solve(double a, double b, double c) {
    static vector<pdd> res;

    res.clear();
    if(dcmp(a) == 0) {
        if(dcmp(b) == 0) {
            if(dcmp(c) <= 0) {
                res.pb(mp(-1e9, 1e9));
            }
            return res;
        }

        if(dcmp(b) > 0) {
            res.pb(mp(-1e9, -c / b));
        } else {
            res.pb(mp(-c / b, 1e9));
        }
        return res;
    }

    double delta = b * b - 4 * a * c;

    if(dcmp(delta) < 0) {
        if(dcmp(a) < 0) {
            res.pb(mp(-1e9, 1e9));
        }
        return res;
    }

    double x0 = (- b - sqrt(delta)) / (2*a), x1 = (- b + sqrt(delta)) / (2*a);
    if(x0 > x1) std::swap(x0, x1);

    if(dcmp(a) > 0) { 
        res.pb(mp(x0, x1)); 
    } else {
        res.pb(mp(-1e9, x0));
        res.pb(mp(x1, 1e9));
    }

    return res;
}

#define nxt(x) ((x + 1) % n)

vector<pdd> range;
void get_range(double l) {

    range.clear();
    double t = T / m;
    pid a = mp(0, len(p[1]-p[0])), b;
    for(int i = 0; i < n; ++i) {
        double l_ = len(p[nxt(i)] - p[i]);
        if(l_ < t) t -= l_; else { b = mp(i, l_ - t); break; }
    }

    t = 0;
    while(a.fst < n) {
        Point va = unit(p[nxt(a.fst)] - p[a.fst]);
        Point vb = unit(p[nxt(b.fst)] - p[b.fst]);
        Point pa = p[nxt(a.fst)] + unit(p[a.fst] - p[nxt(a.fst)]) * a.snd;
        Point pb = p[nxt(b.fst)] + unit(p[b.fst] - p[nxt(b.fst)]) * b.snd;

        double d = std::min(a.snd, b.snd); a.snd -= d, b.snd -= d;
        if(!dcmp(a.snd)) a.fst = a.fst + 1 , a.snd = len(p[nxt(a.fst)] - p[a.fst]);
        if(!dcmp(b.snd)) b.fst = nxt(b.fst), b.snd = len(p[nxt(b.fst)] - p[b.fst]);

        static vector<pdd> sol;
        sol = solve(dot(va-vb, va-vb), 2.*dot(pa-pb, va-vb), dot(pa-pb, pa-pb) - l*l);

        for(int i = 0; i < int(sol.size()); ++i) {
            pdd tmp = sol[i];
            chkmax(tmp.fst, 0.); chkmin(tmp.snd, d);

            if(tmp.fst <= tmp.snd) {
                range.pb(mp(tmp.fst + t, tmp.snd + t));
            }
        }
        t += d;
    }

    //for(auto x : range) { printf("%lf %lf\n", x.fst, x.snd); }
}

bool chk(double l) {
    get_range(l);
    static vector<pdd> can;
    static vector<double> pos;

    for(int i = 1; i < int(range.size()); ++i) {
        if(range[i].fst < range[i-1].snd + 1e-6) range[i].fst += 1e-6;
    }
    vector<pdd>::iterator it = range.begin();

    can.clear();
    pos.clear();
    for(int i = 1; i <= m; ++i) {
        double L = (i-1)*T / m, R = i*T / m;
        for(; it != range.end() && (*it).fst <= i*T / m; ) {
            double x = std::max((*it).fst, L);
            double y = std::min((*it).snd, R);
            
            can.pb(mp(x-L, y-L));
            pos.pb(x-L), pos.pb(y-L);
            if((*it).snd <= i*T / m + eps) ++ it; else break;
        }
    }

    static int cnt; cnt = 0;
    static double q[N*4 + 5];

    std::sort(pos.begin(), pos.end());
    std::sort(can.begin(), can.end());

    it = can.begin();
    for(int i = 0; i < int(pos.size()); ++i) {
        while(it != can.end() && (*it).fst <= pos[i]) {
            q[cnt ++] = (*it).snd; ++ it;
            std::push_heap(q, q + cnt, std::greater<double>()); 
        }

        while(cnt && q[0] < pos[i]) {
            std::pop_heap(q, q + (cnt--), std::greater<double>());
        }

        if(cnt >= m) return true;
    }
    return false;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    
    read(n), read(m);
    for(int i = 0; i < n; ++i) {
        static int x, y;
        read(x), read(y);
        p[i] = Point(x, y);
    }
    for(int i = 0; i < n; ++i) T += len(p[nxt(i)] - p[i]); 
    
    int TIMES = 50;
    double l = 0, r = 4000;

    for(; TIMES--; ) {
        double mid = (l + r) / 2.0;
        if(chk(mid)) r = mid; else l = mid;
    }
    printf("%.10lf\n", r);

    return 0;
}
