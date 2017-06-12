#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back

template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int maxn = 4e5 + 10;
const int oo = 0x3f3f3f3f;

template<typename T> T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

typedef int Arr[maxn];

int n, m, tot;
long long sumd[maxn][2], sum[maxn][2];

Arr fa, dep, son, top, sz;
Arr mid, L, R, lc, rc, node;

int input(int l, int r) {
    int cur = ++ tot;

    L[cur] = l, R[cur] = r;
    if(l < r) {
        mid[cur] = read<int>();      
        fa[lc[cur] = input(l, mid[cur])] = cur;
        fa[rc[cur] = input(mid[cur]+1, r)] = cur;
    }else node[l] = cur;
    return cur;
}

int lca(int x, int y) {
    while(top[x] ^ top[y]) 
        { dep[top[x]] < dep[top[y]] ? y = fa[top[y]] : x = fa[top[x]]; }
    return dep[x] < dep[y] ? x : y;
}
int dis(int x, int y) {
    return dep[x] + dep[y] - 2 * dep[lca(x, y)];
}

LL Calc(int x, int u, bool t) {
    int Rt = lca(x, u);
    LL ans = LL(sum[x][t] - sum[Rt][t]) * (dep[u] - 2*dep[Rt]) + sumd[x][t] - sumd[Rt][t];
    ans += LL(2 + dep[u]) * sum[Rt][t] - sumd[Rt][t];

    if(u == Rt || x == Rt) return ans;
    while(fa[u] != Rt) {
        if(top[u] == top[Rt]) 
            u = son[Rt];
        else u = top[u];

        if(fa[u] != Rt) u = fa[u];
    }
    if((rc[Rt] == u) == t) ans -= 2;
    return ans;
}
LL query(int u, int l, int r) {
    int Rt = lca(node[l], node[r]);
    if(l == L[Rt] && r == R[Rt]) return dis(Rt, u);
    if(l == L[Rt]) return Calc(node[r+1], u, 0) - Calc(Rt, u, 0);
    if(r == R[Rt]) return Calc(node[l-1], u, 1) - Calc(Rt, u, 1);

    return Calc(node[r+1], u, 0) - Calc(rc[Rt], u, 0) 
        +  Calc(node[l-1], u, 1) - Calc(lc[Rt], u, 1);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    n = read<int>(); 
    input(1, n); 
    for(int i = 1; i <= tot; i++) dep[i] = dep[fa[i]] + 1;
    for(int i = tot; i >= 1; i--) 
        sz[fa[i]] += ++sz[i], sz[i] > sz[son[fa[i]]] ? son[fa[i]] = i : 1;
    for(int i = 1; i <= tot; i++) 
        top[i] = i == son[fa[i]] ? top[fa[i]] : i;

    for(int i = 1; i <= tot; i++) {
        sum[i][0] = sum[fa[i]][0] + (i == rc[fa[i]]);
        sum[i][1] = sum[fa[i]][1] + (i == lc[fa[i]]);
        sumd[i][0] = sumd[fa[i]][0] + (i == rc[fa[i]]) * dep[i];
        sumd[i][1] = sumd[fa[i]][1] + (i == lc[fa[i]]) * dep[i];
    }

    m = read<int>();
    while(m--) {
        int u, x, y;
        u = read<int>();
        x = read<int>();
        y = read<int>();
        printf("%lld\n", query(u, x, y));
    }
    
    return 0;
}
