#include <bits/stdc++.h>

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

const int oo = 0x3f3f3f3f;

template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

const int N = 510;
const int M = 100000;
const double eps = 1e-7;

inline int dcmp(double x) {
    return (x > -eps) - (x < eps);
}

struct Point { 
    double x, y; 
    Point() { }
    Point(double x_, double y_): x(x_), y(y_) { }

    friend double cross(const Point& a, const Point& b) { 
        return a.x * b.y - a.y * b.x; 
    }
};

struct Query { 
    int id; 
    Point p; 
    Query() { }
    Query(int id_, Point p_): id(id_), p(p_) { }
};

struct Cross { 
    int x, y; 
    Point p; 
    Cross() { }
    Cross(int x_, int y_, Point p_): x(x_), y(y_), p(p_) { } 
};

struct Line {
    double a, b, c, k;

    Line() { }
    Line(double a_, double b_, double c_):a(a_), b(b_), c(c_) {
        if(dcmp(b)) {
            if(dcmp(b) < 0) {
                a = -a, b = -b, c = -c;
            }
        } else if(dcmp(a) > 0) a = -a, c = -c;

        k = dcmp(b) ? -a / b : DBL_MAX;
    }

    double operator() (const Point& p) const {
        return a * p.x + b * p.y + c;
    }
};

bool cmp_point(const Point& a, const Point& b) {
    return dcmp(a.x - b.x) ? a.x < b.x : a.y < b.y;
}

bool cmp_query(const Query& a, const Query& b) {
    return cmp_point(a.p, b.p);
}

bool cmp_cross(const Cross& a, const Cross& b) {
    if(dcmp(a.p.x - b.p.x)) {
        return a.p.x < b.p.x;
    } else if(dcmp(a.p.y - b.p.y)) {
        return a.p.y < b.p.y;
    }
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool cmp_line(const Line& a, const Line& b) {
    if(dcmp(a.k - b.k)) {
        return a.k < b.k;
    } else {
        if(dcmp(a.b)) {
            return -a.c / a.b > -b.c / b.b;
        }
        return -a.c / a.a < -b.c / b.a;
    }
}

Point inter(const Line& a, const Line& b) {
    double x = (a.b * b.c - b.b * a.c) / (b.b * a.a - a.b * b.a);
    return Point(x, dcmp(a.b) ? (-a.c - a.a * x) / a.b : (-b.c - b.a * x) / b.b);
}

Line l[N + 5];
Query q[M + 5];
Cross c[N*N + 5];

double L;
int n, m;
int totCro;

void input() {
    read(n), read(m); scanf("%lf", &L);

    for(int i = 1; i <= n; ++i) {
        static double x, y, z;
        scanf("%lf%lf%lf", &x, &y, &z); l[i] = Line(x, y, z);
    }
    l[++ n] = Line(-1, 0, -L);
    l[++ n] = Line(-1, 0, +L);
    l[++ n] = Line(0, -1, -L);
    l[++ n] = Line(0, -1, +L);

    for(int i = 1; i <= m; ++i) {
        static double x, y;
        scanf("%lf%lf", &x, &y);
        q[i] = Query(i, Point(x, y));
    }

    std::sort(l + 1, l + n + 1, cmp_line);
    std::sort(q + 1, q + m + 1, cmp_query);
    
//    for(int i = 1; i <= n; ++i) debug("l[%d] = (%lf, %lf, %lf, %lf)\n", i, l[i].a, l[i].b, l[i].c, l[i].k);
    for(int i = 1; i <= n; ++i) {
        for(int j = i+1; j <= n; ++j) {
            if(dcmp(l[i].k - l[j].k)) {
                c[++ totCro] = Cross(i, j, inter(l[i], l[j]));
                //debug("%d %d (%lf, %lf)\n", i, j, inter(l[i], l[j]).x, inter(l[i], l[j]).y);
            }
        }
    }
    std::sort(c + 1, c + totCro + 1, cmp_cross);
}

Point lst[N + 5];
int id[N + 5], rk[N + 5];

vector<int> in[N + 5];
double ans[M + 5], area[N + 5];

int find_pos(const Point& a) {
    int l_ = 1, r_ = n;
    while(l_ < r_) {
        int mid = (l_ + r_) >> 1;
        if(l[id[mid]](a) > 0) r_ = mid; else l_ = mid + 1;
    }
    return l_;
}

void solve() {
    for(int i = 1; i <= n; ++i) id[i] = rk[i] = i;
    for(int i = 1, j = 1; i <= totCro; ++i) {

        while(j <= m && cmp_point(q[j].p, c[i].p)) {
            int x = find_pos(q[j].p);
            in[x].pb(q[j].id); ++j;
        }

        int a = rk[c[i].x], b = rk[c[i].y];
        double xa = cross(c[i].p, lst[a]), xb = cross(lst[b], c[i].p);

        assert(a == b - 1);

        area[b] += xa + xb;
        for(const auto &qid : in[b]) ans[qid] = area[b];

        area[b] = 0;
        in[b].clear();

        area[a] -= xa;
        area[b+1] -= xb;
        lst[a] = lst[b] = c[i].p;

        std::swap(id[a], id[b]);
        rk[id[a]] = a; rk[id[b]] = b;
    }
    for(int i = 1; i <= m; ++i) { printf("%.2lf\n", ans[i] / 2); }
}

int main() {
#ifdef Wearry
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    input();
    solve();

    return 0;
}
