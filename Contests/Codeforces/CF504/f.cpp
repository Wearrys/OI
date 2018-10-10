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
    T f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = (int) 5e5;
const int M = (int) 1e6;

int n, k, m;
struct edge {
    int u, v, w;
    bool operator < (const edge& rhs) const {
        return w < rhs.w;
    }
};

edge e[N + 5];
int fw[N + 5];
int fa[N + 5][21], dep[N + 5];
int st[N + 5], to[M + 5], nxt[M + 5], ecnt = 1;

inline void addedge(int u, int v) {
    to[++ ecnt] = v; nxt[ecnt] = st[u]; st[u] = ecnt; 
    to[++ ecnt] = u; nxt[ecnt] = st[v]; st[v] = ecnt;
}

void dfs(int u, int f = 0) {
    fa[u][0] = f;
    dep[u] = dep[f] + 1;
    for(int i = 1; i < 21; ++i) fa[u][i] = fa[fa[u][i-1]][i-1];
    for(int i = st[u]; i; i = nxt[i]) {
        int v = to[i];
        if(v == f) continue;
        dfs(v, u);
        fw[v] = i >> 1;
    }
}

int lca(int x, int y) {
    if(dep[x] < dep[y]) {
        std::swap(x, y);
    }
    for(int i = 20; i >= 0; --i) 
        if(dep[fa[x][i]] >= dep[y]) { x = fa[x][i]; }
    if(x == y) return x;
    for(int i = 20; i >= 0; --i) 
        if(fa[x][i] != fa[y][i]) { x = fa[x][i], y = fa[y][i]; }
    return fa[x][0];
}

int pa[N + 5];
int findset(int x) {
    return pa[x] == x ? x : pa[x] = findset(pa[x]);
}

int ans[N + 5];
int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(k), read(m);
    for(int i = 1; i <= n; ++i) pa[i] = i;
    for(int i = 1; i <= k; ++i) {
        static int x, y; read(x), read(y);
        addedge(x, y), pa[findset(x)] = findset(y);
    }
    for(int i = 1; i <= m; ++i) read(e[i].u), read(e[i].v), read(e[i].w); 

    std::sort(e + 1, e + m + 1);

    for(int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v;
        if(findset(u) ^ findset(v)) {
            e[i].w = -1;
            addedge(u, v);
            pa[findset(u)] = findset(v);
        }
    }

    for(int i = 1; i <= n; ++i) pa[i] = i;
    for(int i = 1; i <= n; ++i) if(!dep[i]) dfs(i); 

    ll res = 0;
    memset(ans, oo, sizeof ans);

    for(int j = 1; j <= m; ++j) if(e[j].w != -1) {
        int r = lca(e[j].u, e[j].v);

        for(int i = findset(e[j].u); i != findset(r); i = findset(i)) {
            ans[fw[i]] = e[j].w, pa[i] = fa[i][0], i = fa[i][0];
        }
        for(int i = findset(e[j].v); i != findset(r); i = findset(i)) {
            ans[fw[i]] = e[j].w, pa[i] = fa[i][0], i = fa[i][0];
        }
    }
    for(int i = 1; i <= k; ++i) {
        if(ans[i] == oo) {
            res = -1; break;
        } 
        res += ans[i];
    }
    printf("%lld\n", res);
    return 0;
}
