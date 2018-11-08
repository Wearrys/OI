#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int M = 3;

struct matrix {
    double a[M][M];
    matrix(const bool& t = 0) {
        memset(a, 0, sizeof a);
        if(t) for(int i = 0; i < M; ++i) a[i][i] = 1.0;
    }
};

matrix operator * (const matrix& a, const matrix& b) {
    matrix c;
    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < M; ++j) {
            for(int k = 0; k < M; ++k) {
                c.a[i][k] += a.a[i][j] * b.a[j][k];
            }
        }
    }
    return c;
}

const int N = 100000;

int n;
long long t;

struct Point { 
    double x, y; 

    Point() { }
    Point(double _x, double _y): x(_x), y(_y) { }

    bool operator < (const Point& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

Point operator - (const Point& a, const Point& b) { return Point(a.x - b.x, a.y - b.y); }

double val;
Point P[N + 5];
double cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d%lld", &n, &t);
    for(int i = 0; i < n; ++i) {
        int a, b; double p;
        scanf("%d%d%lf", &a, &b, &p);
        P[i] = Point(p, p * a); val = max(val, b * p);
    }

    std::sort(P, P + n);

    int m = 0;
    static Point Conv[N + 5];

    auto slope = [&] (const int& x, const int& y) {
        if(Conv[x].x == Conv[y].x) return DBL_MAX;
        return (Conv[x].y - Conv[y].y) / (Conv[x].x - Conv[y].x);
    };

    for(int i = 0; i < n; ++i) {
        while(m > 1 && cross(Conv[m-1] - Conv[m-2], P[i] - Conv[m-2]) >= 0) 
            -- m;
        Conv[m ++] = P[i];
    }

    double ft = 0.0;
    long long T = 0;

    for(int i = 0; i < m; ++i) {
        matrix cur;

        cur.a[0][0] = 1.0 - Conv[i].x; 
        cur.a[0][1] = Conv[i].x;
        cur.a[1][1] = cur.a[1][2] = cur.a[2][2] = 1.0;

        double a = Conv[i].y / Conv[i].x;
        static matrix pw[60];

        pw[0] = cur;
        for(int j = 1; j <= 50; ++j) pw[j] = pw[j-1] * pw[j-1];

        for(int j = 50; j >= 0; --j) if(T + (1ll << ll(j)) <= t) {

            ll _T = T + (1ll << ll(j));
            double _ft = ft * pw[j].a[0][0] + (val * T + a) * pw[j].a[0][1] + val * pw[j].a[0][2];

            if(i == m-1 || slope(i+1, i) < _ft - val * _T) {
                T = _T;
                ft = _ft;
            }
        }

        if(T < t && (i == m-1 || slope(i+1, i) < ft - val*T)) {
            ft = ft * cur.a[0][0] + (val * T + a) * cur.a[0][1];
            ++ T;
        }
    }

    assert(T == t);
    printf("%.8lf\n", ft);

    return 0;
}
