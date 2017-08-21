#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back

template <typename T> inline bool chkmax(T& a, T b) { return a <= b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int maxn = 1e5 + 10;
const int maxm = 3e6 + 10;
const int oo = 0x7fffffff;

template<typename T> inline T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int S, T;
int n, ans;

namespace Dinic {
    int e = 1;
    int dis[maxn], cur[maxn];
    int st[maxn], to[maxm], nxt[maxm], cap[maxm];

    void addedge(int u, int v, int c) {
        to[++e] = v; nxt[e] = st[u]; st[u] = e; cap[e] = c;
        to[++e] = u; nxt[e] = st[v]; st[v] = e; cap[e] = 0;
    }

    bool bfs() {
        static int q[maxn];
        int head = 0, tail = 0;

        memset(dis, -1, sizeof dis);

        dis[q[tail++] = S] = 0;
        while(head < tail) {
            int x = q[head++];
            for(int i = st[x]; i; i = nxt[i]) 
                if(cap[i] && !~dis[to[i]]) 
                    dis[q[tail++] = to[i]] = dis[x] + 1;
        }
        return ~dis[T];
    }

    int dfs(int u, int flow) {
        if(u == T || !flow) 
            return flow;

        int res = 0;
        for(int& i = cur[u]; i; i = nxt[i]) {
            int v = to[i], aug;
            if(dis[v] == dis[u] + 1 && (aug = dfs(v, min(flow, cap[i])))) {
                res += aug;
                flow -= aug;
                cap[i] -= aug;
                cap[i^1] += aug;
                if(!flow) break;
            }
        }
        return res;
    }

    int maxflow() {
        int ans = 0;
        while(bfs()) {
            memcpy(cur, st, sizeof st);
            ans += dfs(S, oo);
        }
        return ans;
    }
    void test() {
        bfs();        
        for(int i = 1; i <= n; i++) {
            printf("%d\n", !~dis[i]);
        }
    }
}

int d[maxn];
struct grid {
    int a, w, b, l, r, p;
    void read() {
        scanf("%d%d%d%d%d%d", &a, &b, &w, &l, &r, &p);
        d[++d[0]] = a; d[++d[0]] = l; d[++d[0]] = r;
    }
}g[maxn];

#define lc (u << 1)
#define rc (lc | 1)
#define mid ((l+r) >> 1)

int idx[maxn], tot;
void modify(int u, int l, int r, int x, int v) {

    ++ tot;
    if(idx[u]) 
        Dinic::addedge(tot, idx[u], oo);
    Dinic::addedge(idx[u] = tot, v, oo);

    if(l < r) {
        if(x <= mid)
            modify(lc, l, mid, x, v);
        else
            modify(rc, mid+1, r, x, v);
    }
}

void query(int u, int l, int r, int x, int y, int v) {
    if(!idx[u] || l > r) return;
    if(x <= l && r <= y) return Dinic::addedge(v, idx[u], oo);

    if(x <= mid)
        query(lc, l, mid, x, y, v);
    if(y > mid)
        query(rc, mid+1, r, x, y, v);
}
#undef lc
#undef rc
#undef mid

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif
    scanf("%d", &n);
    S = (n<<1) + 1; 
    tot = T = (n<<1) + 2;
    for(int i = 1; i <= n; i++) g[i].read();

    sort(d+1, d+d[0]+1);
    d[0] = unique(d+1, d+d[0]+1) - d - 1;

    for(int i = 1; i <= n; i++) {
        g[i].a = lower_bound(d+1, d+d[0]+1, g[i].a) - d;
        g[i].l = lower_bound(d+1, d+d[0]+1, g[i].l) - d;
        g[i].r = lower_bound(d+1, d+d[0]+1, g[i].r) - d;

        query(1, 1, d[0], g[i].l, g[i].r, i+n);
        modify(1, 1, d[0], g[i].a, i);

        Dinic::addedge(i, i+n, g[i].p);
        Dinic::addedge(S, i, g[i].b);
        Dinic::addedge(i, T, g[i].w);

        ans += g[i].b + g[i].w;
    }

    printf("%d\n", ans - Dinic::maxflow());
    //Dinic::test();
    return 0;
}
