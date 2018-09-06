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

inline pii merge(const pii& a, const pii& b) {
    pii temp;
    if(a.snd < b.fst) {
        temp = mp(a.fst + b.fst - a.snd, b.snd);
    } else {
        temp = mp(a.fst, b.snd + a.snd - b.fst);
    } return temp;
}

namespace SEG {
#define lc (u << 1)
#define rc (u << 1 | 1)
#define mid ((l + r) >> 1)
    
    const int SZ = N << 2;

    pii t[SZ + 5];
    bool clr[SZ + 5];

    void push_down(int u, int l, int r) {
        if(clr[u]) {
            clr[u] = false;
            clr[lc] = clr[rc] = true;
            t[rc] = mp(r - mid, 0);
            t[lc] = mp(mid - l + 1, 0);
        }
    }
    void build(int u, int l, int r) { 
        if(l == r) { t[u] = mp(1, 0); return; }
        build(lc, l, mid);
        build(rc, mid+1, r);
        t[u] = merge(t[lc], t[rc]);
    }

    void clear(int u, int l, int r, int x, int y) { 
        if(x <= l && r <= y) {
            clr[u] = true;
            t[u] = mp(r - l + 1, 0);
            return;
        }
        push_down(u, l, r);
        if(x <= mid) clear(lc, l, mid, x, y);
        if(mid < y) clear(rc, mid+1, r, x, y);
        t[u] = merge(t[lc], t[rc]);
    }

    void modify(int u, int l, int r, int p, int v) { 
        if(l == r) { t[u].snd += v; return; }
        push_down(u, l, r);
        (p <= mid) ? modify(lc, l, mid, p, v) : modify(rc, mid+1, r, p, v);
        t[u] = merge(t[lc], t[rc]);
    }

    pii query(int u, int l, int r, int x, int y) { 
        if(x > r || y < l) return mp(0, 0);
        if(x <= l && r <= y) return t[u];
        push_down(u, l, r);
        return merge(query(lc, l, mid, x, y), query(rc, mid+1, r, x, y));
    }
}

int n, q;
vector<int> G[N + 5];
int dfn[N + 5], fa[N + 5], clk;
int top[N + 5], son[N + 5], sz[N + 5];

void dfs(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++ clk;
    if(son[u]) dfs(son[u], tp);

    for(auto v : G[u]) if(v != son[u]) dfs(v, v);
}

pii query(int x) {
    return top[x] == 1 ? 
        SEG::query(1, 1, n, 1, dfn[x]) : merge(query(fa[top[x]]), SEG::query(1, 1, n, dfn[top[x]], dfn[x]));
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n); read(q);
    for(int i = 2; i <= n; ++i) G[read(fa[i])].pb(i);
    for(int i = n; i >= 1; --i) {
        ++ sz[i];
        sz[fa[i]] += sz[i];
        if(!son[fa[i]] || sz[i] > sz[son[fa[i]]]) son[fa[i]] = i;
    }
    dfs(1, 1);

    SEG::build(1, 1, n);
    while(q--) {
        static int op, x;
        read(op), read(x);
        if(op == 1) SEG::modify(1, 1, n, dfn[x], 1);
        else {
            int val = query(x).snd;
            if(op == 2) {
                SEG::modify(1, 1, n, dfn[x], -val);
                SEG::clear(1, 1, n, dfn[x] + 1, dfn[x] + sz[x] - 1);
            } else puts(val ? "black" : "white");
        }
    }

    return 0;
}
