#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int N = (int) 1e6;
const int oo = 0x3f3f3f3f;

template<typename T> T read(T& x) {
    T f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

int n, k, m;
struct edge {
    int u, v, w;

    bool operator < (const edge& rhs) const {
        return w < rhs.w;
    }
};

edge e[N + 5];

namespace LCT {

#define TY(u) (c[fa[u]][1] == u) 
#define rt(u) (c[fa[u]][0] != u && c[fa[u]][1] != u)
    
    bool rev[N + 5];
    int val[N + 5], tag[N + 5];
    int fa[N + 5], c[N + 5][2];

    void clear() {
        memset(val, oo, sizeof val);
        memset(tag, oo, sizeof tag);
    }

    inline void push_down(int u) {
        if(rev[u]) {
            rev[u] = 0;
            swap(c[u][0], c[u][1]);

            rev[c[u][0]] ^= 1;
            rev[c[u][1]] ^= 1;
        }

        if(c[u][0]) {
            chkmin(tag[c[u][0]], tag[u]);
            chkmin(val[c[u][0]], tag[u]);
        }
        if(c[u][1]) {
            chkmin(tag[c[u][1]], tag[u]);
            chkmin(val[c[u][1]], tag[u]);
        }
        tag[u] = oo;
    }

    inline void rotate(int u) {
        int v = fa[u], w = fa[v];
        bool t = (c[v][1] == u);

        if(!rt(v)) c[w][c[w][1] == v] = u;
        c[v][t] = c[u][t^1]; fa[c[u][t^1]] = v;
        c[u][t^1] = v; fa[v] = u; fa[u] = w;
    }

    inline void Push(int u) {
        if(!rt(u)) Push(fa[u]);
        push_down(u);
    }

    inline void splay(int u) {
        Push(u);
        while(!rt(u)) {
            if(!rt(fa[u]))
                rotate(TY(u) == TY(fa[u]) ? fa[u] : u); 
            rotate(u);
        }
    }

    inline int access(int u) {
        int v;
        for(v = 0; u; u = fa[v = u]) {
            splay(u);
            c[u][1] = v;
        }
        return v;
    }
    
    inline void set_rt(int u) { rev[access(u)] ^= 1; splay(u); }
    inline void link(int u, int v) { set_rt(u); fa[u] = v; }
    inline int query(int u) { splay(u); return val[u]; }
    inline void modify(int u, int v, int w) { set_rt(u); access(v); splay(v); chkmin(tag[v], w); }
}

int fa[N + 5];
int findset(int x) {
    return fa[x] == x ? x : fa[x] = findset(fa[x]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(k), read(m);
    for(int i = 1; i <= n; ++i) fa[i] = i;

    int tot = n;
    for(int i = 1; i <= k; ++i) {
        static int x, y;
        read(x), read(y);
        if(findset(x) != findset(y)) {
            ++ tot;
            fa[findset(x)] = findset(y);
            LCT::link(x, tot); LCT::link(y, tot);
        }
    }
    for(int i = 1; i <= m; ++i) { read(e[i].u), read(e[i].v), read(e[i].w); }

    LCT::clear();
    sort(e + 1, e + m + 1);

    for(int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v;

        if(findset(u) ^ findset(v)) {
            ++ tot;
            LCT::link(u, tot);
            LCT::link(tot, v);
            fa[findset(u)] = findset(v);
        } else {
            LCT::modify(u, v, e[i].w); 
        }
    }

    long long ans = 0;
    for(int i = 1; i <= k; ++i) {
        int tmp = LCT::query(i + n);
        if(tmp == oo) return puts("-1"), 0;
        ans += tmp;
    }
    printf("%lld\n", ans);
    return 0;
}
