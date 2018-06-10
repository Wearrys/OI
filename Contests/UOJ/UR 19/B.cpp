#include <bits/stdc++.h>

typedef long long ll;

using std::pair;
using std::vector;
using std::string;

#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

template<typename T> T read(T& x) {
    T f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 2000;

struct Point {
    int x, y;

    Point() { }
    Point(int _x, int _y): x(_x), y(_y) { }
};

pii e[N + 5];
Point P[N + 5];

inline double get_dis1(int x, int y) {
    double dx = (P[x].x - P[y].x), dy = (P[x].y - P[y].y);
    return sqrt(dx * dx + dy * dy);
}

inline double get_dis2(int x, int y) {
}

int n;
vector<int> G[N + 5];
double dis[N + 5][N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 1; i <= n; ++i) read(P[i].x), read(P[i].y);
    for(int i = 1; i < n; ++i) {
        read(e[i].fst), read(e[i].snd);

        G[i + n].pb(e[i].fst);
        G[i + n].pb(e[i].snd);
        G[e[i].fst].pb(i + n);
        G[e[i].snd].pb(i + n);
    }

    for(int i = 1; i < 2*n; ++i)
        for(int j = 1; j < 2*n; ++j) if(i ^ j) {
            if(i > n && j > n) continue;
            if(i > n) 
                dis[i][j] = get_dis2(j, i-n);
            else if(j > n) 
                dis[i][j] = get_dis2(i, j);
            else {
                dis[i][j] = get_dis1(i, j);
            }
        }

    return 0;
}
