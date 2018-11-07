#include <bits/stdc++.h>
using namespace std;

const int N = 2000;
const double PI = acos(-1.0);

#define fst first
#define snd second
#define sqr(x) (1. * (x) * (x))

struct Point {
    double x, y;
    Point() { }
    Point(double _x, double _y): x(_x), y(_y) { }
    Point operator + (const Point& b) const { return Point(x + b.x, y + b.y); }
    Point operator - (const Point& b) const { return Point(x - b.x, y - b.y); }
    Point turn(const double& ang) const { return Point(cos(ang) * x, sin(ang) * x); }
};

double dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
double cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
 
struct Circle {
    Point o;
    double r;
};

int n;
bool vis[N + 5];
Circle C[N + 5];

void fix(double& a) { 
    while(a < -PI) a += 2*PI;
    while(a > +PI) a -= 2*PI; 
}

bool in(Circle a, Circle b) { return sqr(b.r - a.r) >= dot(a.o - b.o, a.o - b.o); }
bool out(Circle a, Circle b) { return sqr(a.r + b.r) <= dot(a.o - b.o, a.o - b.o); }

struct node {
    double l, r;
    node(double _l = 0, double _r = 0): l(_l), r(_r) { }

    bool operator < (const node& rhs) const {
        return r < rhs.r;
    }
};

std::set <node> S[N + 5];
typedef std::set <node> :: iterator sit;

double area = 0.0;
double calc(double l, double r, Circle c) {
    double res = 0.0;
    Point _l = Point(c.r, 0).turn(l), _r = Point(c.r, 0).turn(r);
    res -= .5 * cross(_l, _r);
    res += .5 * (r - l) * c.r * c.r;
    res += .5 * cross(c.o + _l, c.o + _r);
    return res;
}

void remove(int id, double l, double r) {
    fix(l), fix(r);
    if(l > r) {
        remove(id, -PI, r);
        remove(id, l, +PI);
    } else {
        for(sit it = S[id].lower_bound(node(0, l)), tmp; it != S[id].end() && it -> l < r; it = tmp) {
            double _l = it -> l, _r = it -> r;
            tmp = it; ++ tmp;
            S[id].erase(it);
            area -= calc(_l, _r, C[id]);
            if(_l < l) area += calc(_l, l, C[id]), S[id].insert(node(_l, l));
            if(_r > r) area += calc(r, _r, C[id]), S[id].insert(node(r, _r));
        }
    }
}

int main() {
#ifdef Wearry 
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%*d%d", &n);

    for(int i = 1; i <= n; ++i) {
        vis[i] = true;
        scanf("%lf%lf%lf", &C[i].o.x, &C[i].o.y, &C[i].r);

        for(int j = 1; j < i; ++j) if(vis[j]) {
            if(C[j].r >=C[i].r && in(C[i], C[j])) { vis[i] = false; break; }
            if(C[i].r > C[j].r && in(C[j], C[i])) { vis[j] = false; remove(j, -PI, PI); }
        }

        if(!vis[i]) { printf("%.10lf\n", area); continue; }

        area += PI * C[i].r * C[i].r;
        S[i].insert(node(-PI, PI));

        for(int j = 1; j < i; ++j) if(vis[j]) {
            if(out(C[i], C[j])) continue;

            double dist = dot(C[i].o - C[j].o, C[i].o - C[j].o), ang, cur;

            cur = atan2(C[j].o.y - C[i].o.y, C[j].o.x - C[i].o.x);
            ang = acos((sqr(C[i].r) + dist - sqr(C[j].r)) / (2. * C[i].r * sqrt(dist)));
            remove(i, cur - ang, cur + ang);

            cur = atan2(C[i].o.y - C[j].o.y, C[i].o.x - C[j].o.x);
            ang = acos((sqr(C[j].r) + dist - sqr(C[i].r)) / (2. * C[j].r * sqrt(dist)));
            remove(j, cur - ang, cur + ang);
        }

        printf("%.10lf\n", area);
    }

    return 0;
}
