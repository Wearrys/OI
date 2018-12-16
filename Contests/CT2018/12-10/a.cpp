#include <bits/stdc++.h>
using namespace std;

const int S = 325;
const int N = 100000;

int w[N + 5];
int n, m, type;

namespace B {

    int bel[N + 5], bcnt;
    int t[S + 5][2 * N + 5];
    int ans[S + 5], tag[S + 5];

    void init() {
        bcnt = n / S;
        for(int i = 1; i <= n; ++i) { 
            bel[i] = i / S; 

            if(w[i] >= -N && w[i] <= N) {
                ++ t[bel[i]][w[i] + N];
            } else if(w[i] > N) {
                ++ ans[bel[i]];
            }
        }

        for(int b = 0; b <= bcnt; ++b) {
            for(int i = 1; i <= 2 * N; ++i) {
                t[b][i] += t[b][i-1];
            }
        }
    }

    
    void modify(int l, int r, int v) {
        if(bel[l] == bel[r]) {
            for(int i = l; i <= r; ++i) modi(bel[l], w[i], v);
        } else {
            for(int i = l; bel[i] == bel[l]; ++i) modi(bel[l], w[i], v);
            for(int i = bel[l] + 1; i < bel[r]; ++i) tag[i] += v;
            for(int i = r; bel[i] == bel[r]; --i) modi(bel[r], w[i], v);
        }
    }
}

vector<int> G[N + 5];

void addedge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

int dfn[N + 5], top[N + 5], dfc;
int fa[N + 5], sz[N + 5], dep[N + 5];

void dfs(int u, int f = 0) {
    fa[u] = f;
    sz[u] = 1;
    dep[u] = dep[f] + 1;

    for(auto v : G[u]) if(v != f) {
        dfs(v, u);
        sz[u] += sz[v];
        if(!son[u] || sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs(int u, int tp, int f = 0) {
    top[u] = tp;
    dfn[u] = ++ dfc;

    if(son[u]) dfs(son[u], tp, u);
    for(auto v : G[u]) if(v != f && v != son[u]) {
        dfs(v, v, u);
    }   
}

void input() {
    scanf("%d%d%d", &n, &m, &type);

    for(int i = 1; i < n; ++i) {
        static int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v);
    }

    dfs(1);
    dfs(1, 1);

    for(int i = 1; i <= n; ++i) scanf("%d", w + dfn[i]);
    B::init();
}

void solve() {
    while(m--) {
        static int lans = 0;
        static int op, x, y, z;

        scanf("%d%d", &op, &x);
        if(op < 3) scanf("%d", &y);
        if(op < 2) scanf("%d", &z);
        if(type) x ^= lans, y ^= lans;

        if(op == 1) modify(x, y, w);
        if(op == 2) printf("%d\n", lans = query(x, y));
        if(op == 3) printf("%d\n", lans = B::query(dfn[x], dfn[x] + sz[x] - 1));
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    input();
    solve();

    return 0
}
