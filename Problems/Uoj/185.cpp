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

const int N = 20;

int n, m;
bool g[N + 5][N + 5];
vector<int> G[N + 5];

void input() {
    read(n), read(m);
    for(int i = 0; i < m; ++i) {
        static int x, y;
        read(x), read(y);
        -- x, -- y;
        g[x][y] = g[y][x] = true;
    }
    for(int i = 1; i < n; ++i) {
        static int x, y;
        read(x), read(y);
        -- x, -- y;
        G[x].pb(y); G[y].pb(x);
    }
}

ll dp[N + 5][N + 5];
void dfs(int u, int f, int s) {

    for(int i = 0; i < (int) G[u].size(); ++i) {
        int v = G[u][i];
        if(v == f) continue;

        dfs(v, u, s);
    }

    if(f >= 0) {
        for(int i = 0; i < n; ++i) if(s >> i & 1) {
            ll temp = 0;
            for(int j = 0; j < n; ++j) if(s >> j & 1) temp += dp[u][j] * g[i][j];
            dp[f][i] *= temp;
        }
    }
}

ll calc(int s) {
    ll res = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) dp[i][j] = 1;

    dfs(0, -1, s);

    for(int i = 0; i < n; ++i) if(s >> i & 1) res += dp[0][i];
    return res;
}

ll ans = 0;
void solve() {
    for(int i = 1; i < (1 << n); ++i) {
        int s = __builtin_popcount(i);
        ans = ans + (((n - s) & 1) ? -1ll : 1ll) * calc(i);
    }
    printf("%lld\n", ans);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    input();
    solve();

    return 0;
}
