#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb push_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const LL oo = 1e9;
const int maxn = 40000 + 5;
const long double eps = 1e-10;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n;
long double pos[maxn];
int c[maxn], rk[maxn];

struct Line { LL a, b, c; } L[maxn];

inline bool cmp(int x, int y) { return pos[x] < pos[y]; }
inline bool cmpx(Line x, Line y) { return 1.0 * x.a / x.b > 1.0 * y.a / y.b; }
inline bool cmpy(Line x, Line y) { return 1.0 * x.b / x.a > 1.0 * y.b / y.a; }

inline int lowbit(int x) { return x & (-x); }
void update(int u) {
    while(u <= n) {
        c[u] ++;    
        u += lowbit(u);
    }
}
int query(int u) {
    int res = 0;
    while(u > 0) {
        res += c[u];
        u -= lowbit(u);
    }
    return res;
}

bool chkx(long double mid) {
    LL res = 0;
    for(int i = 1; i <= n; ++i) 
        c[i] = 0, rk[i] = i, pos[i] = -(L[i].c + L[i].a * mid) / L[i].b;

    sort(rk + 1, rk + n + 1, cmp);
    for(int i = 1; i <= n; ++i) {
        res += query(rk[i]); update(rk[i]);
    }
    return (res << 2LL) >= 1LL * n * (n-1);
}

bool chky(long double mid) {
    LL res = 0;
    for(int i = 1; i <= n; ++i) 
        c[i] = 0, rk[i] = i, pos[i] = -(L[i].c + L[i].b * mid) / L[i].a;

    sort(rk + 1, rk + n + 1, cmp);
    for(int i = 1; i <= n; ++i) {
        res += query(rk[i]); update(rk[i]);
    }
    return (res << 2LL) >= 1LL * n * (n-1);
}

int main() {
#ifdef Wearry 
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif 

    n = read<int>();
    for(int i = 1; i <= n; ++i) {
        L[i].a = read<int>(); 
        L[i].b = read<int>();
        L[i].c = -read<int>();
    }

    static long double l, r;
    
    l = -oo, r = oo;
    sort(L + 1, L + n + 1, cmpx);

    while(r - l > eps) {
        long double mid = (l + r) / 2.0;
        if(chkx(mid)) r = mid; else l = mid;
    }
    printf("%.10Lf ", l);

    l = -oo, r = oo;
    sort(L + 1, L + n + 1, cmpy);

    while(r - l > eps) {
        long double mid = (l + r) / 2.0;
        if(chky(mid)) r = mid; else l = mid;
    }
    printf("%.10Lf\n", l);

    return 0;
}
