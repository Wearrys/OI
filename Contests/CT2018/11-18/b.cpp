#pragma GCC optimize ("3")
#include <bits/stdc++.h>
using namespace std;

const int N = 50;

typedef long long ll;

int n;
int x[N + 5], y[N + 5];
int sx[N + 5], sy[N + 5];
ll mp[N + 5][1000 * 1000];

inline int _max(int a, int b) { return a > b ? a : b; }

ll dfs1(int u, int sa, int mx) {
    if(u == n) return mx > sy[n]; 
    auto &t = mp[u][sa * 1000 + mx];
    return t>=0 ? t : t = dfs1(u + 1, sa + x[u], _max(mx, sa + x[u]) + y[u]) + dfs1(u + 1, sa, mx);
}

ll dfs2(int u, int sb, int mx) {
    if(u == n) return mx > sx[n];
    auto &t = mp[u][sb * 1000 + mx];
    return t>=0 ? t : t = dfs2(u + 1, sb, mx) + dfs2(u + 1, sb + y[u], _max(mx, sb + y[u]) + x[u]);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif 

    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", x + i), sx[i] += x[i], sx[i + 1] = sx[i];
    for(int i = 0; i < n; ++i) scanf("%d", y + i), sy[i] += y[i], sy[i + 1] = sy[i];

    ll all = 1ll << n;
    memset(mp, -1, sizeof mp); all -= dfs1(0, 0, 0);
    memset(mp, -1, sizeof mp); all -= dfs2(0, 0, 0);

    printf("%lld\n", all);

    return 0;
}
