#include <bits/stdc++.h>
using namespace std;

const int N = 200000;

typedef long long ll;
typedef pair<ll, ll> pll;

int fa[N + 5], sz[N + 5];
int findset(int x) { return fa[x] == x ? x : fa[x] = findset(fa[x]); }

struct node {
    int x, sz;
    ll a, b;

    node() { }
    node(int _x, int _sz, ll _a, ll _b): x(_x), sz(_sz), a(_a), b(_b) { }

    bool operator < (const node& rhs) const {
        if((a < 0) != (rhs.a < 0)) return (a >= 0);
        return (a < 0) ? b > rhs.b : (a - b > rhs.a - rhs.b);
    }
};

int T, n;
vector<int> G[N + 5];
int p[N + 5], w[N + 5];
ll a[N + 5], b[N + 5], c[N + 5], d[N + 5];

namespace TREE {

    namespace SEG {
        const int SZ = N << 2;

#define lc (u << 1)
#define rc (u << 1 | 1)
#define mid ((l + r) >> 1)

        pll tag[SZ + 5];

        inline void merge(pll &a, pll b) {
            a = make_pair(a.first + b.first, max(a.second, a.first + b.second));
        }

        void push_down(int u) {
            merge(tag[lc], tag[u]);
            merge(tag[rc], tag[u]);
            tag[u] = make_pair(0, 0);
        }

        void modify(int u, int l, int r, int x, int y, pll t) {
            if(x <= l && r <= y) { merge(tag[u], t); return; }

            push_down(u);
            if(x <= mid) 
                modify(lc, l, mid, x, y, t);
            if(mid < y)
                modify(rc, mid+1, r, x, y, t);
        }

        ll query(int u, int l, int r, int p) {
            if(l == r) return tag[u].second;

            push_down(u);
            return (p <= mid) ? query(lc, l, mid, p) : query(rc, mid+1, r, p);
        }
    }

    int dfn[N + 5], dfs_clock;
    int sz[N + 5], son[N + 5], top[N + 5];

    void dfs1(int u) {
        sz[u] = 1;
        for(auto v : G[u]) {
            dfs1(v);
            sz[u] += sz[v];
            if(sz[v] > sz[son[u]]) son[u] = v;
        }
    }

    void dfs2(int u, int tp) {
        top[u] = tp;
        dfn[u] = ++ dfs_clock;
        if(son[u]) dfs2(son[u], tp);
        for(auto v : G[u]) if(v != son[u]) dfs2(v, v);
        SEG::modify(1, 1, n, dfn[u], dfn[u], make_pair(w[u], w[u]));
    }

    void init() {
        dfs1(1);
        dfs2(1, 1);
    }

    void modify(int x, int y, ll s, ll m) {
        if(top[y] == top[x]) {
            if(dfn[x] < dfn[y]) 
                SEG::modify(1, 1, n, dfn[x]+1, dfn[y], make_pair(s, m));
        } else {
            SEG::modify(1, 1, n, dfn[top[y]], dfn[y], make_pair(s, m));
            modify(x, p[top[y]], s, m);
        }
    }

    void print_ans() {
        for(int i = 1; i <= n; ++i) {
            printf("%lld ", SEG::query(1, 1, n, dfn[i]));
        }
    }
}

priority_queue<node> q;

int main() {
#ifdef Wearry 
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d%d", &T, &n);
    for(int i = 2; i <= n; ++i) scanf("%d", p + i), G[p[i]].push_back(i);
    for(int i = 1; i <= n; ++i) scanf("%d", w + i), b[p[i]] += w[i];
    for(int i = 1; i <= n; ++i) a[i] = b[i] - w[i], d[i] = c[i] = w[i];

    TREE::init();
    for(int i = 1; i <= n; ++i) {
        sz[i] = 1; fa[i] = i;
        q.push(node(i, 1, a[i], b[i]));
    }

    while(!q.empty()) {
        node x = q.top(); q.pop();
        if(x.sz != sz[x.x] || x.x == 1) continue;

        int u = x.x, v = findset(p[x.x]);
        TREE::modify(v, u, x.a, x.b);

        fa[u] = v;
        sz[v] += sz[u];
        b[v] = max(b[v], a[v] + b[u]);
        a[v] += a[u];

        if(v != 1) {
            q.push(node(v, sz[v], a[v], b[v]));
        }
    }

    TREE::modify(0, 1, a[1], b[1]);
    TREE::print_ans();

    return 0;
}
