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

const int N = 10000;

struct point {
    int x, y;
    point(int _x = 0, int _y = 0): x(_x), y(_y) { }

    inline point operator + (const point& rhs) const { return point(x + rhs.x, y + rhs.y); }
    inline point operator - (const point& rhs) const { return point(x - rhs.x, y - rhs.y); }
    inline bool operator < (const point& rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
};

inline int dot(const point& a, const point& b) { return a.x * b.x + a.y * b.y; }
inline int cross(const point& a, const point& b) { return a.x * b.y - a.y * b.x; }

vector<point> convex_hull(vector<point> a) {
    vector<point> h;
    std::sort(a.begin(), a.end());

    for(auto p : a) {
        while((int) h.size() > 1 && cross(p - *h.rbegin(), p - *(h.rbegin() + 1)) >= 0) {
            h.pop_back();
        }
        h.pb(p);
    }

    int m = h.size(); h.pop_back();
    std::reverse(a.begin(), a.end());

    for(auto p : a) {
        while((int) h.size() > m && cross(p - *h.rbegin(), p - *(h.rbegin() + 1)) >= 0) {
            h.pop_back();
        }
        h.pb(p);
    }
    h.pop_back();

    return h;
}

bool solve(vector<point> a, vector<point> b) {
    vector<pii> edge;
    std::function<void(int, int)> get = [&] (int l, int r) {
        edge.pb(mp(l, r));
        if(r - l < 2) return;

        int p = -1;
        double mx = -DBL_MAX;

        for(int i = l + 1; i < r; ++i) {
            double temp = 1. * dot(a[r] - a[i], a[l] - a[i]) / cross(a[r] - a[i], a[l] - a[i]);
            if(chkmax(mx, temp)) p = i;
        }

        get(l, p);
        get(p, r);
    };

    a = convex_hull(a);
    get(0, a.size() - 1);

    for(auto e : edge) {

        int x = e.fst, y = e.snd;
        double l = -DBL_MAX, r = DBL_MAX;

        for(int i = 0; i < (int) a.size() && l < r; ++i) {
            int p = dot(a[y] - a[i], a[x] - a[i]);
            int q = cross(a[y] - a[i], a[x] - a[i]);
            if(!q) continue;

            if(q < 0) {
                chkmin(r, double(p) / q);
            } else {
                chkmax(l, double(p) / q);
            }
        }

        for(int i = 0; i < (int) b.size() && l < r; ++i) {
            int p = dot(a[y] - b[i], a[x] - b[i]);
            int q = cross(a[y] - b[i], a[x] - b[i]);
            if(!q) {
                if(p > 0) continue;
                l = DBL_MAX; break;
            }

            if(q < 0) {
                chkmax(l, double(p) / q);
            } else {
                chkmin(r, double(p) / q);
            }
        }

        if(l < r) return true;
    }

    return false;
}

int n, m;
vector<point> a, b;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(m);
    for(int i = 0, x, y; i < n; ++i) read(x), read(y), a.emplace_back(x, y);
    for(int i = 0, x, y; i < m; ++i) read(x), read(y), b.emplace_back(x, y);

    if(n == 1 || m == 1) return puts("YES"), 0;

    puts((solve(a, b) || solve(b, a)) ? "YES" : "NO");

    return 0;
}
