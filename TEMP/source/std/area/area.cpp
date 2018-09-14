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

string procStatus() {
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}

template <typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 100000;
const double eps = 1e-7;
const double pi = acos(-1.0);

inline int dcmp(double x) { return (x > -eps) - (x < eps); }

struct Point {
    double x, y;
    Point() { }
    Point(double _x, double _y): x(_x), y(_y) { }
};

Point operator * (const Point& a, const double&b) { return Point(a.x * b, a.y * b); }
Point operator / (const Point& a, const double&b) { return Point(a.x / b, a.y / b); }
Point operator - (const Point& a, const Point& b) { return Point(a.x - b.x, a.y - b.y); }
Point operator + (const Point& a, const Point& b) { return Point(a.x + b.x, a.y + b.y); }

inline double dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
inline double cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
inline double length(const Point& a) { return dot(a, a); }

struct Event {
    double ang;
    int id, ty;
    
    bool operator < (const Event& rhs) const {
        return dcmp(ang - rhs.ang) ? dcmp(ang - rhs.ang) < 0 : ty > rhs.ty; 
    }
};

int n, tot;
vector <Event> E;
int bel[N + 5];
Point L[N + 5][2];

Point get_inter(int id, double ang) {
    Point p = L[id][0], q = L[id][1], s = Point(cos(ang), sin(ang)) * 1000.0;
    double a1 = cross(p, s), a2 = cross(s, q);
    return p + (q - p) * (a1 / (a1 + a2));
}

void input() {
    tot = read(n);
    for(int i = 0; i < n; ++i) {
        static int x1, y1, x2, y2;
        read(x1), read(y1), read(x2), read(y2);

        L[i][0] = Point(x1, y1);
        L[i][1] = Point(x2, y2);
        if(dcmp(cross(L[i][0], L[i][1])) < 0) std::swap(L[i][0], L[i][1]);

        static Event temp;
        double ang1 = atan2(L[i][0].y, L[i][0].x), ang2 = atan2(L[i][1].y, L[i][1].x);

        bel[i] = i;
        if(dcmp(ang1 - ang2) > 0) {
            Point x = get_inter(i, pi);
            L[tot][1] = L[i][1];
            L[i][1] = L[tot][0] = x;

            bel[tot] = i;
            temp = (Event) { ang1, i, 0 }; E.pb(temp);
            temp = (Event) { pi, i, 1 }; E.pb(temp);
            temp = (Event) {-pi, tot, 0 }; E.pb(temp);
            temp = (Event) { ang2, tot, 1 }; E.pb(temp); tot ++;
        } else {
            temp = (Event) { ang1, i, 0 }; E.pb(temp);
            temp = (Event) { ang2, i, 1 }; E.pb(temp);
        }
    } n = tot;
}

double ang, lstang;
struct node {
    int id;

    bool operator < (const node& rhs) const {
        return dcmp(length(get_inter(id, ang)) - length(get_inter(rhs.id, ang))) < 0;
    }
};

double delta[N + 5];

std::set <node> s;
std::map <pii, double> mp;
std::set <node> :: iterator it;

void solve() {
    double area = 0;
    std::sort(E.begin(), E.end());
    for(int i = 0, j = 0; i < (int) E.size(); i = j) {
        static int x, y, z;
        static double a1, a2;

        ang = E[i].ang;
        if(s.size()) { 
            x = (*s.begin()).id;
            area += (a1 = cross(get_inter(x, lstang), get_inter(x, ang)));

            if(s.size() <= 1) { 
                delta[bel[x]] = 1e18; 
            } else {
                it = s.begin(), y = (*++it).id;
                delta[bel[x]] += (a2 = cross(get_inter(y, lstang), get_inter(y, ang))) - a1;

                if(s.size() > 2) {
                    z = (*++it).id;
                    mp[mp(bel[x], bel[y])] += cross(get_inter(z, lstang), get_inter(z, ang)) - a2;
                } else {
                    mp[mp(bel[x], bel[y])] = 1e18;
                }
            }
        }

        j = i;
        while(j < (int) E.size() && !dcmp(E[j].ang - ang)) {
            if(E[j].ty == 0) { 
                s.insert((node) { E[j].id }); 
            } else { 
                s.erase((node) { E[j].id }); 
            }
            ++ j;
        }

        lstang = ang;
    }

    printf("%.2lf\n", area / 2.0);

    double del2 = 0.0;
    for(auto x : mp) {
        chkmax(del2, x.snd + delta[x.fst.fst] + delta[x.fst.snd]);
    }

    std::sort(delta, delta + n, std::greater<double>());

    if(delta[0] >= 1e18) 
        puts("infinite"); 
    else 
        printf("%.2lf\n", (area + delta[0]) / 2.0);

    chkmax(del2, delta[0] + delta[1]);

    if(del2 >= 1e18) {
        puts("infinite");
    } else {
        printf("%.2lf\n", (area + del2) / 2.0);
    }
}

int main() {
    freopen("area.in", "r", stdin);
    freopen("area.out", "w", stdout);

    input();
    solve();

    return 0;
}
