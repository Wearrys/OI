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

namespace SEG {
    const int SZ = N << 2;

#define lc (u << 1)
#define rc (u << 1 | 1)
#define mid ((l + r) >> 1)

    int taga[SZ + 5], mn[SZ + 5];

    void clear() {
        memset(mn, oo, sizeof mn);
        memset(taga, 0, sizeof taga);
    }

    void push_down(int u) {
        if(taga[u]) {
            taga[lc] += taga[u], mn[lc] += taga[u];
            taga[rc] += taga[u], mn[rc] += taga[u];
        } taga[u] = 0;
    }

    void modify(int u, int l, int r, int p, int v) {
        if(l == r) { mn[u] = v; return; }
        push_down(u);
        (p <= mid) ? modify(lc, l, mid, p, v) : modify(rc, mid+1, r, p, v);

        mn[u] = std::min(mn[lc], mn[rc]);
    }

    void add(int u, int l, int r, int x, int y, int v) {
        if(x <= l && r <= y) { mn[u] += v; taga[u] += v; return; }
        push_down(u);

        if(x <= mid) add(lc, l, mid, x, y, v);
        if(mid < y) add(rc, mid+1, r, x, y, v);

        mn[u] = std::min(mn[lc], mn[rc]);
    }

    int query(int u, int l, int r, int v) {
        if(l == r) return l;
        push_down(u);
        return (mn[rc] == v) ? query(rc, mid+1, r, v) : query(lc, l, mid, v);
    }
#undef lc
#undef rc
}

int rtl[N + 5], rtr[N + 5];

namespace PRE {
    const int SZ = N << 6;

    int cnt;
    int lc[SZ + 5], rc[SZ + 5], mx[SZ + 5];

    inline int cpy(int x) {
        ++ cnt;
        mx[cnt] = mx[x];
        lc[cnt] = lc[x], rc[cnt] = rc[x];
        return cnt;
    }

    void modify(int &u, int v, int l, int r, int p, int c) {
        u = cpy(v); mx[u] = c;
        if(l == r) return;
        (p <= mid) ? modify(lc[u], lc[v], l, mid, p, c) : modify(rc[u], rc[v], mid+1, r, p, c);
    }

    int query(int u, int l, int r, int x, int y) {
        if(!u || y < l || x > r) return -oo;
        if(x <= l && r <= y) return mx[u];
        return std::max(query(lc[u], l, mid, x, y), query(rc[u], mid+1, r, x, y));
    }
}

int n, q, ty;
vector<pii> mx, mn;
int p[N + 5], r[N + 5], l[N + 5];

void init() {
    SEG::clear();
    for(int i = n; i >= 1; --i) {
        int cur = i + 1;
        while(mx.size() && mx.back().fst < p[i]) {
            SEG::add(1, 1, n, cur, mx.back().snd, p[i] - mx.back().fst);
            cur = mx.back().snd + 1; mx.pop_back();
        } mx.pb(mp(p[i], cur - 1)); 

        cur = i + 1;
        while(mn.size() && mn.back().fst > p[i]) {
            SEG::add(1, 1, n, cur, mn.back().snd, mn.back().fst - p[i]);
            cur = mn.back().snd + 1; mn.pop_back();
        } mn.pb(mp(p[i], cur - 1));

        SEG::modify(1, 1, n, i, -i);
        r[i] = SEG::query(1, 1, n, -i);
    }

    std::reverse(p + 1, p + n + 1);
    SEG::clear(), mn.clear(), mx.clear();

    for(int i = n; i >= 1; --i) {
        int cur = i + 1;
        while(mx.size() && mx.back().fst < p[i]) {
            SEG::add(1, 1, n, cur, mx.back().snd, p[i] - mx.back().fst);
            cur = mx.back().snd + 1; mx.pop_back();
        } mx.pb(mp(p[i], cur - 1)); 

        cur = i + 1;
        while(mn.size() && mn.back().fst > p[i]) {
            SEG::add(1, 1, n, cur, mn.back().snd, mn.back().fst - p[i]);
            cur = mn.back().snd + 1; mn.pop_back();
        } mn.pb(mp(p[i], cur - 1));

        SEG::modify(1, 1, n, i, -i);
        l[n - i + 1] = n - SEG::query(1, 1, n, -i) + 1;
    }

    for(int i = 1; i <= n; ++i) { PRE::modify(rtl[i], rtl[i-1], 1, n, r[i], i); }
    for(int i = n; i >= 1; --i) { PRE::modify(rtr[i], rtr[i+1], 1, n, l[i], n-i); }
}

int main() {

    read(n);
    for(int i = 1; i <= n; ++i) read(p[i]);

    init();

    read(q); read(ty);
    for(int i = 1; i <= q; ++i) {
        static int x, y;
        static pii lans;

        read(x), read(y);
        x ^= (ty * lans.fst), y ^= (ty * lans.snd);

        lans.fst = PRE::query(rtl[x], 1, n, y, n);
        lans.snd = n-PRE::query(rtr[y], 1, n, 1, x);

        printf("%d %d\n", lans.fst, lans.snd);
    }

    return 0;
}
