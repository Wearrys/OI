#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back
#define getchar getchar_unlocked

template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const LL oo = 1LL << 60;
const int maxn = 2e5 + 10;

template<typename T> inline T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48;
	return n * f;
}

LL w[maxn];
int st[maxn], nxt[maxn], to[maxn], ecnt = 1;
inline void addedge(int u, int v, LL wi) {
    to[++ecnt] = v;
    nxt[ecnt] = st[u];
    w[ecnt] = wi;
    st[u] = ecnt;
}

bool mark[maxn];
int fa[maxn];
LL f[maxn], dis[maxn], p[maxn], q[maxn], l[maxn];

inline bool cmp(const int& x, const int& y) { 
    return dis[x] - l[x] > dis[y] - l[y];
}

void dfs0(int u) {
    for(int i = st[u]; i; i = nxt[i]) 
        dis[to[i]] = dis[u] + w[i], dfs0(to[i]);
}

int size[maxn];
void dfs1(int u, int sz, int& c) {
    size[u] = 1;
    bool flag = 1;

    for(int i = st[u], v; i; i = nxt[i]) 
        if(!mark[i]) {
            dfs1(v = to[i], sz, c);
            size[u] += size[v];
            flag &= (size[v] << 1) <= sz;
        }

    flag &= ((sz-size[u]) << 1) <= sz;
    if(flag) c = u;
}

vector<int> A;
void find(int u) {
    A.pb(u);
    for(int i = st[u]; i; i = nxt[i]) 
        if(!mark[i]) find(to[i]);
}

int Q[maxn];
double K[maxn];

#define slope(a, b) (1.0 * (f[a] - f[b]) / (dis[a] - dis[b]))

int top, n;
inline void insert(int pos) {
    while(top > 1 && slope(pos, Q[top-1]) >= K[top-1]) 
        -- top;
    
    Q[top++] = pos;
    K[top-1] = top > 1 ? slope(Q[top-1], Q[top-2]) : 1e18;
}

inline int search(double k) {
    int L = 0, R = top-1;
    while(L < R) {
        int mid = (L + R + 1) >> 1;
        if(K[mid] >= k) L = mid; else R = mid - 1;
    }return Q[L];
}

void solve(int rt, int sz) {
    if(sz <= 1) return;
    int c; dfs1(rt, sz, c);

    for(int i = st[c]; i; i = nxt[i]) 
        mark[i] = true;

    solve(rt, sz - size[c] + 1);

    A.clear();
    for(int i = st[c]; i; i = nxt[i]) find(to[i]);

    top = 0;
    sort(A.begin(), A.end(), cmp);
    for(int i = 0, pos = c; i < int(A.size()); i++) {
        int v = A[i];
        while(pos != fa[rt] && dis[v] - l[v] <= dis[pos])
            insert(pos), pos = fa[pos];

        if(top > 0) {
            int t = search(p[v]);
            chkmin(f[v], f[t] + p[v] * (dis[v] - dis[t]) + q[v]);
        }
    }for(int i = st[c]; i; i = nxt[i]) solve(to[i], size[to[i]]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    n = read<int>(); read<int>();
    for(int i = 2; i <= n; i++) {
        fa[i] = read<int>(); addedge(fa[i], i, read<LL>());
        p[i] = read<LL>(), q[i] = read<LL>(), l[i] = read<LL>();

        f[i] = oo;
    }
    dfs0(1);
    solve(1, n);
    for(int i = 2; i <= n; i++) printf("%lld\n", f[i]);

    return 0;
}
